#include "Adafruit_MAX31855.h"
#include "ReflowPhase.h"

//enum Phase { PREHEAT, SOAK, REFLOW, COOLDOWN };

//stores the amount of time for each reflow phase to last.
ReflowPhase phases[4];

void setup() {
 

  
  //take the user input for the time, temperature parameters.
  for (int i = 0; i <= ReflowPhase::COOLDOWN; i++) {
    phases[i] = ReflowPhase iPhase(i);
    
    //Take time/temp specifications from user.
    Serial.println(strcat("Input the time for ", phaseName));
    Serial.read(inputParm); 
    phases[i].setPhaseDuration(inputParm);
    
    Serial.println(strcat("Input the target temp in C for ", phaseName));
    Serial.read(inputParm);
    phases[i].setTargetTemp(inputParm);  
  }

  //Display input params.
  Serial.println("Here is your profile:");
  for (int i = 0; i < COOLDOWN; i++) {
    Serial.println(phases[i].toString());
  }
  
}

void loop() {

}
