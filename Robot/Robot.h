/*
 * Robot.h
 *
 *  Created on: Dec 14, 2014
 *      Author: user
 */

#ifndef ROBOT_H_
#define ROBOT_H_

#include "Location.h"
#include "Position.h"
#include "Laser.h"
#include <iostream>

#include <libplayerc++/playerc++.h>
using namespace std;

using namespace PlayerCc;

class Robot {
	PlayerClient* _pc;
	Position2dProxy* _pp;
	LaserProxy* _lp;
	Graphics2dProxy* _gp;

	Position _currPos;
	Position _lastMoveDelta;

	double _laserArr[LASER_SAMPLES_NUM];
	bool _addNoise;

	static const float OBSTABLE_MIN_DIST 	= 0.6;
	static const int   FORWARD_LASER_INDEX 	= 333;
	static const float   X_SIZE_METER 		= 0.35;
	static const float   Y_SIZE_METER 		= 0.45;
	static const int 	LASER_READ_JUMP = 1;

	float calcDeltaX();
	float calcDeltaY();
	float calcDeltaYaw();
public:
	//Robot(char* ip, int port);
	Robot(char* ip, int port,Position startPos);
	virtual ~Robot();

	double getXPos();
	double getYPos();
	double getYaw();
	void calcDeltas() ;
	Position getLastMoveDelta();
	Position getCurrPos();
	double getLaser(int index);
	double* getLaserArr();

	void setAddNoise(bool addNoise);

	void setSpeed(float xSpeed, float angularSpeed);

	float getVisualAngle(float distance,float linearSize);
	void wander(double *forwardSpeed, double *turnSpeed);
	void draw(player_color_t color,player_point_2d_t points[],int count);
	void read();
	bool isRightFree();
	bool isLeftFree();
	bool isForwardFree();
	bool isLeftMoreFree();
	Location getObstacleLocation(double distanceFromObs,int sensorIndex);

};

#endif /* ROBOT_H_ */
