/*
 * pngUtil.cpp
 *
 *  Created on: Mar 30, 2015
 *      Author: colman
 */
#include "pngUtil.h"
#include "lodepng.h"
#include <iostream>

using namespace std;

//Encode from raw pixels to disk with a single function call
//The image argument has width * height RGBA pixels or width * height * 4 bytes
void encodeOneStep(const char* filename, std::vector<unsigned char> image,
		unsigned width, unsigned height) {
	//Encode the image
	unsigned error = lodepng::encode(filename, image, width, height);

	//if there's an error, display it
	if (error)
		std::cout << "encoder error " << error << ": "
				<< lodepng_error_text(error) << std::endl;
}

void decodeOneStep(const char* filename) {
	std::vector<unsigned char> image; //the raw pixels
	unsigned width, height;

	//decode
	unsigned error = lodepng::decode(image, width, height, filename);

	//if there's an error, display it
	if (error)
		std::cout << "decoder error " << error << ": "
				<< lodepng_error_text(error) << std::endl;

	//the pixels are now in the vector "image", 4 bytes per pixel, ordered RGBARGBA..., use it as texture, draw it, ...
}
void ConvertMapBlackToWhiteAndWhiteToBlack(const char* filename) {
	std::vector<unsigned char> image; //the raw pixels
	unsigned width, height;
	unsigned x, y;
	//decode
	unsigned error = lodepng::decode(image, width, height, filename);

	//if there's an error, display it
	if (error)
		std::cout << "decoder error " << error << ": "
				<< lodepng_error_text(error) << std::endl;

	std::vector<unsigned char> navImage; //the raw pixels
	navImage.resize(width * height * 4);
	unsigned char color;
	for (y = 0; y < height; y++)
		for (x = 0; x < width; x++) {
			if (image[y * width * 4 + x * 4 + 0]
					|| image[y * width * 4 + x * 4 + 1]
					|| image[y * width * 4 + x * 4 + 2])
				color = 0; // Black
			else
				color = 255; // White
			navImage[y * width * 4 + x * 4 + 0] = color;
			navImage[y * width * 4 + x * 4 + 1] = color;
			navImage[y * width * 4 + x * 4 + 2] = color;
			navImage[y * width * 4 + x * 4 + 3] = 255;
		}

	encodeOneStep("newMap.png", navImage, width, height);
}

