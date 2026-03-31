

//Ardunio TheraPatch Firmware :p :p



#include <Adafruit_GFX.h>     
#include <Adafruit_ST7735.h>    
#include <SPI.h>               


Adafruit_ST7735 tft(10, A3, 12);  

// Arduino pin map
#define BTN_TEMP  2     
#define BTN_TIME  4     
#define BTN_MODE  A5    
#define BTN_START 9     
#define PIN_INA   6     
#define PIN_INB   7     
#define PIN_PWM   5     
#define PIN_FAN   3     
#define PIN_THERM A0   
#define PIN_BUZZ  8     

// constraints/saftey setting
#define TEMP_MIN    35      // min temp
#define TEMP_MAX    120     // max temp
#define OVERHEAT_F  125     // shutoff if it reaches this max
#define DEFAULT_T   60      // defualt temp
#define DEFAULT_S   300     // default time
#define COLD_F      59      // cool mode auto set
#define HOT_F       105     // hot mode auto set
#define PWM_POWER   200      
#define HOLD_MS     2000    
#define BUZZ_MS     5000    

// LCD COLOR
#define C_HOT   0xFB20   // orange-red
#define C_COLD  0x5DFF   // light blue
#define C_GREEN 0x07E0
#define C_GREY  0x8410

// GLOBAL STATE
int setTemp = DEFAULT_T, setTime = DEFAULT_S;
bool isCold = false, running = false;
bool tempNeg = false, timeNeg = false;       
bool buzzing = false, forceRedraw = true;
unsigned long lastTick = 0, buzzStart = 0;
// display cache (avoids redrawing unchanged values)
int pT = -1, pS = -1; bool pC = false, pR = false; float pH = -999;

//BUTTON BIG
struct Btn {
  uint8_t pin;
  bool last;
  bool held;
  unsigned long downAt;
  unsigned long dbAt;
};

Btn btnT = {2,   1, 0, 0, 0};  // temp button: D2
Btn btnS = {4,   1, 0, 0, 0};  // time button:D4
Btn btnM = {A5,  1, 0, 0, 0};  // mode button: A5
Btn btnX = {9,   1, 0, 0, 0};  // str/stp: D9

uint8_t readBtn(Btn &b) {

  bool raw = digitalRead(b.pin);

  uint8_t ev = 0;

  // noise filter
  bool changed = (raw != b.last);
  bool stable  = (millis() - b.dbAt > 50);

  if (changed && stable) {
    b.dbAt = millis();
    b.last = raw;

    if (raw == LOW) {
      b.held = false;           // new press
      b.downAt = millis();      
    }
    else {
      if (!b.held) ev = 1;      // short press
    }
  }

  bool down    = (b.last == LOW);
  bool fresh   = (!b.held);
  bool twoSec  = (millis() - b.downAt >= HOLD_MS);

  if (down && fresh && twoSec) {
    b.held = true;              
    ev = 2;                     // hold for 2+ Sec, flips temp from + to - or vise versa
  }

  // 0 = nothing
  // 1 = short press
  // 2 = hold
  return ev;
}

//THERMISTOR TO READ TEMP

float readThermF() {
  int raw = max(analogRead(PIN_THERM), 1);
  float resistance = 10000.0 / (1023.0 / raw - 1.0);
  float kelvin = log(resistance / 10000.0) / 3950.0 + 1.0 / 298.15;

  float celsius    = (1.0 / kelvin) - 273.15;
  float fahrenheit = celsius * 9.0 / 5.0 + 32.0; //convesrion cuz i dont like celsius 

  return fahrenheit;
}

// PELTIER + FAN CONTROL

void peltierOff() {
  digitalWrite(PIN_INA, LOW);
  digitalWrite(PIN_INB, LOW);
  analogWrite(PIN_PWM, 0);
  digitalWrite(PIN_FAN, LOW);
}

// peltier on
void peltierOn() {
  // Cold: INA on but INB off 
  // Hot:  INA off but INB on
  if (isCold) {
    digitalWrite(PIN_INA, HIGH);
    digitalWrite(PIN_INB, LOW);
  } else {
    digitalWrite(PIN_INA, LOW);
    digitalWrite(PIN_INB, HIGH);
  }

  analogWrite(PIN_PWM, PWM_POWER);  
  digitalWrite(PIN_FAN, HIGH);       
}

