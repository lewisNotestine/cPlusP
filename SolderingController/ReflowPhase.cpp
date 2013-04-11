#include "ReflowPhase.h"
#include "Arduino.h"
//#include <iostream>
//#include <iomanip>

using namespace std;

ReflowPhase::ReflowPhase() {
}


ReflowPhase::ReflowPhase(char*& phaseName, const Phase& order, const double& duration, const double& targetTemp) :
	phaseName_(phaseName),
	phaseOrder_(order),
	phaseDuration_(duration),
	phaseTemp_(targetTemp)
{}

ReflowPhase::ReflowPhase(Phase& order, const double& duration, const double& targetTemp) {
    
}


//this is what will most likely be used. 
ReflowPhase::ReflowPhase(Phase& order) : phaseOrder_(order) {
    this->setOrderName(order);
    this->setDuration(0);
    this->setTargetTemp(0);
}


ReflowPhase::ReflowPhase(ReflowPhase& otherPhase) :
    phaseOrder_(otherPhase.getPhaseOrder()),
    phaseName_((char*)otherPhase.getPhaseName()),
    phaseDuration_(otherPhase.getDuration()),
    phaseTemp_(otherPhase.getTargetTemp())
{
    
}

ReflowPhase::~ReflowPhase() {}

void ReflowPhase::setPhaseName(const char*& phaseName) {
	this->phaseName_ = (char*)phaseName;
	return;
}

char*& ReflowPhase::getPhaseName() {
    return this->phaseName_;
}

void ReflowPhase::setPhaseOrder(const Phase& order) {
	this->phaseOrder_ = order;
	return;
}

ReflowPhase::Phase ReflowPhase::getPhaseOrder() const {
	return this->phaseOrder_;
}

void ReflowPhase::setDuration(const double& duration) {
	this->phaseDuration_ = duration;
	return;
}

double ReflowPhase::getDuration() const {
	return this->phaseDuration_;
}

void ReflowPhase::setTargetTemp(const double& temp) {
	this->phaseTemp_ = temp;
	return;
}

double ReflowPhase::getTargetTemp() const {
	return this->phaseTemp_;
}

char* ReflowPhase::toString() {
	char* retVal = new char;
    strcpy(retVal, "Phase: ");
    char* strDurationTemp = new char;
    int n;
    strcat(retVal, this->getPhaseName());

    n = sprintf(strDurationTemp, ", Duration: %4.2f, Temperature: %4.2f \n", this->getDuration(), this->getTargetTemp());
    
    strcat(retVal, strDurationTemp);

           
	//snprintf( retVal, sizeof(retVal), "%s:, Duration: %d, Target Temp: %d", this->getPhaseName(), this->getDuration(), this->getTargetTemp());
	
    //delete [] strDurationTemp;
    
	return retVal;
}

void ReflowPhase::setOrderName(const ReflowPhase::Phase& order) {
    const char* theName;
    
    switch (order) {
		case ReflowPhase::PREHEAT:
            theName = "preheat";
			break;
		case SOAK:
			theName = "soak";
			break;
		case REFLOW:
            theName = "reflow";
			break;
		case COOLDOWN:
			theName = "cooldown";
			break;
		default:
			theName = "error";
			break;
	}
    setPhaseName(theName);
}
