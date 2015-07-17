/*
 * Manager.cpp
 *
 *  Created on: Dec 21, 2014
 *      Author: user
 */

#include "Manager.h"

Manager::Manager(Robot* robot, Map* map, Plan* plan, WaypointManager* wayPoints){
	_robot = robot;
	_map = map;
	_plan = plan;
	_curr = plan->getStartPoint();

	_pm = new ParticleManager(robot->getCurrPos());
	_wm = wayPoints;
}

void Manager::run() {
	cout << "Start manager" << endl;
	cout << "Robot position before move: [" << _robot->getCurrPos().x << "," << _robot->getCurrPos().y << "," << _robot->getCurrPos().yaw << "]" << endl;

	int count = 0, updates = 0;
	Position deltas;
	cout << "Start moving" << endl;

	// Choose the first behavior of the plan
	if (_curr->startCondition() == false)
		_curr = _curr->selectNext();

	bool reached = false;
	while(!reached) {

		reached = _wm->isWaypointReached(_robot->getCurrPos());

		cout << count << endl;
			_curr->action();
		// Move in the same direction until conditions change
		while(!(_curr->stopCondition())) {
			count++;
			_robot->read();
			_robot->calcDeltas();
			deltas = _robot->getLastMoveDelta();
			if (deltas.x != 0 || deltas.y != 0 || deltas.yaw != 0) {
				//_pm->update(deltas,_robot->getLaserArr(),_map);
				updates++;
			}

		}

		// Perform the next behavior according to the plan
		_curr = _curr->selectNext();
		if (!_curr)
			break;
	}

	cout << "Stop moving" << endl;
	cout << "Localization updates :" << updates << endl;
	cout << "Particle number " << _pm->getParticles().size() << endl;
	cout << "Print result : " << endl;

	unsigned char col = 30;
	unsigned char col2 = 200;
	unsigned char black = 0;
	float maxBel = 0;
	Particle* part = NULL;

	// Update map with particles
	for (vector<Particle>::iterator curr = _pm->getParticles().begin() ; curr != _pm->getParticles().end() ;++curr) {

		cout << "[" << curr->getBelPos().x << "," << curr->getBelPos().y << ","
					<< curr->getBelPos().yaw << "," << curr->getBelWeight()<<  "]";

		_map->getGrid()[_map->yPosToIndexLocal(curr->getBelPos().y * 100)]
		               [_map->xPosToIndexLocal(curr->getBelPos().x * 100)].color = col;

		if (curr->getBelWeight() > maxBel) {
			maxBel = curr->getBelWeight();
			part = &(*curr);
		}
	}

	cout << endl << "Max particle: [" << part->getBelPos().x << "," << part->getBelPos().y  << "," << part->getBelPos().yaw << "]" << endl;
	cout << "Max bel : " << part->getBelWeight() << " Max gen : " << part->getGeneration() << endl;

	// Put robot on map
	_map->getGrid()[_map->yPosToIndexLocal(_robot->getYPos() * 100)][_map->xPosToIndexLocal(_robot->getXPos() * 100)].color = col2;

	for (int x= 0; x < _map->getHeightGrid(); x++) {
		for (int y = 0; y < _map->getWidthGrid(); y++) {
			if (_map->getGrid()[x][y].color == col){
				cout << "X";
			} else if (_map->getGrid()[x][y].color == col2) {
				cout << "R";
			} else if (_map->getGrid()[x][y].color == black) {
				cout << "*";
			}
			else {
				cout << " ";
			}
		}
		cout << endl;
	}
}

Manager::~Manager() {
	delete _pm;
	delete _wm;
}
