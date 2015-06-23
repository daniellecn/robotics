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

Particle::Particle(Particle* parent) {
	_belPos = parent->getBelPos();
	_belWeight = parent->getBelWeight();
	randomize();
}

void Particle::randomize() {

	_belPos.x += ((float(rand()) / float(RAND_MAX)) * MAX_WALK_DIST*2 - MAX_WALK_DIST) ;
	_belPos.y += ((float(rand()) / float(RAND_MAX)) * MAX_WALK_DIST*2 - MAX_WALK_DIST) ;
	_belPos.yaw += (((float(rand()) / float(RAND_MAX)) * MAX_TURN_DIST*2 - MAX_TURN_DIST)) * 0.1 ;

	/*int sign = ((rand() % 2) == 0) ? -1 : 1;
	_belPos.x += (rand() % 5) * sign ;
	_belPos.y += (rand() % 5) * sign;
	_belPos.yaw += ((rand() % 3) * sign * 0.1);*/
}

Position Particle::getBelPos() {
	return _belPos;
}

float Particle::getBelWeight() {
	return _belWeight;
}

void Particle::setBelWeight(float belWeight) {
	_belWeight = belWeight;
}

void Particle::update(Position deltaPos,double* laserArr,Map* map) {
	double dist = sqrt(pow(deltaPos.x,2) + pow(deltaPos.y,2));
	_belPos.x += deltaPos.x;
	_belPos.y += deltaPos.y;
	_belPos.yaw += deltaPos.yaw;

	if ((abs(_belPos.x ) > 6.875) ||
			(abs(_belPos.y ) > 4.75)) {
		_belWeight = 0;
	} else {
		float predBel = _belWeight * probByMovement(deltaPos);
		predBel = predBel * probByMeasurements(laserArr,map);
		//predBel =  predBel * (1.0 + ((1.0 - predBel) / 2.0));
		//cout << "bel " <<  predBel << endl;
		_belWeight =  1.2 * predBel;
	}
	//cout << "bel " << _belWeight << endl;
	// apply the calculated motion
/*	_belPos.yaw += deltaPos.yaw;
	_belPos.x += (cos(_belPos.yaw) * dist);
	_belPos.y += (sin(_belPos.yaw) * dist);*/
}

float Particle::probByMovement(Position deltaPos) {
	double distance;
	distance = sqrt(pow(deltaPos.x,2) + pow(deltaPos.y,2));
	float posiblity;

	// Get positive val of delYaw
	deltaPos.yaw = abs(deltaPos.yaw) ;
	if (distance <= SHORT_DIST && deltaPos.yaw <= SMALL_ANGLE)
		posiblity = 1.0;
	else if (distance <= LONG_DIST && deltaPos.yaw <= BIG_ANGLE)
		posiblity = 0.7;
	else if (distance <= LONG_DIST)
		posiblity = 0.4;
	else if (deltaPos.yaw <= BIG_ANGLE)
		posiblity = 0.5;
	 else
		 posiblity = 0.3;

	return posiblity;
}

float Particle::probByMeasurements(double* laserArr,Map* map) {
	unsigned char C_BLACK = 0;
	unsigned char C_WHITE = 255;
	float hit = 0.0,miss = 0.0;
	int heightIndex,widthIndex;
	cellGrid** grid = map->getGrid();
	cellGrid currCell ;
	Location obsLocation,currLocation;
	for (int i=0; i < LASER_SAMPLES_NUM; i+=10) {
		for (int j=0; j < laserArr[i] ; j ++) {

			currLocation = map->getObstacleLocation(_belPos.x,_belPos.y,_belPos.yaw,laserArr[i],i);
			widthIndex = map->xPosToIndex(currLocation.x * 100);
			heightIndex = map->yPosToIndex(currLocation.y * 100);
			currCell = grid[heightIndex][widthIndex];

			if (currCell.color == C_WHITE) {
				hit++;
			} else {
				miss++;
			}
		}

		if (laserArr[i] < LASER_RANGE_MAX) {
			obsLocation = map->getObstacleLocation(_belPos.x,_belPos.y,_belPos.yaw,laserArr[i],i);
			widthIndex = map->xPosToIndex(obsLocation.x * 100);
			heightIndex = map->yPosToIndex(obsLocation.y * 100);
			currCell = grid[heightIndex][widthIndex];

			if (currCell.color == C_BLACK) {
				hit++;
			} else {
				miss++;
			}
		}
	}

	return (hit / (hit + miss));
}

Particle::~Particle() {
}


} /* namespace PlayerCc */
