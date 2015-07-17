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
	double obs = _robot->getLaser(_robot->getObsIndex());

	// If far away and on the right
	if (obs > 1 && _robot->getObsIndex() < 333) {
		return true;
	// If midway on the right and there is more space on the left
	} else if (obs > 0.5 && _robot->getObsIndex() < 333 && (_robot->isLeftMoreFree())) {
		return true;
	// If very close on the right and left is free
	} else if (obs < 0.5 && _robot->isLeftFree() && _robot->getObsIndex() < 333) {
		return true;
	}

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
/*	double obs = _robot->getLaser(_robot->getObsIndex());
	if (obs > 1) {
		_robot->setSpeed(0.5, dtor(40));
	} else if (obs > 0.5) {
		_robot->setSpeed(0.3, dtor(60));
	} else {
		_robot->setSpeed(0.0, dtor(90));
	}*/

	double obs = _robot->getLaser(_robot->getObsIndex());

	if (obs > 1) {
		_robot->setSpeed(0.2, dtor(10));
	} else if (obs > 0.5) {
		_robot->setSpeed(0.1, dtor(30));
	} else {
		_robot->setSpeed(0.0, dtor(90));
	}
}

TurnLeft::~TurnLeft() {
}
