/*
 * Map.cpp
 *
 *  Created on: Jun 2, 2015
 *      Author: colman
 */

#include "Map.h"

Map::Map() {
	std::vector<unsigned char> map; //the raw pixels
	unsigned widthMap, heightMap;

	//*****Map*********
	unsigned error = lodepng::decode(map, widthMap, heightMap, "/usr/robotics/PcBotWorld/roboticLabMap.png");
	this->setWidthMap(widthMap);
	this->setHeightMap(heightMap);

	if (error)
		std::cout << "decoder error " << error << ": "
				<< lodepng_error_text(error) << std::endl;

	// Set attributes
	// TODO Read param
	this->setNumPixelsToBlow(this->cmToPixel(15)); // TODO Conversion from cm (cfg) to pixels
	this->setWidthGrid(this->getWidthMap() / (10 / 2.5));
	this->setHeightGrid(this->getHeightMap() / (10 / 2.5));

	//*****Grid********
	this->_grid = new cellGrid*[this->getHeightGrid()];

	for (int h = 0; h < this->getHeightGrid(); h++){
		this->_grid[h] = new cellGrid[this->getWidthGrid()];
	}

	this->mapToGrid(map, this->getGrid(), this->getWidthMap(), this->getHeightMap(), this->getWidthGrid(), this->getHeightGrid(), 10);

	this->gridToPng("grid.png", this->getGrid(), this->getWidthGrid(), this->getHeightGrid());

	//*****Blow*Map****
	blowMap(map, this->getWidthMap(), this->getHeightMap(), this->getNumPixelsToBlow(), "roboticLabMapBlow.png");
	this->setWidthBlowGrid(this->getWidthBlowMap() / (10 / 2.5));
	this->setHeightBlowGrid(this->getHeightBlowMap() / (10 / 2.5));

	//*****Blow*Grid***
	this->_blowGrid = new cellGrid*[this->getHeightBlowGrid()];

	for (int h = 0; h < this->getHeightBlowGrid(); h++){
		this->_blowGrid[h] = new cellGrid[this->getWidthBlowGrid()];
	}

	this->mapToGrid(this->getBlowMap(), this->getBlowGrid(), this->getWidthBlowMap(), this->getHeightBlowMap(),
			this->getWidthBlowGrid(), this->getHeightBlowGrid(), 10);

	this->gridToPng("blowGrid.png", this->getBlowGrid(), this->getWidthBlowGrid(), this->getHeightBlowGrid());
	cout << "END" << endl;
}

Map::~Map() {
	for (int h = 0; h < this->getWidthGrid(); h++){
		delete [] this->_grid[h];
	}
	delete [] this->_grid;

	for (int h = 0; h < this->getWidthGrid(); h++){
		delete [] this->_blowGrid[h];
	}
	delete [] this->_blowGrid;
}

unsigned Map::getWidthMap(){
	return this->_widthMap;
}

unsigned Map::getHeightMap(){
	return this->_heightMap;
}

unsigned Map::getHeightBlowMap(){
	return this->_heightBlowMap;
}

unsigned Map::getWidthBlowMap(){
	return this->_widthBlowMap;
}

int Map::getNumPixelsToBlow(){
	return this->_numPixelsToBlow;
}

std::vector<unsigned char> Map::getBlowMap(){
	return this->_blowMap;
}

cellGrid** Map::getBlowGrid(){
	return this->_blowGrid;
}

cellGrid** Map::getGrid(){
	return this->_grid;
}

int Map::getWidthGrid(){
	return this->_widthGrid;
}

int Map::getHeightGrid(){
	return this->_heightGrid;
}

int Map::getWidthBlowGrid(){
	return this->_widthBlowGrid;
}

int Map::getHeightBlowGrid(){
	return this->_heightBlowGrid;
}

void Map::setHeightBlowMap(unsigned height){
	this->_heightBlowMap = height;
}

void Map::setWidthBlowMap(unsigned width){
	this->_widthBlowMap = width;
}

