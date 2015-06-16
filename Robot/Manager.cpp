/*
 * Manager.cpp
 *
 *  Created on: Dec 21, 2014
 *      Author: user
 */

#include "Manager.h"

Manager::Manager(Robot* robot) {
	_robot = robot;
	Position startPos {_robot->getXPos(),_robot->getYPos(),_robot->getYaw()};

	_beh[0] = new TurnRight(_robot);
	_beh[1] = new TurnLeft(_robot);

	_pm = new ParticleManager();
}
void Manager::run()
{
	player_color_t color;
	color.red = 255;
	int ftp = 20,count = 0;
	double forwardSpeed, turnSpeed, x, y, yaw;

	_robot->read();

	x = _robot->getXPos();
	y = _robot->getYPos();
	yaw =_robot->getYaw();

	cout << "Position before any movement: " << x << "," << y << "," << yaw << endl;

	while(true) {
		count++;
		//pm.update(deltaPos,_robot->getLaserArr());

		if (count == ftp) {
			_robot->draw(color,&(_pm->getDrawableParticles())[0],_pm->getParticles().size());
			count = 0;
		}

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
}
