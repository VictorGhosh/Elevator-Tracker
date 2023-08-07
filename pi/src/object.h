// object.h
//
// A 2D object represented with a set of line segments, having a position.


#ifndef OBJECT_H
#define OBJECT_H


#include "headers.h"
#include "gpuProgram.h"
#include <vector> 


class Segment {
 public:

  vec3 tail, head;

  Segment( vec3 t, vec3 h )
    { tail = t; head = h; }
};



class Object {

 public:

  GLuint VAO;			// VAO for geometry
  vector<Segment> segments;	// all segments of model

  vec3 position;		// position in world coordinates
  quaternion orientation;
  float scaleFactor;

  // Object has an initial position and a set of edges (in 'verts').
  // The 'setupVAO' centres the vertices at (0,0) and scales the
  // vertices so that their width is 'width'.

  Object( vec3 pos, float verts[], float width, vec3 colour ) {
    setupVAO( verts, width, colour );
    position = pos;
    orientation = quaternion( 0, vec3(1,0,0) );
    scaleFactor = 1.0;
  };

  void setupVAO( float objectVerts[], float objectWidth, vec3 objectColour );
  void draw( mat4 &worldToViewTransform, GPUProgram *gpuProg );
  mat4 modelToWorldTransform() const;
};


#endif

