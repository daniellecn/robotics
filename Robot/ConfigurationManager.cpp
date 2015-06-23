/*
 * ConfigurationManager.cpp
 *
 *  Created on: Jun 21, 2015
 *      Author: colman
 */

#include "ConfigurationManager.h"

	string 		ConfigurationManager::_mapPath = "";
	Position	ConfigurationManager::_startLocation = {0, 0, 0};
	location 	ConfigurationManager::_goal = {0, 0};
	robotSize 	ConfigurationManager::_robotSize = {0, 0};
	float		ConfigurationManager::_mapResolutionCM = 0;
	float 		ConfigurationManager::_gridResolutionCM = 0;

string ConfigurationManager::getParameter(string paramName){
	ifstream paramsFile;
	string   line;
	string readParamName;
	int found;
	string returnVal;
	paramsFile.open("parameters.txt");

	//Check if the file is open
	if(paramsFile.is_open())
	{
		while(returnVal.empty() || paramsFile.eof()){
			getline(paramsFile, line);
			found = line.find(' ');
			readParamName = line.substr(0, found - 1);

			if	(paramName.compare(readParamName) == 0){
				returnVal = line.substr(found + 1);
			}
		}

		paramsFile.close();

		if	(returnVal.empty()){
			cout << "Parameters file error" << endl;
		}
	}
	else {
		cout << "Parameters file error" << endl;
	}
	return returnVal;
}

string ConfigurationManager::getMapPath(){
	if (ConfigurationManager::_mapPath.empty()){
		ConfigurationManager::_mapPath = ConfigurationManager::getParameter(GeneralService::P_MAP_PATH);
	}

	return ConfigurationManager::_mapPath;
}

Position ConfigurationManager::getStartLocation(){
	string data;
	int found;

	if ((ConfigurationManager::_startLocation.x == 0) &&
		(ConfigurationManager::_startLocation.y == 0) &&
		(ConfigurationManager::_startLocation.yaw == 0)) {

		data = ConfigurationManager::getParameter(GeneralService::P_START_LOCATION);

		found = data.find(' ');
		ConfigurationManager::_startLocation.x = atoi(data.substr(0, found).c_str());
		data.erase(0, found + 1);

		found = data.find(' ');
		ConfigurationManager::_startLocation.y = atoi(data.substr(0, found).c_str());
		data.erase(0, found + 1);

		found = data.find(' ');
		ConfigurationManager::_startLocation.yaw = atoi(data.substr(0, found).c_str());
	}

	return ConfigurationManager::_startLocation;
}

location ConfigurationManager::getGoal(){
	string data;
	int found;

	if((ConfigurationManager::_goal.x == 0) &&
		(ConfigurationManager::_goal.y == 0)){

		data = ConfigurationManager::getParameter(GeneralService::P_GOAL);

		found = data.find(' ');
		ConfigurationManager::_goal.x = atoi(data.substr(0, found).c_str());
		data.erase(0, found + 1);

		found = data.find(' ');
		ConfigurationManager::_goal.y = atoi(data.substr(0, found).c_str());

	}

	return ConfigurationManager::_goal;
}

robotSize ConfigurationManager::getRobotSize(){
	string data;
	int found;

	if ((ConfigurationManager::_robotSize.width == 0) &&
		(ConfigurationManager::_robotSize.height == 0)){
		data = ConfigurationManager::getParameter(GeneralService::P_ROBOT_SIZE);

		found = data.find(' ');
		ConfigurationManager::_robotSize.width = atoi(data.substr(0, found).c_str());
		data.erase(0, found + 1);

		found = data.find(' ');
		ConfigurationManager::_robotSize.height = atoi(data.substr(0, found).c_str());
	}

	return ConfigurationManager::_robotSize;
}

float ConfigurationManager::getMapResolutionCM(){
	string data;
	int found;

	if (ConfigurationManager::_mapResolutionCM == 0){
		data = ConfigurationManager::getParameter(GeneralService::P_ROBOT_SIZE);

		found = data.find(' ');
		ConfigurationManager::_mapResolutionCM = atoi(data.substr(0, found).c_str());
	}

	return ConfigurationManager::_mapResolutionCM;
}

float ConfigurationManager::getGridResolutionCM(){
	string data;
	int found;

	if (ConfigurationManager::_gridResolutionCM == 0){
		data = ConfigurationManager::getParameter(GeneralService::P_ROBOT_SIZE);

		found = data.find(' ');
		ConfigurationManager::_gridResolutionCM = atoi(data.substr(0, found).c_str());
	}

	return ConfigurationManager::_gridResolutionCM;
}