// REST TO FACTORY SETTINGS
void resetAll() {
  running = false;
  setTemp = DEFAULT_T;       
  setTime = DEFAULT_S;       
  isCold = false;          
  tempNeg = false;       
  timeNeg = false;           
  peltierOff();              
  forceRedraw = true;        
}
//Runs in 3 senarios 1: stop is pressed 2: Overheating 3:timer runs out


// LCD DRAWING CODE

void drawStatic() {
  tft.fillScreen(ST77XX_BLACK);

  // two grey divider lines
  tft.drawFastHLine(0, 36, tft.width(), C_GREY);
  tft.drawFastHLine(0, tft.height() - 30, tft.width(), C_GREY);

  // grey labels
  tft.setTextSize(1);
  tft.setTextColor(C_GREY);
  tft.setCursor(2, 2);
  tft.print("SET TEMP");
  tft.setCursor(tft.width() - 36, 2);
  tft.print("TIME");
  tft.setCursor(2, tft.height() - 12);
  tft.print("SENSOR:");
}

// lcd temp in top left
void drawTemp() {
  // erase old number
  tft.fillRect(0, 12, 75, 22, ST77XX_BLACK);

  // draw new number in white
  tft.setTextSize(2);
  tft.setTextColor(ST77XX_WHITE);
  tft.setCursor(2, 14);
  tft.print(setTemp);
  tft.setTextSize(1);
  tft.print("F");

  // draw +/- indicator green:+ red:-
  tft.fillRect(62, 2, 10, 10, ST77XX_BLACK);
  tft.setCursor(62, 2);
  if (tempNeg) {
    tft.setTextColor(C_HOT);
    tft.print("-");
  } else {
    tft.setTextColor(C_GREEN);
    tft.print("+");
  }
}

// lcd timer
void drawTime() {
  char buf[6];
  sprintf(buf, "%02d:%02d", setTime / 60, setTime % 60);
  // erase old time
  int x = tft.width() - 62;
  tft.fillRect(x, 12, 62, 22, ST77XX_BLACK);
  // draw new time in white
  tft.setTextSize(2);
  tft.setTextColor(ST77XX_WHITE);
  tft.setCursor(x, 14);
  tft.print(buf);
  // draw +/- indicator
  tft.fillRect(tft.width() - 46, 2, 10, 10, ST77XX_BLACK);
  tft.setTextSize(1);
  tft.setCursor(tft.width() - 46, 2);
  if (timeNeg) {
    tft.setTextColor(C_HOT);
    tft.print("-");
  } else {
    tft.setTextColor(C_GREEN);
    tft.print("+");
  }
}

// lcd mode (hot/cold)
void drawMode() {
  tft.fillRect(0, 42, tft.width(), 50, ST77XX_BLACK);

  // in the center draw hot or cold
  if (isCold) {
    tft.setTextSize(3);
    tft.setTextColor(C_COLD);
    tft.setCursor(tft.width() / 2 - 36, 48);
    tft.print("COLD");
  } else {
    tft.setTextSize(3);
    tft.setTextColor(C_HOT);
    tft.setCursor(tft.width() / 2 - 27, 48);
    tft.print("HOT");
  }

  // draw running or standby 
  if (running) {
    tft.setTextSize(1);
    tft.setTextColor(C_GREEN);
    tft.setCursor(tft.width() / 2 - 27, 78);
    tft.print("> RUNNING");
  } else {
    tft.setTextSize(1);
    tft.setTextColor(C_GREY);
    tft.setCursor(tft.width() / 2 - 27, 78);
    tft.print("  STANDBY");
  }
}

// lcd thermistor reading
void drawTherm(float f) {

  tft.fillRect(46, tft.height() - 14, 80, 12, ST77XX_BLACK);
  tft.setTextSize(1);
  tft.setTextColor(ST77XX_WHITE);
  tft.setCursor(46, tft.height() - 12);
  tft.print(f, 1);
  tft.print("F");
}

