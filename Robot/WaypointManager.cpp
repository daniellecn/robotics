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

	for (vector<locationF>::iterator curr = _wayPointPool.begin() ; curr != _wayPointPool.end() ;++curr) {
		cout << curr->x << "," << curr->y << endl;
	}

/*	_wayPointPool.push_back({1.08,-1.61});
	_wayPointPool.push_back({-0.1,-0.65});
	_wayPointPool.push_back({-0.75,-0.11});
	_wayPointPool.push_back({-1.74,-0.32});
	_wayPointPool.push_back({-2.49,0.91});
	_wayPointPool.push_back({-2.73,1.75});*/

/*	_wayPointPool.push_back({2.68,-2.13});
	_wayPointPool.push_back({3.40,-1.26});
	_wayPointPool.push_back({3.52,-0.12});
	_wayPointPool.push_back({2.77,1.02});
	_wayPointPool.push_back({1.96,2.31});*/

	_robot = robot;
	_targetIndex = 0;
	_target = _wayPointPool.at(0);
}

WaypointManager::~WaypointManager() {
	// TODO Auto-generated destructor stub
}

vector <locationF> WaypointManager::getWayPointPool(){
	return this->_wayPointPool;
}

void WaypointManager::setWayPointPool(vector <wayPoint> wayPoints, PathPlanner* pathP){
	int counter = 0;
	locationF waypoint;
	 std::reverse(wayPoints.begin(),wayPoints.end());
	vector<wayPoint>::iterator prevElement = wayPoints.begin();
	for(vector<wayPoint>::iterator it = wayPoints.begin(); it != wayPoints.end(); ++it) {
/*		waypoint = {pathP->getMap()->xIndexToPos((*it).pointLoc.x) / 100,
					pathP->getMap()->yIndexToPos((*it).pointLoc.y) / 100};
		_wayPointPool.push_back(waypoint);
		pathP->getGrid()[(*it).pointLoc.y][(*it).pointLoc.x].color = GeneralService::C_PURPLE;
		*/
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

float WaypointManager::angleBetween(locationF a, locationF b) {
	return (atan2(b.y - a.y,b.x - a.x));
}

bool WaypointManager::isWaypointReached(Position avgLocation) {
	//cout << "me : " << avgLocation.x << "," << avgLocation.y << " target : " << _target.x << "," << _target.y << endl;
	//cout << "distance : " << distanceBetween(_target,avgLocation) << endl;
	return (distanceBetween(_target,{avgLocation.x,avgLocation.y}) <= REACH_RADIUS);
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

void WaypointManager::turnToWaypoint(Position avgLocation,ParticleManager* pm,Map* map) {
	float angle = (atan2(_target.y - avgLocation.y,_target.x - avgLocation.x));
	float positiveTargetDeg = (angle * 180 / M_PI);
	float positiveAvgDeg = (avgLocation.yaw * 180 / M_PI);
	if (angle < 0) {
		positiveTargetDeg = 360 + positiveTargetDeg;
	}
	if (avgLocation.yaw < 0) {
		positiveAvgDeg = 360 + positiveAvgDeg;
	}
	// If robot angle is not correct
	if (fabs(positiveAvgDeg - positiveTargetDeg) > 8) {
		cout << "efresh " << abs(positiveAvgDeg - positiveTargetDeg) << endl;
  		if (positiveAvgDeg < positiveTargetDeg) {
			_robot->setSpeed(0,dtor(20));
			//cout << "left mine: " << avgLocation.yaw << " target: " << angle<< endl;
			cout << "left mine: " << avgLocation.yaw * 180 / M_PI<< " target: " << angle * 180 / M_PI<< endl;
		} else {
			_robot->setSpeed(0,dtor(-20));
			//cout << "right mine: " << avgLocation.yaw << " target: " << angle<< endl;
			cout << "right mine: " << positiveAvgDeg<< " target: " << positiveTargetDeg<< endl;
		}
		cout << "turn to waypoint : "<< _targetIndex << ": " << _target.x << "," << _target.y << endl;
	}
	Position deltas;
	while (fabs(positiveAvgDeg - positiveTargetDeg) > 8) {
		_robot->read();
		cout << "evil" << _robot->getXPos() << "," << _robot->getYPos() << "," << _robot->getYaw() << endl;
		//cout << "efresh np abs " << (positiveAvgDeg - positiveTargetDeg) << endl;
		cout << "efresh " << fabs(positiveAvgDeg - positiveTargetDeg) << endl;
		//cout << "my angle " << pm->getAvgParticle().getBelPos().yaw  << endl;
		cout << "my angle " << positiveAvgDeg << endl;
		_robot->calcDeltas();
		deltas = _robot->getLastMoveDelta();
		if (deltas.x != 0 || deltas.y != 0 || deltas.yaw != 0) {
			pm->update(deltas,_robot->getLaserArr(),map);
		}
		positiveAvgDeg = pm->getAvgParticle().getBelPos().yaw * 180 / M_PI;
		if (positiveAvgDeg < 0) {
			positiveAvgDeg = 360 + positiveAvgDeg;
		}
	}

	_robot->setSpeed(0,0);
}


