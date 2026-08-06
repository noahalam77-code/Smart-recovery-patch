# TheraPatch

## Repository file structure
- BOM: JCLPCB BOM & regular BOM
- CADfiles: STEP files, STL files, and assembly notes
- PCB: PCB files, Gerber files, schematic images, and PCB images
- Firmware: Code & flashing instructions


## What it is
TheraPatch is a handheld therapeutic device designed to help mitigate the effects of injuries such as bruises, sprains, minor cuts, and more. By using a reverse-polarity system via an H-bridge, TheraPatch can heat the affected area (dilating blood vessels) or cool it (constricting blood vessels), both of which have been shown to help with injury healing at certain temperatures (which TheraPatch can achieve). 

## Motivation
I created TheraPatch with the primary motivation of helping people with common sports/activty related injuries while maintaining an efficient device to do so. Most of the time, when you have a bruise or scrape, you'd rely on disposable ice packs or inefficient heating pads, which are wasteful and time-consuming for long-term use. TheraPatch offers an effective, infinitely reusable solution to this. Instead of freezing water for 3-4 hours or boiling a heatpack everytime you need to reuse it, all you do with TheraPatch is plug and play. It's effective for athletes and normal people.

## Use of TheraPatch
To use the TheraPatch, first ensure your battery/wall adapter is plugged in. Then locate the 4 buttons on the top of the device; these buttons will allow you to set your desired parameters by moving through the menus: mode (hot/cold), set temp, and set time. After your desired settings are set, click the start button to initiate your therapy session, and place the side with the Peltier facing out against the affected area

## How it works
The TheraPatch looks like a simple black-and-white hot-cold block, but its guts are far more advanced. In electronics, generating heat is relatively simple. Electrons bump into each other rapidly in the wire, vibrating and thus creating the heat we feel. This is the easy part; cooling is the real engineering challenge. To cool it, I used a Peltier module, which transfers heat from one side to the other. Now, this needs to be driven by a heatsink and a fan to effectively cool. To achieve heating and cooling on the same side, I used an H bridge. The H-bridge module reverses the polarity in a Peltier module, meaning that when one side is positive and the other is negative, it cools; vice versa. All of this is controlled by a custom 4-layer PCB I designed in KiCad, with an ATmega328P as my microcontroller. The firmware reads a thermistor pressed against the Peltier plate and uses a bang-bang controller to turn the Peltier on/off to reach the desired temperature. This is all run by a rechargeable 12V battery, which charges via USB-C or a 12V wall adapter. These components are combined in a logical order in a CAD-designed box with a hole for all the input plugs and vent fans for air circulation.

Here are images of my project






## CAD with the PCB:

<img width="491" height="524" alt="Screenshot 2026-07-04 at 1 53 12 PM" src="https://github.com/user-attachments/assets/c9aa02cf-47bf-4d0b-9159-3f62e53c6c75" />

<img width="860" height="535" alt="Screenshot 2026-07-04 at 1 53 32 PM" src="https://github.com/user-attachments/assets/61e79f9d-1325-4d9e-8768-30e69478cb92" />


## CAD input ports, fins, and Peliter hole

<img width="576" height="519" alt="Screenshot 2026-07-04 at 1 54 11 PM" src="https://github.com/user-attachments/assets/8a456222-b25e-43ab-94a3-2ddde18c2c22" />

<img width="739" height="498" alt="Screenshot 2026-07-04 at 1 55 22 PM" src="https://github.com/user-attachments/assets/37d6ade7-3b82-45b5-abc2-69d01d795669" />

<img width="366" height="356" alt="Screenshot 2026-07-04 at 1 55 41 PM" src="https://github.com/user-attachments/assets/d9225b02-e006-4cde-81e3-795e07dad236" />

## Link to Onshape case:

https://cad.onshape.com/documents/d627d659f05dae60588ec801/w/ad74ef98cd2d7a13cb59f9ec/e/f50ed022a94792dc2cfe6130?renderMode=0&uiState=6a4947abb17d022f5d41873a



# PCB (Signal Layer and ground):

## F.cu (signal traces and ground):

<img width="654" height="654" alt="Screenshot 2026-06-03 at 1 51 27 AM" src="https://github.com/user-attachments/assets/fbb4aada-035c-4d4d-a86d-8448950266f5" />


## In1.cu(ground):

<img width="746" height="748" alt="Screenshot 2026-06-03 at 1 52 55 AM" src="https://github.com/user-attachments/assets/b6a859eb-523d-4d4b-ae47-f9068150ecfb" />

