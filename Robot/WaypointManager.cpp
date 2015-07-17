/*
 * WaypointManager.cpp
 *
 *  Created on: Jun 14, 2015
 *      Author: colman
 */

#include "WaypointManager.h"


WaypointManager::WaypointManager(vector <wayPoint> wayPoints, PathPlanner* pathP) {
	this->setWayPointPool(wayPoints, pathP);
	pathP->getMap()->gridToPng(GeneralService::PNG_BLOW_GRID, pathP->getGrid(),
			pathP->getMap()->getWidthBlowGrid(), pathP->getMap()->getHeightBlowGrid());
}

WaypointManager::~WaypointManager() {
	// TODO Auto-generated destructor stub
}

void WaypointManager::setWayPoint(location point, cellGrid** grid){
	this->_wayPointPool.push_back(point);
	grid[point.y][point.x].color = GeneralService::C_PURPLE;
}

vector <location> WaypointManager::getWayPointPool(){
	return this->_wayPointPool;
}

void WaypointManager::setWayPointPool(vector <wayPoint> wayPoints, PathPlanner* pathP){
	vector<wayPoint>::iterator prevElement;
	int counter = 0;

	for(vector<wayPoint>::iterator it = wayPoints.begin(); it != wayPoints.end(); ++it) {
		// If start / Goal location
		if ((((*it).pointLoc.x == pathP->getStartIndex().currLoc.x) &&
			((*it).pointLoc.y == pathP->getStartIndex().currLoc.y))||
			(((*it).pointLoc.x == pathP->getGoalIndex().currLoc.x) &&
			((*it).pointLoc.y == pathP->getGoalIndex().currLoc.y))){
			this->setWayPoint((*it).pointLoc, pathP->getGrid());
			counter = 0;
		}
		// If direction change
		else if ((*it).dirArrival != (*prevElement).dirArrival){
			this->setWayPoint((*it).pointLoc, pathP->getGrid());
			counter = 0;
		}
		else if (counter == 3){
			this->setWayPoint((*it).pointLoc, pathP->getGrid());
			counter = 0;
		}
		else{
			counter++;
		}

		prevElement = it;
	}
}