void Map::setNumPixelsToBlow(int numPixelsToBlow){
	this->_numPixelsToBlow = numPixelsToBlow;
}

// Set a section to color
void Map::setBlowMap(unsigned yStart, unsigned yEnd, unsigned xStart, unsigned xEnd, unsigned char color){
	for (unsigned yDye = yStart; yDye < yEnd; yDye++){
		for (unsigned xDye = xStart; xDye < xEnd; xDye++){
			// If the cell is NOT darker
			if (((this->_blowMap[yDye * this->getWidthBlowMap() * 4 + xDye * 4 + 0] ) > color) ||
				((this->_blowMap[yDye * this->getWidthBlowMap() * 4 + xDye * 4 + 1] ) > color ) ||
				((this->_blowMap[yDye * this->getWidthBlowMap() * 4 + xDye * 4 + 2] ) > color)){

				this->_blowMap[yDye * this->getWidthBlowMap() * 4 + xDye * 4 + 0] = color;
				this->_blowMap[yDye * this->getWidthBlowMap() * 4 + xDye * 4 + 1] = color;
				this->_blowMap[yDye * this->getWidthBlowMap() * 4 + xDye * 4 + 2] = color;
				this->_blowMap[yDye * this->getWidthBlowMap() * 4 + xDye * 4 + 3] = 255;
			}
		}
	}
}

void Map::setWidthMap(unsigned width){
	this->_widthMap = width;
}

void Map::setHeightMap(unsigned height){
	this->_heightMap = height;
}

void Map::setWidthGrid(int width){
	this->_widthGrid = width;
}

void Map::setHeightGrid(int height){
	this->_heightGrid = height;
}

void Map::setWidthBlowGrid(int width){
	this->_widthBlowGrid = width;
}

void Map::setHeightBlowGrid(int height){
	this->_heightBlowGrid = height;
}

void Map::setGridCell(cellGrid **grid, int y, int x, cellGrid cell){
	//this->_blowGrid[y][x] = cell;
	grid[y][x] = cell;
}

// Initialize the blow map to WHITE base
void Map::initBlowMap(){
	for (unsigned yDye = 0; yDye < this->getHeightBlowMap(); yDye++){
		for (unsigned xDye = 0; xDye < this->getWidthBlowMap(); xDye++){
			this->_blowMap[yDye * this->getWidthBlowMap() * 4 + xDye * 4 + 0] = C_WHITE;
			this->_blowMap[yDye * this->getWidthBlowMap() * 4 + xDye * 4 + 1] = C_WHITE;
			this->_blowMap[yDye * this->getWidthBlowMap() * 4 + xDye * 4 + 2] = C_WHITE;
			this->_blowMap[yDye * this->getWidthBlowMap() * 4 + xDye * 4 + 3] = 255;
		}
	}
}

