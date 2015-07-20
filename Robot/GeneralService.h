/*
 * GeneralService.h
 *
 *  Created on: Jun 23, 2015
 *      Author: colman
 */

#ifndef GENERALSERVICE_H_
#define GENERALSERVICE_H_

#include <string>
#include <math.h>
#include <iostream>

using namespace std;

struct location {
	int x;
	int y;
};

struct locationF {
	float x;
	float y;
};

struct position {
	float x;
	float y;
	float yaw;
};

struct robotSize{
	int width;
	int height;
};

struct cellGrid{
	unsigned char color;
	int g;
	int h;
	int f = 0;
	int expandOrder;
	bool closed;
	int dirArrival;
};

struct Acell{
	//cellGrid cell;
	int g;
	int f;
	int dirArrival;
	location currLoc;
};

struct wayPoint{
	location pointLoc;
	int dirArrival;
};

class GeneralService {
public:
	// Parameters names
	static const string P_MAP_PATH;
	static const string P_START_LOCATION;
	static const string P_GOAL;
	static const string P_ROBOT_SIZE;
	static const string P_MAP_RESOLUTION;
	static const string P_GRID_RESOLUTION;

	// PNG Names
	static const char* PNG_GRID;
	static const char* PNG_BLOW_MAP;
	static const char* PNG_BLOW_GRID;

	// Colors
	static const unsigned char C_BLACK;
	static const unsigned char C_GRAY;
	static const unsigned char C_GREEN;
	static const unsigned char C_WHITE;
	static const unsigned char C_PURPLE;
	static const unsigned char C_RED;
	static const unsigned char C_BLUE;
	static const unsigned char C_ORANGE;

	// Priorities
	static const int P_BLACK;
	static const int P_GRAY;
	static const int P_WHITE;

	// Real Robot
	static const float STOP_MOVE_SPEED;
	static const float MIDDLE_MOVE_SPEED;
	static const float SLOW_MOVE_SPEED;

	static const float STOP_TURN_ANGLE;
	static const float SLOW_TURN_ANGLE;
	static const float MIDDLE_TURN_ANGLE;
	static const float FAST_TURN_ANGLE;
	static const float FULL_TURN_ANGLE;

	static const float TURN_AND_MOVE_OBSTACLE_RANGE;
	static const float TURN_ONLY_OBSTACLE_RANGE;

	// Particles
	static const float MAX_WALK_DISTRIBUTION;
	static const float MAX_TURN_DISTRIBUTION;
	static const float BIG_ANGLE;
	static const float SMALL_ANGLE;
	static const float SHORT_DIST;
	static const float LONG_DIST;
	static const float NORMALIZE_FACTOR;
	static const int   PARTICLE_LASER_READ_JUMP;

	// Particle Manager
	static const int   MAX_PARTICLES;
	static const float STRONG_BELIEF;
	static const float WEAK_BELIEF;

	// Robot
	static const int 	OBSTABLE_LASER_READ_JUMP;
	static const float 	OBSTABLE_MIN_DIST;
	static const float 	FREE_SIDE_DIST;
	static const float 	MAX_WALK_DIST;
	static const float 	MAX_TURN_DIST;
};

#endif /* GENERALSERVICE_H_ */
