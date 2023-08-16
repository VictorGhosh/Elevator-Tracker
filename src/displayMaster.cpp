#include "displayMaster.h"

DisplayMaster::DisplayMaster() {
	dat = new DataGetter();
}

int DisplayMaster::getElevDirection() {
	dat->update();

	if (dat->getDirection() > 2 || dat->getDirection() < 0) {
		throw invalid_argument("Invalid elevator direction");
	} else {
		return dat->getDirection();
	}
}

float DisplayMaster::getElevLoc() {
	dat->update();
	
	if (dat->getFloor() == 1) {
		return -6/7.0;
	
	} else if (dat->getFloor() == 2) {
		return 	-4/7.0;

	} else if (dat->getFloor() == 3) {
		return -2/7.0;

	} else if (dat->getFloor() == 4) {
		return 0.0;

	} else if (dat->getFloor() == 5) {
		return 2/7.0;

	} else if (dat->getFloor() == 6) {
		return 4/7.0;

	} else if (dat->getFloor() == 7) {
		return 4/7.0;

	} else {
		throw invalid_argument("Invalid floor number");
	}
}
