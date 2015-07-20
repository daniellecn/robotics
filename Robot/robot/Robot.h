/*
 * Robot.h
 *
 *  Created on: Dec 14, 2014
 *      Author: user
 */

#ifndef ROBOT_H_
#define ROBOT_H_

#include "Laser.h"
#include "../GeneralService.h"
#include "../ConfigurationManager.h"
#include <libplayerc++/playerc++.h>

using namespace PlayerCc;

class Robot {
	PlayerClient* 		_pc;
	Position2dProxy* 	_pp;
	LaserProxy* 		_lp;
	position 			_currPos;
	position 			_lastMoveDelta;
	double 				_laserArr[LASER_SAMPLES_NUM];
	bool 				_addNoise;
	int 				_obsIndex;

	float calcDeltaX();
	float calcDeltaY();
	float calcDeltaYaw();
	float getVisualAngle(float distance,float linearSize);

public:

	Robot(char* ip, int port, position startPos);
	virtual ~Robot();

	int 		getObsIndex();
	double 		getXPos();
	double 		getYPos();
	double 		getYaw();
	double 		getLaser(int index);
	double* 	getLaserArr();
	position 	getCurrPos();
	position 	getLastMoveDelta();
	void 		setAddNoise(bool addNoise);
	void 		setSpeed(float xSpeed, float angularSpeed);

	void 		read();
	void 		calcDeltas() ;
	bool 		isRightFree();
	bool 		isLeftFree();
	bool 		isForwardFree();
	bool 		isLeftMoreFree();
	void 		wander(double *forwardSpeed, double *turnSpeed);
};

#endif /* ROBOT_H_ */
