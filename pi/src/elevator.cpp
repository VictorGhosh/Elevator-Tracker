// elevator.cpp


#include "elevator.h"


// Elevator model consisting of line segments
//
// These are in a ARBITRARY coordinate system and get remapped to the
// world coordinate system (with the centre of the elevator at (0,0) and
// width ELEVATOR_WIDTH) when the VAO is set up.

float Elevator::verts[] = {

   3,0,  0,9,
   0,9, -3,0, 
  -3,0,  0,1,
   0,1,  3,0,

  9999
};

