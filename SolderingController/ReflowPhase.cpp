#include "ReflowPhase.h"

ReflowPhase::ReflowPhase() {
}

ReflowPhase::ReflowPhase(const char*& phaseName, const Phase& order, const double& duration, const double& targetTemp) :
	phaseName_(phaseName),
	phaseOrder_(order),
	phaseDuration_(duration),
	phaseTemp_(targetTemp)
{}

ReflowPhase(const ReflowPhase& otherPhase) {
	this->setPhaseName(otherPhase.getPhaseName());
	this->setPhaseOrder(otherPhase.getPhaseOrder());
	this->setDuration(otherPhase.getDuration());
	this->setTargetTemp(otherPhase.getTargetTemp());
}

void ReflowPhase::setPhaseName(const char*& phaseName) {

}

const char*& ReflowPhase::getPhaseName() const {

}

void ReflowPhase::setPhaseOrder(const int& order) {

}

const int ReflowPhase::getPhaseOrder() const {

}

void ReflowPhase::setDuration(const double& temp) {

}

const double ReflowPhase::getDuration() const {

}

void ReflowPhase::setTargetTemp(const double& temp) {

}

const double ReflowPhase::getTargetTemp() const {
	
}
