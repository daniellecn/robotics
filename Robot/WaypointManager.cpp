/*
 * WaypointManager.cpp
 *
 *  Created on: Jun 14, 2015
 *      Author: colman
 */

#include "WaypointManager.h"


WaypointManager::WaypointManager(PathPlanner* pathP, Robot* robot) {
	this->setWayPointPool(pathP->getWayPoints(), pathP);
	pathP->getMap()->gridToPng(GeneralService::PNG_BLOW_GRID, pathP->getGrid(),
			pathP->getMap()->getWidthBlowGrid(), pathP->getMap()->getHeightBlowGrid());

	_robot = robot;
	_targetIndex = 0;
	// TODO
	_target = this->getWayPointPool().at(0);
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

double WaypointManager::distanceBetween(location a, location b) {
	return sqrt(pow(a.x - b.x,2) + pow(a.y - b.y,2));
}

float WaypointManager::angleBetween(location a, location b) {
	return acos((a.x - b.x)/distanceBetween(a,b));
}

void WaypointManager::getNextWaypoint() {
	_targetIndex++;

	if (this->getWayPointPool().size() == _targetIndex) {
		_target = {NULL, NULL};
	} else {
		_target = this->getWayPointPool().at(_targetIndex);
	}
}

bool WaypointManager::isWaypointReached(Position avgLocation) {
	double distance = sqrt(pow(_target.x - avgLocation.x,2) + pow(_target.y - avgLocation.y,2));

	if (distance <= REACH_RADIUS) {
		getNextWaypoint();
		return true;
	}

	return false;
}

void WaypointManager::goToWaypoint(Position avgLocation) {
	location target = this->getWayPointPool().at(_targetIndex);
	double distance = sqrt(pow(target.x - avgLocation.x,2) + pow(target.y - avgLocation.y,2));
	float angle = acos((target.x - avgLocation.x)/distance);

	if (avgLocation.yaw > angle) {
		_robot->setSpeed(0,dtor(-40));
	} else {
		_robot->setSpeed(0,dtor(40));
	}

	while (abs(_robot->getYaw() - angle) > dtor(5)) {
		_robot->read();
	}
}

bool WaypointManager::isEndReached(Position avgLocation) {
	bool isTargetReached = false;

	if (this->getWayPointPool().size() == _targetIndex + 1) {
		location target = this->getWayPointPool().at(_targetIndex);
		double distance = sqrt(pow(target.x - avgLocation.x,2) + pow(target.y - avgLocation.y,2));

		if (distance <= REACH_RADIUS) {
			isTargetReached = true;
			_robot->setSpeed(0,0);
			cout << "Reached!" << endl;
		}
	}

	return isTargetReached;
}
