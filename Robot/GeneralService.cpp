/*
 * GeneralService.cpp
 *
 *  Created on: Jun 23, 2015
 *      Author: colman
 */

#include "GeneralService.h"

// Parameters name
const string GeneralService::P_MAP_PATH = "map";
const string GeneralService::P_START_LOCATION = "startLocation";
const string GeneralService::P_GOAL = "goal";
const string GeneralService::P_ROBOT_SIZE = "robotSize";
const string GeneralService::P_MAP_RESOLUTION = "MapResolutionCM";
const string GeneralService::P_GRID_RESOLUTION = "GridResolutionCM";

// PNG names
const char* GeneralService::PNG_GRID = "grid.png";
const char* GeneralService::PNG_BLOW_MAP = "roboticLabMapBlow.png";
const char* GeneralService::PNG_BLOW_GRID = "blowGrid.png";

// Colors
const unsigned char GeneralService::C_BLACK  = 0;
const unsigned char GeneralService::C_GRAY   = 176;
const unsigned char GeneralService::C_GREEN  = 250;
const unsigned char GeneralService::C_WHITE  = 255;
const unsigned char GeneralService::C_PURPLE = 127;
const unsigned char GeneralService::C_RED	 = 245;
const unsigned char GeneralService::C_BLUE 	 = 20;
const unsigned char GeneralService::C_ORANGE = 128;

//priorities
const int GeneralService::P_WHITE = 1;
const int GeneralService::P_GRAY  = 5;
const int GeneralService::P_BLACK = 10;

// Real Robot

// Meter/Second
const float GeneralService::STOP_MOVE_SPEED 	= 0;
const float GeneralService::MIDDLE_MOVE_SPEED 	= 0.2;
const float GeneralService::SLOW_MOVE_SPEED 	= 0.1;

// Degrees
const float GeneralService::STOP_TURN_ANGLE 	= 0;
const float GeneralService::SLOW_TURN_ANGLE 	= 10;
const float GeneralService::MIDDLE_TURN_ANGLE 	= 30;
const float GeneralService::FAST_TURN_ANGLE 	= 60;
const float GeneralService::FULL_TURN_ANGLE 	= 100;

// Meters
const float GeneralService::TURN_AND_MOVE_OBSTACLE_RANGE 	= 1;
const float GeneralService::TURN_ONLY_OBSTACLE_RANGE 		= 0.5;

// Particles
const int   GeneralService::PARTICLE_LASER_READ_JUMP  	= 10;
const float GeneralService::MAX_WALK_DISTRIBUTION 		= 0.2;
const float GeneralService::MAX_TURN_DISTRIBUTION 		= 0.5;
const float GeneralService::BIG_ANGLE 					= 0.5;
const float GeneralService::SMALL_ANGLE 				= 0.1;
const float GeneralService::SHORT_DIST 					= 0.2;
const float GeneralService::LONG_DIST 					= 0.7;
const float GeneralService::NORMALIZE_FACTOR 			= 1.4;

// Particle Manager
const int   GeneralService::MAX_PARTICLES 	= 100;
const float GeneralService::STRONG_BELIEF 	= 0.7;
const float GeneralService::WEAK_BELIEF 	= 0.3;
