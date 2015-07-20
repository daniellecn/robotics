/*
 * ParticleManager.h
 *
 *  Created on: Jun 13, 2015
 *      Author: colman
 */

#ifndef PARTICLEMANAGER_H_
#define PARTICLEMANAGER_H_

#include "../GeneralService.h"
#include "Particle.h"
#include <vector>

class ParticleManager {

	vector <Particle> 	_particleArr;
	Particle			_avgParticle;
public:

	ParticleManager(float mapWidth,float mapHeight);
	ParticleManager(position start);
	virtual ~ParticleManager();

	Particle			getAvgParticle();
	vector <Particle> 	getParticles();
	void 			  	update(position deltaPosition,double* laserArr,Map* map);
};

#endif /* PARTICLEMANAGER_H_ */
