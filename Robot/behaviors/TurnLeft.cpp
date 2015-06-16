/*
 * TurnLeft.cpp
 *
 *  Created on: Jun 14, 2015
 *      Author: colman
 */

#include "TurnLeft.h"

namespace PlayerCc {

TurnLeft::TurnLeft(Robot* robot):Behavior(robot) {
	// TODO Auto-generated constructor stub

}
bool TurnLeft::startCondition()
{
	if(_robot->isLeftFree() )
		return true;
	else
		return false;
}
bool TurnLeft::stopCondition()
{
	if(_robot->isForwardFree())
				return true;
			else
				return false;
}
void TurnLeft::action()
{
	_robot->setSpeed(0.0, -0.3);
}
TurnLeft::~TurnLeft() {
	// TODO Auto-generated destructor stub
}

} /* namespace PlayerCc */