// Blow the map to avoid obstacles
void Map::blowMap(std::vector<unsigned char> map, int widthMap, int heightMap, int numPixelsToBlow, const char* blowFileName){
	unsigned xNav, yNav;
	unsigned xBlow, yBlow;

	// Set blow map size
	this->setWidthBlowMap(widthMap + this->getNumPixelsToBlow()*2);
	this->setHeightBlowMap(heightMap + this->getNumPixelsToBlow()*2);

	this->_blowMap.resize((this->getWidthBlowMap() * this->getHeightBlowMap()) * 4);

	// Init blow map WHITE
	this->initBlowMap();

	/***************FRAME******************/
	// Top frame
	this->setBlowMap(0, this->getNumPixelsToBlow(),
					 0, this->getWidthBlowMap(),
					 C_GRAY_D);

	// Bottom frame
	this->setBlowMap(heightMap + this->getNumPixelsToBlow(), this->getHeightBlowMap(),
					 0, this->getWidthBlowMap(),
					 C_GRAY_D);

	// Left frame
	this->setBlowMap(0, this->getHeightBlowMap(),
					 0, this->getNumPixelsToBlow(),
					 C_GRAY_D);

	// Right frame
	this->setBlowMap(0, this->getHeightBlowMap(),
			widthMap + this->getNumPixelsToBlow(), this->getWidthBlowMap(),
					 C_GRAY_D);
	/***********END*FRAME******************/

	// Move on the map
	yBlow = this->getNumPixelsToBlow();
	for (yNav = 0; yNav < heightMap; yNav++){
		xBlow = numPixelsToBlow;
		for (xNav = 0; xNav < widthMap; xNav++){
			// If the cell is BLACK
			if (map[yNav * widthMap * 4 + xNav * 4 + 0] == C_BLACK
			 				|| map[yNav * widthMap * 4 + xNav * 4 + 1] == C_BLACK
			 				|| map[yNav * widthMap * 4 + xNav * 4 + 2] == C_BLACK){

				// Blow the pixel in two levels
				this->setBlowMap(yBlow - this->getNumPixelsToBlow(), yBlow + this->getNumPixelsToBlow(),
								 xBlow - this->getNumPixelsToBlow(), xBlow + this->getNumPixelsToBlow(),
								 C_GRAY_B);

				this->setBlowMap(yBlow - this->getNumPixelsToBlow()/2, yBlow + this->getNumPixelsToBlow()/2,
								 xBlow - this->getNumPixelsToBlow()/2, xBlow + this->getNumPixelsToBlow()/2,
								 C_GRAY_D);

				// Set the BLACK pixel
				this->setBlowMap(yBlow, yBlow + 1, xBlow, xBlow + 1, C_BLACK);
			}
			xBlow++;
		}
		yBlow++;
	}

	// Export to PNG file
	encodeOneStep(blowFileName, this->getBlowMap(), this->getWidthBlowMap(), this->getHeightBlowMap());
}

// Conversion from CM to pixels
int Map::cmToPixel(int cm){
	return cm / 2.5;
}

// Calculation grid cell properties
cellGrid Map::calcGridCell(std::vector<unsigned char> map, int widthMap, int cellCm, unsigned yStart, unsigned xStart){
	// TODO: calc cm to Pixel
	cellGrid cell;
	cell.color = C_WHITE;
	cell.priority = 0;

	// Calculate the color and priority of the cell
	for (unsigned y = yStart; y < yStart + this->cmToPixel(cellCm); y++){
		for (unsigned x = xStart; x < xStart + this->cmToPixel(cellCm); x++){
			if (((map[y * widthMap * 4 + x * 4 + 0] ) == C_BLACK) ||
				((map[y * widthMap * 4 + x * 4 + 1] ) == C_BLACK) ||
				((map[y * widthMap * 4 + x * 4 + 2] ) == C_BLACK)){
				cell.color = C_BLACK;
				cell.priority += P_BLACK;
			}
			else if (((map[y * widthMap * 4 + x * 4 + 0] ) == C_GRAY_D) ||
					((map[y * widthMap * 4 + x * 4 + 1] ) == C_GRAY_D) ||
					((map[y * widthMap * 4 + x * 4 + 2] ) == C_GRAY_D)){
					cell.color = C_BLACK;
					cell.priority += P_GRAY_D;
			}
			else if (((map[y * widthMap * 4 + x * 4 + 0] ) == C_GRAY_B) ||
					((map[y * widthMap * 4 + x * 4 + 1] ) == C_GRAY_B ) ||
					((map[y * widthMap * 4 + x * 4 + 2] ) == C_GRAY_B)){
				cell.color = C_BLACK;
				cell.priority += P_GRAY_B;
			}
			else if (((map[y * widthMap * 4 + x * 4 + 0] ) == C_WHITE) ||
					((map[y * widthMap * 4 + x * 4 + 1] ) == C_WHITE ) ||
					((map[y * widthMap * 4 + x * 4 + 2] ) == C_WHITE)){
				cell.priority += P_WHITE;
			}
		}
	}
	return cell;
}

