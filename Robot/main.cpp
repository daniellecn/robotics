/*
 * main.cpp
 *
 *  Created on: Jan 10, 2015
 *      Author: colman
 */

#include <libplayerc++/playerc++.h>
#include <iostream>
using namespace std;
using namespace PlayerCc;

int main() {

	PlayerClient pc("localhost", 6665);
	LaserProxy lp(&pc);
	Position2dProxy pp(&pc);

	int avoid = 0;
	int maxPosObs = 0;
	int minPosObs = 682;
	bool obs;

	pp.SetMotorEnable(true);

	while (true) {
		pc.Read();
		//cout << lp.GetSize() << endl;
		obs = false;
		for (uint i = 241; i < 441; i++)
		{
		  if(lp[i] < 0.750)
			obs = true;
		  	avoid = 15;

		  	if (i > maxPosObs) {
		  		maxPosObs = i;
		  	}
		  	if (i < minPosObs) {
		  		minPosObs = i;
		  	}
		}

		if (obs && avoid > 0 ) {
			if (lp.GetMinLeft() < lp.GetMinRight()) {
				pp.SetSpeed(0.0, -0.6);
			} else {
				pp.SetSpeed(0.0, 0.6);
			}
			avoid--;

		} else {
			avoid = 0;
			pp.SetSpeed(0.8, 0.0);
		}
		/*
		if (lp[3] < 0.8) {
			pp.SetSpeed(0.0, 0.3);
		}
		else if(lp[1]) {

		}
		else {
			pp.SetSpeed(0.8, 0.0);
		}
		*/
	}

	return 0;

}
