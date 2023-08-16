// world.h

#ifndef WORLD_H
#define WORLD_H

#include <vector>
#include "headers.h"
#include "main.h"
#include "elevator.h"
#include "seq.h"
#include "gpuProgram.h"

#include "displayMaster.h"

class World {

  Elevator *elevator;
 
  Floor *floor1;
  Floor *floor2;
  Floor *floor3;
  Floor *floor4;
  Floor *floor5;
  Floor *floor6;
  Floor *floor7;

  Arrow *upArrow;
  Arrow *upArrow2;
  Arrow *downArrow;
  Arrow *downArrow2;

  static char *objectVertexShader;
  static char *objectFragmentShader;
  GPUProgram *objectGPUProg;

  DisplayMaster *dsp;

 public:

  vec3 worldMin, worldMax;	// min and max world coordinates

  float time;

  World( vec3 min, vec3 max ) {

    worldMin = min;
    worldMax = max;

    objectGPUProg = new GPUProgram();
    objectGPUProg->init( objectVertexShader, objectFragmentShader, "object" );

    time = 0;

    dsp = new DisplayMaster();

    elevator = new Elevator();

    floor1 = new Floor();
    floor2 = new Floor();
    floor3 = new Floor();
    floor4 = new Floor();
    floor5 = new Floor();
    floor6 = new Floor();
    floor7 = new Floor();

    upArrow = new Arrow(2, 0.3);
    upArrow2 = new Arrow(2, 0.25);
    downArrow = new Arrow(1, 0.3);
    downArrow2 = new Arrow(1, 0.25);
  }

  void draw();

  void updateState( float elapsedTime ) {
    time += elapsedTime;
  }
};


#endif
