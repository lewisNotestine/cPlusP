/*
Adapted from Adafruit Max31855 breakout board code.

controls a heat gun based on thermocouple reading. Trying different algorithms, like simple on/off and temperature control reading versus PID algorithm.
*/

#include "Adafruit_MAX31855.h"

int thermoDO = 3;
int thermoCS = 4;
int thermoCLK = 5;
const int gunPin = 11;


int phaseIndex = 0;  //current state of the reflow.

//Times are given as t (not period).


const double TEMP_THRESHOLD = 2.0;
const double PREHEAT_TIME = 470;
const double PREHEAT_TEMP = 125;

const double SOAK_TIME = 575;
const double SOAK_TEMP = 160;

const double REFLOW_TIME = 675;
const double REFLOW_TEMP = 210;

const double COOLDOWN_TIME = 800;
const double COOLDOWN_TEMP = 160;
const int SECONDS = 120;

double secondsArray[SECONDS];
double timeArray[4];
double tempArray[4];
double dTdtArray[4];
char nameArray[4][10];


char phaseType[10];  //name of the phase.
double phaseTime = 0.0;  //tracks the time.
double totalTime = 0.0;
double targetTemp;  //current target temperature.
double initTemp = 0;
double lastTemp = 0;
bool gunIsOn = false;

Adafruit_MAX31855 thermocouple(thermoCLK, thermoCS, thermoDO);
  
void setup() { 
  pinMode(gunPin, OUTPUT);
  
  timeArray[0] = PREHEAT_TIME;
  tempArray[0] = PREHEAT_TEMP;
  strcpy(nameArray[0], "Preheat");
  //dTdtArray is populated after initTemp is recorded.
  
  timeArray[1] = SOAK_TIME;
  tempArray[1] = SOAK_TEMP;
  strcpy(nameArray[1], "Soak");
  dTdtArray[1] = (tempArray[1] - tempArray[0]) / (timeArray[1] - timeArray[0]);
  
  timeArray[2] = REFLOW_TIME;
  tempArray[2] = REFLOW_TEMP;
  strcpy(nameArray[2], "Reflow");
  dTdtArray[2] = (tempArray[2] - tempArray[1]) / (timeArray[2] - timeArray[1]);
  
  timeArray[3] = COOLDOWN_TIME;
  tempArray[3] = COOLDOWN_TEMP;
  strcpy(nameArray[3], "Cooldown");
  dTdtArray[3] = (tempArray[3] - tempArray[2]) / (timeArray[3] - timeArray[2]);  
  
  
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
  
  lastTemp = initTemp;
  dTdtArray[0] = (tempArray[0] - initTemp) / timeArray[0];
  
  
  int currentPhase = 0;
  double rate = dTdtArray[currentPhase];
  
  //populate target temp for each second.
  for (int i = 0; i < SECONDS; i++) {
   
    if (i > timeArray[currentPhase]) {
      currentPhase++;
      rate = dTdtArray[currentPhase];
    }
    
    if (i == 0) {
      secondsArray[i] = initTemp;
    } else {
      secondsArray[i] = secondsArray[i - 1] + dTdtArray[currentPhase];
    }
    
    Serial.print("Phase: ");
    Serial.print(nameArray[currentPhase]);
    Serial.print("; "); 
    Serial.print("rate: ");
    Serial.print(rate);
    Serial.print("; "); 
    Serial.print("t = ");
    Serial.print(i);
    Serial.print("; "); 
    Serial.print("Target Temp: ");
    Serial.println(secondsArray[i]);
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
  
  if (totalTime < SECONDS) {
  // basic readout test, just print the current temp
   //Serial.print("Internal Temp = " );
   //Serial.println(thermocouple.readInternal());
   
   double dTdt;    //rate of temp change current.
   double c = thermocouple.readCelsius();
   
   if (isnan(c)) {
     Serial.println("Something wrong with thermocouple!");
     phaseTime += 1.0;
     totalTime += 1.0;
     
   } else {
     
     
     //calculate, print the phase.
     if(phaseTime >= timeArray[phaseIndex]) {
       phaseIndex++;
       //phaseTime = 0;
     }
     
     Serial.print(nameArray[phaseIndex]);
     Serial.print("; ");
     
     Serial.print("Phase Time: ");
     Serial.print(phaseTime);
     Serial.print("; ");
     
     //calculate and print the rate of temp change.  set for an interval of 1 sec.
     dTdt = (c - lastTemp);
     int intTime = totalTime;     
     //calculate and print the target temperature.
     /*
     if (phaseIndex == 0) {
       targetTemp =  initTemp + (phaseTime / timeArray[phaseIndex]) * tempArray[phaseIndex];
     } else {
       targetTemp =  tempArray[phaseIndex - 1] + (phaseTime / timeArray[phaseIndex]) * tempArray[phaseIndex];
     }*/
     targetTemp = secondsArray[intTime];
     
     Serial.print("Target Temp = C ");
     Serial.print(targetTemp);
     Serial.print("; ");
     
     //print the observed temperature.
     Serial.print("Current Temp = C "); 
     Serial.print(c);
     Serial.print("; ");
     
     Serial.print("dT: ");
     Serial.print(dTdt);
     //Serial.print(c - targetTemp);
     Serial.print("; ");
     
     //print the state of the heat gun, determine whether to turn on or off.
     /*
     if (dTdt < dTdtArray[phaseIndex]) {
       gunIsOn = true;
     } else {
       gunIsOn = false;
     }
     */

     if (c < secondsArray[intTime]) {
       gunIsOn = true;
     } else {
       gunIsOn = false;
     }
     
     
     //if (c - targetTemp >= TEMP_THRESHOLD) { //Too hot.
     //if (c > targetTemp) {
       //gunIsOn = false;
     //} else if (targetTemp - c >= TEMP_THRESHOLD) {//Too cold
     //} else { 
       //gunIsOn = true;
     //}
     
     //toggle heat.
     if (gunIsOn) {
       digitalWrite(gunPin, HIGH);
       Serial.println("gun ON");
     } else {
       digitalWrite(gunPin, LOW);
       Serial.println("gun OFF");
     }
     
     
     lastTemp = c;
     
     phaseTime += 1.0;
     totalTime += 1.0;
   }
   //Serial.print("F = ");
   //Serial.println(thermocouple.readFarenheit());
   } else {
     digitalWrite(gunPin, LOW);
   }
   
   delay(1000);
}
