/*
 * Manager.cpp
 *
 *  Created on: Dec 21, 2014
 *      Author: user
 */

#include "Manager.h"

Manager::Manager(Robot* robot, Map* map, Plan* plan) {
	_robot = robot;
	_map = map;
	_plan = plan;
	_curr = plan->getStartPoint();

	_pm = new ParticleManager();
}

void Manager::run()
{

	int count = 0, updates = 0;
	Position deltas;
	cout << "Position before move: " << _robot->getCurrPos().x << "," << _robot->getCurrPos().y << "," << _robot->getCurrPos().yaw << endl;
	// Perform the first behavior of the plan
	if (_curr->startCondition() == false)
		_curr = _curr->selectNext();
	_curr->action();

	while(count < 100) {
		count++;
		_robot->read();

		while(!(_curr->stopCondition()))
		{
			_curr->action();
			_robot->calcDeltas();
			deltas = _robot->getLastMoveDelta();
			if (deltas.x != 0 || deltas.y != 0 || deltas.yaw != 0) {
				//_pm->update(deltas,_robot->getLaserArr(),_map);
				updates++;
			}

			_robot->read();
			_robot->read();
		}
		// Perform the next behavior according to the plan
		_curr = _curr->selectNext();
		if (!_curr)
			break;



		//cout << "Delta : " << _robot->getLastMoveDelta().x << "," << _robot->getLastMoveDelta().y<< "," << _robot->getLastMoveDelta().yaw << endl;
		//cout << "Position : " << _robot->getCurrPos().x << "," << _robot->getCurrPos().y << "," << _robot->getCurrPos().yaw << endl;


/*		cout << "new parts " << endl;
		for (vector<Particle>::iterator curr = _pm->getParticles().begin() ; curr != _pm->getParticles().end() ;++curr) {
			cout << "[" <<(int)curr->getBelPos().x << "," << (int)curr->getBelPos().y << "," << (int)curr->getBelPos().yaw << curr->getBelWeight()<<  "]";
		}
		cout << endl;*/
		//_robot->wander(&forwardSpeed, &turnSpeed);
		//_robot->isForwardFree();
		//set motors
		//_robot->setSpeed(forwardSpeed, dtor(turnSpeed));
	}
cout << "update " << updates << endl;

unsigned char col = 30;
unsigned char col2 = 200;
unsigned char col3 = 300;
unsigned char black = 0;
for (vector<Particle>::iterator curr = _pm->getParticles().begin() ; curr != _pm->getParticles().end() ;++curr) {
	_map->getGrid()[_map->xPosToIndex(curr->getBelPos().x * 100)][_map->yPosToIndex(curr->getBelPos().y * 100)].color = col;
}
_map->getGrid()[_map->xPosToIndex(_robot->getXPos() * 100)][_map->yPosToIndex(_robot->getYPos() * 100)].color = col3;
_map->getGrid()[_map->xPosToIndex(_robot->getXPos() * 100)][_map->yPosToIndex(_robot->getYPos() * 100)].color = col2;
cout << _pm->getParticles().size() << endl;
for (int y = 0; y < _map->getWidthGrid(); y++){
	for (int x = 0; x < _map->getHeightGrid(); x++) {
		if (_map->getGrid()[x][y].color == col){
			cout << "X";
		}
		else if (_map->getGrid()[x][y].color == col2) {
			cout << "M";
		}
		else if (_map->getGrid()[x][y].color == col3) {
				cout << "B";
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
	//delete _map;
}
