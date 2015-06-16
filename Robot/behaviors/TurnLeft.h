/*
 * TurnLeft.h
 *
 *  Created on: Jun 14, 2015
 *      Author: colman
 */

#ifndef TURNLEFT_H_
#define TURNLEFT_H_
#include "Behavior.h"
namespace PlayerCc {

class TurnLeft : public Behavior {
public:
	TurnLeft(Robot* robot);
	bool startCondition();
	bool stopCondition();
	void action();
	virtual ~TurnLeft();
};

} /* namespace PlayerCc */

#endif /* TURNLEFT_H_ */
