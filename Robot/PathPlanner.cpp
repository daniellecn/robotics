/*
 * PathPlanner.cpp
 *
 *  Created on: Jun 16, 2015
 *      Author: colman
 */

#include "PathPlanner.h"

PathPlanner::PathPlanner(Map map, int xStart, int yStart, int xGoal, int yGoal) {
	// TODO Auto-generated constructor stub
	location loc;
	Acell cell;
	this->_grid = map.getBlowGrid();

	loc.x = xStart;
	loc.y = yStart;
	cell.currLoc = loc;
	cell.g = 0;
	this->_start = cell;

	loc.x = xGoal;
	loc.y = yGoal;
	cell.currLoc = loc;
	cell.g = 0;
	this->_goal = cell;

	this->search(map);
}

PathPlanner::~PathPlanner() {
	// TODO Auto-generated destructor stub
}

bool compare(const Acell& first, const Acell& second){
  if (first.g < second.g)
    return true;
  else
    return false;
}

void PathPlanner::search(Map map){

	list<Acell> openCells;
	list<Acell> closeCells;
	list<Acell>::iterator it;
	Acell newCell;
	bool found = false; 	// Flag that is set when search complete
	bool resign = false;	// Flag set if we can't find expand

	it = openCells.begin();
	openCells.insert(it, this->_start);

	while((found == false) && (resign == false)){
		// Check if we still have elements on the open list
		if (openCells.empty()){
			resign = true;
			cout << "Faild" << endl;
		}
		else{
			// Get the element with the smaller g value
			openCells.sort(compare);
			openCells.reverse(); // Check about pop_front, pop_back

			if (((*it).currLoc.x == this->_goal.currLoc.x) && ((*it).currLoc.y == this->_goal.currLoc.y)){
				found = true;
				//cout << (*it).currLoc.x << " " << (*it).currLoc.y << endl;
				cout << "Find Goal" << endl;
			}
			else{
				for (int i = 0; i < 4; i++){
					newCell.currLoc.x = (*it).currLoc.x + DIR_VEC[i].x;
					newCell.currLoc.y = (*it).currLoc.y + DIR_VEC[i].y;

					if ((newCell.currLoc.x >= 0)&&(newCell.currLoc.x < map.getWidthBlowGrid()) &&
							(newCell.currLoc.y >= 0)&&(newCell.currLoc.y < map.getHeightBlowGrid())){

						if((this->findInListByLoc(closeCells.begin(), closeCells.end(), newCell.currLoc)) &&
							(this->_grid[newCell.currLoc.y][newCell.currLoc.x].color != C_BLACK)){
							newCell.g = (*it).g + this->_cost;
							openCells.push_back(newCell);
						}
					}
				}
				closeCells.push_back((*it));
			}

			this->_cost++;
		}
	}
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

bool PathPlanner::findInListByLoc(list<Acell>::iterator it1, list<Acell>::iterator it2, location loc){
	while (it1 != it2){
		if (((*it1).currLoc.x == loc.x) && ((*it1).currLoc.y == loc.y)){
			return true;
		}
		++it1;
	}
	return false;
}
