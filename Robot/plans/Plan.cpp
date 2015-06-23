/*
 * Plan.cpp
 *
 *  Created on: Dec 21, 2014
 *      Author: user
 */

#include "Plan.h"

Plan::Plan(Robot* robot) {
	_robot = robot;
	_behArr = NULL;
	_start = NULL;
}

Behavior* Plan::getStartPoint() {
	return _start;
}

Plan::~Plan() {
}
