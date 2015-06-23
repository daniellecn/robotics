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
const unsigned char GeneralService::C_BLACK = 0;
const unsigned char GeneralService::C_GRAY_D = 110;
const unsigned char GeneralService::C_GRAY_B = 192;
const unsigned char GeneralService::C_GREEN = 250;
const unsigned char GeneralService::C_WHITE = 255;
const unsigned char GeneralService::C_PURPLE = 127;
const unsigned char GeneralService::C_RED = 252;
const unsigned char GeneralService::C_BLUE = 252;

//priorities
const int GeneralService::P_BLACK = 0;
const int GeneralService::P_GRAY_D = 1;
const int GeneralService::P_GRAY_B = 2;
const int GeneralService::P_WHITE = 3;