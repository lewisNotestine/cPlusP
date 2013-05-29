/*************************************************** 
  This is an example for the Adafruit Thermocouple Sensor w/MAX31855K

  Designed specifically to work with the Adafruit Thermocouple Sensor
  ----> https://www.adafruit.com/products/269

  These displays use SPI to communicate, 3 pins are required to  
  interface
  Adafruit invests time and resources providing this open source code, 
  please support Adafruit and open-source hardware by purchasing 
  products from Adafruit!

  Written by Limor Fried/Ladyada for Adafruit Industries.  
  BSD license, all text above must be included in any redistribution
 ****************************************************/

#include "Adafruit_MAX31855.h"

int thermoDO = 3;
int thermoCS = 4;
int thermoCLK = 5;
const int gunPin = 11;


int phaseIndex = 0;  //current state of the reflow.

const double TEMP_THRESHOLD = 2.0;
const double PREHEAT_TIME = 100;
const double PREHEAT_TEMP = 160;

const double SOAK_TIME = 100;
const double SOAK_TEMP = 200;

const double REFLOW_TIME = 40;
const double REFLOW_TEMP = 230;

const double COOLDOWN_TIME = 150;
const double COOLDOWN_TEMP = 40;

double timeArray[4];
double tempArray[4];
char nameArray[4][10];

char phaseType[10];  //name of the phase.
double phaseTime = 0.0;  //tracks the time.
double totalTime = 0.0;
double targetTemp;  //current target temperature.
double initTemp = 0;
bool gunIsOn = false;

Adafruit_MAX31855 thermocouple(thermoCLK, thermoCS, thermoDO);
  
void setup() { 
  pinMode(gunPin, OUTPUT);
  
  timeArray[0] = PREHEAT_TIME;
  tempArray[0] = PREHEAT_TEMP;
  strcpy(nameArray[0], "Preheat");
  
  timeArray[1] = SOAK_TIME;
  tempArray[1] = SOAK_TEMP;
  strcpy(nameArray[1], "Soak");
  
  timeArray[2] = REFLOW_TIME;
  tempArray[2] = REFLOW_TEMP;
  strcpy(nameArray[2], "Reflow");
  
  timeArray[3] = COOLDOWN_TIME;
  timeArray[3] = COOLDOWN_TEMP;
  strcpy(nameArray[3], "Cooldown");
  
  Serial.begin(9600);
  
  
  Serial.println("MAX31855 test");
  // wait for MAX chip to stabilize
  delay(500);
  
  while (initTemp == 0) {
    initTemp = thermocouple.readCelsius();
  
    if (isnan(initTemp)) {
       Serial.println("reinitializing...");
       initTemp = 0;
    } else if (initTemp < 5 || initTemp > 30) {
       Serial.println("reinitializing...");
       initTemp = 0;
    }
  }
  
  delay(1000);
  
  Serial.println("Testing gun");
  
  Serial.println("gun ON");
  digitalWrite(gunPin, HIGH);
  Serial.println(digitalRead(gunPin));
  delay(1000);
  
  Serial.println("gun OFF");
  digitalWrite(gunPin, LOW);
  Serial.println(digitalRead(gunPin));
  delay(1000);
  
    Serial.println("gun ON");
  digitalWrite(gunPin, HIGH);
  Serial.println(digitalRead(gunPin));
  delay(1000);
  
  Serial.println("gun OFF");
  digitalWrite(gunPin, LOW);
  Serial.println(digitalRead(gunPin));
  delay(1000);
  
}

void loop() {
  // basic readout test, just print the current temp
   //Serial.print("Internal Temp = " );
   //Serial.println(thermocouple.readInternal());
   

   double c = thermocouple.readCelsius();
   if (isnan(c)) {
     Serial.println("Something wrong with thermocouple!");
     phaseTime += 1.0;
     
   } else {
     //calculate, print the phase.
     if(phaseTime >= timeArray[phaseIndex]) {
       phaseIndex++;
       phaseTime = 0;
     }
     
     Serial.print(nameArray[phaseIndex]);
     Serial.print("; ");
     
     Serial.print("Phase Time: ");
     Serial.print(phaseTime);
     Serial.print("; ");
     
     //calculate and print the target temperature.
     if (phaseIndex == 0) {
       targetTemp =  initTemp + (phaseTime / timeArray[phaseIndex]) * tempArray[phaseIndex];
     } else {
       targetTemp =  tempArray[phaseIndex - 1] + (phaseTime / timeArray[phaseIndex]) * tempArray[phaseIndex];
     }
     
     Serial.print("Target Temp = C ");
     Serial.print(targetTemp);
     Serial.print("; ");
     
     //print the observed temperature.
     Serial.print("Current Temp = C "); 
     Serial.print(c);
     Serial.print("; ");
     
     Serial.print("dT: ");
     Serial.print(c - targetTemp);
     Serial.print("; ");
     
     //print the state of the heat gun, determine whether to turn on or off.
     //if (c - targetTemp >= TEMP_THRESHOLD) { //Too hot.
     if (c > targetTemp) {
       gunIsOn = false;
     //} else if (targetTemp - c >= TEMP_THRESHOLD) {//Too cold
     } else { 
       gunIsOn = true;
     }
     
     //toggle heat.
     if (gunIsOn) {
       digitalWrite(gunPin, HIGH);
       Serial.println("gun ON");
     } else {
       digitalWrite(gunPin, LOW);
       Serial.println("gun OFF");
     }
     
     

     phaseTime += 1.0;
   }
   //Serial.print("F = ");
   //Serial.println(thermocouple.readFarenheit());
 
   delay(1000);
}
