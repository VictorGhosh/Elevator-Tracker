#include "datGet.h"

class DisplayMaster {

	DataGetter *dat;

	public:
		DisplayMaster();

		float getElevLoc();

		int getElevDirection();

		// Only used for testing
		//float getP1() { return dat->getLobbyPressure(); }
		//float getP2() { return dat->getElevatorPressure(); }
};
