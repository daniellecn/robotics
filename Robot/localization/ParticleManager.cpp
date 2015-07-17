/*
 * ParticlesManager.cpp
 *
 *  Created on: Jun 13, 2015
 *      Author: colman
 */

#include "ParticleManager.h"

ParticleManager::ParticleManager(Position start) {
	Particle newParticle(start,1.0);
	_particleArr.push_back(newParticle);
}

ParticleManager::ParticleManager() {

	// Fill the map with particles
	for (int i=0;i < MAX_PARTICLES; i++) {
		Position pos;

		// Get random position values
		pos.x = (double)rand()/(RAND_MAX)*(13.75)-(13.75/2);
		pos.y = (double)rand()/(RAND_MAX)*(9.5)-(9.5/2);
		int sign = ((rand() % 2) == 0) ? -1 : 1;
		pos.yaw = (double)rand()/(RAND_MAX)* 2.0 * M_PI * sign;

		Particle newParticle(pos,1.0);
		_particleArr.push_back(newParticle);
	}
}

vector<Particle> ParticleManager::getParticles() {
	return _particleArr;
}

void ParticleManager::update(Position deltaPosition,double* laserArr,Map* map) {

	int count = 0;
	vector <Particle> particles_new;

	for (vector<Particle>::iterator curr = _particleArr.begin(); curr != _particleArr.end(); ++curr) {
		count++;
		curr->update(deltaPosition, laserArr, map);

		// Save the particle if its belief isn't too weak
		if (curr->getBelWeight() > WEAK_BELIEF) {
			particles_new.push_back((*curr));

			// Multiply the particle if its belief is strong and there is enough room
			if ((curr->getBelWeight() > STRONG_BELIEF) &&
				(particles_new.size() < MAX_PARTICLES - (_particleArr.size() - count) - 2))	{
				particles_new.push_back(Particle(&(*curr)));
				particles_new.push_back(Particle(&(*curr)));
			}
		}
	}

	if (particles_new.size() > 0) {
		_particleArr = particles_new;
	}
}

ParticleManager::~ParticleManager() {
}
