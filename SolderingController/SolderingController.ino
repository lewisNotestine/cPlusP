#include "Adafruit_MAX31855.h"
#include "ReflowPhase.h"

//enum Phase { PREHEAT, SOAK, REFLOW, COOLDOWN };

//stores the amount of time for each reflow phase to last.
float timeParams[4];
float tempParams[4];
char** phaseNames;

void setup() {
  phaseNames = new char*[4];
  char*   phaseName; 
  float   inputParm;
  
  //take the user input for the time, temperature parameters.
  for (int i = 0; i <= COOLDOWN; i++) {
    switch (i) {
        case PREHEAT:
          phaseNames[PREHEAT] = new char[8];
          strcpy_s(phasenames[PREHEAT],  "preheat\0");
          break;
        case SOAK:
          phaseNames[SOAK];
          phaseName = "soak\0";
          break;
        case REFLOW:
          phasename = "reflow";
          break;
        case COOLDOWN:
          phaseName = "cooldown";
          break;          
        default:
          phaseName = "ERROR";
          break;
          
        
    }
    
    
    //Take time/temp specifications from user.
    Serial.println(strcat("Input the time for ", phaseName));
    Serial.read(inputParm); 
    timeParams[i] = inputParm;
    
    Serial.println(strcat("Input the target temp in C for ", phaseName));
    Serial.read(inputParm);
    tempParams[i] = inputParm;     
  }
  
  Serial.println("Here is your profile:");
  for (int i = 0; i < COOLDOWN; i++) {
    Serial.println("test");
  }
  
}

void loop() {

}
