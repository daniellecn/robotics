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

struct cellGrid{
	unsigned char color;
	int priority;
};

class Map {
public:

	Map();
	virtual ~Map();

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

private:
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
	cellGrid 	calcGridCell(std::vector<unsigned char> map, int widthMap, int resolution, unsigned yStart, unsigned xStart);
	void 		blowMap(std::vector<unsigned char> map, int widthMap, int heightMap, int numPixelsToBlow, const char* blowFileName);
	void 		mapToGrid(std::vector<unsigned char> map, cellGrid **grid, unsigned widthMap, unsigned heightMap,
							int widthGrid, int heightGrid, int resolution);
	static void gridToPng(const char* fileName, cellGrid **grid, int widthGrid, int heightGrid);
};

#endif /* MAP_H_ */
