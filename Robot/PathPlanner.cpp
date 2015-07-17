/*
 * PathPlanner.cpp
 *
 *  Created on: Jun 16, 2015
 *      Author: colman
 */

#include "PathPlanner.h"

PathPlanner::PathPlanner(Map* map, int xStart, int yStart, int xGoal, int yGoal) {
	// Set attributes
	this->setMap(map);
	this->setGrid(map->getBlowGrid());
	this->setStartIndex(yStart, xStart, 0, 0);
	this->setGoalIndex(yGoal, xGoal, 0, 0);

	// Calculations
	this->calcHeuristicFunction();
	this->calcPriorities();
	this->search();
}

PathPlanner::~PathPlanner() {
	for (int h = 0; h < _map->getWidthBlowGrid(); h++){
		delete [] this->_grid[h];
	}
	delete [] this->_grid;
}

void PathPlanner::setStartIndex(int y, int x, int g, int f){
	this->_start.currLoc.y = y;
	this->_start.currLoc.x = x;
	this->_start.g = g;
	this->_start.f = f;
}

void PathPlanner::setGoalIndex(int y, int x, int g, int f){
	this->_goal.currLoc.y = y;
	this->_goal.currLoc.x = x;
	this->_goal.g = g;
	this->_goal.f = f;
}

void PathPlanner::setGrid(cellGrid** grid){
	this->_grid = grid;
}

void PathPlanner::setMap(Map* map){
	this->_map = map;
}

void PathPlanner::setWayPoint(wayPoint wayPoint){
	this->_wayPoints.push_back(wayPoint);
}

Acell PathPlanner::getStartIndex(){
	return this->_start;
}

Acell PathPlanner::getGoalIndex(){
	return this->_goal;
}

cellGrid** PathPlanner::getGrid(){
	return this->_grid;
}

Map* PathPlanner::getMap(){
	return this->_map;
}

vector <wayPoint> PathPlanner::getWayPoints(){
	return this->_wayPoints;
}

bool compare(const Acell& first, const Acell& second){
  if (first.f < second.f)
    return true;
  else
    return false;
}

void PathPlanner::search(){

	list<Acell> openCells;
	list<Acell> closeCells;
	list<Acell>::iterator it;
	Acell newCell;
	bool found = false; 	// Flag that is set when search complete
	bool resign = false;	// Flag set if we can't find expand
	int counter = 0;
	int cost = 0;

	// Insert start cell
	it = openCells.begin();
	openCells.insert(it, this->_start);

	// Set the start index cell
	this->getGrid()[this->getStartIndex().currLoc.y][this->getStartIndex().currLoc.x].g = cost;
	this->getGrid()[this->getStartIndex().currLoc.y][this->getStartIndex().currLoc.x].expandOrder = counter;
	this->getGrid()[this->getStartIndex().currLoc.y][this->getStartIndex().currLoc.x].dirArrival = 0;

	cost++;
	counter++;

	// As long as we have not reached the goal or have a possible route
	while((found == false) && (resign == false)){
		// Check if we still have elements on the open list
		if (openCells.empty()){
			resign = true;
			cout << "Faild" << endl;
		}
		else{
			// Get the element with the smaller g value
			openCells.sort(compare);
			it = openCells.begin();

			// If we got the goal
			if (((*it).currLoc.x == this->getGoalIndex().currLoc.x) &&
					((*it).currLoc.y == this->getGoalIndex().currLoc.y)){
				found = true;
				cout << "Find Goal" << endl;
			}
			else{
				// Move on all the directions
				for (int i = 0; i < 8; i++){
					newCell.currLoc.x = (*it).currLoc.x + DIR_VEC[i].x;
					newCell.currLoc.y = (*it).currLoc.y + DIR_VEC[i].y;
					newCell.dirArrival = i;

					// If in the grid
					if ((newCell.currLoc.x >= 0)&&(newCell.currLoc.x < this->getMap()->getWidthBlowGrid()) &&
							(newCell.currLoc.y >= 0)&&(newCell.currLoc.y < this->getMap()->getHeightBlowGrid())){

						if((this->isExistListByLoc(openCells.begin(), openCells.end(), newCell.currLoc) == false)&&
							(this->getGrid()[newCell.currLoc.y][newCell.currLoc.x].closed == false)&&
							(this->getGrid()[newCell.currLoc.y][newCell.currLoc.x].color != GeneralService::C_BLACK)){

							this->getGrid()[newCell.currLoc.y][newCell.currLoc.x].g = (*it).g + cost;
							this->getGrid()[newCell.currLoc.y][newCell.currLoc.x].expandOrder = counter;
							this->getGrid()[newCell.currLoc.y][newCell.currLoc.x].dirArrival = i;
							counter++;

							newCell.g = (*it).g + cost;
							newCell.f = this->getGrid()[newCell.currLoc.y][newCell.currLoc.x].g +
									this->getGrid()[newCell.currLoc.y][newCell.currLoc.x].h +
									this->getGrid()[newCell.currLoc.y][newCell.currLoc.x].f;
							openCells.push_back(newCell);
						}
					}
				}

				this->getGrid()[(*it).currLoc.y][(*it).currLoc.x].closed = true;
				openCells.erase(it);
			}
		}
	}

	if(found){
		this->plan();
		this->getMap()->gridToPng(GeneralService::PNG_BLOW_GRID, this->getGrid(),
				this->getMap()->getWidthBlowGrid(), this->getMap()->getHeightBlowGrid());
	}
}

