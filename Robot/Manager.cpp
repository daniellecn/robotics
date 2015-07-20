/*
 * Manager.cpp
 *
 *  Created on: Dec 21, 2014
 *      Author: user
 */

#include "Manager.h"

Manager::Manager(Robot* robot, Map* map, Plan* plan, PathPlanner* pathPlan){
	_robot = robot;
	_map = map;
	_plan = plan;
	_path = pathPlan;
	_curr = plan->getStartPoint();

	_wm = new WaypointManager(pathPlan,robot);
	_pm = new ParticleManager(robot->getCurrPos());
}

void Manager::run() {
	cout << "Start manager" << endl;
	cout << "Robot position before move: [" << _robot->getCurrPos().x << "," << _robot->getCurrPos().y << "," << _robot->getCurrPos().yaw << "]" << endl;

	Position deltas;
	cout << "Start moving" << endl;
	locationF target = _wm->getWayPointPool().at(0);
	// Choose the first behavior of the plan
	if (_curr->startCondition() == false)
		_curr = _curr->selectNext();
	// Stop when the last waypoint is reached
	while(!_wm->isLastWaypoint()) {

		while (!_wm->isWaypointReached(_pm->getAvgParticle().getBelPos())) {
			if (_robot->isForwardFree()) {
				_wm->turnToWaypoint(_robot->getCurrPos(),_pm,_map);
			}
			_curr->action();
			_curr->print();
			// Move in the same direction until conditions change
			while((!_curr->stopCondition()) &&
				  (!_wm->isWaypointReached(_pm->getAvgParticle().getBelPos()))) {
				_robot->read();
				_robot->calcDeltas();
				deltas = _robot->getLastMoveDelta();
				if (deltas.x != 0 || deltas.y != 0 || deltas.yaw != 0) {
					_pm->update(deltas,_robot->getLaserArr(),_map);
				}

			}

			// Perform the next behavior according to the plan
			if (_curr->stopCondition()) {
				_curr = _curr->selectNext();
			}
			if (_curr == NULL) {
				cout << "sad" << endl;
				break;
			}

/*			_wm->turnToWaypoint(_robot->getCurrPos());
			_robot->setSpeed(0.5,0);
			while(!_wm->isWaypointReached({_robot->getCurrPos().x,_robot->getCurrPos().y}))
				{
			_robot->read();
			_robot->calcDeltas();
				}*/
		}
		cout << "me dd : " << _robot->getXPos() << "," << _robot->getYPos() << "," << _robot->getYaw()<< endl;
		cout << "before switch me : " << _robot->getCurrPos().x << "," << _robot->getCurrPos().y << ","<< _robot->getCurrPos().yaw << "target : " << target.x << "," << target.y << endl;
		cout << " distance " << sqrt(pow(_robot->getCurrPos().x - target.x,2) + pow(_robot->getCurrPos().y - target.y,2)) << endl;
		//_path->getGrid()[_map->yPosToIndexLocal(target.y *100)][_map->xPosToIndexLocal(target.x*100)].color = GeneralService::C_PURPLE;
		target=_wm->switchToNextWaypoint();
		_path->getGrid()[_map->yPosToIndexLocal(_pm->getAvgParticle().getBelPos().y *100)][_map->xPosToIndexLocal(_pm->getAvgParticle().getBelPos().x*100)].color = GeneralService::C_ORANGE;
		cout << "after switch target : " << target.x << "," << target.y << endl;
/*		_map->getGrid()[_map->yPosToIndexLocal(target.y *100)][_map->xPosToIndexLocal(target.x*100)].color = GeneralService::C_PURPLE;
		target=_wm->switchToNextWaypoint();
		_map->getGrid()[_map->yPosToIndexLocal(_robot->getCurrPos().y *100)][_map->xPosToIndexLocal(_robot->getCurrPos().x*100)].color = GeneralService::C_ORANGE;
		//_map->gridToPng(GeneralService::PNG_BLOW_GRID, _map->getGrid(),
		//		_map->getWidthGrid(), _map->getHeightGrid());*/
/*			for (vector<Particle>::iterator curr = _pm->getParticles().begin() ; curr != _pm->getParticles().end() ;++curr) {

					cout << "[" << curr->getBelPos().x << "," << curr->getBelPos().y << ","
								<< curr->getBelPos().yaw << "," << curr->getBelWeight()<<  "]";

					_map->getGrid()[_map->yPosToIndexLocal(curr->getBelPos().y * 100)]
					               [_map->xPosToIndexLocal(curr->getBelPos().x * 100)].color =  GeneralService::C_PURPLE;
				}
			_map->getGrid()[_map->yPosToIndexLocal(_robot->getYPos() * 100)][_map->xPosToIndexLocal(_robot->getXPos() * 100)].color = GeneralService::C_ORANGE;

		for (int x= 0; x < _map->getHeightGrid(); x++) {
			for (int y = 0; y < _map->getWidthGrid(); y++) {
				if (_map->getGrid()[x][y].color ==  GeneralService::C_ORANGE) {
					cout << "R";
				} else if (_map->getGrid()[x][y].color ==  GeneralService::C_PURPLE) {
					cout << "M";
				} else if (_map->getGrid()[x][y].color ==  GeneralService::C_BLACK) {
					cout << "*";
				}
				else {
					cout << " ";
				}
			}
			cout << endl;
		}*/
	}

	cout << "I'm here!" << endl;
	cout << "Stop moving" << endl;
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
	_path->getMap()->gridToPng(GeneralService::PNG_BLOW_GRID, _path->getGrid(),
			_path->getMap()->getWidthBlowGrid(), _path->getMap()->getHeightBlowGrid());

	cout << endl << "Max particle: [" << part->getBelPos().x << "," << part->getBelPos().y  << "," << part->getBelPos().yaw << "]" << endl;
	cout << "Max bel : " << part->getBelWeight() << " Max gen : " << part->getGeneration() << endl;
	cout << "Avg particle: [" << _pm->getAvgParticle().getBelPos().x << ","
		<< _pm->getAvgParticle().getBelPos().y << ","
		<< _pm->getAvgParticle().getBelPos().yaw << "]";
	cout << " Avg bel : " << _pm->getAvgParticle().getBelWeight()<< endl;
	cout << "dist avg max" << sqrt(pow(_pm->getAvgParticle().getBelPos().x - part->getBelPos().x,2) + pow(_pm->getAvgParticle().getBelPos().y - part->getBelPos().y,2));

	// Put robot on map
	_map->getGrid()[_map->yPosToIndexLocal(_robot->getYPos() * 100)][_map->xPosToIndexLocal(_robot->getXPos() * 100)].color = col2;

	for (int x= 0; x < _map->getHeightGrid(); x++) {
		for (int y = 0; y < _map->getWidthGrid(); y++) {
			if (_map->getGrid()[x][y].color == col){
				cout << "X";
			} else if (_map->getGrid()[x][y].color == col2) {
				cout << "R";
			} else if (_map->getGrid()[x][y].color ==  GeneralService::C_ORANGE) {
					cout << "O";
			} else if (_map->getGrid()[x][y].color ==  GeneralService::C_PURPLE) {
					cout << "W";
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
