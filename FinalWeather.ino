//created by Macpickle
#include <EEPROM.h>
#include <math.h>
#include <DHT.h>
#include <Adafruit_Sensor.h>
#include <LiquidCrystal.h>

#define Type DHT11

//DHT SENSOR
const int sensPin = 2;
double humidity;
double tempC;
DHT sens(sensPin, Type);

//LCD DISPLAY
const int rs = 7;
const int en = 8;
const int d4 = 9;
const int d5 = 10;
const int d6 = 11;
const int d7 = 12;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

//buttons for menu select
const int b1Pin = A1;
const int b2Pin = A0;
int readb1, readb2;

//makes buttons function as toggles
int state = 0;
int oldState = 1;
int newState;
bool pushed = true;

//time
int hours, mins;
unsigned long long timeSincePress = 0;
const int timeIncrease = 15;
const int delayBetweenPress = 1000;

//data collection
float timePerRead;
int address = 0;

//light to indicate collection has completed
int blueLED = 3;

//continue program
int menu = 0;

void setup() {
  lcd.begin(16, 2);
  sens.begin();

  pinMode(blueLED, OUTPUT);
  clearData();

  pinMode(b1Pin, INPUT);
  pinMode(b2Pin, INPUT);

  Serial.begin(9600);
}

void loop() {
  //collects temperature/humidity from sensor
  humidity = sens.readHumidity();
  tempC = sens.readTemperature();

  //reads buttons
  readb1 = digitalRead(b1Pin);
  readb2 = digitalRead(b2Pin);

  if (menu == 0) {
    //changes time upon button press
    hours, mins, timeSincePress = changeTime(readb1, readb2, timeSincePress, delayBetweenPress, timeIncrease, hours, mins);
  }

  if (menu == 1) {
    lcd.setCursor(0, 0);

    //printing to LCD to indicate data collection has begun
    if (address == 0) {
      lcd.print("Data collection");
      lcd.setCursor(0, 1);
      lcd.print("has begun...");
      delay(3000);

      lcd.clear();
      lcd.setCursor(0, 0);

      lcd.print("Total Time:");
      if (hours < 10) lcd.print("0");
      lcd.print(hours);
      lcd.print(":");
      if (mins < 10) lcd.print("0");
      lcd.print(mins);
      delay(3000);
      lcd.clear();

      timePerRead = determineTime(hours, mins);
      timeSincePress = millis();
      address += 1;
    }

    if (millis() - timeSincePress >= timePerRead) {
      timeSincePress = writeData(address, tempC);
    }

    buttonState(oldState, readb1, state, pushed);

    if (pushed == true) {
      //printing data to LCD display
      lcdPrintData(humidity, "Humidity:", '%', 0, 10);
      lcdPrintData(tempC, "Temp:", 'C', 1, 10);
    } else if (pushed == false) {
      lcdShowWrite(address, tempC);
    }
  }
}

// will take in the location to write the temperature, if it is maxed (aka, cannot write, writes LED to high)
unsigned long long writeData(int &location, float tempC) {
  if (!(location == EEPROM.length() + 1)) {
    EEPROM.update(location, round(tempC));
    Serial.print(address);
    Serial.print(" ");
    Serial.println(round(tempC));
    location += 1;
  } else {
    digitalWrite(blueLED, HIGH);
  }
  return millis();
}

//determines time per data write
float determineTime(int hours, int minutes) {
  float timePerData = 0;

  //determine total minutes
  minutes += (hours * 60);

  //determine milliseconds
  timePerData = (minutes * 60);
  timePerData *= 1000;

  //1 MB of EEPROM = 1024 data writes
  return timePerData / 1024;
}

//determines total time user puts into the button
int changeTime(int button1Val, int button2Val, int lastPress, int delay, int changeTime, int &hr, int &min) {
  // increases time only if last press is above the delayBetweenPress 
  if (millis() - lastPress >= delayBetweenPress) {
    if (button1Val == 0) {
      min += changeTime;
      lastPress = millis();
    }

    else if (button2Val == 0) {
      if (mins - changeTime >= 0) {
        min -= changeTime;
        lastPress = millis();
      }
    }

    if (min >= 60) {
      min -= 60;
      hr += 1;
    }

    if (min < 0) {
      if (hr >= 1) {
        min += 60;
        hr -= 1;
      }
    }
  }

  lcd.setCursor(0, 0);
  lcd.print("Time of reading: ");
  lcd.setCursor(0, 1);
  if (hr < 10) lcd.print("0");
  lcd.print(hr);
  lcd.print(":");
  if (min < 10) lcd.print("0");
  lcd.print(min);

  // checks for 5 secs to see if any button state changes
  if (millis() - lastPress >= 5000) {
    if (mins > 0 || hours > 0) {
      menu += 1;
      lcd.clear();
    }
  }

  return hr, min, lastPress;
}

//toggle switch logic
void buttonState(int &oldState, int readButton, int &state, bool &pushed) {
  if (oldState == 0 && readButton == 1) {
    if (state == 0) {
      pushed = true;
      state = 1;
    } else {
      pushed = false;
      state = 0;
    }
    lcd.clear();
  }
  oldState = readButton;
}

//shows temp and humidity
void lcdPrintData(float data, String measurement, char unit, int column, int row) {
  lcd.setCursor(0, column);
  lcd.print(measurement);
  lcd.setCursor(row, column);
  lcd.print(data);
  lcd.print(unit);
}

//shows where address is currently, and what was written to it
void lcdShowWrite(int address, float tempC) {
  lcd.setCursor(0, 0);
  lcd.print("Writing on: ");
  lcd.setCursor(12, 0);
  if (address < 10) lcd.print("0");
  if (address < 100) lcd.print("0");  
  if (address < 1000) lcd.print("0");
  lcd.print(address);

  lcd.setCursor(0, 1);
  lcd.print("Value: ");
  lcd.print(round(tempC));
}

//when initalized, clear all data from the board to not mess with future reading
void clearData() {
  lcd.setCursor(0, 0);
  lcd.print("Clearing data...");
  for (int i = 0; i < EEPROM.length(); i++) {
    EEPROM.update(i, 0);
  }
  lcd.clear();
}
