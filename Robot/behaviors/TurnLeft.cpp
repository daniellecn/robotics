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
	if (_robot->getObsIndex() < LASER_MIDDLE_INDEX && _robot->isLeftFree()) {
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
	double obs = _robot->getLaser(_robot->getObsIndex());

	if (obs > GeneralService::TURN_AND_MOVE_OBSTACLE_RANGE) {
		_robot->setSpeed(GeneralService::MIDDLE_MOVE_SPEED, dtor(GeneralService::SLOW_TURN_ANGLE));
	}
	else if (obs > GeneralService::TURN_ONLY_OBSTACLE_RANGE) {
		_robot->setSpeed(GeneralService::SLOW_MOVE_SPEED, dtor(GeneralService::MIDDLE_TURN_ANGLE));
	}
	else {
		_robot->setSpeed(GeneralService::STOP_MOVE_SPEED, dtor(GeneralService::FAST_TURN_ANGLE));
	}
}

void TurnLeft::print()
{
	cout << "Going Left" << endl;
}

TurnLeft::~TurnLeft() {
}
