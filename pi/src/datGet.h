#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <csignal>
#include <iostream>
#include <fstream>
#include <ctime>

using namespace std;

class DataGetter {
	public:
		DataGetter();
		
		/**
		 * FIXME: Deconstructor is not used for some resion. Only needed to end
		 * the help program. Currently constructor ensures only one instance
		 * is ever runnining but it runs even when display is off.
		 */
		virtual ~DataGetter();

		int update();
			
		/**
		 * Updates extended log file, called by update().
		 */
		int log();

		float getElevatorPressure();

		float getLobbyPressure();

		/**
		 * Returns Ardunio floor estimate, not currently in use.
		 */
		int getFloor();
	
		int getDirection();

	private:
		time_t lastTime;

		float elevatorPressure;

		float lobbyPressure;

		float prevElevatorPressure;
};	
