#include "datGet.h"

#include <sstream>

DataGetter::DataGetter() {
	system("pkill -f ../src/datGetHelp.py");
	system("python3 ../src/datGetHelp.py &");
	
	this->elevatorPressure = -1;
	this->lobbyPressure = -1;
	this->lastTime = time(0);
	this->prevElevatorPressure = 0;
}

DataGetter::~DataGetter() {
	cout << "DataGetter: Killing python helper\n";
	system("pkill -f ../src/datGetHelp.py");
}

int DataGetter::update() {
	ifstream f;
	string res;
	stringstream ss;

	f.open("buff.txt");
	while (getline (f, res)) {
		ss << res;	
	}
	f.close();

	string tmpStr;
	float tmpFloat;
	int stringNum = 0;
	while (!ss.eof()) {
		stringNum++;
		ss >> tmpStr;
	
		if (stringNum == 2 && stringstream(tmpStr) >> tmpFloat) {
			this->lobbyPressure = tmpFloat;

		} else if (stringNum == 3 && stringstream(tmpStr) >> tmpFloat) {
			if (tmpFloat != elevatorPressure) {
				this->prevElevatorPressure = elevatorPressure;
				this->elevatorPressure = tmpFloat;
			}
		}
		tmpStr = "";
	}

	return log();
}

int DataGetter::log() {
/*	ofstream f;
	time_t t = time(0);
	tm *curTime = gmtime(&t);
	//tm *prevTime = gmtime(&lastTime);

	// Only write to log file every second
	if (t == lastTime) {
		return 1;
	}

	f.open("log.txt", ios::app);

	cout << asctime(curTime);
	f.close();
*/
	return 1;
}

float DataGetter::getElevatorPressure() { return elevatorPressure; }

float DataGetter::getLobbyPressure() { return lobbyPressure; }

int DataGetter::getFloor() { 
	update();
	float diff = lobbyPressure - elevatorPressure;

	if (diff > 74) {
		return 1;
	} else if (diff > 33) {
		return 2;
	} else if (diff > -5.5) {
		return 3;
	} else if (diff > -45) {
		return 4;
	} else if (diff > -84) {
		return 5;
	} else if (diff > -123.5) {
		return 6;
	} else {
		return 7;
	}
}

int DataGetter::getDirection() { 
	// 2 for up, 1 for down, 0 for still	
	float elevatorPressureDiff = elevatorPressure - prevElevatorPressure;
	
	if (elevatorPressureDiff > 5) {
		return 1;
	} else if (elevatorPressureDiff < -5) {
		return 2;
	}
	return 0;
}

void signalHandler (int signum) {
	cout << "Interrupt signal (" << signum << "). Killing python getter.\n";
	system("pkill -f arduinoGet.py");
	exit(signum);
}

