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

	float maxBelief = 0.0;
	float totalBelief = 0.0;
	int count = 0;
	vector <Particle> particles_new;
	for (vector<Particle>::iterator curr = _particleArr.begin() ; curr != _particleArr.end() ;++curr) {
		count++;
		curr->update(deltaPosition, laserArr, map);
		if (curr->getBelWeight() > maxBelief) {
			maxBelief = curr->getBelWeight();
		}
		totalBelief+=curr->getBelWeight();

		if (curr->getBelWeight() > WEAK_BELIEF) {
			particles_new.push_back((*curr));
			if ((curr->getBelWeight() > STRONG_BELIEF) && (particles_new.size() < MAX_PARTICLES - (_particleArr.size() - count) - 4))	{
				particles_new.push_back(Particle((*curr)));
				particles_new.push_back(Particle((*curr)));
				particles_new.push_back(Particle((*curr)));
				particles_new.push_back(Particle((*curr)));
			}
		}
	}
	if(particles_new.size() > 0)	{
		_particleArr = particles_new;
	}

	Particle* a;
	// Normalization
/*	for (vector<Particle>::iterator curr = _particleArr.begin() ; curr != _particleArr.end() ;++curr) {
		curr->setBelWeight(curr->getBelWeight()/totalBelief);

		if (curr->getBelWeight() > maxBelief) {
			maxBelief = curr->getBelWeight();
			a = &(*curr);
		}

	}*/
	//cout << endl;
	//cout << "maxBelief : " << maxBelief << endl;
	//cout << "part " << a->getBelPos().x << " " << a->getBelPos().y << " " << a->getBelPos().yaw << endl;
	//vector <Particle> newParticlesVec;

/*	/// RESAMPLE
	int index = static_cast<int>((double)rand()/(RAND_MAX) * (_particleArr.size()));
	double beta = 0.0;
	float totalWX = 0,totalWY = 0,totalX = 0,totalY = 0;
	for(vector<Particle>::iterator curr = _particleArr.begin(); curr != _particleArr.end(); ++curr) {
	    beta += ((double)rand()/(RAND_MAX)) * 2.0 * maxBelief;

	    while(beta > _particleArr[index].getBelWeight()) {
	      beta -= _particleArr[index].getBelWeight();
	      index = (index + 1) % _particleArr.size();
	    }
	    particles_new.push_back(_particleArr[index]);
	    totalWX +=(_particleArr[index].getBelPos().x * _particleArr[index].getBelWeight());
	    totalWY +=(_particleArr[index].getBelPos().y * _particleArr[index].getBelWeight());
	    totalX += _particleArr[index].getBelPos().x;
	    totalY += _particleArr[index].getBelPos().y;
		//cout << "(" << index << ")[" << _particleArr[index].getBelPos().x << "," << _particleArr[index].getBelPos().y << "," << _particleArr[index].getBelPos().yaw << "]";

	}

	for(vector<Particle>::iterator curr = particles_new.begin(); curr != particles_new.end(); ++curr) {

		//cout << "new parts [" << curr->getBelPos().x << "," << curr->getBelPos().y << "," << curr->getBelPos().yaw << "]";

	}
	cout << endl;
	totalWX = floor(totalWX / totalX);
	totalWY = floor(totalWY / totalY);

	totalX = floor(totalX / _particleArr.size());
	totalY = floor(totalY / _particleArr.size());


    cout << "totalXY [" << totalX << "," << totalY << "]";
	//cout << endl;
	_particleArr.clear();
	_particleArr.assign(particles_new.begin(), particles_new.end());*/
}

vector <player_point_2d_t> ParticleManager::getDrawableParticles() {
	vector <player_point_2d_t> particles;

	for(vector<Particle>::iterator pd = _particleArr.begin(); pd != _particleArr.end(); ++pd) {
		player_point_2d_t tmp_pnt;
		tmp_pnt.px = pd->getBelPos().x;
		tmp_pnt.py = pd->getBelPos().y;

		particles.push_back(tmp_pnt);
	}

	return particles;
}

ParticleManager::~ParticleManager() {
}
}
