/*
 * Particle.h
 *
 *  Created on: Jun 13, 2015
 *      Author: colman
 */

#ifndef PARTICLE_H_
#define PARTICLE_H_

#include "../Position.h"
#include "../Location.h"
#include "../Laser.h"
#include "../Map.h"
#include <libplayerc++/playerc++.h>
#include <stdlib.h>
#include <math.h>
#include <iostream>

using namespace std;

class Particle {

	Position 	_belPos;
	float  		_belWeight;
	int 		_gen;

	static const float MAX_WALK_DIST 	= 0.5;
	static const float MAX_TURN_DIST 	= 0.3;
	static const float BIG_ANGLE 		= 0.5;
	static const float SMALL_ANGLE 		= 0.1;
	static const float SHORT_DIST 		= 0.2;
	static const float LONG_DIST 		= 0.7;
	static const float NORMALIZE_FACTOR = 1.2;
	static const int   LASER_READ_JUMP  = 10;

	float 	probByMovement(Position deltaPos);
	float 	probByMeasurements(double* laserArr,Map* map);
	void 	randomize();

public:

	Particle();
	Particle(Particle* parent);
	Particle(Position belPos, float belWeight);
	virtual ~Particle();

	void 		setBelWeight(float belWeight);
	Position 	getBelPos();
	float 	 	getBelWeight();
	int 		getGeneration();

	void 		update(Position deltaPos,double* laserArr,Map* map);
	Location 	relativeObjectLocation(float x,float y,float yaw,double distanceFromObj,int sensorIndex);
};

#endif /* PARTICLE_H_ */
