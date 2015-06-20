/*
 * Manager.cpp
 *
 *  Created on: Dec 21, 2014
 *      Author: user
 */

#include "Manager.h"

Manager::Manager(Robot* robot, Map* map) {
	_robot = robot;
	_map = map;

	_beh[0] = new TurnRight(_robot);
	_beh[1] = new TurnLeft(_robot);

	_pm = new ParticleManager();
}

void Manager::run()
{

	int count = 0, updates = 0;
	Position deltas;
	_robot->read();
	cout << "Position before move: " << _robot->getCurrPos().x << "," << _robot->getCurrPos().y << "," << _robot->getCurrPos().yaw << endl;

	while(count < 100) {
		count++;

		_robot->calcDeltas();
		deltas = _robot->getLastMoveDelta();
		//cout << "Delta : " << _robot->getLastMoveDelta().x << "," << _robot->getLastMoveDelta().y<< "," << _robot->getLastMoveDelta().yaw << endl;
		//cout << "Position : " << _robot->getCurrPos().x << "," << _robot->getCurrPos().y << "," << _robot->getCurrPos().yaw << endl;

		if (deltas.x != 0 || deltas.y != 0 || deltas.yaw != 0) {
			_pm->update(deltas,_robot->getLaserArr(),_map);
			updates++;
		}
		cout << "new parts " << endl;
		for (vector<Particle>::iterator curr = _pm->getParticles().begin() ; curr != _pm->getParticles().end() ;++curr) {
			cout << "[" <<(int)curr->getBelPos().x << "," << (int)curr->getBelPos().y << "," << (int)curr->getBelPos().yaw << curr->getBelWeight()<<  "]";
		}
		cout << endl;
		//_robot->wander(&forwardSpeed, &turnSpeed);
		//_robot->isForwardFree();
		//set motors
		//_robot->setSpeed(forwardSpeed, dtor(turnSpeed));

		if (_robot->isForwardFree()) {
			_robot->setSpeed(0.7,0.0);
		} else if (_beh[0]->startCondition() ){
			_beh[0]->action();
		} else if (_beh[1]->startCondition()) {
			_beh[1]->action();
		}
		_robot->read();
		_robot->read();

	}
cout << "update " << updates << endl;

unsigned char col = 30;
unsigned char col2 = 200;
unsigned char col3 = 300;
unsigned char black = 0;
for (vector<Particle>::iterator curr = _pm->getParticles().begin() ; curr != _pm->getParticles().end() ;++curr) {
	_map->getGrid()[_map->yPosToIndex(curr->getBelPos().x * 100)][_map->xPosToIndex(curr->getBelPos().y * 100)].color = col;
}
_map->getGrid()[_map->yPosToIndex(_robot->getYPos() * 100)][_map->xPosToIndex(_robot->getXPos() * 100)].color = col3;
_map->getGrid()[_map->yPosToIndex(_robot->getXPos() * 100)][_map->xPosToIndex(_robot->getYPos() * 100)].color = col2;
cout << _pm->getParticles().size() << endl;
for (int y = 0; y < _map->getHeightGrid(); y++){
	for (int x = 0; x < _map->getWidthGrid(); x++) {
		if (_map->getGrid()[y][x].color == col){
			cout << "X";
		}
		else if (_map->getGrid()[y][x].color == col2) {
			cout << "M";
		}
		else if (_map->getGrid()[y][x].color == col3) {
				cout << "B";
		} else if (_map->getGrid()[y][x].color == black) {
			cout << "*";
		}
		else {
			cout << " ";
		}
	}
	cout << endl;
}



/*	while (_curr) {
		_robot->read();
		if(!(_curr->startCondition()))
			return;
		_curr->action();
		while(_curr !=NULL)
		{
			while(_curr->stopCondition() == false)
			{
				_curr->action();
				_robot->read();
			}
			_curr = _curr->selectNext();
			_robot->read();
		}
	}*/
}

Manager::~Manager() {
	delete _pm;
	//delete _map;
}
