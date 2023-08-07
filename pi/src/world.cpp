// world.cpp


#include "world.h"
#include "main.h"
#include "gpuProgram.h"
#include "strokefont.h"

#include <sstream>


void World::draw()

{
  // Keep window in [-1,1]x[-1,1] space

  mat4 worldToViewTransform = identity4();

  // Draw elevator

  objectGPUProg->activate();

  elevator->position = vec3( -0.8, 0.8*sin(time), 0.0 ); // position the elevator in [-1,1]x[-1,1]

  elevator->draw( worldToViewTransform, objectGPUProg );

  objectGPUProg->deactivate();

  // Draw floor number inside elevator
  
  stringstream ss;
  ss << (int) rint( (sin(time)+1)/2.0*6+1 );

  strokeFont->drawStrokeString( ss.str(), -0.8, 0.8*sin(time)-0.07, 0.1, 0, CENTRE );

  // Draw the title

  strokeFont->drawStrokeString( "ELEVATOR", 0, 0.85, 0.06, 0, CENTRE );
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



