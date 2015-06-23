/*
 * Particle.h
 *
 *  Created on: Jun 13, 2015
 *      Author: colman
 */

#ifndef PARTICLE_H_
#define PARTICLE_H_

#include <stdlib.h>
#include <math.h>
#include <iostream>
#include "../Position.h"
#include "../Location.h"
#include "../Laser.h"
#include "../Map.h"
#include <libplayerc++/playerc++.h>
using namespace std;
namespace PlayerCc {

class Particle {


	Position 	_belPos;
	float  		_belWeight;

	static const float MAX_WALK_DIST 	= 1.0;
	static const float MAX_TURN_DIST 	= 1.0;
	static const float BIG_ANGLE 		= 3.0;
	static const float SMALL_ANGLE 		= 0.5;
	static const float SHORT_DIST 		= 0.5;
	static const float LONG_DIST 		= 2;

public:
	Particle();
	Particle(Particle* parent);
	Particle(Position belPos, float belWeight);
	virtual ~Particle();

	void setBelWeight(float belWeight);
	Position getBelPos();
	float 	 getBelWeight();

	void 	update(Position deltaPos,double* laserArr,Map* map);
	void 	randomize();
	float 	probByMovement(Position deltaPos);
	float 	probByMeasurements(double* laserArr,Map* map);
};

}

#endif /* PARTICLE_H_ */
