/*
 * Particle.cpp
 *
 *  Created on: Jun 13, 2015
 *      Author: colman
 */

#include "Particle.h"

namespace PlayerCc {

Particle::Particle() {
	_belPos.x = 0;
	_belPos.y = 0;
	_belPos.yaw = 0;
	_belWeight = 1;
}

Particle::Particle(Position belPos, float belWeight) {
	_belPos = belPos;
	_belWeight = belWeight;
}

void Particle::randomize() {
	_belPos.x += ((float(rand()) / float(RAND_MAX)) * MAX_WALK_DIST*2 - MAX_WALK_DIST) ;
	_belPos.y += ((float(rand()) / float(RAND_MAX)) * MAX_WALK_DIST*2 - MAX_WALK_DIST) ;
	_belPos.yaw += (((float(rand()) / float(RAND_MAX)) * MAX_TURN_DIST*2 - MAX_TURN_DIST)) * 0.1 ;
}

Position Particle::getBelPos() {
	return _belPos;
}

float Particle::getBelWeight() {
	return _belWeight;
}

void Particle::update(Position deltaPos,double* laserArr) {
	_belPos.x += deltaPos.x;
	_belPos.y += deltaPos.y;
	_belPos.yaw += deltaPos.yaw;

	float predBel = _belWeight * probByMovement(deltaPos);
	predBel = predBel * probByMeasurements(laserArr);
	predBel =  predBel * (1.0 + ((1.0 - predBel) / 2.0));
	_belWeight = predBel;
}

float Particle::probByMovement(Position deltaPos) {
	double distance;
	distance = sqrt(pow(deltaPos.x,2) + pow(deltaPos.y,2));
	float probByDist;
	float probByAngle;

	if (distance <= SHORT_DIST)
		probByDist = 1.0;
	else if (distance <= LONG_DIST)
		probByDist = 1.0 - (distance/SHORT_DIST) * 0.05;
	 else
		 probByDist = 0.3;

	// Get positive val of delYaw
	deltaPos.yaw = deltaPos.yaw > 0 ? deltaPos.yaw : deltaPos.yaw * (-1);

	if (deltaPos.yaw <= SMALL_ANGLE)
		probByAngle = 1.0;
	else if (deltaPos.yaw <= BIG_ANGLE)
		probByAngle = 1.0 - (deltaPos.yaw/SMALL_ANGLE) * 0.1;
	else
		probByAngle = 0.3;

	return (probByAngle + probByDist) / 2.0;
}

float Particle::probByMeasurements(double* laserArr) {

	int hit = 0,miss=0;
	for (int i=0; i < LASER_SAMPLES_NUM; i++) {

		if (laserArr[i] < LONG_DIST) {
			Location obsLocation;
			obsLocation.x =
					_belPos.x + laserArr[i]*cos(_belPos.yaw + LASER_INDEX_TO_ANGLE_DEG(i));
			obsLocation.y =
					_belPos.y  + laserArr[i]*sin(_belPos.yaw + LASER_INDEX_TO_ANGLE_DEG(i));

			//cout << mp->GetWidth() << endl;
			//int8_t aMap[mp->GetWidth()*mp->GetHeight()];
			//mp->GetMap(aMap);
			//int index = mp->GetCellIndex(obsLocation.x,obsLocation.y);

			//(obsLocation.y*mp->GetWidth() + obsLocation.x)
			//int a = (int)aMap[];
/*			cout << a << endl;

			if (a == 1) {
				hit++;
			} else {
				miss++;
			}*/
		}
	}

	return ((float)(hit)/(miss + hit));
}


Particle::~Particle() {
}

} /* namespace PlayerCc */
