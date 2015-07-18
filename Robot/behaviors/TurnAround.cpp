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
	if((!(_robot->getObsIndex() > 333 && _robot->isRightFree())) &&
	   (!(_robot->getObsIndex() < 333 && _robot->isLeftFree())) &&
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
	_robot->setSpeed(0.0, 2.0);
}

void TurnAround::print()
{
	cout << "Turn Around" << endl;
}

TurnAround::~TurnAround() {
}
