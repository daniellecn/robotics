/*
 * TurnAround.h
 *
 *  Created on: Jun 20, 2015
 *      Author: colman
 */

#ifndef TURNAROUND_H_
#define TURNAROUND_H_

#include "Behavior.h"

class TurnAround: public Behavior {

public:
	TurnAround(Robot* robot);
	virtual ~TurnAround();

	bool startCondition();
	bool stopCondition();
	void action();
	void print();
};

#endif /* TURNAROUND_H_ */