void PathPlanner::plan(){
	vector <wayPoint> wayPoints;

	wayPoint point = {this->getGoalIndex().currLoc.x, this->getGoalIndex().currLoc.y, 0};
	wayPoint next;

	while ((point.pointLoc.x != this->getStartIndex().currLoc.x) || (point.pointLoc.y != this->getStartIndex().currLoc.y)){
		this->getGrid()[point.pointLoc.y][point.pointLoc.x].color = GeneralService::C_GREEN;

		next.pointLoc.x = point.pointLoc.x - DIR_VEC[this->getGrid()[point.pointLoc.y][point.pointLoc.x].dirArrival].x;
		next.pointLoc.y = point.pointLoc.y - DIR_VEC[this->getGrid()[point.pointLoc.y][point.pointLoc.x].dirArrival].y;
		next.dirArrival = this->getGrid()[point.pointLoc.y][point.pointLoc.x].dirArrival;
		this->setWayPoint(point);
		point = next;
	}
}

void PathPlanner::calcHeuristicFunction(){
	DIR diriction = DOWN;
	int counter;

	for(int y = 0; y < this->getMap()->getHeightBlowGrid(); y++){
		counter = this->_goal.currLoc.y + this->_goal.currLoc.x - y;
		for(int x = 0; x < this->getMap()->getWidthBlowGrid(); x++){

			this->getGrid()[y][x].h = counter;
			if (diriction == DOWN){
				counter--;
			}
			else{
				counter++;
			}

			if (counter == 0){
				diriction = UP;
			}
		}
	}
}

void PathPlanner::calcPriorities(){
	for (int y = 0; y < this->getMap()->getHeightBlowGrid(); y++){
		for (int x = 0; x < this->getMap()->getWidthBlowGrid(); x++){
			for (int i = 0; i < 8; i++){
				if (((x + DIR_VEC[i].x) >= 0)&&((x + DIR_VEC[i].x) < this->getMap()->getWidthBlowGrid()) &&
					((y + DIR_VEC[i].y) >= 0)&&((y +DIR_VEC[i].y) < this->getMap()->getHeightBlowGrid())){
					if (this->_grid[y + DIR_VEC[i].y][x + DIR_VEC[i].x].color == GeneralService::C_BLACK){
						this->_grid[y][x].f += GeneralService::P_BLACK;
					}
					if (this->_grid[y + DIR_VEC[i].y][x + DIR_VEC[i].x].color == GeneralService::C_GRAY){
						this->_grid[y][x].f += GeneralService::P_GRAY;
					}
					else{
						this->_grid[y][x].f += GeneralService::P_WHITE;
					}
				}
			}
		}
	}
}

bool PathPlanner::isExistListByLoc(list<Acell>::iterator begin, list<Acell>::iterator end, location loc){
	while (begin != end){
		if (((*begin).currLoc.x == loc.x) && ((*begin).currLoc.y == loc.y)){
			return true;
		}
		++begin;
	}
	return false;
}
