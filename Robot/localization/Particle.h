/*
 * Particle.h
 *
 *  Created on: Jun 13, 2015
 *      Author: colman
 */

#ifndef PARTICLE_H_
#define PARTICLE_H_

#include "../GeneralService.h"
#include "../Laser.h"
#include "../Map.h"

class Particle {

	position 	_belPos;
	float  		_belWeight;
	int 		_gen;

	float 		probByMovement(position deltaPos);
	float 		probByMeasurements(double* laserArr,Map* map);
	void 		randomize();
	locationF 	relativeObjectLocation(float x,float y,float yaw,double distanceFromObj,int sensorIndex);

public:

	Particle();
	Particle(Particle* parent);
	Particle(position belPos, float belWeight);
	virtual ~Particle();

	void 		setBelWeight(float belWeight);
	position 	getBelPos();
	float 	 	getBelWeight();
	int 		getGeneration();

	void 		update(position deltaPos,double* laserArr,Map* map);
};

#endif /* PARTICLE_H_ */
