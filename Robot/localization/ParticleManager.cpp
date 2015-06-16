/*
 * ParticlesManager.cpp
 *
 *  Created on: Jun 13, 2015
 *      Author: colman
 */

#include "ParticleManager.h"

namespace PlayerCc {

ParticleManager::ParticleManager() {

	for (int i=0;i < MAX_PARTICLES; i++) {
		Position pos;
		pos.x = (double)rand()/(RAND_MAX)*(MAP_HEIGHT)-(MAP_HEIGHT/2);
		pos.y = (double)rand()/(RAND_MAX)*(MAP_WIDTH)-(MAP_WIDTH/2);
		pos.yaw = (double)rand()/(RAND_MAX)* 2.0 * M_PI;

		Particle newParticle(pos,0);
		_particleArr.push_back(newParticle);
	}
}

ParticleManager::ParticleManager(Position robotStartPos) {
	Particle newParticle(robotStartPos,1);

	_particleArr.push_back(newParticle);
}

vector<Particle> ParticleManager::getParticles() {
	return _particleArr;
}

void ParticleManager::update(Position deltaPosition,double* laserArr) {
	int pIndex = 0;
	int strongestId = NULL;
	float strongestVal = 0.0;
	int partCounter = 0;

	vector <Particle> newParticlesVec;

	for (vector<Particle>::iterator curr = _particleArr.begin() ; curr != _particleArr.end() ;++curr) {

		partCounter++;

		curr->update(deltaPosition, laserArr);

		// Saving the strongest particle so we can print it later
		if (curr->getBelWeight() > strongestVal) {
			strongestVal = curr->getBelWeight();
			strongestId = pIndex;
		}
/*		// not keeping weak beliefs
		if (curr->getBelWeight() > WEAK_BELIEF) {

			newParticlesVec.push_back(*curr);
			pIndex++;

			// Saving the strongest particle so we can print it later
			if (curr->getBelWeight() > strongestVal) {
				strongestVal = curr->getBelWeight();
				strongestId = pIndex;
			}

			// strong beliefs are to be evolved
			if ((curr->getBelWeight() > STRONG_BELIEF) && (newParticlesVec.size() < MAX_PARTICLES - (_particleArr.size() - partCounter) - 2))	{

				Particle childP(curr->getBelPos(),curr->getBelWeight());
				childP.randomize();
				newParticlesVec.push_back(childP);

				Particle childP2(curr->getBelPos(),curr->getBelWeight());
				childP2.randomize();
				newParticlesVec.push_back(childP2);

				pIndex = pIndex + 2;
			}
		}*/
	}

	/// RESAMPLE
	int index = static_cast<int>((double)rand()/(RAND_MAX) * (_particleArr.size()));
	double beta = 0.0;
	vector<Particle> particles_new;

	for(vector<Particle>::iterator curr = _particleArr.begin(); curr != _particleArr.end(); ++curr) {
	    beta += ((double)rand()/(RAND_MAX)) * 2.0 * strongestVal;

	    while(beta > _particleArr[index].getBelWeight()) {
	      beta -= _particleArr[index].getBelWeight();
	      index = (index + 1) % _particleArr.size();
	    }
	    particles_new.push_back(_particleArr[index]);
	}
	_particleArr.clear();
	_particleArr.assign(particles_new.begin(), particles_new.end());
}

int ParticleManager::returnCellColInMapByXPos(float x){
	return (((int)x)/MAP_RESOLUTION + MAP_WIDTH/2) < 0 ? (- ((((int)x)/MAP_RESOLUTION + MAP_WIDTH/2))) : (((int)x)/MAP_RESOLUTION + MAP_WIDTH/2);
}

int ParticleManager::returnCellRowInMapByYPos(float y){
	return (MAP_HEIGHT/2 - ((int)y)/MAP_RESOLUTION ) < 0 ? -((MAP_HEIGHT/2 - ((int)y))) : (MAP_HEIGHT/2 - ((int)y)/MAP_RESOLUTION) ;
}

vector <player_point_2d_t> ParticleManager::getDrawableParticles() {
	vector <player_point_2d_t> particles;

	for(vector<Particle>::iterator pd = _particleArr.begin(); pd != _particleArr.end(); ++pd) {
		player_point_2d_t tmp_pnt;
		//tmp_pnt.px = returnCellColInMapByXPos(pd->getBelPos().x);
		//tmp_pnt.py = returnCellRowInMapByYPos(pd->getBelPos().y);
		tmp_pnt.px = pd->getBelPos().x;
		tmp_pnt.py = pd->getBelPos().y;

		particles.push_back(tmp_pnt);
	}

	return particles;
}

ParticleManager::~ParticleManager() {
}
}
