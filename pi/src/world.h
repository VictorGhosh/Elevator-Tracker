// world.h


#ifndef WORLD_H
#define WORLD_H


#include <vector>
#include "headers.h"
#include "main.h"
#include "elevator.h"
#include "seq.h"
#include "gpuProgram.h"


class World {

  Elevator *elevator;
  
  static char *objectVertexShader;
  static char *objectFragmentShader;
  GPUProgram *objectGPUProg;

 public:

  vec3 worldMin, worldMax;	// min and max world coordinates

  float time;

  World( vec3 min, vec3 max ) {

    worldMin = min;
    worldMax = max;

    objectGPUProg = new GPUProgram();
    objectGPUProg->init( objectVertexShader, objectFragmentShader, "object" );

    time = 0;

    elevator = new Elevator();
  }

  void draw();

  void updateState( float elapsedTime ) {
    time += elapsedTime;
  }
};


#endif
