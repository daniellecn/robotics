/*
 * TurnRight.h
 *
 *  Created on: Dec 14, 2014
 *      Author: user
 */

#ifndef TURNRIGHT_H_
#define TURNRIGHT_H_

#include "Behavior.h"

class TurnRight: public Behavior {

public:
	TurnRight(Robot* robot);
	virtual ~TurnRight();

	bool startCondition();
	bool stopCondition();
	void action();
};

#endif /* TURNRIGHT_H_ */