void BlowMap(const char* fileName){// int numPixelsToBlow, const char* blowFileName){
	std::vector<unsigned char> image; //the raw pixels
	unsigned width, height;
	unsigned xNav, yNav;
	unsigned xBlow, yBlow;
	unsigned robotWidth = 45;

	//decode
	unsigned error = lodepng::decode(image, width, height, fileName);

	//if there's an error, display it
	if (error)
		std::cout << "decoder error " << error << ": "
				<< lodepng_error_text(error) << std::endl;

	std::vector<unsigned char> navImage; //the raw pixels
	std::vector<unsigned char> blowImage;
	navImage.resize(width * height * 4);
	blowImage.resize((width + robotWidth*2) * (height + robotWidth*2 ) * 4);

	cout << 'Width ' + width << endl;
	cout << 'height ' + width << endl;

	// Top frame
	for (yBlow = 0; yBlow < robotWidth; yBlow++){
		for (xBlow = 0; xBlow < (width + robotWidth*2); xBlow++){
			blowImage[yBlow * (width + robotWidth*2) * 4 + xBlow * 4 + 0] = 0;
			blowImage[yBlow * (width + robotWidth*2) * 4 + xBlow * 4 + 1] = 0;
			blowImage[yBlow * (width + robotWidth*2) * 4 + xBlow * 4 + 2] = 0;
			blowImage[yBlow * (width + robotWidth*2) * 4 + xBlow * 4 + 3] = 255;

		}
	}

	// Bottom frame
	for (yBlow = height + robotWidth; yBlow < height + robotWidth*2; yBlow++){
		for (xBlow = 0; xBlow < width + robotWidth*2; xBlow++){
			blowImage[yBlow * (width + robotWidth*2) * 4 + xBlow * 4 + 0] = 0;
			blowImage[yBlow * (width + robotWidth*2) * 4 + xBlow * 4 + 1] = 0;
			blowImage[yBlow * (width + robotWidth*2) * 4 + xBlow * 4 + 2] = 0;
			blowImage[yBlow * (width + robotWidth*2) * 4 + xBlow * 4 + 3] = 255;
		}
	}

	// Left frame
	for (yBlow = 0; yBlow < height + robotWidth*2; yBlow++){
		for (xBlow = 0; xBlow < robotWidth; xBlow++){
			blowImage[yBlow * (width + robotWidth*2) * 4 + xBlow * 4 + 0] = 0;
			blowImage[yBlow * (width + robotWidth*2) * 4 + xBlow * 4 + 1] = 0;
			blowImage[yBlow * (width + robotWidth*2) * 4 + xBlow * 4 + 2] = 0;
			blowImage[yBlow * (width + robotWidth*2) * 4 + xBlow * 4 + 3] = 255;
		}
	}

	// Right frame
	for (yBlow = 0; yBlow < height + robotWidth*2; yBlow++){
		for (xBlow = width + robotWidth; xBlow < (width + robotWidth*2); xBlow++){
			blowImage[yBlow * (width + robotWidth*2) * 4 + xBlow * 4 + 0] = 0;
			blowImage[yBlow * (width + robotWidth*2) * 4 + xBlow * 4 + 1] = 0;
			blowImage[yBlow * (width + robotWidth*2) * 4 + xBlow * 4 + 2] = 0;
			blowImage[yBlow * (width + robotWidth*2) * 4 + xBlow * 4 + 3] = 255;
		}
	}

	yBlow = robotWidth;
	for (yNav = 0; yNav < height; yNav++){
		xBlow = robotWidth;
		for (xNav = 0; xNav < width; xNav++){
			if (image[yNav * width * 4 + xNav * 4 + 0]
				|| image[yNav * width * 4 + xNav * 4 + 1]
				|| image[yNav * width * 4 + xNav * 4 + 2]){

				blowImage[yBlow * (width + robotWidth*2) * 4 + xBlow * 4 + 0] = 255;
				blowImage[yBlow * (width + robotWidth*2) * 4 + xBlow * 4 + 1] = 255;
				blowImage[yBlow * (width + robotWidth*2) * 4 + xBlow * 4 + 2] = 255;
				blowImage[yBlow * (width + robotWidth*2) * 4 + xBlow * 4 + 3] = 255;

			} else{
				blowImage[(yBlow - 1) * (width + robotWidth*2) * 4 + (xBlow - 1) * 4 + 0] = 0;
				blowImage[(yBlow - 1) * (width + robotWidth*2) * 4 + (xBlow - 1) * 4 + 1] = 0;
				blowImage[(yBlow - 1) * (width + robotWidth*2) * 4 + (xBlow - 1) * 4 + 2] = 0;
				blowImage[(yBlow - 1) * (width + robotWidth*2) * 4 + (xBlow - 1) * 4 + 3] = 255;

				blowImage[(yBlow - 1) * (width + robotWidth*2) * 4 + xBlow * 4 + 0] = 0;
				blowImage[(yBlow - 1) * (width + robotWidth*2) * 4 + xBlow * 4 + 1] = 0;
				blowImage[(yBlow - 1) * (width + robotWidth*2) * 4 + xBlow * 4 + 2] = 0;
				blowImage[(yBlow - 1) * (width + robotWidth*2) * 4 + xBlow * 4 + 3] = 255;

				blowImage[(yBlow - 1) * (width + robotWidth*2) * 4 + (xBlow + 1) * 4 + 0] = 0;
				blowImage[(yBlow - 1) * (width + robotWidth*2) * 4 + (xBlow + 1) * 4 + 1] = 0;
				blowImage[(yBlow - 1) * (width + robotWidth*2) * 4 + (xBlow + 1) * 4 + 2] = 0;
				blowImage[(yBlow - 1) * (width + robotWidth*2) * 4 + (xBlow + 1) * 4 + 3] = 255;

				blowImage[yBlow * (width + robotWidth*2) * 4 + (xBlow - 1) * 4 + 0] = 0;
				blowImage[yBlow * (width + robotWidth*2) * 4 + (xBlow - 1) * 4 + 1] = 0;
				blowImage[yBlow * (width + robotWidth*2) * 4 + (xBlow - 1) * 4 + 2] = 0;
				blowImage[yBlow * (width + robotWidth*2) * 4 + (xBlow - 1) * 4 + 3] = 255;

				blowImage[yBlow * (width + robotWidth*2) * 4 + (xBlow + 1) * 4 + 0] = 0;
				blowImage[yBlow * (width + robotWidth*2) * 4 + (xBlow + 1) * 4 + 1] = 0;
				blowImage[yBlow * (width + robotWidth*2) * 4 + (xBlow + 1) * 4 + 2] = 0;
				blowImage[yBlow * (width + robotWidth*2) * 4 + (xBlow + 1) * 4 + 3] = 255;

				blowImage[(yBlow + 1) * (width + robotWidth*2) * 4 + (xBlow - 1) * 4 + 0] = 0;
				blowImage[(yBlow + 1) * (width + robotWidth*2) * 4 + (xBlow - 1) * 4 + 1] = 0;
				blowImage[(yBlow + 1) * (width + robotWidth*2) * 4 + (xBlow - 1) * 4 + 2] = 0;
				blowImage[(yBlow + 1) * (width + robotWidth*2) * 4 + (xBlow - 1) * 4 + 3] = 255;

				blowImage[(yBlow + 1) * (width + robotWidth*2) * 4 + xBlow * 4 + 0] = 0;
				blowImage[(yBlow + 1) * (width + robotWidth*2) * 4 + xBlow * 4 + 1] = 0;
				blowImage[(yBlow + 1) * (width + robotWidth*2) * 4 + xBlow * 4 + 2] = 0;
				blowImage[(yBlow + 1) * (width + robotWidth*2) * 4 + xBlow * 4 + 3] = 255;

				blowImage[(yBlow + 1) * (width + robotWidth*2) * 4 + (xBlow + 1) * 4 + 0] = 0;
				blowImage[(yBlow + 1) * (width + robotWidth*2) * 4 + (xBlow + 1) * 4 + 1] = 0;
				blowImage[(yBlow + 1) * (width + robotWidth*2) * 4 + (xBlow + 1) * 4 + 2] = 0;
				blowImage[(yBlow + 1) * (width + robotWidth*2) * 4 + (xBlow + 1) * 4 + 3] = 255;
			}
			xBlow++;
		}
		yBlow++;
	}

	encodeOneStep("blowMap.png", blowImage, width + robotWidth*2, height + robotWidth*2);

}
