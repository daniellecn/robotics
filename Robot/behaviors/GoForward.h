/*
 * GoForward.h
 *
 *  Created on: Jun 20, 2015
 *      Author: colman
 */

#ifndef GOFORWARD_H_
#define GOFORWARD_H_

#include "Behavior.h"

class GoForward: public Behavior {

public:
	GoForward(Robot* robot);
	virtual ~GoForward();

	bool startCondition();
	bool stopCondition();
	void action();
};

#endif /* GOFORWARD_H_ */
