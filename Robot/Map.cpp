/*
 * Map.cpp
 *
 *  Created on: Jun 2, 2015
 *      Author: colman
 */

#include "Map.h"

Map::Map() {
	vector<unsigned char> map; //the raw pixels
	unsigned widthMap, heightMap;

	//*****Map*********
	unsigned error = lodepng::decode(map, widthMap, heightMap, "/usr/robotics/PcBotWorld/roboticLabMap.png");//ConfigurationManager::getMapPath());
	this->setWidthMap(widthMap);
	this->setHeightMap(heightMap);

	if (error)
		cout << "decoder error " << error << ": "
				<< lodepng_error_text(error) << endl;

	// Set attributes
	this->setNumPixelsToBlow(this->cmToPixel(ConfigurationManager::getRobotSize().width / 2));
	this->setWidthGrid(this->getWidthMap() /
			(ConfigurationManager::getGridResolutionCM() / ConfigurationManager::getMapResolutionCM()));
	this->setHeightGrid(this->getHeightMap() /
			(ConfigurationManager::getGridResolutionCM() / ConfigurationManager::getMapResolutionCM()));
	cout << "End map" << endl;

	//*****Grid********
	this->_grid = new cellGrid*[this->getHeightGrid()];

	for (int h = 0; h < this->getHeightGrid(); h++){
		this->_grid[h] = new cellGrid[this->getWidthGrid()];
		this->_grid[h]->color = GeneralService::C_WHITE;
		this->_grid[h]->g = 0;
		this->_grid[h]->closed = false;
	}

	this->mapToGrid(map, this->getGrid(), this->getWidthMap(), this->getHeightMap(), this->getWidthGrid(),
			this->getHeightGrid(), ConfigurationManager::getGridResolutionCM());

	this->gridToPng(GeneralService::PNG_GRID, this->getGrid(), this->getWidthGrid(), this->getHeightGrid());
	cout << "End grid" << endl;

	//*****Blow*Map****
	blowMap(map, this->getWidthMap(), this->getHeightMap(), this->getNumPixelsToBlow(), GeneralService::PNG_BLOW_MAP);

	this->setWidthBlowGrid(this->getWidthBlowMap() /
			(ConfigurationManager::getGridResolutionCM() / ConfigurationManager::getMapResolutionCM()));
	this->setHeightBlowGrid(this->getHeightBlowMap() /
			(ConfigurationManager::getGridResolutionCM() / ConfigurationManager::getMapResolutionCM()));
	cout << "End blow map" << endl;

	//*****Blow*Grid***
	this->_blowGrid = new cellGrid*[this->getHeightBlowGrid()];

	for (int h = 0; h < this->getHeightBlowGrid(); h++){
		this->_blowGrid[h] = new cellGrid[this->getWidthBlowGrid()];
		this->_blowGrid[h]->color = GeneralService::C_WHITE;
		this->_blowGrid[h]->g = 0;
		this->_blowGrid[h]->closed = false;
	}

	this->mapToGrid(this->getBlowMap(), this->getBlowGrid(), this->getWidthBlowMap(), this->getHeightBlowMap(),
			this->getWidthBlowGrid(), this->getHeightBlowGrid(), ConfigurationManager::getGridResolutionCM());

	this->gridToPng(GeneralService::PNG_BLOW_GRID, this->getBlowGrid(), this->getWidthBlowGrid(), this->getHeightBlowGrid());
	cout << "End blow grid" << endl;
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
	grid[y][x] = cell;
}

