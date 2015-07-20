/*
 * Robot.cpp
 *
 *  Created on: Dec 14, 2014
 *      Author: user
 */

#include "Robot.h"

Robot::Robot(char* ip, int port, Position startPos) {
	_pc = new PlayerClient(ip,port);
	_pp = new Position2dProxy(_pc);
	_lp = new LaserProxy(_pc);

	_pp->SetOdometry(startPos.x,startPos.y,startPos.yaw);
	_pp->SetMotorEnable(true);

	//For fixing Player's reading BUG
	for(int i=0;i<15;i++) {
		_pc->Read();
		_pp->SetOdometry(startPos.x,startPos.y,startPos.yaw);
	}

	_pp->SetOdometry(startPos.x,startPos.y,startPos.yaw);
	cout << "ODOMETRY" << getXPos() << "," << getYPos() << "," << getYaw() << endl;
	_currPos = startPos;
	_addNoise = false;
	_lastMoveDelta = Position {0,0,0};
	_obsIndex = 0;
}

Robot::~Robot() {
	delete _pc;
	delete _pp;
	delete _lp;
}

Position Robot::getLastMoveDelta() {
	return _lastMoveDelta;
}

Position Robot::getCurrPos() {
	return _currPos;
}

double Robot::getXPos() {
	return _pp->GetXPos();
}

double Robot::getYPos() {
	return _pp->GetYPos();
}

double Robot::getYaw() {
	return _pp->GetYaw();
}

double* Robot::getLaserArr() {

	for (int i=0;i < LASER_SAMPLES_NUM;i++) {
		_laserArr[i] = getLaser(i);
	}

	return _laserArr;
}

double Robot::getLaser(int index) {
	if (index < 0 || index > LASER_SAMPLES_NUM) {
		return -1;
	}

	return (*_lp)[index];
}

int Robot::getObsIndex() {
	return _obsIndex;
}

void Robot::setSpeed(float xSpeed, float angularSpeed) {
	_pp->SetSpeed(xSpeed, angularSpeed);
}

void Robot::setAddNoise(bool addNoise) {
	_addNoise = addNoise;
}

void Robot::read() {
	_pc->Read();
}

void Robot::calcDeltas() {
	float deltaX = calcDeltaX();
	float deltaY = calcDeltaY();
	float deltaYaw = calcDeltaYaw();
	_lastMoveDelta = Position {deltaX,deltaY,deltaYaw};
}

float Robot::calcDeltaX(){
	float x = getXPos();

	if (_addNoise) {
		x = x + ((float(rand()) / float(RAND_MAX)) * MAX_WALK_DIST*2 - MAX_WALK_DIST);
	}

	float deltaX = x - _currPos.x;
	_currPos.x = x;

	return deltaX;
}

float Robot::calcDeltaY(){
	float y = getYPos();

	if (_addNoise) {
		y = y + ((float(rand()) / float(RAND_MAX)) * MAX_WALK_DIST*2 - MAX_WALK_DIST);
	}
	float deltaY = y - _currPos.y;
	_currPos.y = y;

	return deltaY;
}

float Robot::calcDeltaYaw(){
	float yaw = getYaw();

	if (_addNoise) {
		yaw = yaw + ((float(rand()) / float(RAND_MAX)) * MAX_TURN_DIST*2 - MAX_TURN_DIST);
	}

	float delYaw = yaw - _currPos.yaw;
	_currPos.yaw = yaw;

	return delYaw;
}

float Robot::getVisualAngle(float distance,float linearSize) {
	return 2 * atan(linearSize / (2 * distance));
}

bool Robot::isLeftMoreFree() {
	int left = 0 , right = 0, lcount = 0, rcount = 0;

	for (int i = LASER_ANGLE_TO_INDEX_DEG(90), j = LASER_ANGLE_TO_INDEX_DEG(-90);
			 i < LASER_ANGLE_TO_INDEX_DEG(47) && j > LASER_ANGLE_TO_INDEX_DEG(-47);
			 i += LASER_READ_JUMP, j-=LASER_READ_JUMP) {

		if ((*_lp)[i] < 0.3) {
			left+=(*_lp)[i];
			lcount++;
		}
		if ((*_lp)[j] < 0.3) {
			right+=(*_lp)[j];
			rcount++;
		}
	}

	return (left / lcount) < (right / rcount);
}

bool Robot::isRightFree() {
	if ((*_lp)[LASER_ANGLE_TO_INDEX_DEG(-50)] > 0.2)
		return true;
	else
		return false;
}

bool Robot::isLeftFree() {

	if ((*_lp)[LASER_ANGLE_TO_INDEX_DEG(50)] > 0.2)
		return true;
	else
		return false;
}

bool Robot::isForwardFree() {

	float visualRadAngle = getVisualAngle(OBSTABLE_MIN_DIST,X_SIZE_METER);
	int angleLaserAddition = (visualRadAngle / LASER_ANGULAR_RESOLUTION_RAD) ;
	float minObs = 4, minIndex = 0;

	for (int i = FORWARD_LASER_INDEX - (angleLaserAddition/2);
			 i < FORWARD_LASER_INDEX + (angleLaserAddition/2);
			 i += LASER_READ_JUMP) {
		if ((*_lp)[i] < OBSTABLE_MIN_DIST && (*_lp)[i] < minObs) {
			minObs = (*_lp)[i];
			minIndex =i;
		}
	}

	if (minObs < OBSTABLE_MIN_DIST) {
		cout << "OBS i-" << minIndex << " " << (*_lp)[minIndex] << endl;
		_obsIndex = minIndex;
		return false;
	}

	return true;
}

 void Robot::wander(double* forwardSpeed,double* turnSpeed) {
		int maxSpeed = 1;
		int maxTurn = 90;
		double fspeed, tspeed;
		//fspeed is between 0 and 10
		fspeed = rand()%11;
		//(fspeed/10) is between 0 and 1
		fspeed = (fspeed/10)*maxSpeed;
		tspeed = rand()%(2*maxTurn);
		tspeed = tspeed-maxTurn;
		//tspeed is between -maxTurn and +maxTurn
		*forwardSpeed = fspeed;
		*turnSpeed = tspeed;
 }