## In2.cu (5V & 12V power)

<img width="784" height="783" alt="Screenshot 2026-06-03 at 1 53 45 AM" src="https://github.com/user-attachments/assets/139ca568-bd86-47c3-9217-3a166924e9ce" />

## B.cu (signal traces and ground):

<img width="783" height="778" alt="Screenshot 2026-06-03 at 1 54 23 AM" src="https://github.com/user-attachments/assets/faacdbda-8a3d-41f6-8973-919288aac1d3" />

## 3D:

<img width="879" height="861" alt="Screenshot 2026-06-03 at 1 55 00 AM" src="https://github.com/user-attachments/assets/a0fd8c00-925b-4637-ac82-2886d6d96704" />

# Schematic (wiring diagram):

## Pic_1:

<img width="975" height="641" alt="Screenshot 2026-06-03 at 1 55 57 AM" src="https://github.com/user-attachments/assets/ce9e7d3d-e9ee-4357-b866-ed55678c2371" />

## Pwr:

<img width="1009" height="650" alt="Screenshot 2026-06-03 at 1 56 46 AM" src="https://github.com/user-attachments/assets/f2777dec-bb50-4640-930f-3b2bf1c6f293" />




## BOM(main)

| Item | Quantity | Unit price | Total price | Descrption | Link |
|------|----------|-----------|-------------|------------|------|
| Fan | 1 | 4.81 | 4.81 | Facliate heaitng & cooling | [Link](https://www.aliexpress.us/item/3256808462428286.html?spm=a2g0o.productlist.main.1.6babkeHNkeHNko&algo_pvid=c39052da-f6dd-4b67-816a-d90e786c586d&algo_exp_id=c39052da-f6dd-4b67-816a-d90e786c586d-0&pdp_ext_f=%7B%22order%22%3A%2262%22%2C%22eval%22%3A%221%22%2C%22fromPage%22%3A%22search%22%7D&pdp_npi=6%40dis%21USD%2111.50%214.79%21%21%2178.10%2132.53%21%402101d6ff17774285328603962e8757%2112000046088904920%21sea%21US%210%21ABX%211%210%21n_tag%3A-29910%3Bd%3Ad6b644bf%3Bm03_new_user%3A-29895%3BpisId%3A5000000204886261&curPageLogUid=VweLjIS1lGkI&utparam-url=scene%3Asearch%7Cquery_from%3A%7Cx_object_id%3A1005008648743038%7C_p_origin_prod%3A) |
| Peltier | 1 | 3.90$ | $3.90 | Cool and heat | [Link](https://www.aliexpress.us/item/3256806863842277.html?src=google&gatewayAdapt=glo2usa) |
| Heatsink | 2 | 4.80$ | $9.79 | Disspate heat | [Link](https://www.amazon.com/Awxlumv-Aluminum-60mmx60mmx15mm-Conductive-Amplifier/dp/B0DNLXD4NL) |
| LCD screen | 1 | 0.9900$ | 0.9900$ | Displaying modes | [Link](https://www.aliexpress.us/item/3256807264700302.html?spm=a2g0o.productlist.main.15.3bb1HGrhHGrhWv&algo_pvid=f071bd73-714c-4717-acaa-3f74ef8deb17&algo_exp_id=f071bd73-714c-4717-acaa-3f74ef8deb17-14&pdp_ext_f=%7B%22order%22%3A%223710%22%2C%22eval%22%3A%221%22%2C%22fromPage%22%3A%22search%22%7D&pdp_npi=6%40dis%21USD%213.14%210.99%21%21%213.14%210.99%21%4021030a6217776832914577048eb84d%2112000040806152744%21sea%21US%210%21ABX%211%210%21n_tag%3A-29910%3Bd%3Ad6b644bf%3Bm03_new_user%3A-29895%3BpisId%3A5000000203537378&curPageLogUid=GNgXD2HWAIP5&utparam-url=scene%3Asearch%7Cquery_from%3A%7Cx_object_id%3A1005007451015054%7C_p_origin_prod%3A#nav-specification) |
| Thermistor | 1 | 0.9500$ | 0.9500$ | Temp meauring | [Link](https://www.adafruit.com/product/4890?srsltid=AfmBOopGi_4mLQSeRw3V9sBgnchAdNrL2zdLeJHItTaAc1rCL6Ne9o2P) |
| Battery | 1 | 26.99$ | $26.99 | Used as main source of power (for moblity) BMS confirmed | [Link](https://liionwholesale.com/products/3s1p-3-7v-3500mah-18650-battery-with-wires-and-connector-lg-mj1-cell-inside?srsltid=AfmBOopbHVjk3o8ywzVI_wQWHKZhMZp1uCq0ynXZWNxGTDKPMvd9ZKI6&variant=31229057794117) |
| Wire | 1 | 2.2300$ | 2.23$ | Battery caddy, peliter and fan extesion | [Link](https://www.aliexpress.us/item/3256802140205012.html?spm=a2g0o.productlist.main.8.4437dfNPdfNPLw&aem_p4p_detail=202606281750527933413825797320002756170&algo_pvid=c53e4217-68c6-4b26-9b29-3624128716f9&algo_exp_id=c53e4217-68c6-4b26-9b29-3624128716f9-7&pdp_ext_f=%7B%22order%22%3A%22123%22%2C%22eval%22%3A%221%22%2C%22fromPage%22%3A%22search%22%7D&pdp_npi=6%40dis%21USD%214.70%212.79%21%21%214.70%212.79%21%402103212b17826942522901169e02c1%2112000052586672765%21sea%21US%210%21ABX%211%210%21n_tag%3A-29910%3Bd%3Ad6b644bf%3Bm03_new_user%3A-29895%3BpisId%3A5000000208023469&curPageLogUid=CY0b8Pvel5HR&utparam-url=scene%3Asearch%7Cquery_from%3A%7Cx_object_id%3A1005002326519764%7C_p_origin_prod%3A&search_p4p_id=202606281750527933413825797320002756170_2) |
| Wall adapter | 1 | $1.28 | $1.28 | 2nd way of recving power (1st battery) | [Link](https://www.aliexpress.us/item/3256806555593510.html?spm=a2g0o.productlist.main.5.103eNCpVNCpVMj&algo_pvid=3d352d1e-bc43-4e77-9d29-16e4344ed46b&algo_exp_id=3d352d1e-bc43-4e77-9d29-16e4344ed46b-4&pdp_ext_f=%7B%22order%22%3A%221992%22%2C%22eval%22%3A%221%22%2C%22fromPage%22%3A%22search%22%7D&pdp_npi=6%40dis%21USD%2111.78%211.28%21%21%2179.73%218.69%21%402101eecd17826947715547891e5012%2112000038157481542%21sea%21US%210%21ABX%211%210%21n_tag%3A-29910%3Bd%3Ad6b644bf%3Bm03_new_user%3A-29895%3BpisId%3A5000000209510139&curPageLogUid=H50idJ0yOZub&utparam-url=scene%3Asearch%7Cquery_from%3A%7Cx_object_id%3A1005006741908262%7C_p_origin_prod%3A) |
| M2 screw 8mm | 100 | 0.0100$ | $1.35 | screws for battery caddy | [Link](https://www.aliexpress.us/item/2251832857570651.html?spm=a2g0o.productlist.main.3.4e3cdUVEdUVEfl&algo_pvid=ea8d64ad-4af7-4109-af97-4e674e97f9e5&algo_exp_id=ea8d64ad-4af7-4109-af97-4e674e97f9e5-2&pdp_ext_f=%7B%22order%22%3A%2216288%22%2C%22eval%22%3A%221%22%2C%22fromPage%22%3A%22search%22%7D&pdp_npi=6%40dis%21USD%211.35%210.99%21%21%211.35%210.99%21%402103129f17825915196483426e5a8e%2112000020018123413%21sea%21US%210%21ABX%211%210%21n_tag%3A-29910%3Bd%3Ad6b644bf%3Bm03_new_user%3A-29895%3BpisId%3A5000000208023469&curPageLogUid=WMcjfyJWRpdQ&utparam-url=scene%3Asearch%7Cquery_from%3A%7Cx_object_id%3A33043885403%7C_p_origin_prod%3A) |
| M2 screw 14mm | 100 | 0.0100$ | $1.35 | screws for main case | [Link](https://www.aliexpress.us/item/2251832857570651.html?spm=a2g0o.productlist.main.3.4e3cdUVEdUVEfl&algo_pvid=ea8d64ad-4af7-4109-af97-4e674e97f9e5&algo_exp_id=ea8d64ad-4af7-4109-af97-4e674e97f9e5-2&pdp_ext_f=%7B%22order%22%3A%2216288%22%2C%22eval%22%3A%221%22%2C%22fromPage%22%3A%22search%22%7D&pdp_npi=6%40dis%21USD%211.35%210.99%21%21%211.35%210.99%21%402103129f17825915196483426e5a8e%2112000020018123413%21sea%21US%210%21ABX%211%210%21n_tag%3A-29910%3Bd%3Ad6b644bf%3Bm03_new_user%3A-29895%3BpisId%3A5000000208023469&curPageLogUid=WMcjfyJWRpdQ&utparam-url=scene%3Asearch%7Cquery_from%3A%7Cx_object_id%3A33043885403%7C_p_origin_prod%3A) |
| Dupont connectors | 40 | 0.0253$ | 1.01$ | connectors for LCD and ISP proggarmer | [Link](https://www.aliexpress.us/item/3256809185840584.html?spm=a2g0o.productlist.main.4.7725T11aT11aC1&aem_p4p_detail=202606272107031134387990076280002008158&algo_pvid=84f900fb-1f7e-4029-80e1-2e2e9eab2415&algo_exp_id=84f900fb-1f7e-4029-80e1-2e2e9eab2415-3&pdp_ext_f=%7B%22order%22%3A%22686%22%2C%22eval%22%3A%221%22%2C%22fromPage%22%3A%22search%22%7D&pdp_npi=6%40dis%21USD%211.56%211.01%21%21%2110.57%216.87%21%402101e80317826196231237198ed5a5%2112000048899602396%21sea%21US%210%21ABX%211%210%21n_tag%3A-29910%3Bd%3Ad6b644bf%3Bm03_new_user%3A-29895%3BpisId%3A5000000208023469&curPageLogUid=48BAjk6LrSZa&utparam-url=scene%3Asearch%7Cquery_from%3A%7Cx_object_id%3A1005009372155336%7C_p_origin_prod%3A&search_p4p_id=202606272107031134387990076280002008158_2) |
| ISP porgrammer | 1 | 1.9100$ | $1.91 | Flashes code onto the ATMega chip | [Link](https://www.aliexpress.us/item/3256810618247711.html?spm=a2g0o.productlist.main.2.71a9WonxWonxOW&algo_pvid=013dc172-5dcd-4517-a7dc-e44b31c61f77&algo_exp_id=013dc172-5dcd-4517-a7dc-e44b31c61f77-1&pdp_ext_f=%7B%22order%22%3A%2220%22%2C%22eval%22%3A%221%22%2C%22fromPage%22%3A%22search%22%7D&pdp_npi=6%40dis%21USD%212.41%211.91%21%21%212.41%211.91%21%402101d6ff17826055513113304ea732%2112000053555380165%21sea%21US%210%21ABX%211%210%21n_tag%3A-29910%3Bd%3Ad6b644bf%3Bm03_new_user%3A-29895%3BpisId%3A5000000208023469&curPageLogUid=atD9pSQGrkCO&utparam-url=scene%3Asearch%7Cquery_from%3A%7Cx_object_id%3A1005010804562463%7C_p_origin_prod%3A) |
| Buttons | 20 | 0.1095$ | 2.19$ | Switching between menus & 0start/stop | [Link](https://www.aliexpress.us/item/3256801638385730.html?spm=a2g0o.productlist.main.18.6eae9KoY9KoY39&algo_pvid=a04722e0-ab76-4104-b323-04a47393d95b&algo_exp_id=a04722e0-ab76-4104-b323-04a47393d95b-17&pdp_ext_f=%7B%22order%22%3A%2239%22%2C%22eval%22%3A%221%22%2C%22fromPage%22%3A%22search%22%7D&pdp_npi=6%40dis%21USD%213.15%212.59%21%21%213.15%212.59%21%402101eee917825893617621165ec559%2112000017947649837%21sea%21US%210%21ABX%211%210%21n_tag%3A-29910%3Bd%3Ad6b644bf%3Bm03_new_user%3A-29895%3BpisId%3A5000000208023469&curPageLogUid=ypVEuRkxBtEG&utparam-url=scene%3Asearch%7Cquery_from%3A%7Cx_object_id%3A1005001824700482%7C_p_origin_prod%3A) |
| Terminal Block | 5 | 0.0864$ | 0.4300$ | For conencting things without JST conenctor | [Link](https://www.lcsc.com/product-detail/C394556.html?s_z=n_JILN%2520JL126-50002G01) |
| Barrel Jack | 5 | 0.1462$ | $0.73 | Wall power input | [Link](https://www.lcsc.com/product-detail/C720558.html?s_z=n_q_barrel%2520jack%25205A&spm=wm.fly.bg.0.xh&lcsc_vid=QFJaAQFeTlFdU1xXTwILAlBQQQILVwYAQQALAlYEFFYxVlNRTlVfU1NRRlVfXzsOAxUeFF5JWBYZEEoKFBINSQcJGk4NBhADEA4cHktRRVBADxALGw%3D%3D) |
| JST female | 20 | 0.0403$ | 0.81$ | Battery inpt | [Link](https://www.lcsc.com/product-detail/C158012.html?s_z=n_q_C158012&globalKeyword=C158012) |
| 4 Pin connector for LCD | 10 | 0.0807$ | 0.81$ | LCD input | [Link](https://www.lcsc.com/product-detail/C50950.html?s_z=n_q_C50950&globalKeyword=C50950) |
| Arundio flash input | 5 | 0.2238$ | 1.12$ | Pins to flash code | [Link](https://www.lcsc.com/product-detail/C50980.html?s_z=n_q_C50980&globalKeyword=C50980) |
| USB-C | 5 | $0.1857 | $0.93 | Charging | [Link](https://www.lcsc.com/product-detail/C165948.html?s_z=n_q_C165948&globalKeyword=C165948) |
| 5A fuse | 10 | 0.0506$ | $0.51 | PCB | [Link](https://www.lcsc.com/product-detail/C41367229.html?s_z=n_q_t_5A%2520smd%2520fuse&spm=wm.fly.bg.0.xh___wm.ssy.tc.1.tz&lcsc_vid=QFJaAQFeTlFdU1xXTwILAlBQQQILVwYAQQALAlYEFFYxVlNRX1JWRFhbVTsOAxUeFF5JWBYZEEoKFBINSQcJGk4eFQsCAgIaSgADAwAHC0slQ1hcUV1ST1ZADxALGw%3D%3D) |
| 16 Mhz cyrstal | 5 | 0.2372$ | $1.19 | PCB | [Link](https://www.lcsc.com/product-detail/C122519.html?s_z=n_q_C122519&globalKeyword=C122519) |
| Ferrite Bead | 10 | 0.0262$ | $0.26 | PCB | [Link](https://www.lcsc.com/product-detail/C21519.html?s_z=n_q_600%2520ohm%2520ferrite%2520bead%25200805&spm=wm.fly.bg.0.xh&lcsc_vid=QFJaAQFeTlFdU1xXTwILAlBQQQILVwYAQQALAlYEFFYxVlNRTlNeUFZWRFZaXjsOAxUeFF5JWBYZEEoKFBINSQcJGk4eFQsCAgIaSgADAwAHC0slQFFbUVZIHxUDCw%3D%3D) |
| AO3400A | 5 | 0.0846$ | $0.42 | diode for the fan | [Link](https://www.lcsc.com/product-detail/C20917.html?s_z=n_q_C20917&globalKeyword=C20917) |
| SS54 Diode | 10 | 0.0366$ | 0.3700$ | Diode used in buck and input pwr | [Link](https://www.lcsc.com/product-detail/C22452.html?s_z=n_q_SS54%2520diode&spm=wm.fly.bg.0.xh&lcsc_vid=QFJaAQFeTlFdU1xXTwILAlBQQQILVwYAQQALAlYEFFYxVlNRTlNaVVRURldfUzsOAxUeFF5JWBYZEEoKFBINSQcJGk4eFQsCAgIaSgADAwAHC0slT1dZUUoOAwwC) |
| 33uH buck Inductor | 5 | 0.2204$ | 1.10$ | PCB | [Link](https://www.lcsc.com/product-detail/C9400.html?s_z=n_q_t_33uH%2520SMD%2520ind&spm=wm.fly.bg.0.xh___wm.ssy.tc.0.tz&lcsc_vid=QFJaAQFeTlFdU1xXTwILAlBQQQILVwYAQQALAlYEFFYxVlNRT1leX1JUQFNXUTsOAxUeFF5JWBYZEEoKFBINSQcJGk4dAgUUFAk%3D) |
| 2.2uH boost Inductor | 5 | 0.1161$ | $0.58 | PCB | [Link](https://www.lcsc.com/product-detail/C7461347.html?s_z=n_q_CXP0530-2R2M-AG&spm=wm.fly.bg.0.xh&lcsc_vid=QFJaAQFeTlFdU1xXTwILAlBQQQILVwYAQQALAlYEFFYxVlNRT1leX11TRlhaUjsOAxUeFF5JWBYZEEoKFBINSQcJGk4NBhADEA4cHktXRllfSQwSGg0%3D) |
| 120K resistor | 100 | $0.0022 | $0.22 | PCB | [Link](https://www.lcsc.com/product-detail/C2907223.html?s_z=n_q_C2907223&globalKeyword=C2907223) |
| 90K resitor | 10 | $0.0654 | $0.65 | PCB | [Link](https://www.lcsc.com/product-detail/C5123603.html?s_z=n_q_C5123603&globalKeyword=C5123603) |
| 68K resistor | 100 | $0.0021 | $0.21 | PCB | [Link](https://www.lcsc.com/product-detail/C2907283.html?s_z=n_q_C2907283&globalKeyword=C2907283) |
| 51k resistor | 100 | $0.0021 | $0.21 | PCB | [Link](https://www.lcsc.com/product-detail/C2933461.html?s_z=n_q_C2933461&globalKeyword=C2933461) |
| 47K resistor | 100 | $0.0021 | $0.21 | PCB | [Link](https://www.lcsc.com/product-detail/C2930202.html?s_z=n_q_C2930202&globalKeyword=C2930202) |
| 10K resistor | 100 | $0.0020 | $0.20 | PCB | [Link](https://www.lcsc.com/product-detail/C2907219.html?s_z=n_q_C2907219&globalKeyword=C2907219) |
| 5.1K resistor | 100 | $0.00 | $0.27 | PCB | [Link](https://www.lcsc.com/product-detail/C27834.html?s_z=n_q_C27834&globalKeyword=C27834) |
| 3.3K resistor | 100 | $0.0020 | $0.20 | PCB | [Link](https://www.lcsc.com/product-detail/C2907023.html?s_z=n_q_t_3.3K%2520resistor&spm=wm.fly.bg.1.xh___wm.ssy.tc.0.tz&lcsc_vid=QFJaAQFeTlFdU1xXTwILAlBQQQILVwYAQQALAlYEFFYxVlNRT1lfUVBUTlNfXzsOAxUeFF5JWBYZEEoKFBINSQcJGk4eFQsCAgIaSgADAwAHC0slRVZWVFBIHxUDCw%3D%3D) |
| 1k resistor | 100 | $0.0076 | $0.76 | PCB | [Link](https://www.lcsc.com/product-detail/C2907002.html?s_z=n_q_t_0603%25201k%25CE%25A9%2520&spm=wm.fly.bg.0.xh___wm.ssy.tc.0.tz&lcsc_vid=QFJaAQFeTlFdU1xXTwILAlBQQQILVwYAQQALAlYEFFYxVlNeRFBXUFRQT1NcUzsOAxUeFF5JWBYZEEoKFBINSQcJGk4NBhADEA4cHktXRlhXSQwSGg0%3D) |
| 100Ω resistor | 100 | $0.0014 | $0.14 | PCB | [Link](https://www.lcsc.com/product-detail/C105588.html?s_z=n_q_t_100%25CE%25A9%2520resistor&spm=wm.fly.bg.0.xh___wm.ssy.tc.0.tz&lcsc_vid=QFJaAQFeTlFdU1xXTwILAlBQQQILVwYAQQALAlYEFFYxVlNRT1lfUVxWQ1RbXzsOAxUeFF5JWBYZEEoKFBINSQcJGk4NBhADEA4cHktXRlhXSQwSGg0%3D) |
| 470uF capacitor | 5 | $0.0875 | $0.44 | PCB | [Link](https://www.lcsc.com/product-detail/C976030.html) |
| 220uF capacitor | 10 | $0.0276 | $0.28 | PCB | [Link](https://www.lcsc.com/product-detail/C22388075.html?s_z=n_q_220uF%2520%25C2%25B120%2525%252025V%2520Aluminum%2520Electrolytic%2520Capacitors%2520SMD&spm=wm.fly.bg.0.xh&lcsc_vid=QFJaAQFeTlFdU1xXTwILAlBQQQILVwYAQQALAlYEFFYxVlNRT1lfUFxUQ1NdVjsOAxUeFF5JWBYZEEoKFBINSQcJGk4NBhADEA4cHktXRlVeSQwSGg0%3D) |
| 100uF capacitor | 20 | $0.0372 | $0.74 | PCB | [Link](https://www.lcsc.com/product-detail/C970685.html?s_z=n_q_C970685&globalKeyword=C970685) |
| 22uF capacitor | 20 | $0.0349 | $0.70 | PCB | [Link](https://www.lcsc.com/product-detail/C45783.html?s_z=n_q_C45783&globalKeyword=C45783) |
| 10uF capacitor | 10 | $0.0394 | $0.39 | PCB | [Link](https://www.lcsc.com/product-detail/C9807.html?s_z=n_q_10uF%2520%25C2%25B110%2525%252025V%2520Ceramic%2520Capacitor&spm=wm.fly.bg.0.xh&lcsc_vid=QFJaAQFeTlFdU1xXTwILAlBQQQILVwYAQQALAlYEFFYxVlNRT1lfUFNSQVNXVDsOAxUeFF5JWBYZEEoKFBINSQcJGk4eFQsCAgIaSgADAwAHC0slRlRWUlRIHxUDCw%3D%3D) |
| 1uF capacitor | 50 | $0.0069 | $0.35 | PCB | [Link](https://www.lcsc.com/product-detail/C29936.html?s_z=n_q_1uF%2520%25C2%25B110%2525%252025V%2520Ceramic%2520Capacitor%2520&spm=wm.fly.bg.0.xh&lcsc_vid=QFJaAQFeTlFdU1xXTwILAlBQQQILVwYAQQALAlYEFFYxVlNRT1lfUFBfTlhZUTsOAxUeFF5JWBYZEEoKFBINSQcJGk4eFQsCAgIaSgADAwAHC0slQlBXXlxRRU8GEwkK) |
| 0.1uF capacitor | 100 | $0.004 | $0.40 | PCB | [Link](https://www.lcsc.com/product-detail/C1590.html?s_z=n_q_100nF%2520%25C2%25B110%2525%252025V%2520Ceramic%2520Capacitor%2520&spm=wm.fly.bg.0.xh&lcsc_vid=QFJaAQFeTlFdU1xXTwILAlBQQQILVwYAQQALAlYEFFYxVlNRT1lfUFFfRVVdVzsOAxUeFF5JWBYZEEoKFBINSQcJGk4eFQsCAgIaSgADAwAHC0slRlVYUVdIHxUDCw%3D%3D) |
| 22pF capacitor | 100 | $0.0041 | $0.41 | PCB | [Link](https://www.lcsc.com/product-detail/C1653.html?s_z=n_q_C1653&globalKeyword=C1653) |
| ST VNH5019ATR-E | 1 | 9.36$ | 9.36$ | H-bridge to switch polairty | [Link](https://www.lcsc.com/product-detail/C2653552.html?s_z=n_VNH5019A-E&spm=wm.ssy.bg.0.stp&lcsc_vid=QFJaAQFeTlFdU1xXTwILAlBQQQILVwYAQQALAlYEFFYxVlNRQ1VZV1NQRFZcUjsOAxUeFF5JWBYZEEoKFBINSQcJGk4eFQsCAgIaSgADAwAHC0slQlJZUlRIHxUDCw%3D%3D) |
| LM2596S-5.0 | 1 | 1.42$ | 1.37$ | Buck convetor for non 12V parts | [Link](https://www.lcsc.com/product-detail/C116713.html?s_z=n_LM2596S-5&spm=wm.ssy.bg.17.xh&lcsc_vid=QFJaAQFeTlFdU1xXTwILAlBQQQILVwYAQQALAlYEFFYxVlNRQ1VZVVdQR1leVjsOAxUeFF5JWBYZEEoKFBINSQcJGk4eFQsCAgIaSgADAwAHC0slRlRdVVZUWQkaCgg%3D) |
| WCH CH224K | 1 | $0.61 | $0.61 | Power negogatior, Requests 9V | [Link](https://www.lcsc.com/product-detail/C970725.html?s_z=n_q_CH224K&spm=wm.ssy.bg.0.xh&lcsc_vid=QFJaAQFeTlFdU1xXTwILAlBQQQILVwYAQQALAlYEFFYxVlNRQFZaUldfQlhfVjsOAxUeFF5JWBYZEEoKFBINSQcJGk4dAgUUFAk%3D) |
| IP2326 | 1 | $0.62 | $0.62 | Boost converter for charging 9V to 12.6V | [Link](https://www.lcsc.com/product-detail/C2832094.html?s_z=n_q_IP2326&spm=wm.fly.bg.0.xh&lcsc_vid=QFJaAQFeTlFdU1xXTwILAlBQQQILVwYAQQALAlYEFFYxVlNRT1lfVVxfQFdeXzsOAxUeFF5JWBYZEEoKFBINSQcJGk4eFQsCAgIaSgADAwAHC0slTlZeUFZTWQkaCgg%3D) |
| ATMEGA328P-AU | 1 | $2.65 | $2.65 | Microcontroller | [Link](https://www.lcsc.com/product-detail/C14877.html?s_z=n_q_ATmega328P-A&spm=wm.fly.bg.0.xh&lcsc_vid=QFJaAQFeTlFdU1xXTwILAlBQQQILVwYAQQALAlYEFFYxVlNRT1lfVFReT1FZVTsOAxUeFF5JWBYZEEoKFBINSQcJGk4eFQsCAgIaSgADAwAHC0slRVldVVRfQ08GEwkK) |




## BOM(JLCPCB)

| Comment | Designator | Footprint | LCSC Part Number |
|---------|-----------|-----------|------------------|
| USB-C | USBC1 | USBC_U:USB-C_SMD-TYPE-C-31-M-12_1 | C165948 |
| 5A Fuse | F2 | Fuse:Fuse_1206_3216Metric | C41367229 |
| Crystal | Y1 | Crystal:Crystal_SMD_5032-2Pin_5.0x3.2mm | C122519 |
| Ferrite bead | FB1 | Inductor_SMD:L_0805_2012Metric | C21519 |
| AO3400A diode | Q4 | Package_TO_SOT_SMD:SOT-23 | C20917 |
| SS54 Diode | D1, D2, D3, D6 | Diode_SMD:D_SMA | C22452 |
| 33µH inductor | L1 | inductor_33uh:IND-SMD_L12.3-W12.3 | C9400 |
| 120K Resitor | R21, R35 | Resistor_SMD:R_0805_2012Metric | C2907223 |
| 90K Resitor | R24 | Resistor_SMD:R_0805_2012Metric | C5123603 |
| 68K Resitor | R22 | Resistor_SMD:R_0805_2012Metric | C2907283 |
| 51K Resitor | R20 | Resistor_SMD:R_0805_2012Metric | C2933461 |
| 47K restior | R27 | Resistor_SMD:R_0805_2012Metric | C2930202 |
| 10K Restior | R34, R33, R28, R16, R13, R12, R10, R9, R8, R5, R3, R2, R1 | Resistor_SMD:R_0805_2012Metric | C2907219 |
| 5.1K resistor | R18, R19 | Resistor_SMD:R_0805_2012Metric | C27834 |
| 3.3K resistor | R7, R14 | Resistor_SMD:R_0603_1608Metric | C2907023 |
| 1k resistor | R32, R23, R17, R15, R6, R4 | Resistor_SMD:R_0603_1608Metric | C2907002 |
| 100Ω resistor | R11 | Resistor_SMD:R_0603_1608Metric | C105588 |
| 220uF capacitor | C2 | Capacitor_SMD:CP_Elec_6.3x7.7 | C22388075 |
| 100uF capacitor | C8 | Capacitor_SMD:CP_Elec_6.3x7.7 | C970685 |
| 22uF capacitor | C14, C17 | Capacitor_SMD:C_0805_2012Metric | C45783 |
| 10uF capacitor | C25, C23, C22,C10 | Capacitor_SMD:C_1206_3216Metric | C9807 |
| 1uF capacitor | C7 | Capacitor_SMD:C_0603_1608Metric | C29936 |
| 0.1uF capacitor | C24, C19, C18, C15, C13, C12, C11, C9, C6, C5, C4, C3, C1 | Capacitor_SMD:C_0603_1608Metric | C1590 |
| 22pF capacitor | C20,C21 | Capacitor_SMD:C_0603_1608Metric | C1653 |
| ST VNH5019ATR-E | U2 | Package_SO:ST_MultiPowerSO-30 | C2653552 |
| LM2596S-5.0 | U1 | Package_TO_SOT_SMD:TO-263-5_TabPin3 | C116713 |
| WCH CH224K | U3 | CH224K:ESSOP-10_L4.9-W3.9-P1.0-LS6.0-TL-EP | C970725 |
| IP2326 | U5 | Package_DFN_QFN:QFN-24-1EP_4x4mm_P0.5mm_EP2.6x2.6mm | C2832094 |
| ATMEGA328P-AU | U4 | Package_QFP:TQFP-32_7x7mm_P0.8mm | C14877 |
