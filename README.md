
# Weather Sensor Reader

This Arduino project was created to analyze the surrounding wearher conditions in any room, while storing data for analysis. After the collection is complete, you can do anything you wish with the data, such as plotting the data.

Keep in mind, it will only save the temperature, but the humidity will also show on the LCD display.

### User Manual

This board will turn on, and show a display stating to select a time. With the two buttons, increase/decrease as you see fit (time is in hours/minutes). To select, do not press any buttons for five seconds. From then, the data collection period will start. On menu one, it will show the current temperature and humidity, by pressing the right button (if set up as it is in the image below) you can switch to menu 2. This menu will show the address the board has written to last, as well as the value it was written with. After the board is full of new data the blue LED will light up, signifying it has been completed.

### Components Used

These components can be simply found online, though I used components only from an [Elegoo Uno Super Starter Kit](https://www.amazon.ca/Elegoo-Project-Starter-Tutorial-Arduino/dp/B01D8KOZF4/ref=sr_1_5?dib=eyJ2IjoiMSJ9.AcWZy-Yg4mDTnhzEHozxzJjUEeTZ9fbaMtj9CPsZZzYvIxfQ_6AvSBVgosgjam0lfNG2RXfVjnv-WfndQ22P9qoqk-erkiSjfmpW_JO3uRIlW_1mTFgT_3uNYL0L_ccT35MGk8R2uD3VMgyI-_bMG1zhB16VoIAkFmtNim48V-MkEoq9gYUNJrAzDYNSg2Xa2-phleisTggC1A9Zs8gTa-rwEaqOjo4f-_bWVmQ4xQFp7EieBAbskfi-93y4n34G4FwIfvVTN_ha_NWFG0hkt4y2Z4P5va95IlzUMYr_R2c.Di_fDS4NrpBXJ0yJ7HznYSng3QitiZy-_G7QfavhqYg&dib_tag=se&keywords=arduino+kit&qid=1708905416&sr=8-5). The indiviual key parts used are:
- ELEGOO UNO R3 Controller Board
- DHT11 temperature and Humidity Sensor
- LCD1602 Module
- 2 buttons
- Potentiometer 
- Blue LED
- 2 10K Ω resistor
- 1 470 Ω resistor
- 1 220 Ω resistor
- A bunch of wires

### Circuit Design
![Weather Reader Circuit Board](https://github.com/Macpickle/Arduino-Weather-Sensor-Reader/blob/main/Weather%20Reader%20Circuit%20Design.png)


### Extras/Comments

I understand this is not optimum, but this is all I really had. Although that is the case, it still works completely fine.
Feel free to leave suggestions/comments on anything.

\- Macpickle
