/*
 * main.cpp
 *
 *  Created on: Jan 10, 2015
 *      Author: colman
 */

#include <libplayerc++/playerc++.h>
#include <iostream>

#include "Map.h"
#include "Robot.h"
#include "Manager.h"
#include "PathPlanner.h"
#include "WaypointManager.h"
#include "plans/PlnObstacleAvoid.h"
using namespace std;
using namespace PlayerCc;

int main() {
	int resolution = ConfigurationManager::getGridResolutionCM() /
			ConfigurationManager::getMapResolutionCM();

	// Read config
	Position start = {2.10,-2.9,dtor(20)};

	// Init and start classes
	Map map;

	PathPlanner path(&map,
			ConfigurationManager::getStartLocation().x / resolution,
			ConfigurationManager::getStartLocation().y / resolution,
			ConfigurationManager::getGoal().x / resolution,
			ConfigurationManager::getGoal().y / resolution);

	Robot robot("localhost", 6665, start);
	//robot.setAddNoise(true);

	PlnObstacleAvoid plan(&robot);
	Manager manager(&robot, &map, &plan, &path);
	manager.run();


	//Robot robot("localhost",6665, start);
	//robot.setAddNoise(true);
	//PlnObstacleAvoid plan(&robot);
	//Manager manager(&robot, &map, &plan);
	//manager.run();

	// Check real robot code
/*
	PlayerClient pc("localhost", 6665);
	LaserProxy lp(&pc);
	Position2dProxy pp(&pc);
	float prevX,prevY,prevYaw;
	float currX,currY,currYaw;
	float distance = 0;
	float distanceToStop = 0.3;
	pp.SetMotorEnable(true);

	bool go = true;

	//For fixing Player's reading BUG
	for(int i=0;i<15;i++)
		pc.Read();

	pc.Read();
	pp.SetSpeed(0.5, 0.0);

	prevX = pp.GetXPos();
	prevY = pp.GetYPos();
	prevYaw = pp.GetYaw();
	cout << "x : " << prevX << " y : " << prevY  << " yaw : " << prevYaw << endl;

	while (go) {
		pc.Read();
		currX = pp.GetXPos();
		currY = pp.GetYPos();
		currYaw = pp.GetYaw();
		cout << "x : " << currX << " y : " << currY << " yaw : " << currYaw << endl;
		distance += sqrt(pow(currX-prevX,2) + pow(currY-prevY,2));
		cout << "dist : " << distance << endl;

		if (distance >= distanceToStop) {
			pp.SetSpeed(0.0, 0.0);
			go = false;
		}
	}*/

	return 0;

}





