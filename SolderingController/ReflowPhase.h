/*
ReflowPhase.
Defines a phase of a soldering reflow operation, of which there are four. 
*/

#ifndef REFLOWPHASE_H
#define REFLOWPHASE_H

class ReflowPhase {

public:
	enum Phase { PREHEAT, SOAK, REFLOW, COOLDOWN };

	//ctors
	ReflowPhase();
	ReflowPhase(char*& phaseName, const Phase& order, const double& duration, const double& targetTemp); 
	ReflowPhase(Phase& order, const double& duration, const double& targetTemp);
	ReflowPhase(Phase& order);
	ReflowPhase(ReflowPhase& otherPhase);
	~ReflowPhase();

	void setPhaseName(const char*& phaseName);
	char*& getPhaseName();
	
	void setPhaseOrder(const Phase& order);
	Phase getPhaseOrder() const;

	void setDuration(const double& temp);
	double getDuration() const;

	void setTargetTemp(const double& temp);
	double getTargetTemp() const;

	char* toString();

private:
	char* 					phaseName_;
	ReflowPhase::Phase		phaseOrder_;
	double					phaseDuration_;
	double					phaseTemp_;

	void setOrderName(const Phase& order);
};

#endif