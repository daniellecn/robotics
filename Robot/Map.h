/*
 * Map.h
 *
 *  Created on: Jun 2, 2015
 *      Author: colman
 */

#ifndef MAP_H_
#define MAP_H_

#include <iostream>
#include <vector>
#include "pngUtil.h"
#include "lodepng.h"

using namespace std;

// Colors
const unsigned char C_BLACK = 0;
const unsigned char C_GRAY_D = 110;
const unsigned char C_GRAY_B = 192;
const unsigned char C_WHITE = 255;

//priorities
const int P_BLACK = 0;
const int P_GRAY_D = 1;
const int P_GRAY_B = 2;
const int P_WHITE = 3;

struct cellGrid{
	unsigned char color;
	int priority;
};

class Map {
public:

	Map();
	virtual ~Map();

	unsigned 					getWidthMap();
	unsigned 					getHeightMap();
	unsigned 					getWidthBlowMap();
	unsigned 					getHeightBlowMap();
	int 						getNumPixelsToBlow();
	std::vector<unsigned char>	getBlowMap();
	cellGrid** 				 	getBlowGrid();
	cellGrid** 				 	getGrid();
	int 					 	getWidthGrid();
	int 					 	getHeightGrid();
	int 					 	getWidthBlowGrid();
	int 					 	getHeightBlowGrid();

	int							xPosToIndex(int xPos);
	int							yPosToIndex(int yPos);

private:
	unsigned					_widthMap;
	unsigned					_heightMap;
	unsigned 					_widthBlowMap;
	unsigned 					_heightBlowMap;
	unsigned 					_widthGrid;
	unsigned 					_heightGrid;
	unsigned 					_widthBlowGrid;
	unsigned 					_heightBlowGrid;
	int 						_numPixelsToBlow;
	std::vector<unsigned char> 	_blowMap;
	cellGrid 					**_blowGrid;
	cellGrid 					**_grid;


	void setWidthMap(unsigned width);
	void setHeightMap(unsigned height);
	void setWidthBlowMap(unsigned width);
	void setHeightBlowMap(unsigned height);
	void setNumPixelsToBlow(int numPixelsToBlow);
	void setBlowMap(unsigned yStart, unsigned yEnd, unsigned xStart, unsigned xEnd, unsigned char color);
	void setGridCell(cellGrid **grid, int y, int x, cellGrid cell);
	void setWidthGrid(int width);
	void setHeightGrid(int height);
	void setWidthBlowGrid(int width);
	void setHeightBlowGrid(int height);

	void 		initBlowMap();
	int  		cmToPixel(int cm);
	cellGrid 	calcGridCell(std::vector<unsigned char> map, int widthMap, int cellCm, unsigned yStart, unsigned xStart);
	void 		blowMap(std::vector<unsigned char> map, int widthMap, int heightMap, int numPixelsToBlow, const char* blowFileName);
	void 		mapToGrid(std::vector<unsigned char> map, cellGrid **grid, unsigned widthMap, unsigned heightMap,
							int widthGrid, int heightGrid, int resolution);
	static void gridToPng(const char* fileName, cellGrid **grid, int widthGrid, int heightGrid);
};

#endif /* MAP_H_ */
