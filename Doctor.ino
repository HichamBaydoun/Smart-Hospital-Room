//Hicham Baydoun

//Keypad
/*
  Keypad Pin 1 –> Arduino Pin 9
  Keypad Pin 2 –> Arduino Pin 8
  Keypad Pin 3 –> Arduino Pin 7
  Keypad Pin 4 –> Arduino Pin 6
  Keypad Pin 5 –> Arduino Pin 5
  Keypad Pin 6 –> Arduino Pin 10
  Keypad Pin 7 –> Arduino Pin 3
  Keypad Pin 8 –> Arduino Pin 2
*/
#include "Keypad.h"
const byte ROWS = 4; //four rows
const byte COLS = 4; //four columns
char keys[ROWS][COLS] =
{ {'1', '2', '3', 'A'},
  {'4', '5', '6', 'B'},
  {'7', '8', '9', 'C'},
  {'*', '0', '#', 'D'}
};
byte rowPins[ROWS] = {
  9, 8, 7, 6
}; //connect to the row pinouts of the keypad
byte colPins[COLS] = {
  5, 10, 3, 2
}; //connect to the column pinouts of the keypad

Keypad keypad = Keypad( makeKeymap(keys), rowPins, colPins, ROWS, COLS );

//SD Crad
/*
  GND  --> ground of Arduino.
  VCC  --> 5V .
  MISO --> pin 12
  MOSI --> pin 11
  SCK  --> pin 13
  CS   --> pin 4
*/
#include <SPI.h>
#include <SD.h>
File myFile;
bool r = true; // bool in Arduino c is equivalent to boolean in java

//Piezo
//Yes, the analog pins on the Arduino can be used as digital outputs, I googled it and tested it and it worked
#define PIEZO A0 

void setup() {
  Serial.begin(9600);
  pinMode(PIEZO, OUTPUT);
}

//----------------------Enter data from serial monitor to SD Card----------------------
void writeData() {
  //check if sd card is ready before entering data
  if (!SD.begin(4)) {
    Serial.println("⚠ Card failed, or not present");
    return;
  }
  Serial.println("✔ MicroSD card is ready\n");
  delay(1000);

  Serial.println("➡ Enter patient data: ");
  String data = "";
  while (Serial.available() == 0) { //Wait for user input
  }

  if (Serial.available() > 0) { // check if something enters the serial buffer
    //read data and save it to SD Card
    data = Serial.readString();
    Serial.println(data);
    File dataFile = SD.open("Rob.TXT", FILE_WRITE);
    if (dataFile) {
      dataFile.println(data); //write the Data in the SD Card
      dataFile.close(); //Save the data
      Serial.println("\n✔ Data Saved! ✔");
    }
    else {
      Serial.println("⚠ Error opening File");
    }
  }

}

//----------------------Read data SD Card and display it on Serial Monitor----------------------
void readData() {
  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
  }
  // see if the card is present and can be initialized, if not exit
  if (!SD.begin(4)) {
    Serial.println("⚠ Card failed, or not present");
    return;
  }
  Serial.print("✔ Initializing SD card...");
  Serial.println("card initialized\n");
  delay(1500);

  File dataFile = SD.open("Rob.txt");

  // if the file is available, write to it
  if (dataFile) {
    Serial.println("💾 Patient Data: ");
    while (dataFile.available()) {
      Serial.write(dataFile.read()); //Read From the SD Card
    }
    dataFile.close();
  }
  // if the file isn't open, pop up an error
  else {
    Serial.println("⚠ Error opening File");
  }
}

//----------------------Send an emergency signal (piezo)----------------------
void callHelp() {
  digitalWrite(PIEZO, HIGH);
  Serial.println("\n🔔 CALLING HELP 🔔");
  delay(3000);
  digitalWrite(PIEZO, LOW);
}

//----------------------Loop----------------------
void loop() {
  Serial.println("➡ Press: ");
  Serial.println("👉 '1' to enter patient’s data");
  Serial.println("👉 '2' to read patient’s data");
  Serial.println("👉 '3' to send an emergency signal\n");
  Serial.println("__________________________________________________\n");

  char key = keypad.getKey(); //get key pressed by the doctor

  while (key == NO_KEY) { //wait for user to enter a key
    key = keypad.getKey();
  }

  if (key != NO_KEY) {

    Serial.print("You entered ");
    Serial.println(key);
    //Enter data from serial monitor to SD Card
    if (key == '1') {
      writeData();
      delay(2000);
    }

    //Read data SD Card and display it on Serial Monitor
    else if (key == '2') {
      readData();
      delay(2000);
    }

    //Send an emergency signal (piezo)
    else if (key == '3') {
      callHelp();
    }

    //Invalid input
    else {
      Serial.println("⚠ Invalid Input ⚠");
    }

  }

  Serial.println("\n__________________________________________________\n");

}
