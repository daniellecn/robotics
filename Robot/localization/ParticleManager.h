/*
 * ParticleManager.h
 *
 *  Created on: Jun 13, 2015
 *      Author: colman
 */

#ifndef PARTICLEMANAGER_H_
#define PARTICLEMANAGER_H_

#include <vector>
#include <iostream>

#include "Particle.h"
#include <libplayerc++/playerc++.h>
using namespace std;

namespace PlayerCc {

class ParticleManager {
	static const int 	MAX_PARTICLES 	= 1000;
	static const float 	STRONG_BELIEF 	= 0.7;
	static const float 	WEAK_BELIEF 	= 0.3;

	// MAP.H
	static const int 	MAP_HEIGHT 		= 18;
	static const int 	MAP_WIDTH 		= 40;
	static const float  MAP_RESOLUTION = 0.02;

	vector <Particle> _particleArr;

public:

	ParticleManager();
	ParticleManager(Position robotStartPos);
	virtual ~ParticleManager();

	vector <Particle> getParticles();
	vector <player_point_2d_t> getDrawableParticles();

	void update(Position deltaPosition,double* laserArr);

	// MAP.H
    int returnCellColInMapByXPos(float x);
    int returnCellRowInMapByYPos(float y);
};
}

#endif /* PARTICLEMANAGER_H_ */
