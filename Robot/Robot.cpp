/*
 * Robot.cpp
 *
 *  Created on: Dec 14, 2014
 *      Author: user
 */

#include "Robot.h"

Robot::Robot(char* ip, int port,Position startPos) {
	_pc = new PlayerClient(ip,port);
	_pp = new Position2dProxy(_pc);
	_lp = new LaserProxy(_pc);
	_gp = new Graphics2dProxy(_pc);

	_pp->SetMotorEnable(true);

	//For fixing Player's reading BUG
	for(int i=0;i<15;i++)
		_pc->Read();

	//_currPos = Position {getXPos(),getYPos(),getYaw()};
	_pp->SetOdometry(startPos.x,startPos.y,startPos.yaw);
	_currPos = startPos;
	_addNoise = false;
	_lastMoveDelta = Position {0,0,0};
}

Robot::~Robot() {
	delete _pc;
	delete _pp;
	delete _lp;
	delete _gp;
}

void Robot::setAddNoise(bool addNoise) {
	_addNoise = addNoise;
}

void Robot::read() {
	_pc->Read();
}

Position Robot::getLastMoveDelta() {

	return _lastMoveDelta;
}

Position Robot::getCurrPos() {
	return _currPos;
}

void Robot::draw(player_color_t color,player_point_2d_t points[],int count) {
	_gp->Clear();
	_gp->Color(color);
	_gp->DrawPolyline(points,count);
	//_gp->DrawPoints(points,count);
	//_gp->DrawPolygon(points,count,true,color);
}

double* Robot::getLaserArr() {

	for (int i=0;i < LASER_SAMPLES_NUM;i++) {
		_laserArr[i] = getLaser(i);
	}

	return _laserArr;
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

void Robot::calcDeltas() {
	_lastMoveDelta = Position {calcDeltaX(),calcDeltaY(), calcDeltaYaw()};
}

float Robot::calcDeltaX(){
	float x = getXPos();

	if (_addNoise) {
		x = x + (rand() % 5);
	}


	float deltaX = x - _currPos.x;
	_currPos.x = x;

	return deltaX;
}

float Robot::calcDeltaY(){
	float y = getYPos();

	if (_addNoise) {
		y = y + (rand() % 5);
	}
	float deltaY = y - _currPos.y;
	_currPos.y = y;

	return deltaY;
}

float Robot::calcDeltaYaw(){
	float yaw = getYaw();

	if (_addNoise) {
		yaw = yaw + ((float)(rand())/(float)(RAND_MAX));
	}
	// make sure we are still in the 0-2*pi range
	//yaw = fmod(yaw,2*M_PI);
	float delYaw = yaw - _currPos.yaw;
	_currPos.yaw = yaw;

	return delYaw;
}

bool Robot::isRightFree() {
	if ((*_lp)[LASER_ANGLE_TO_INDEX_DEG(50)] > 0.5)
		return true;
	else
		return false;
}

bool Robot::isLeftFree() {

	if ((*_lp)[LASER_ANGLE_TO_INDEX_DEG(-50)] > 0.5)
		return true;
	else
		return false;
}

float Robot::getVisualAngle(float distance,float linearSize) {
	return 2 * atan(linearSize / (2 * distance));
}

bool Robot::isForwardFree() {

	float visualRadAngle = getVisualAngle(OBSTABLE_MIN_DIST,X_SIZE_METER);
	int angleLaserAddition = (visualRadAngle / LASER_ANGULAR_RESOLUTION_RAD) ;

	bool isObs  = false;

	for (int i = FORWARD_LASER_INDEX - (angleLaserAddition/2);
			 i < FORWARD_LASER_INDEX + (angleLaserAddition/2);
			 i += LASER_READ_JUMP) {
		if ((*_lp)[i] < OBSTABLE_MIN_DIST) {
			isObs = true;
		}
	}
	if (!isObs)
		return true;
	else
		return false;
}


void Robot::setSpeed(float xSpeed, float angularSpeed) {
	_pp->SetSpeed(xSpeed, angularSpeed);
}

double Robot::getLaser(int index) {
	if (index < 0 || index > LASER_SAMPLES_NUM) {
		return -1;
	}

	return (*_lp)[index];
}

 Location Robot::getObstacleLocation(double distanceFromObs,int sensorIndex) {
	Location obsLocation;

	obsLocation.x = getXPos() + distanceFromObs*cos(getYaw() + LASER_INDEX_TO_ANGLE_DEG(sensorIndex));
	obsLocation.y = getYPos() + distanceFromObs*sin(getYaw() + LASER_INDEX_TO_ANGLE_DEG(sensorIndex));

	return obsLocation;
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
