// Asteroids game


#include "headers.h"
#include "gpuProgram.h"
#include "world.h"
#include "strokefont.h"
#include "main.h"


World *world;			// the world, including ship, asteroids, other ships, missiles
StrokeFont *strokeFont;		// code to draw characters

KeyState upKey    = UP;		// state of the arrow keys
KeyState downKey  = UP;
KeyState leftKey  = UP;
KeyState rightKey = UP;

int screenWidth, screenHeight;

// Handle a keypress and record the state (UP or DOWN) of the arrows


void keyCallback( GLFWwindow* window, int key, int scancode, int action, int mods )

{
  // Note that GLFW always returns the uppercase letter, even if the lowercase letter was pressed.
  
  if (action == GLFW_PRESS)
    
    switch (key) {
      
    case GLFW_KEY_ESCAPE:	// quit upon ESC
      glfwSetWindowShouldClose( window, GL_TRUE );
      break;
      
    case GLFW_KEY_UP:
      upKey = DOWN; break;
      
    case GLFW_KEY_DOWN:
      downKey = DOWN; break;
      
    case GLFW_KEY_LEFT:
      leftKey = DOWN; break;
      
    case GLFW_KEY_RIGHT:
      rightKey = DOWN; break;
    }
      
  else if (action == GLFW_RELEASE)

    switch (key) {
      
    case GLFW_KEY_UP:
      upKey = UP; break;
      
    case GLFW_KEY_DOWN:
      downKey = UP; break;
      
    case GLFW_KEY_LEFT:
      leftKey = UP; break;
      
    case GLFW_KEY_RIGHT:
      rightKey = UP; break;
    }
}


  
// Error callback

void errorCallback( int error, const char* description )

{
  cerr << "Error " << error << ": " << description << endl;
  exit(1);
}



// Main program


int main( int argc, char **argv )

{
  // Trap all errors (do this *before* creating the window)

  glfwSetErrorCallback( errorCallback );
  
  // Init everything

  if (!glfwInit())
    return 1;
  
#ifdef MACOS
  glfwWindowHint( GLFW_CONTEXT_VERSION_MAJOR, 3 );
  glfwWindowHint( GLFW_CONTEXT_VERSION_MINOR, 2 );
  glfwWindowHint( GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE );
  glfwWindowHint( GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE );
#else
  glfwWindowHint( GLFW_CLIENT_API, GLFW_OPENGL_ES_API );
  glfwWindowHint( GLFW_CONTEXT_VERSION_MAJOR, 3 );
  glfwWindowHint( GLFW_CONTEXT_VERSION_MINOR, 0 );
#endif

  GLFWmonitor *monitor = glfwGetPrimaryMonitor();

  // int x, y, w, h;
  // glfwGetMonitorWorkarea( monitor, &x, &y, &w, &h );
  // cout << x << " " << y << " " << w << " " << h << endl;

  const GLFWvidmode* mode = glfwGetVideoMode( monitor );

  screenWidth = mode->width;
  screenHeight = mode->height;

  cout << "screen is " << screenWidth << "x" << screenHeight << endl;
  
  GLFWwindow* window = glfwCreateWindow( screenWidth, screenHeight, "Title", monitor, NULL );
  
  if (!window) {
    glfwTerminate();
    return 1;
  }

  glfwMakeContextCurrent( window );
  glfwSwapInterval( 1 );
  gladLoadGLLoader( (GLADloadproc) glfwGetProcAddress );

  // Define callbacks

  glfwSetKeyCallback( window, keyCallback );

  // Set up fonts
  
  strokeFont = new StrokeFont();

  // Seed the random number generator

  timeb time;
  ftime( &time );
  srand( time.time );

  // Hide cursor

  glfwSetInputMode( window, GLFW_CURSOR, GLFW_CURSOR_HIDDEN );

  // Set up world

  vec3 worldMin( 0, 0, 0 );
  vec3 worldMax( screenWidth, screenHeight, 0 );

  world = new World( worldMin, worldMax );

  // Main loop

  struct timeb prevTime, thisTime; // record the last rendering time
  ftime( &prevTime );

  while (!glfwWindowShouldClose( window )) {

    // Find elapsed time since last render

    ftime( &thisTime );
    float elapsedSeconds = (thisTime.time + thisTime.millitm / 1000.0) - (prevTime.time + prevTime.millitm / 1000.0);
    prevTime = thisTime;

    // Update the world state

    world->updateState( elapsedSeconds );

    // Clear, display, and check for events

    glClearColor( 0.0, 0.0, 0.0, 0.0 );
    glClear( GL_COLOR_BUFFER_BIT );
    
    world->draw();
      
    glfwSwapBuffers( window );
    glfwPollEvents();
  }

  // Clean up

  glfwDestroyWindow( window );
  glfwTerminate();

  return 0;
}
