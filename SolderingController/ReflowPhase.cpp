#include "ReflowPhase.h"

ReflowPhase::ReflowPhase() {
}



ReflowPhase::ReflowPhase(const char*& phaseName, const Phase& order, const double& duration, const double& targetTemp) :
	phaseName_(phaseName),
	phaseOrder_(order),
	phaseDuration_(duration),
	phaseTemp_(targetTemp)
{}

ReflowPhase(const ReflowPhase::Phase& order, const double& duration, const double& targetTemp) :	
	phaseOrder_(order),
	phaseDuration_(duration),
	phaseTemp_(targetTemp)
{
	this->setOrderName(order);
}

//this is what will most likely be used. 
ReflowPhase(const ReflowPhase::Phase& order) :	
	phaseOrder_(order),
{
	this->setOrderName(order);
	this->setDuration(0);
	this->setTargetTemp(0);
}



ReflowPhase(const ReflowPhase& otherPhase) {
	this->setPhaseName(otherPhase.getPhaseName());
	this->setPhaseOrder(otherPhase.getPhaseOrder());
	this->setDuration(otherPhase.getDuration());
	this->setTargetTemp(otherPhase.getTargetTemp());
}

void ReflowPhase::setPhaseName(const char*& phaseName) {
	this->phaseName_ = phaseName;
	return;
}

const char*& ReflowPhase::getPhaseName() const {
	return this->phaseName_;
}

void ReflowPhase::setPhaseOrder(const int& order) {
	this->phaseOrder_ = order;
	return;
}

const int ReflowPhase::getPhaseOrder() const {
	return this->phaseOrder_;
}

void ReflowPhase::setDuration(const double& duration) {
	this->phaseDuration_ = duration;
	return;
}

const double ReflowPhase::getDuration() const {
	return this->phaseDuration_;
}

void ReflowPhase::setTargetTemp(const double& temp) {
	this->phaseTemp_ = temp;
	return;
}

const double ReflowPhase::getTargetTemp() const {
	return this->phaseTemp_;
}

const char* toString() const {
	char* retVal[60];
	snprintf( retVal, sizeof(retVal), "%s:, Duration: %d, Target Temp: %d", this->getPhaseName(), this->getDuration(), this->getTargetTemp());
	
	return retVal;
}

void setOrderName(const ReflowPhase::Phase& order) {
	switch (order) {
		case PREHEAT:
			setPhaseName("preheat");
			break;
		case SOAK:
			setPhaseName("soak");
			break;
		case REFLOW:
			setPhaseName("reflow");
			break;
		case COOLDOWN:
			setPhaseName("cooldown");
			break;
		default:
			setPhaseName("error!");
			break;
	}
}
