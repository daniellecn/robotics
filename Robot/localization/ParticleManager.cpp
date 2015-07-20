/*
 * ParticlesManager.cpp
 *
 *  Created on: Jun 13, 2015
 *      Author: colman
 */

#include "ParticleManager.h"

ParticleManager::ParticleManager(position start) {
	Particle newParticle(start,1.0);
	_particleArr.push_back(newParticle);
	_avgParticle = newParticle;
}

ParticleManager::ParticleManager(float mapWidth,float mapHeight) {

	// Fill the map with particles
	for (int i=0;i < GeneralService::MAX_PARTICLES; i++) {
		position pos;

		// Get random position values
		pos.x = (double)rand()/(RAND_MAX)*(mapWidth)-(mapWidth/2);
		pos.y = (double)rand()/(RAND_MAX)*(mapHeight)-(mapHeight/2);
		int sign = ((rand() % 2) == 0) ? -1 : 1;
		pos.yaw = (double)rand()/(RAND_MAX)* 2.0 * M_PI * sign;

		Particle newParticle(pos,1.0);
		_particleArr.push_back(newParticle);
	}
}

vector<Particle> ParticleManager::getParticles() {
	return _particleArr;
}

void ParticleManager::update(position deltaPosition,double* laserArr,Map* map) {
	vector <Particle> particles_new;
	position avgPos = {0,0,0};
	int count = 0;
	float avgWeight = 0;

	for (vector<Particle>::iterator curr = _particleArr.begin(); curr != _particleArr.end(); ++curr) {
		count++;

		// Update belief of this particle according to the map and movement
		curr->update(deltaPosition, laserArr, map);

		// Save the particle if its belief isn't too weak
		if (curr->getBelWeight() > GeneralService::WEAK_BELIEF) {
			particles_new.push_back((*curr));

			// Multiply the particle if its belief is strong and there is enough room
			if ((curr->getBelWeight() > GeneralService::STRONG_BELIEF) &&
				(particles_new.size() < GeneralService::MAX_PARTICLES - (_particleArr.size() - count) - 2))	{
				particles_new.push_back(Particle(&(*curr)));
				particles_new.push_back(Particle(&(*curr)));
			}
		}
	}

	if (particles_new.size() > 0) {
		// Switch to new particles
		_particleArr = particles_new;

		// Calculate new average that will be the current location
		for (vector<Particle>::iterator curr = _particleArr.begin(); curr != _particleArr.end(); ++curr) {
			avgPos.x+=curr->getBelPos().x;
			avgPos.y+=curr->getBelPos().y;
			avgPos.yaw+=curr->getBelPos().yaw;
			avgWeight+=curr->getBelWeight();
		}

		avgPos.x /= (_particleArr.size() * 1.0);
		avgPos.y /= (_particleArr.size() * 1.0);
		avgPos.yaw /= (_particleArr.size() * 1.0);
		avgWeight /= (_particleArr.size() * 1.0);

		Particle a(avgPos,avgWeight);
		_avgParticle = a;
	}
}

Particle ParticleManager::getAvgParticle() {
	return _avgParticle;
}

ParticleManager::~ParticleManager() {
}