// Initialize the blow map to WHITE base
void Map::initBlowMap(){
	for (unsigned yDye = 0; yDye < this->getHeightBlowMap(); yDye++){
		for (unsigned xDye = 0; xDye < this->getWidthBlowMap(); xDye++){
			this->_blowMap[yDye * this->getWidthBlowMap() * 4 + xDye * 4 + 0] = GeneralService::C_WHITE;
			this->_blowMap[yDye * this->getWidthBlowMap() * 4 + xDye * 4 + 1] = GeneralService::C_WHITE;
			this->_blowMap[yDye * this->getWidthBlowMap() * 4 + xDye * 4 + 2] = GeneralService::C_WHITE;
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
					 GeneralService::C_BLACK);

	// Bottom frame
	this->setBlowMap(heightMap + this->getNumPixelsToBlow(), this->getHeightBlowMap(),
					 0, this->getWidthBlowMap(),
					 GeneralService::C_BLACK);

	// Left frame
	this->setBlowMap(0, this->getHeightBlowMap(),
					 0, this->getNumPixelsToBlow(),
					 GeneralService::C_BLACK);

	// Right frame
	this->setBlowMap(0, this->getHeightBlowMap(),
					widthMap + this->getNumPixelsToBlow(), this->getWidthBlowMap(),
					GeneralService::C_BLACK);
	/***********END*FRAME******************/

	// Move on the map
	yBlow = this->getNumPixelsToBlow();
	for (yNav = 0; yNav < heightMap; yNav++){
		xBlow = numPixelsToBlow;
		for (xNav = 0; xNav < widthMap; xNav++){
			// If the cell is BLACK
			if (map[yNav * widthMap * 4 + xNav * 4 + 0] == GeneralService::C_BLACK
			 				|| map[yNav * widthMap * 4 + xNav * 4 + 1] == GeneralService::C_BLACK
			 				|| map[yNav * widthMap * 4 + xNav * 4 + 2] == GeneralService::C_BLACK){

				// Blow the pixel in two levels

				this->setBlowMap(yBlow - 2*this->getNumPixelsToBlow(), yBlow + 2*this->getNumPixelsToBlow(),
								 xBlow - 2*this->getNumPixelsToBlow(), xBlow + 2*this->getNumPixelsToBlow(),
								 GeneralService::C_GRAY);

				this->setBlowMap(yBlow - this->getNumPixelsToBlow(), yBlow + this->getNumPixelsToBlow(),
								 xBlow - this->getNumPixelsToBlow(), xBlow + this->getNumPixelsToBlow(),
								 GeneralService::C_BLACK);
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
	return cm / ConfigurationManager::getMapResolutionCM();
}

// Conversion map to grid according to Resolution
void Map::mapToGrid(std::vector<unsigned char> map, cellGrid **grid, unsigned widthMap, unsigned heightMap,
		int widthGrid, int heightGrid, int resolution){

	unsigned yMapStart = 0;
	unsigned xMapStart = 0;
	int numPixels = this->cmToPixel(resolution);

	// Move on the grid
	for(int yGrid = 0; yGrid < heightGrid; yGrid++){
		for(int xGrid = 0; xGrid < widthGrid; xGrid++){
			// Calculate grid cell
			grid[yGrid][xGrid].color = map[(yMapStart + numPixels/2) * widthMap *4 + (xMapStart + numPixels/2) * 4 +0];
			xMapStart += numPixels;
		}
		yMapStart += this->cmToPixel(resolution);
		xMapStart = 0;
	}
}

void Map::gridToPng(const char* fileName, cellGrid **grid, int widthGrid, int heightGrid){
	vector<unsigned char> image; //the raw pixels
	image.resize(widthGrid * heightGrid * 4);

	for (int y = 0; y < heightGrid; y++){
		for (int x = 0; x < widthGrid; x++) {
			this->changePixelColor(&image, widthGrid, y, x, grid[y][x].color);
		}
	}

	if (fileName == GeneralService::PNG_BLOW_GRID){
		// Start location
		this->changePixelColor(&image, widthGrid, ConfigurationManager::getStartLocation().y / 4,
				ConfigurationManager::getStartLocation().x / 4, GeneralService::C_RED);
		// Goal
		this->changePixelColor(&image, widthGrid, ConfigurationManager::getGoal().y / 4,
				ConfigurationManager::getGoal().x / 4, GeneralService::C_BLUE);
	}

	// Export to PNG
	encodeOneStep(fileName, image, widthGrid, heightGrid);
}

void Map::changePixelColor(vector<unsigned char>* image, int width, int y, int x, unsigned char color){
	if (color == GeneralService::C_GREEN){
		(*image)[y * width * 4 + x * 4 + 0] = 0;
		(*image)[y * width * 4 + x * 4 + 1] = GeneralService::C_GREEN;
		(*image)[y * width * 4 + x * 4 + 2] = 0;
		(*image)[y * width * 4 + x * 4 + 3] = 255;
	}
	else if (color == GeneralService::C_PURPLE) {
		(*image)[y * width * 4 + x * 4 + 0] = 178;
		(*image)[y * width * 4 + x * 4 + 1] = 102;
		(*image)[y * width * 4 + x * 4 + 2] = 255;
		(*image)[y * width * 4 + x * 4 + 3] = 255;
	}
	else if (color == GeneralService::C_RED){
		(*image)[y * width * 4 + x * 4 + 0] = color;
		(*image)[y * width * 4 + x * 4 + 1] = 0;
		(*image)[y * width * 4 + x * 4 + 2] = 0;
		(*image)[y * width * 4 + x * 4 + 3] = 255;
	}
	else if (color == GeneralService::C_BLUE){
		(*image)[y * width * 4 + x * 4 + 0] = 0;
		(*image)[y * width * 4 + x * 4 + 1] = 0;
		(*image)[y * width * 4 + x * 4 + 2] = 255;
		(*image)[y * width * 4 + x * 4 + 3] = 255;
	}
	else if (color == GeneralService::C_ORANGE){
		(*image)[y * width * 4 + x * 4 + 0] = 255;
		(*image)[y * width * 4 + x * 4 + 1] = 128;
		(*image)[y * width * 4 + x * 4 + 2] = 0;
		(*image)[y * width * 4 + x * 4 + 3] = 255;
	}
	else{
		(*image)[y * width * 4 + x * 4 + 0] = color;
		(*image)[y * width * 4 + x * 4 + 1] = color;
		(*image)[y * width * 4 + x * 4 + 2] = color;
		(*image)[y * width * 4 + x * 4 + 3] = 255;
	}
}

int Map::xPosToIndex(int xPosCm){
	return (xPosCm / 4);
}

int Map::yPosToIndex(int yPosCm){
	return (yPosCm / 4);
}

float Map::xIndexToPos(int xIndex) {
	return (10.0 * (xIndex  - (getWidthGrid() / 2.0)));
}

float Map::yIndexToPos(int yIndex) {
	return (-10.0 * (yIndex  - (getHeightGrid() / 2.0)));
}

int Map::xPosToIndexLocal(float xPos){
	int xIndex = ((getWidthGrid() / 2.0) + (xPos / (ConfigurationManager::getGridResolutionCM() * 1.0)));

	if (xIndex < 0) {
		xIndex = 0;
	} else if (xIndex >= getWidthGrid()) {
		xIndex = getWidthGrid() -1;
	}

	return xIndex;
}

int Map::yPosToIndexLocal(float yPos){
	int yIndex = ((getHeightGrid() / 2.0) - (yPos / (ConfigurationManager::getGridResolutionCM() * 1.0)));

	if (yIndex < 0) {
		yIndex = 0;
	} else if (yIndex >= getHeightGrid()) {
		yIndex = getHeightGrid() -1;
	}

	return yIndex;
}
