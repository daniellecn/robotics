/*
 * Robot.h
 *
 *  Created on: Dec 14, 2014
 *      Author: user
 */

#ifndef ROBOT_H_
#define ROBOT_H_

#include "Laser.h"
#include <iostream>
#include <libplayerc++/playerc++.h>
#include "GeneralService.h"
#include <stdlib.h>
using namespace std;

using namespace PlayerCc;

class Robot {
	PlayerClient* 		_pc;
	Position2dProxy* 	_pp;
	LaserProxy* 		_lp;
	Position 			_currPos;
	Position 			_lastMoveDelta;
	double 				_laserArr[LASER_SAMPLES_NUM];
	bool 				_addNoise;
	int 				_obsIndex;

	static const int 	LASER_READ_JUMP 	= 1;
	static const int   	FORWARD_LASER_INDEX = 333;
	static const float 	OBSTABLE_MIN_DIST 	= 1.5;
	static const float 	X_SIZE_METER 		= 0.35;
	static const float 	Y_SIZE_METER 		= 0.45;
	static const float 	MAX_WALK_DIST 		= 0.01;
	static const float 	MAX_TURN_DIST 		= 0.01;

	float calcDeltaX();
	float calcDeltaY();
	float calcDeltaYaw();
	float getVisualAngle(float distance,float linearSize);

public:

	Robot(char* ip, int port, Position startPos);
	virtual ~Robot();

	int 		getObsIndex();
	double 		getXPos();
	double 		getYPos();
	double 		getYaw();
	double 		getLaser(int index);
	double* 	getLaserArr();
	Position 	getCurrPos();
	Position 	getLastMoveDelta();
	void 		setAddNoise(bool addNoise);
	void 		setSpeed(float xSpeed, float angularSpeed);

	void 		calcDeltas() ;
	void 		wander(double *forwardSpeed, double *turnSpeed);
	void 		read();
	bool 		isRightFree();
	bool 		isLeftFree();
	bool 		isForwardFree();
	bool 		isLeftMoreFree();
};

#endif /* ROBOT_H_ */
