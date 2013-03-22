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
	ReflowPhase(const char*& phaseName, const Phase& order, const double& duration, const double& targetTemp); 
	ReflowPhase(const Phase& order, const double& duration, const double& targetTemp);
	ReflowPhase(const Phase& order);
	ReflowPhase(const ReflowPhase& otherPhase);
	~ReflowPhase();

	void setPhaseName(const char*& phaseName);
	const char*& getPhaseName() const;
	
	void setPhaseOrder(const int& order);
	const int getPhaseOrder() const;

	void setDuration(const double& temp);
	const double getDuration() const;

	void setTargetTemp(const double& temp);
	const double getTargetTemp() const;

	const char* toString() const;

private:
	char* 					phaseName_;
	ReflowPhase::Phase		phaseOrder_;
	double					phaseDuration_;
	double					phaseTemp_;

	void setOrderName(const Phase& order);
};

#endif