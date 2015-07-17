/*
 * Behavior.h
 *
 *  Created on: Dec 14, 2014
 *      Author: user
 */

#ifndef BEHAVIOR_H_
#define BEHAVIOR_H_

#include "../Robot.h"

using namespace std;

class Behavior {

	Behavior** 	_behArr;
	int 		_size;

protected:
	Robot* _robot;

public:

	Behavior(Robot* robot);
	virtual ~Behavior();

	virtual bool startCondition() 	= 0;
	virtual bool stopCondition() 	= 0;
	virtual void action() 			= 0;
	virtual void print() 			= 0;

	void 		addNext(Behavior* next);
	Behavior* 	selectNext();
};

#endif /* BEHAVIOR_H_ */
