/*
 * ConfigurationManager.h
 *
 *  Created on: Jun 21, 2015
 *      Author: colman
 */

#ifndef CONFIGURATIONMANAGER_H_
#define CONFIGURATIONMANAGER_H_

#include <iostream>
#include <fstream>
#include <stdlib.h>

//#include "Position.h"
//#include "PathPlanner.h"
#include "GeneralService.h"

using namespace std;

class ConfigurationManager {
private:
	static string 		_mapPath;
	static position 	_startLocation;
	static location 	_goal;
	static robotSize 	_robotSize;
	static float	 	_mapResolutionCM;
	static float 		_gridResolutionCM;

	static string getParameter(string paramName);
public:
	static string 		getMapPath();
	static position 	getStartLocation();
	static location 	getGoal();
	static robotSize 	getRobotSize();
	static float 		getMapResolutionCM();
	static float 		getGridResolutionCM();
};

#endif /* CONFIGURATIONMANAGER_H_ */
