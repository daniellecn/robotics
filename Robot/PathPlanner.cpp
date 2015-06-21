/*
 * PathPlanner.cpp
 *
 *  Created on: Jun 16, 2015
 *      Author: colman
 */

#include "PathPlanner.h"

PathPlanner::PathPlanner(Map* map, int xStart, int yStart, int xGoal, int yGoal) {
	// TODO Auto-generated constructor stub
	_map = map;
	location loc;
	Acell cell;
	this->_grid = map->getBlowGrid();
	this->_cost = 0;

	loc.x = xStart;
	loc.y = yStart;
	cell.currLoc = loc;
	cell.f = this->_cost;
	this->_start = cell;

	loc.x = xGoal;
	loc.y = yGoal;
	cell.currLoc = loc;
	cell.f = this->_cost;
	this->_goal = cell;


	this->calcHeuristicFunction(map);
	cout << "before search" << endl;
	this->search(map);

	cout << "end search" << endl;
	//this->checkGValue(map);
}

PathPlanner::~PathPlanner() {
	// TODO Auto-generated destructor stub
	for (int h = 0; h < _map->getWidthBlowGrid(); h++){
		delete [] this->_grid[h];
	}
	delete [] this->_grid;
}

bool compare(const Acell& first, const Acell& second){
  if (first.f < second.f)
    return true;
  else
    return false;
}

void PathPlanner::search(Map* map){

	list<Acell> openCells;
	list<Acell> closeCells;
	list<Acell>::iterator it;
	Acell newCell;
	bool found = false; 	// Flag that is set when search complete
	bool resign = false;	// Flag set if we can't find expand
	int counter = 0;

	it = openCells.begin();
	openCells.insert(it, this->_start);

	this->_grid[this->_start.currLoc.y][this->_start.currLoc.x].g = this->_cost;
	this->_grid[this->_start.currLoc.y][this->_start.currLoc.x].expandOrder = counter;
	this->_grid[this->_start.currLoc.y][this->_start.currLoc.x].dirArrival = 0;
	this->_cost++;
	counter++;

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

			if (((*it).currLoc.x == this->_goal.currLoc.x) && ((*it).currLoc.y == this->_goal.currLoc.y)){
				found = true;
				cout << "Find Goal" << endl;
			}
			else{
				// Move on all the directions
				for (int i = 0; i < 4; i++){
					newCell.currLoc.x = (*it).currLoc.x + DIR_VEC[i].x;
					newCell.currLoc.y = (*it).currLoc.y + DIR_VEC[i].y;

					// If in the grid
					if ((newCell.currLoc.x >= 0)&&(newCell.currLoc.x < map->getWidthBlowGrid()) &&
							(newCell.currLoc.y >= 0)&&(newCell.currLoc.y < map->getHeightBlowGrid())){

						if((this->isExistListByLoc(openCells.begin(), openCells.end(), newCell.currLoc) == false)&&
							(this->_grid[newCell.currLoc.y][newCell.currLoc.x].closed == false)&&
							(this->_grid[newCell.currLoc.y][newCell.currLoc.x].color != C_BLACK)){

							this->_grid[newCell.currLoc.y][newCell.currLoc.x].g = (*it).g + this->_cost;
							this->_grid[newCell.currLoc.y][newCell.currLoc.x].expandOrder = counter;
							this->_grid[newCell.currLoc.y][newCell.currLoc.x].dirArrival = i;
							counter++;

							newCell.g = (*it).g + this->_cost;
							newCell.f = this->_grid[newCell.currLoc.y][newCell.currLoc.x].g +
									this->_grid[newCell.currLoc.y][newCell.currLoc.x].h;
							openCells.push_back(newCell);
						}
					}
				}

				this->_grid[(*it).currLoc.y][(*it).currLoc.x].closed = true;
				openCells.erase(it);
			}
		}
	}

	cout << "before plan" << endl;
	if(found){
		this->plan();
		map->gridToPng("blowGrid.png", this->_grid, map->getWidthBlowGrid(), map->getHeightBlowGrid());
		cout << "end plan" << endl;
	}
}

