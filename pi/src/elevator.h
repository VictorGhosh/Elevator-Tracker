// elevator.h


#ifndef ELEVATOR_H
#define ELEVATOR_H


#include <vector>
#include "headers.h"
#include "object.h"


#define ELEVATOR_WIDTH 0.2 // 0.2 in [-1,1]x[-1,1] screen space
#define ELEVATOR_COLOUR vec3( 0.686, 0.933, 0.933 )


class Elevator : public Object {

  static float verts[]; // elevator model, defined in elevator.cpp

 public:

  Elevator()
    : Object( vec3(0,0,0), verts, ELEVATOR_WIDTH, ELEVATOR_COLOUR )
    {};
};


#endif
