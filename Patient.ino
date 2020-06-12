//Hicham Baydoun

/*
 LED set to D5
 Piezo set to D4
 Servo Motor set to D6
 */
 
//ESP8266
#define BLYNK_PRINT Serial
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>

char auth[] = "N3z8tCnN2juQh11aSUsn3JTrkGZajZag";
char ssid[] = "seranco";
char pass[] = "3081968G";

//Servo Motor
#include <Servo.h>
Servo myservo;

//Piezo
#define PIEZO 2 // 2 is D4 pin of ESP8266

void setup()
{
  Serial.begin(9600);
  Blynk.begin(auth , ssid ,pass ,"blynk-cloud.com" ,8080);
  myservo.attach(12); // 12 is D6 pin of ESP8266
  pinMode(PIEZO, OUTPUT);
}

//Adjust servo motor angle through getting value from slider (Slider set to virtual V1)
BLYNK_WRITE(V1) {
  myservo.write(param.asInt());
  Blynk.notify("Bed Angle Adjusted");
}

//turn on piezo when button is pressed (Button set to virtual V0)
BLYNK_WRITE(V0) {
  analogWrite(PIEZO, param.asInt());
}

void loop()
{
  Blynk.run();
}
