#ifndef ELEVATOR_H
#define ELEVATOR_H

#include <vector>
#include "headers.h"
#include "object.h"

#define ELEVATOR_WIDTH 0.2 // 0.2 in [-1,1]x[-1,1] screen space
#define ELEVATOR_COLOUR vec3( 0.686, 0.933, 0.933 )

class Arrow : public Object {
	static float upVerts[];
	static float downVerts[];

	public:
		Arrow(int direction, double size) : Object(vec3(0,0,0), getVerts(direction), size, ELEVATOR_COLOUR) {};

	private:
		static float* getVerts(int direction) {
			if (direction == 2) {
				return upVerts;
			} else if (direction == 1) {
				return downVerts;
			} else {
				throw invalid_argument("Invalid direction");
			}
		}
};

class Floor : public Object {
	static float verts[];

	public:
		Floor() : Object(vec3(0,0,0), verts, 0.2, ELEVATOR_COLOUR) {};
};

class Elevator : public Object {
    	static float verts[];

 	public:
		Elevator() : Object( vec3(0,0,0), verts, 0.1, ELEVATOR_COLOUR) {};
};
#endif
