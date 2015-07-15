/*
 * TurnRight.cpp
 *
 *  Created on: Dec 14, 2014
 *      Author: user
 */

#include "TurnRight.h"

TurnRight::TurnRight(Robot* robot):Behavior(robot) {
}

bool TurnRight::startCondition()
{
/*	if(_robot->isRightFree() && _robot->getObsIndex() > 333) {
		return true;
	}
	else
		return false;*/

	double obs = _robot->getLaser(_robot->getObsIndex());

	// If far away and on the left
	if (obs > 1 && _robot->getObsIndex() > 333) {
		return true;
	// If midway on the left and there is more space on the right
	} else if (obs > 0.5 && _robot->getObsIndex() > 333 && (!_robot->isLeftMoreFree())) {
		return true;
	// If very close on the left and right is free
	} else if (obs < 0.5 && _robot->isRightFree() && _robot->getObsIndex() > 333) {
		return true;
	}

	return false;
}

bool TurnRight::stopCondition()
{
	if(_robot->isForwardFree())
		return true;
	else
		return false;
}

void TurnRight::action()
{
/*	double obs = _robot->getLaser(_robot->getObsIndex());
	if (obs > 1) {
		_robot->setSpeed(0.5, -0.3);
	} else if (obs > 0.6) {
		_robot->setSpeed(0.3, -0.5);
	} else {
		_robot->setSpeed(0.0, -0.7);
	}*/

	double obs = _robot->getLaser(_robot->getObsIndex());
	if (obs > 1) {
		_robot->setSpeed(0.2, dtor(-10));
	} else if (obs > 0.5) {
		_robot->setSpeed(0.1, dtor(-30));
	} else {
		_robot->setSpeed(0.0, dtor(-90));
	}
}

TurnRight::~TurnRight() {
}
