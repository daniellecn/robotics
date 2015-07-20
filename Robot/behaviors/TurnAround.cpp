/*
 * TurnAround.cpp
 *
 *  Created on: Jun 20, 2015
 *      Author: colman
 */

#include "TurnAround.h"

TurnAround::TurnAround(Robot* robot):Behavior(robot) {
}

bool TurnAround::startCondition()
{
	if((!(_robot->getObsIndex() > LASER_MIDDLE_INDEX && _robot->isRightFree())) &&
	   (!(_robot->getObsIndex() < LASER_MIDDLE_INDEX && _robot->isLeftFree())) &&
	   (!_robot->isForwardFree()))
		return true;
	else
		return false;
}

bool TurnAround::stopCondition()
{
	if(_robot->isForwardFree())
		return true;
	else
		return false;
}

void TurnAround::action()
{
	_robot->setSpeed(GeneralService::STOP_MOVE_SPEED, dtor(GeneralService::FULL_TURN_ANGLE));
}

void TurnAround::print()
{
	cout << "Turn Around" << endl;
}

TurnAround::~TurnAround() {
}
