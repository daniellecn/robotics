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
	position deltas;

	cout << "Start manager" << endl;
	cout << "Robot position before move: [" << _robot->getCurrPos().x << "," << _robot->getCurrPos().y << "," << _robot->getCurrPos().yaw << "]" << endl;
	cout << "Start moving" << endl;

	// Get first target
	locationF target = _wm->getWayPointPool().at(0);

	// Choose the first behavior of the plan
	if (_curr->startCondition() == false)
		_curr = _curr->selectNext();

	// Stop when the last waypoint is reached
	while(!_wm->isLastWaypoint()) {

		// While target is not reached
		while (!_wm->isWaypointReached(_pm->getAvgParticle().getBelPos())) {

			// If obstacle avoidance isn't working now
			if (_robot->isForwardFree()) {
				// Turn robot in the direction of the obstacle
				while (!_wm->turnToWaypoint(_pm->getAvgParticle().getBelPos())) {
					_robot->read();
					_robot->calcDeltas();
					deltas = _robot->getLastMoveDelta();

					// Update robot location
					if (deltas.x != 0 || deltas.y != 0 || deltas.yaw != 0) {
						_pm->update(deltas,_robot->getLaserArr(),_map);
					}
				}
			}

			// Perform movement action
			_curr->action();
			_curr->print();

			// Move in the same direction until conditions change
			while((!_curr->stopCondition()) &&
				  (!_wm->isWaypointReached(_pm->getAvgParticle().getBelPos()))) {
				_robot->read();
				_robot->calcDeltas();
				deltas = _robot->getLastMoveDelta();

				// Update robot location
				if (deltas.x != 0 || deltas.y != 0 || deltas.yaw != 0) {
					_pm->update(deltas,_robot->getLaserArr(),_map);
				}
			}

			// Perform the next behavior according to the plan
			if (_curr->stopCondition()) {
				_curr = _curr->selectNext();
			}

			if (_curr == NULL) {
				cout << "Stuck!" << endl;
				break;
			}
		}

		// Draw location
		_path->getGrid()[_map->yPosToIndexLocal(_pm->getAvgParticle().getBelPos().y *100)][_map->xPosToIndexLocal(_pm->getAvgParticle().getBelPos().x*100)].color = GeneralService::C_ORANGE;

		cout << "My location before switching waypoints : ["
			 << _pm->getAvgParticle().getBelPos().x << "," << _pm->getAvgParticle().getBelPos().y << ","<< _pm->getAvgParticle().getBelPos().yaw << "]" << endl;
		cout << "target was: " << target.x << "," << target.y << endl;

		// Switch to next waypoint
		target=_wm->switchToNextWaypoint();
		cout << "target after switch : " << target.x << "," << target.y << endl;
	}

	// Draw last location
	_path->getGrid()[_map->yPosToIndexLocal(_pm->getAvgParticle().getBelPos().y *100)][_map->xPosToIndexLocal(_pm->getAvgParticle().getBelPos().x*100)].color = GeneralService::C_ORANGE;

	cout << "I'm here! location : [" << _pm->getAvgParticle().getBelPos().x << "," << _pm->getAvgParticle().getBelPos().y << "," << _pm->getAvgParticle().getBelPos().yaw << "]" << endl;
	cout << "Stop moving" << endl;
	cout << "Particle number " << _pm->getParticles().size() << endl;

	// Draw map again
	_path->getMap()->gridToPng(GeneralService::PNG_BLOW_GRID, _path->getGrid(),
			_path->getMap()->getWidthBlowGrid(), _path->getMap()->getHeightBlowGrid());
}

Manager::~Manager() {
	delete _pm;
	delete _wm;
}
