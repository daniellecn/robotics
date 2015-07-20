/*
 * Behavior.cpp
 *
 *  Created on: Dec 14, 2014
 *      Author: user
 */

#include "Behavior.h"

Behavior::Behavior(Robot* robot) {
	_robot = robot;
	_behArr = NULL;
	_size = 0;
}

void Behavior::addNext(Behavior* beh)
{
	int i;
	Behavior** tmp = new Behavior*[_size+1];
	for(i=0;i<_size;i++)
		tmp[i] = _behArr[i];
	tmp[i] = beh;

	delete [] _behArr;

	_behArr=tmp;
	_size++;
}

Behavior* Behavior::selectNext()
{
	int i;
	for(i=0;i<_size;i++)
		if(_behArr[i]->startCondition())
			return _behArr[i];

	return NULL;
}

Behavior::~Behavior() {
}
