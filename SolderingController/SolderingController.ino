#include "Adafruit_MAX31855.h"
#include "ReflowPhase.h"

#ifndef STRBUF 
#define STRBUF 256
#endif

using namespace std;

void setup() {
    //stores the amount of time for each reflow phase to last.
    ReflowPhase phases[4];
    double inputParm;
    //string  strInput;
    char strInput[10];
    char inputPref[30];
    ReflowPhase::Phase eachPhase;
    
    Serial.begin(9600);
    
    //take the user input for the time, temperature parameters.
    for (int i = 0; i <= ReflowPhase::COOLDOWN; i++) {
      strcpy(inputPref, "Input the time for ");

        //if (strInput != 0) {
            //delete [] strInput;
            //strInput = 0;
        //}
        
        eachPhase = (ReflowPhase::Phase)i;
        phases[i] = ReflowPhase(eachPhase);
        
        //Take time/temp specifications from user.
        //strInput = new char[STRBUF];
        
        //cout << "Input the time for " << phases[i].getPhaseName() << endl;
        strcat(inputPref, phases[i].getPhaseName());
        Serial.println(inputPref);
        Serial.readBytesUntil('\n', strInput, 8);
        inputParm = atof(strInput);
        //cin >> inputParm;
        phases[i].setDuration(inputParm);
        
        strcpy(inputPref, "Input the temp for ");
        strcat(inputPref, phases[i].getPhaseName());
        Serial.println(inputPref);
        Serial.readBytesUntil('\n', strInput, 8);
        inputParm = atof(strInput);
        
        //cout << "Input the target temp in C for " << phases[i].getPhaseName() << endl;
        //cin >> inputParm;
        phases[i].setTargetTemp(inputParm);
    }
    
    //Display input params.
    //Serial.println("Here is your profile:");
    //cout << "Here is your profile: " << endl;
    for (int i = 0; i <= ReflowPhase::COOLDOWN; i++) {
        Serial.println(phases[i].toString());
        //cout << phases[i].toString();
    }
}

void loop() {
  

}
    
