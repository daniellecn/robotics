/*
 * ParticleManager.h
 *
 *  Created on: Jun 13, 2015
 *      Author: colman
 */

#ifndef PARTICLEMANAGER_H_
#define PARTICLEMANAGER_H_

#include "Particle.h"
#include <vector>
#include <iostream>
#include <libplayerc++/playerc++.h>

using namespace std;

class ParticleManager {
	static const int 	MAX_PARTICLES 	= 100;
	static const float 	STRONG_BELIEF 	= 0.7;
	static const float 	WEAK_BELIEF 	= 0.3;

	vector <Particle> _particleArr;
	Particle	_avgParticle;
public:

	ParticleManager();
	ParticleManager(Position start);
	virtual ~ParticleManager();

	Particle	getAvgParticle();
	vector <Particle> getParticles();
	void 			  update(Position deltaPosition,double* laserArr,Map* map);
};

#endif /* PARTICLEMANAGER_H_ */
