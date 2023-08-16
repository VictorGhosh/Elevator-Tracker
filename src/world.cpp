// world.cpp

#define CENTER CENTRE

#include "world.h"
#include "main.h"
#include "gpuProgram.h"
#include "strokefont.h"

#include <sstream>


void World::draw()

{
  // Keep window in [-1,1]x[-1,1] space

  mat4 worldToViewTransform = identity4();

  /* ACTIVATE GPU PROG */
  objectGPUProg->activate();

  // Draw floors
  floor1->position = vec3( -0.8, -6/7.0, 0.0 );
  floor2->position = vec3( -0.8, -4/7.0, 0.0 );
  floor3->position = vec3( -0.8, -2/7.0, 0.0 );
  floor4->position = vec3( -0.8, 0.0, 0.0 );
  floor5->position = vec3( -0.8, 2/7.0, 0.0 );
  floor6->position = vec3( -0.8, 4/7.0, 0.0 );
  floor7->position = vec3( -0.8, 6/7.0, 0.0 );

  floor1->draw( worldToViewTransform, objectGPUProg );
  floor2->draw( worldToViewTransform, objectGPUProg );
  floor3->draw( worldToViewTransform, objectGPUProg );
  floor4->draw( worldToViewTransform, objectGPUProg );
  floor5->draw( worldToViewTransform, objectGPUProg );
  floor6->draw( worldToViewTransform, objectGPUProg );
  floor7->draw( worldToViewTransform, objectGPUProg );
  
 // Draw elevator
 // elevator->position = vec3( -0.8, 0.8*sin(time), 0.0 ); // position the elevator in [-1,1]x[-1,1]
  elevator->position = vec3( -0.8, dsp->getElevLoc(), 0.0 );
  elevator->draw( worldToViewTransform, objectGPUProg );

  // Draw direction indicators
  upArrow->position = vec3( -0.5, 0.0, 0.0 );
  upArrow2->position = vec3( -0.5, 0.0, 0.0 );
  downArrow->position = vec3( -0.5, 0.0, 0.0 );
  downArrow2->position = vec3( -0.5, 0.0, 0.0 );
  
  if (dsp->getElevDirection() == 1) {
  	downArrow->draw( worldToViewTransform, objectGPUProg );
  	downArrow2->draw( worldToViewTransform, objectGPUProg );
  
  } else if (dsp->getElevDirection() == 2) {
  	upArrow->draw( worldToViewTransform, objectGPUProg );
  	upArrow2->draw( worldToViewTransform, objectGPUProg );
  
  }

  /* DEACTIVATE GPU PROG */
  objectGPUProg->deactivate();

  // Draw floor number inside elevator
  stringstream ss;
  ss << (int) rint( (sin(time)+1)/2.0*6+1 );

  //strokeFont->drawStrokeString( ss.str(), -0.8, 0.8*sin(time)-0.07, 0.1, 0, CENTRE );

  // Draw the title
  strokeFont->drawStrokeString( "ELEVATOR", 0, 0.85, 0.06, 0, CENTRE);

  // Draw testing stuff
  //strokeFont->drawStrokeString("Lobby pressure: " + to_string(dsp->getP1()), 0, -0.25, 0.06, 0, CENTER);
  //strokeFont->drawStrokeString("Elevator pressure: " + to_string(dsp->getP2()), 0, -0.5, 0.06, 0, CENTER);
}

// Shaders for object rendering

char *World::objectVertexShader = R"XX(

#version 300 es

uniform mediump mat4 MVP;

layout (location = 0) in mediump vec4 position;
layout (location = 1) in mediump vec4 colour_in;

out mediump vec4 colour;


void main()

{
  gl_Position = MVP * position;
  colour = colour_in;
}

)XX";



char *World::objectFragmentShader = R"XX(

#version 300 es

in mediump vec4 colour;

out mediump vec4 fragColour;


void main()

{
  fragColour = colour;
}

)XX";



