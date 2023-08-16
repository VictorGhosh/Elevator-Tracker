#include <iostream>
#include <fstream>

using namespace std;

int main() {
	ifstream f;
	f.open("/dev/ttyACM0");
	//f.open("testFile.txt");

	if (f.is_open()) {
		char ch;
		bool loop = true;
		
		// Go to end of file skip over last nl
		f.seekg(-2, ios::end);
		
		while (loop) {
			f.get(ch);
			if (ch == '\n') {
				loop = false;
			} else {
				// Ch not nl so move past read char + 1
				f.seekg(-2, ios::cur);
			}
		}
	
		string line;
		getline(f, line);
		cout << line << '\n';		
	
	} else {
		cerr << "PortMonitor: Failed to open connection to port";
	}

	f.close();
	return 0;
}
