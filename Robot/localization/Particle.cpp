/*
 * Particle.cpp
 *
 *  Created on: Jun 13, 2015
 *      Author: colman
 */

#include "Particle.h"

Particle::Particle() {
	_belPos.x = 0;
	_belPos.y = 0;
	_belPos.yaw = 0;
	_gen = 0;
	_belWeight = 1;
}

Particle::Particle(Position belPos, float belWeight) {
	_belPos = belPos;
	_belWeight = belWeight;
	_gen = 0;
}

Particle::Particle(Particle* parent) {
	_belPos = parent->getBelPos();
	_belWeight = parent->getBelWeight();
	_gen = parent->getGeneration() + 1;
	randomize();
}

int Particle::getGeneration() {
	return _gen;
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

void Particle::randomize() {

	float randX = ((float(rand()) / float(RAND_MAX)) * MAX_WALK_DIST*2 - MAX_WALK_DIST);
	_belPos.x +=  randX;
	float randY = ((float(rand()) / float(RAND_MAX)) * MAX_WALK_DIST*2 - MAX_WALK_DIST);
	_belPos.y += randY;
	float randYaw = (((float(rand()) / float(RAND_MAX)) * MAX_TURN_DIST*2 - MAX_TURN_DIST)) * 0.1;
	_belPos.yaw +=  randYaw;
}

void Particle::update(Position deltaPos,double* laserArr,Map* map) {
	double dist = sqrt(pow(deltaPos.x,2) + pow(deltaPos.y,2));

	// apply the calculated motion
	_belPos.yaw += deltaPos.yaw;
	_belPos.x += (cos(_belPos.yaw) * dist);
	_belPos.y += (sin(_belPos.yaw) * dist);

	// If it reached out of the map there it has slim chances of being right
	if ((abs(_belPos.x ) > 6.875) || (abs(_belPos.y ) > 4.75)) {
		_belWeight = _belWeight * 0.001;
	// Calculate probability by other factors
	} else {
		float predBel = _belWeight * probByMovement(deltaPos);
		predBel *= probByMeasurements(laserArr,map);
		_belWeight =  NORMALIZE_FACTOR * predBel;

		if (_belWeight > 1) {
			_belWeight = 1;
		}
	}
}

float Particle::probByMovement(Position deltaPos) {
	double distance = sqrt(pow(deltaPos.x,2) + pow(deltaPos.y,2));
	double yaw = abs(deltaPos.yaw);
	float posiblity;

	if (distance <= SHORT_DIST && yaw <= SMALL_ANGLE) {
		posiblity = 1.0;
	}
	else if (distance >= LONG_DIST && yaw >= BIG_ANGLE) {
		posiblity = 0.7;
	}
	else if (distance >= SHORT_DIST && yaw >= BIG_ANGLE) {
		posiblity = 0.8;
	} else {
		posiblity = 0.9;
	}

	return posiblity;
}

float Particle::probByMeasurements(double* laserArr,Map* map) {
	unsigned char C_BLACK = 0;
	unsigned char C_WHITE = 255;

	float hit = 0.0,miss = 0.0;
	int heightIndex,widthIndex;
	unsigned char currCell ;
	Location obsLocation,currLocation;

	for (int i=0; i < LASER_SAMPLES_NUM; i+=LASER_READ_JUMP) {

		// Check space between obstacle
		for (int j=0; j < laserArr[i] ; j++) {

			// Check if the space the laser read as open is also open on the map
			// considering the believed place of the robot is this particle
			currLocation = relativeObjectLocation(_belPos.x,_belPos.y,_belPos.yaw,j,i);
			widthIndex = map->xPosToIndexLocal(currLocation.x * 100);
			heightIndex = map->yPosToIndexLocal(currLocation.y * 100);
			currCell = map->getGrid()[heightIndex][widthIndex].color;

			if (currCell == C_WHITE) {
				hit++;
			} else {
				miss++;
			}
		}

		// Check if laser found obstacle
		if (laserArr[i] < LASER_RANGE_MAX) {

			// Check if the obstacle the laser found is also on the map
			// considering the believed place of the robot is this particle
			obsLocation = relativeObjectLocation(_belPos.x,_belPos.y,_belPos.yaw,laserArr[i],i);
			widthIndex = map->xPosToIndexLocal(obsLocation.x * 100);
			heightIndex = map->yPosToIndexLocal(obsLocation.y * 100);
			currCell = map->getGrid()[heightIndex][widthIndex].color;

			if (currCell == C_BLACK) {
				hit++;
			} else {
				miss++;
			}
		}
	}

	return (hit / (hit + miss));
}

Location Particle::relativeObjectLocation(float x,float y,float yaw,double distanceFromObj,int sensorIndex) {
	Location objLocation;

	objLocation.x = x + distanceFromObj*cos(yaw + LASER_INDEX_TO_ANGLE_RAD(sensorIndex));
	objLocation.y = y + distanceFromObj*sin(yaw + LASER_INDEX_TO_ANGLE_RAD(sensorIndex));

	return objLocation;
}

Particle::~Particle() {
}


