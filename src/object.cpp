// object.cpp
//
// Set up and move an object.


#include "headers.h"
#include "object.h"
#include "world.h"
#include "gpuProgram.h"
#include "main.h"


// Set up an object by creating a VAO and rewriting the object
// vertices so that it is centred at (0,0).

void Object::setupVAO( float objectVerts[], float objectWidth, vec3 objectColour )

{
  // ---- Rewrite the object vertices ----

  // Find the bounding box of the object

  vec3 min = vec3( objectVerts[0], objectVerts[1], 0 );
  vec3 max = vec3( objectVerts[0], objectVerts[1], 0 );

  int i;
  for (i=0; objectVerts[i] != 9999; i+=2) {
    vec3 v( objectVerts[i], objectVerts[i+1], 0 );
    if (v.x < min.x) min.x = v.x;
    if (v.x > max.x) max.x = v.x;
    if (v.y < min.y) min.y = v.y;
    if (v.y > max.y) max.y = v.y;
  }

  // Rewrite the model vertices so that the object is centred at (0,0)
  // and has width objectWidth

  float s = objectWidth / (max.x - min.x);
 
  mat4 modelToOriginTransform
    = scale( s, s, 1 )
    * translate( -0.5*(min.x+max.x), -0.5*(min.y+max.y), 0 );

  for (int i=0; objectVerts[i] != 9999; i+=2) {
    vec4 newV = modelToOriginTransform * vec4( objectVerts[i], objectVerts[i+1], 0.0, 1.0 );
    objectVerts[i]   = newV.x / newV.w;
    objectVerts[i+1] = newV.y / newV.w;
  }

  // Store segments in the object model for later

  for (int i=0; objectVerts[i] != 9999; i+=4)
    segments.push_back( Segment( vec3( objectVerts[i],   objectVerts[i+1], 0 ),
				 vec3( objectVerts[i+2], objectVerts[i+3], 0 ) ) );

  // ---- Create a VAO for this object ----

  glGenVertexArrays( 1, &VAO );
  glBindVertexArray( VAO );

  // Store the vertices

  GLuint VBO1;
  glGenBuffers( 1, &VBO1 );
  glBindBuffer( GL_ARRAY_BUFFER, VBO1 );

  glBufferData( GL_ARRAY_BUFFER, 2 * segments.size() * sizeof(vec2), objectVerts, GL_STATIC_DRAW );

  // define the 2D position attribute

  glEnableVertexAttribArray( 0 );
  glVertexAttribPointer( 0, 2, GL_FLOAT, GL_FALSE, 0, 0 );

  // Store the colours

  GLuint VBO2;
  glGenBuffers( 1, &VBO2 );
  glBindBuffer( GL_ARRAY_BUFFER, VBO2 );

  vec3 colours[ 2*segments.size() ];
  for (unsigned int i=0; i<2*segments.size(); i++)
    colours[i] = objectColour;

  glBufferData( GL_ARRAY_BUFFER, 2 * segments.size() * sizeof(vec3), colours, GL_STATIC_DRAW );

  // define the 3D colour attribute

  glEnableVertexAttribArray( 1 );
  glVertexAttribPointer( 1, 3, GL_FLOAT, GL_FALSE, 0, 0 );
}


// Draw the object


void Object::draw( mat4 &worldToViewTransform, GPUProgram *gpuProg )

{
  glBindVertexArray( VAO );

  mat4 modelToViewTransform
    = worldToViewTransform
    * modelToWorldTransform();

  gpuProg->setMat4( "MVP", modelToViewTransform );

  glDrawArrays( GL_LINES, 0, 2 * segments.size() );
}


mat4 Object::modelToWorldTransform() const

{
  mat4 M
    = translate( position )
    * scale( scaleFactor, scaleFactor, scaleFactor )
    * orientation.toMatrix();

  return M;
}
