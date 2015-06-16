#ifndef LASER_H_
#define LASER_H_

#include <math.h>

static const int   LASER_SAMPLES_NUM = 666;
static const float LASER_RANGE_MIN = 0;
static const float LASER_RANGE_MAX = 4.095;
static const float LASER_FOV_DEG = 240;
static const float LASER_FOV_RAD = LASER_FOV_DEG * M_PI / 180.0;
static const float LASER_MAX_ANGLE_RAD = LASER_FOV_RAD/2.0;
static const float LASER_MIN_ANGLE_RAD = -LASER_MAX_ANGLE_RAD;
static const float LASER_ANGULAR_RESOLUTION_DEG = LASER_FOV_DEG / LASER_SAMPLES_NUM;
static const float LASER_ANGULAR_RESOLUTION_RAD = LASER_FOV_RAD / LASER_SAMPLES_NUM;
static const float LASER_MAX_ANGLE_DEG = LASER_FOV_DEG/2.0;
static const float LASER_MIN_ANGLE_DEG = -LASER_MAX_ANGLE_DEG;

static inline int LASER_ANGLE_TO_INDEX_DEG(float degree) {
	return ((int)((degree/(LASER_FOV_DEG/2)) * LASER_SAMPLES_NUM/2 + LASER_SAMPLES_NUM/2));
}

static inline float LASER_INDEX_TO_ANGLE_DEG(int index) {
	return ((double)(index*LASER_ANGULAR_RESOLUTION_DEG+LASER_MIN_ANGLE_DEG));
}

#endif /* LASER_H_ */
