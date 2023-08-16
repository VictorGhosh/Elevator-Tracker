// elevator.cpp


#include "elevator.h"


// Elevator model consisting of line segments
//
// These are in a ARBITRARY coordinate system and get remapped to the
// world coordinate system (with the centre of the elevator at (0,0) and
// width ELEVATOR_WIDTH) when the VAO is set up.

float Arrow::upVerts[] = {
	5,0	,	5,10	,
	5,10	,	10,10	,
	10,10	,	0,25	,
	0,25	,	-10,10	,
	-10,10	,	-5,10	,
	-5,10	,	-5,0	,
	-5,0	,	5,0	,

	9999
};

float Arrow::downVerts[] = {
	5,0	,	5,-10	,
	5,-10	,	10,-10	,	
	10,-10	,	0,-25	,
	0,-25	,	-10,-10	,
	-10,-10	,	-5,-10	,
	-5,-10	,	-5,0	,
	-5,0	,	5,0	,

	9999
};

float Floor::verts[] = {
	1,1.4	,	-1,1.4	,
  	-1,1.4	, 	-1,-1.4	,
  	-1,-1.4	, 	1,-1.4	,
  	1,-1.4	, 	1,1.4	,

  	9999
};

float Elevator::verts[] = {
	// Frame
	5,10	,	-5,10	,
	-5,10	,	-5,-10	,
	-5,-10	,	5,-10	,
	5,-10	,	5,10	,

	// Door
	3.5,-10 ,	3.5,6	,
	3.5,6	,	-3.5,6	,
	-3.5,6	,	-3.5,-10,	
	0,-10	,	0,6	,

	// Butons
	7,2	,	6,2	,
	6,2	,	6,-2	,
	6,-2	,	7,-2	,
	7,-2	,	7,2	,

	9999
};

/* Old elevator model
float Elevator::testShape[] = {
	5,10	,	4,10	,
	4,10	,	4,8	,
	4,8	,	-4,8	,
	-4,8	,	-4,10	,
	-4,10	,	-5,10	,	
	-5,10	,	-5,-10	,
	-5,-10	,	-4,-10	,
	-4,-10	,	-4,-8	,
	-4,-8	,	4,-8	,
	4,-8	,	4,-10	,
	4,-10	,	5,-10	,
	5,-10	,	5,10	,
	
	0,8	,	0,-8	,
  9999
};
*/
