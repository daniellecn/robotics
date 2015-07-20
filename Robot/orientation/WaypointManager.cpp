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

	cout << "Waypoints :" << endl;
	for (vector<locationF>::iterator curr = _wayPointPool.begin() ; curr != _wayPointPool.end() ;++curr) {
		cout << curr->x << "," << curr->y << endl;
	}

	_robot = robot;
	_targetIndex = 0;
	_target = _wayPointPool.at(0);
}

WaypointManager::~WaypointManager() {
}

vector <locationF> WaypointManager::getWayPointPool(){
	return this->_wayPointPool;
}

void WaypointManager::setWayPointPool(vector <wayPoint> wayPoints, PathPlanner* pathP){
	int counter = 0;
	locationF waypoint;
	vector<wayPoint>::iterator prevElement = wayPoints.begin();

	// Reverse path from a star
	std::reverse(wayPoints.begin(),wayPoints.end());

	// Choose waypoints
	for(vector<wayPoint>::iterator it = wayPoints.begin(); it != wayPoints.end(); ++it) {
		// If start / Goal location
		if ((((*it).pointLoc.x == pathP->getStartIndex().currLoc.x) &&
			((*it).pointLoc.y == pathP->getStartIndex().currLoc.y))||
			(((*it).pointLoc.x == pathP->getGoalIndex().currLoc.x) &&
			((*it).pointLoc.y == pathP->getGoalIndex().currLoc.y))){
			waypoint = {pathP->getMap()->xIndexToPos((*it).pointLoc.x) / 100,
						pathP->getMap()->yIndexToPos((*it).pointLoc.y) / 100};
			_wayPointPool.push_back(waypoint);
			pathP->getGrid()[(*it).pointLoc.y][(*it).pointLoc.x].color = GeneralService::C_PURPLE;
			counter = 0;
		}
		else if (counter == 3){
			waypoint = {pathP->getMap()->xIndexToPos((*it).pointLoc.x) / 100,
						pathP->getMap()->yIndexToPos((*it).pointLoc.y) / 100};
			_wayPointPool.push_back(waypoint);
			pathP->getGrid()[(*it).pointLoc.y][(*it).pointLoc.x].color = GeneralService::C_PURPLE;
			counter = 0;
		}
		else{
			counter++;
		}

		prevElement = it;
	}
}

int WaypointManager::getTargetIndex() {
	return _targetIndex;
}

double WaypointManager::distanceBetween(locationF a, locationF b) {
	return sqrt(pow(a.x - b.x,2) + pow(a.y - b.y,2));
}

bool WaypointManager::isWaypointReached(position avgLocation) {
	//cout << "me : " << avgLocation.x << "," << avgLocation.y << " target : " << _target.x << "," << _target.y << endl;
	//cout << "distance : " << distanceBetween(_target,avgLocation) << endl;
	return (distanceBetween(_target,{avgLocation.x,avgLocation.y}) <= GeneralService::REACH_RADIUS);
}

bool WaypointManager::isLastWaypoint() {
	return (this->getWayPointPool().size() == _targetIndex);
}

locationF WaypointManager::switchToNextWaypoint() {
	_targetIndex++;

	if (_targetIndex < this->getWayPointPool().size()) {
		_target = this->getWayPointPool().at(_targetIndex);
	}

	return _target;
}

bool WaypointManager::turnToWaypoint(position avgLocation) {

	// Get angle to target
	float angle = (atan2(_target.y - avgLocation.y,_target.x - avgLocation.x));
	float positiveTargetDeg = (angle > 0) ? (angle * 180 / M_PI) : (360 + (angle * 180 / M_PI));
	float positiveAvgDeg = (avgLocation.yaw > 0) ? (avgLocation.yaw * 180 / M_PI) : (360 + (avgLocation.yaw * 180 / M_PI));

	// If robot angle is not correct
	if (fabs(positiveAvgDeg - positiveTargetDeg) > GeneralService::MAX_ANGLE_DIFF) {
  		if (positiveAvgDeg < positiveTargetDeg) {
			_robot->setSpeed(0,dtor(GeneralService::TURN_TO_ANGLE));
		} else {
			_robot->setSpeed(0,dtor(-GeneralService::TURN_TO_ANGLE));
		}
  		return false;
	}

	_robot->setSpeed(0,0);
	return true;
}


