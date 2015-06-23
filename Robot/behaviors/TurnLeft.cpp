/*
 * TurnLeft.cpp
 *
 *  Created on: Jun 14, 2015
 *      Author: colman
 */

#include "TurnLeft.h"

TurnLeft::TurnLeft(Robot* robot):Behavior(robot) {
}

bool TurnLeft::startCondition()
{
	// && _robot->isLeftMoreFree()
	if(_robot->isLeftFree())
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
	_robot->setSpeed(0.2, -0.3);
}

TurnLeft::~TurnLeft() {
}
