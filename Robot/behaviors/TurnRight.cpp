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
	if(_robot->isRightFree() && _robot->getObsIndex() > MIDDLE_LASER_INDEX) {
		return true;
	}
	else
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
	double obs = _robot->getLaser(_robot->getObsIndex());

	if (obs >  GeneralService::TURN_AND_MOVE_OBSTACLE_RANGE) {
		_robot->setSpeed(GeneralService::MIDDLE_MOVE_SPEED, dtor(-GeneralService::SLOW_TURN_ANGLE));
	}
	else if (obs > GeneralService::TURN_ONLY_OBSTACLE_RANGE) {
		_robot->setSpeed(GeneralService::SLOW_MOVE_SPEED, dtor(-GeneralService::MIDDLE_TURN_ANGLE));
	}
	else {
		_robot->setSpeed(GeneralService::STOP_MOVE_SPEED, dtor(-GeneralService::FAST_TURN_ANGLE));
	}
}

void TurnRight::print()
{
	cout << "Going Right" << endl;
}

TurnRight::~TurnRight() {
}
