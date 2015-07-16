/*
 * Map.h
 *
 *  Created on: Jun 2, 2015
 *      Author: colman
 */

#ifndef MAP_H_
#define MAP_H_

#include "GeneralService.h"
#include "ConfigurationManager.h"
#include "pngUtil.h"
#include "lodepng.h"

using namespace std;

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

	int							xPosToIndex(int xPosCm);
	int							yPosToIndex(int yPosCm);
	int 						xPosToIndexLocal(float xPos);
	int 						yPosToIndexLocal(float xPos);

	void changePixelColor(vector<unsigned char>* map, int widthMap, int y, int x, unsigned char color);
	void gridToPng(const char* fileName, cellGrid **grid, int widthGrid, int heightGrid);

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
	void 		blowMap(vector<unsigned char> map, int widthMap, int heightMap, int numPixelsToBlow, const char* blowFileName);
	void 		mapToGrid(vector<unsigned char> map, cellGrid **grid, unsigned widthMap, unsigned heightMap,
							int widthGrid, int heightGrid, int resolution);

};

#endif /* MAP_H_ */