vector <location> PathPlanner::plan(){
	vector <location> wayPoints;

	location loc = {this->_goal.currLoc.x, this->_goal.currLoc.y};
	location next;

	while ((loc.x != this->_start.currLoc.x) || (loc.y != this->_start.currLoc.y)){
		cout << loc.x << " " << loc.y << endl;
		loc.x = loc.x - DIR_VEC[this->_grid[loc.y][loc.x].dirArrival].x;
		loc.y = loc.y - DIR_VEC[this->_grid[loc.y][loc.x].dirArrival].y;
		this->_grid[loc.y][loc.x].color = C_GREEN;
		wayPoints.push_back(loc);
	}

	return wayPoints;
}

Acell PathPlanner::calcCell(DIR dir, Acell currCell){
	Acell newCell;

	if ((this->_grid[currCell.currLoc.x + DIR_VEC[dir].x][currCell.currLoc.y + DIR_VEC[dir].y].color) == C_WHITE){
		newCell.currLoc.x = currCell.currLoc.x + DIR_VEC[dir].x;
		newCell.currLoc.y = currCell.currLoc.y + DIR_VEC[dir].y;
		newCell.g = this->_cost;
	}
	else{
		newCell.currLoc.x = NULL;
		newCell.currLoc.y= NULL;
		newCell.g = NULL;
	}

	return newCell;
}

void PathPlanner::calcHeuristicFunction(Map* map){
	DIR diriction = DOWN;
	int counter;

	for(int y = 0; y < map->getHeightBlowGrid(); y++){
		counter = this->_goal.currLoc.y + this->_goal.currLoc.x - y;
		for(int x = 0; x < map->getWidthBlowGrid(); x++){
			if ((x == 120) && (y == 97)){
				cout << "CHange" << endl;
			}

			this->_grid[y][x].h = counter;
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


/*	int counter = this->_goal.currLoc.y + this->_goal.currLoc.x;
	int limit = this->_goal.currLoc.y + this->_goal.currLoc.x;;

	int x = 0;
	int y = 0;

	while(counter != 0){
		this->_grid[y][x].h = counter;
		--x;
		++y;
	}

	for(int y = 0; y < limit; y++){
		int yS = 0;
		for(int x = y; x >= 0; x--){
			this->_grid[yS][x].h = counter;
			yS++;
		}
		--counter;
	}



	while(counter != 0){
		this->_grid[y][x].h = counter;
	}*/
	/*this->_grid[this->_goal.currLoc.y][this->_goal.currLoc.x].h= counter;
	counter++;*/

/*//	if ((newCell.currLoc.x >= 0)&&(newCell.currLoc.x < map.getWidthBlowGrid()) &&
//								(newCell.currLoc.y >= 0)&&(newCell.currLoc.y < map.getHeightBlowGrid()))


	for(int y = this->_goal.currLoc.y + 1; y < map.getHeightBlowGrid(); y++){

	}


	while (this->_grid[this->_start.currLoc.y][this->_start.currLoc.x.].h != NULL){
		for (int y = this->_goal.currLoc.y - counter; y > 0; y++){
			for (int x = this->_goal.currLoc.x - counter; x > 0; x++){
				if (((y >= 0) && (y < map.getHeightBlowGrid()) &&
						(x >= 0) && (x < map.getWidthBlowGrid()))){
					this->_grid[y][x].h = counter;
				}
			}

		}
	}*/
}

void PathPlanner::checkGValue(Map* map){
	for (int y = 0; y < map->getHeightBlowGrid(); y++){
		cout << "[ ";
		for (int x = 0; x < map->getWidthBlowGrid(); x++){
			cout << this->_grid[y][x].g << ",";
		}
		cout << " ]" << endl;
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
