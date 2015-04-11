/*
 * main.cpp
 *
 *  Created on: Jan 10, 2015
 *      Author: colman
 */

#include <libplayerc++/playerc++.h>

using namespace PlayerCc;

int main() {

	PlayerClient pc("localhost", 6665);
	LaserProxy lp(&pc);
	Position2dProxy pp(&pc);

	pp.SetMotorEnable(true);
	while (true) {
		pc.Read();

		if (lp[333] < 0.8)
			pp.SetSpeed(0.0, 0.3);
		else
			pp.SetSpeed(0.8, 0.0);
	}
	return 0;

}