// lcd refresh loop
void refresh(float tf) {
  // redraw after reset
  if (forceRedraw) {
    drawStatic();
    drawTemp();
    drawTime();
    drawMode();
    drawTherm(tf);
    forceRedraw = false;
    pT = setTemp;
    pS = setTime;
    pC = isCold;
    pR = running;
    pH = tf;
    return;
  }

  // redraw what changed 
  if (setTemp != pT) { drawTemp(); pT = setTemp; }
  if (setTime != pS) { drawTime(); pS = setTime; }
  if (isCold != pC || running != pR) { drawMode(); pC = isCold; pR = running; }
  if (abs(tf - pH) > 0.3) { drawTherm(tf); pH = tf; }
}

// STARTUP WHEN ARDUINO POWER ON
void setup() {

  // button power
  pinMode(BTN_TEMP, INPUT_PULLUP);   
  pinMode(BTN_TIME, INPUT_PULLUP);  
  pinMode(BTN_MODE, INPUT_PULLUP);   
  pinMode(BTN_START, INPUT_PULLUP);  

  // peliter power
  pinMode(PIN_INA, OUTPUT);    
  pinMode(PIN_INB, OUTPUT);    
  pinMode(PIN_PWM, OUTPUT);  
  pinMode(PIN_FAN, OUTPUT);   
  pinMode(PIN_BUZZ, OUTPUT);  

 
  peltierOff();
  digitalWrite(PIN_BUZZ, LOW);

  // lcd wake up
  tft.initR(INITR_144GREENTAB);   
  tft.setRotation(1);              
  forceRedraw = true;
}

// MAIN LOOP THAT IS THE BEATING HEART OF THIS CODE
void loop() {

  //button check
  uint8_t eT = readBtn(btnT);   
  uint8_t eS = readBtn(btnS);
  uint8_t eM = readBtn(btnM);
  uint8_t eX = readBtn(btnX);

  // temp button long press
  if (eT == 2) {
    tempNeg = !tempNeg;
  }
  // temp button short press
  if (eT == 1) {
    if (tempNeg) {
      setTemp = setTemp - 1;    
    } else {
      setTemp = setTemp + 1;    
    }
    // keep temp within safe limits
    setTemp = constrain(setTemp, TEMP_MIN, TEMP_MAX);
  }

  // time button long press
  if (eS == 2) {
    timeNeg = !timeNeg;
  }
  // time button short press
  if (eS == 1) {
    if (timeNeg) {
      setTime = setTime - 5;
    } else {
      setTime = setTime + 5;
    }
    // don't let time go below 0
    if (setTime < 0) {
      setTime = 0;
    }
  }

 
  // mode button to switch between hot and cold
  if (eM == 1 && !running) {
    isCold = !isCold;          

    if (isCold) {
      setTemp = COLD_F;        
    } else {
      setTemp = HOT_F;         
    }
    tempNeg = false;           
  }

  // start stop
  if (eX == 1) {
    if (!running && setTime > 0) {
      // start
      running = true;
      lastTick = millis();     
      peltierOn();             
    }
    else if (running) {
      // stop which restets
      resetAll();
    }
  }

  // countdown
  if (running && millis() - lastTick >= 1000) {
    lastTick = lastTick + 1000;
    setTime = setTime - 1;

    if (setTime <= 0) {
      setTime = 0;
      running = false;
      peltierOff();          

      // start buzzer
      buzzing = true;
      buzzStart = millis();
      digitalWrite(PIN_BUZZ, HIGH);

      // reset all settings to defaults
      setTemp = DEFAULT_T;
      setTime = DEFAULT_S;
      isCold = false;
      tempNeg = false;
      timeNeg = false;
      forceRedraw = true;       
    }
  }
  // stop buzzer after 5 seconds
  if (buzzing && millis() - buzzStart >= BUZZ_MS) {
    digitalWrite(PIN_BUZZ, LOW);
    buzzing = false;
  }

  // themistor reader
  float tf = readThermF();

  //safety first
  if (running && tf > OVERHEAT_F) {
    peltierOff();
    running = false;

    // start buzzer
    buzzing = true;
    buzzStart = millis();
    digitalWrite(PIN_BUZZ, HIGH);

    // flash warning on screen
    tft.fillScreen(C_HOT);
    tft.setTextSize(2);
    tft.setTextColor(ST77XX_WHITE);
    tft.setCursor(10, 50);
    tft.print("OVERHEAT!");
    delay(3000);

    resetAll();
  }

  // screen update
  refresh(tf);
  delay(10);
}