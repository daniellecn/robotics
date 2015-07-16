/*
 * GeneralService.h
 *
 *  Created on: Jun 23, 2015
 *      Author: colman
 */

#ifndef GENERALSERVICE_H_
#define GENERALSERVICE_H_

#include <string>
using namespace std;

struct location{
	int x;
	int y;
};

struct Position {
	double x;
	double y;
	double yaw;
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
	int g;
	int f;
	location currLoc;
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

	// Priorities
	static const int P_BLACK;
	static const int P_GRAY;
	static const int P_WHITE;
};

#endif /* GENERALSERVICE_H_ */
