/*
 * main.cpp
 *
 *  Created on: Jan 10, 2015
 *      Author: colman
 */

#include <iostream>

#include "orientation/Map.h"
#include "robot/Robot.h"
#include "Manager.h"
#include "orientation/PathPlanner.h"
#include "plans/PlnObstacleAvoid.h"

using namespace std;

int main() {
	int resolution = ConfigurationManager::getGridResolutionCM() /
			ConfigurationManager::getMapResolutionCM();

	position start = {2.10,-2.9,dtor(20)};

	// Init and start classes
	Map map;

	PathPlanner path(&map,
			ConfigurationManager::getStartLocation().x / resolution,
			ConfigurationManager::getStartLocation().y / resolution,
			ConfigurationManager::getGoal().x / resolution,
			ConfigurationManager::getGoal().y / resolution);


	Robot robot("10.10.245.65", 6665, start);
	//Robot robot("localhost", 6665, start);
	//robot.setAddNoise(true);d

	PlnObstacleAvoid plan(&robot);
	Manager manager(&robot, &map, &plan, &path);
	manager.run();

	cout << "Goodbye" << endl;
}