// Conversion map to grid according to Resolution
void Map::mapToGrid(std::vector<unsigned char> map, cellGrid **grid, unsigned widthMap, unsigned heightMap,
		int widthGrid, int heightGrid, int resolution){
	unsigned yMapStart = 0;
	unsigned xMapStart = 0;

	// Move on the grid
	for(int yGrid = 0; yGrid <= heightGrid; yGrid++){
		if (yMapStart + this->cmToPixel(resolution) < heightMap){
			for(int xGrid = 0; xGrid <= widthGrid; xGrid++){

				if (xMapStart + this->cmToPixel(resolution) < widthMap){
					// Calculate grid cell
					grid[yGrid][xGrid] = this->calcGridCell(map, widthMap, resolution, yMapStart, xMapStart);
					xMapStart += this->cmToPixel(resolution);
				}
			}
		}
		yMapStart += this->cmToPixel(resolution); // TODO param
		xMapStart = 0;
	}

}

void Map::gridToPng(const char* fileName, cellGrid **grid, int widthGrid, int heightGrid){
	std::vector<unsigned char> image; //the raw pixels
	image.resize(widthGrid * heightGrid * 4);

	unsigned char color;
	for (int y = 0; y < heightGrid; y++){
		for (int x = 0; x < widthGrid; x++) {
			if (grid[y][x].color == C_BLACK){
				color = C_BLACK;
			}
			else {
				color = C_WHITE;
			}

			image[y * widthGrid * 4 + x * 4 + 0] = color;
			image[y * widthGrid * 4 + x * 4 + 1] = color;
			image[y * widthGrid * 4 + x * 4 + 2] = color;
			image[y * widthGrid * 4 + x * 4 + 3] = 255;
		}
	}

	if (fileName == "blowGrid.png"){
		// Set start and goal on the map
		// RED - START
		int y;
		int x;

		// START - RED
		y = this->yPosToIndex(362, this->getHeightBlowGrid());
		x = this->xPosToIndex(305, this->getWidthBlowGrid());

		x = 90;
		y = 76;

		image[y * widthGrid * 4 + x * 4 + 0] = 255;
		image[y * widthGrid * 4 + x * 4 + 1] = 0;
		image[y * widthGrid * 4 + x * 4 + 2] = 0;
		image[y * widthGrid * 4 + x * 4 + 3] = 255;

		// GOAL - BLUE
		y = this->yPosToIndex(169, this->getHeightBlowGrid());
		x = this->xPosToIndex(138, this->getWidthBlowGrid());

		x = 42;
		y = 34;

		image[y * widthGrid * 4 + x * 4 + 0] = 0;
		image[y * widthGrid * 4 + x * 4 + 1] = 0;
		image[y * widthGrid * 4 + x * 4 + 2] = 255;
		image[y * widthGrid * 4 + x * 4 + 3] = 255;
	}

	encodeOneStep(fileName, image, widthGrid, heightGrid);
}

int Map::xPosToIndex(int xPosCm, int width){
	//return ((width / 2) + (xPosCm / 10)); // TODO : Resolution
	return (xPosCm / 4);
}

int Map::yPosToIndex(int yPosCm, int height){
	//return ((height / 2) + (yPosCm / 10)); // TODO : Resolution
	return (yPosCm / 4);
}

/*int Map::xPosToIndexLocal(float xPos){
	int xIndex = ((getWidthGrid() / 2) + (xPos / 10));

	if (xIndex < 0) {
		xIndex = 0;
	} else if (xIndex >= getWidthGrid()) {
		xIndex = getWidthGrid() -1;
	}

	return xIndex;
}

int Map::yPosToIndexLocal(float yPos){
	int yIndex = ((getHeightGrid() / 2) - (yPos / 10));

	if (yIndex < 0) {
		yIndex = 0;
	} else if (yIndex >= getHeightGrid()) {
		yIndex = getHeightGrid() -1;
	}

	return yIndex;
}*/
