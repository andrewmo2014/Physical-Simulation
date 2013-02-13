
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <vector>
#include <cmath>

#include <GL/glut.h>
#include <vecmath.h>
#include "camera.h"

//TODO: include more headers if necessary

#include "TimeStepper.hpp"
#include "simpleSystem.h"
#include "simplePendulum.h"
#include "simpleChain.h"
#include "ClothSystem.h"
#include "particleSystem.h"
#include "pendulumSystem.h"

using namespace std;

// Globals here.
namespace
{

    ParticleSystem *system;
    PendulumSystem *pendulumSystem = NULL;
    bool isCloth_ON = false;
    int systemToggle = 0;

    TimeStepper * timeStepper;
    float step_size;

  // initialize your particle systems
  void initSystem(int argc, char * argv[])
  {
    if (argc != 3){
	cout << "USAGE: ./a3 <INTEGRATOR> <STEP_SIZE>" << endl;
	exit(0);
    }

    // seed the random number generator with the current time
    srand( time( NULL ) );

    //define step_size by user input arguments
    const char* h_input(argv[2]);
    step_size = atof(h_input); 
    
    string integrator = argv[1];

    system = new SimpleSystem();

    
    if (integrator == "e"){
        timeStepper = new ForwardEuler();
	cout << "INTEGRATOR: ForwardEuler" << endl;
    }

    else if (integrator == "t"){
	timeStepper = new Trapzoidal();
	cout << "INTEGRATOR: Trapzoidal" << endl;
    }

    else if (integrator == "r"){
	timeStepper = new RK4();
	cout << "INTEGRATOR: RK4" << endl;
    }

   else{
    timeStepper = new RK4();
    cout << "Invalid INTEGRATOR: defaulting to RK4" << endl;
   }
		
  }

  // Take a step forward for the particle shower
  void stepSystem()
  {
    const float h = step_size;

    if(timeStepper!=0){
      timeStepper->takeStep(system,h);
    }

  }

  // Draw the current particle positions
  void drawSystem()
  {
    
    // Base material colors (they don't change)
    GLfloat particleColor[] = {0.4f, 0.7f, 1.0f, 1.0f};
    GLfloat floorColor[] = {1.0f, 0.0f, 0.0f, 1.0f};
    
    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, particleColor);
    
    glutSolidSphere(0.1f,10.0f,10.0f);
    
    system->draw();
    
    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, floorColor);
    glPushMatrix();
    glTranslatef(0.0f,-5.0f,0.0f);
    glScaled(50.0f,0.01f,50.0f);
    glutSolidCube(1);
    glPopMatrix();
    
  }
        
    //-------------------------------------------------------------------  
        
    // This is the camera
    Camera camera;

    // These are state variables for the UI
    bool g_mousePressed = false;

    // Declarations of functions whose implementations occur later.
    void arcballRotation(int endX, int endY);
    void keyboardFunc( unsigned char key, int x, int y);
    void specialFunc( int key, int x, int y );
    void mouseFunc(int button, int state, int x, int y);
    void motionFunc(int x, int y);
    void reshapeFunc(int w, int h);
    void drawScene(void);
    void initRendering();

    // This function is called whenever a "Normal" key press is
    // received.
    void keyboardFunc( unsigned char key, int x, int y )
    {

	//functionality when viewing ClothSystem
	if (isCloth_ON){
		switch ( key )
		{

		case 'd':
		    pendulumSystem->windToggle();
		    cout << "wind toggle" << endl;
		    break;

		case 's':
		    pendulumSystem->sinusoidMovementToggle();
		    cout << "swing toggle" << endl;
		    break;

		case 'w':
		    pendulumSystem->wireframeToggle();
		    cout << "wireframe toggle" << endl;
		    break;

		case 'r':
		    system = new ClothSystem(15);
		    pendulumSystem = static_cast<PendulumSystem*>(system);
		    xTrans = 0.0f;
		    yTrans = 0.0f;
		    cout << "reset toggle" << endl;
		    break;

		case 27: // Escape key
		    exit(0);
		    break;

		case ' ':
		{
		    Matrix4f eye = Matrix4f::identity();
		    camera.SetRotation( eye );
		    camera.SetCenter( Vector3f::ZERO );
		    break;
		}

		//Toggle between systems
		case 't':
		{
		    systemToggle++;
		    switch(systemToggle%4){
			case 0:
			    isCloth_ON = false;
			    system = new SimpleSystem();
			    cout << "SYSTEM_TYPE: SimpleSystem" << endl;
			    break;
			case 1:
			    isCloth_ON = false;
			    system = new SimplePendulum();
			    cout << "SYSTEM_TYPE: SimplePendulum" << endl;
			    break;
			case 2:
			    isCloth_ON = false;
			    system = new SimpleChain();
			    cout << "SYSTEM_TYPE: SimpleChain" << endl;
			    break;
			case 3:
			    system = new ClothSystem(15);
		    	    pendulumSystem = static_cast<PendulumSystem*>(system);
			    isCloth_ON = true;
		    	    xTrans = 0.0f;
		    	    yTrans = 0.0f;
			    cout << "SYSTEM_TYPE: ClothSystem" << endl;
			    break;
		    }
		    break;
		}

		default:
		    cout << "Unhandled key press " << key << "." << endl;        
		}


	}
	
	else{		//Functionality when not viewing cloth
	switch ( key )
        {

        case 27: // Escape key
            exit(0);
            break;

        case ' ':
        {
            Matrix4f eye = Matrix4f::identity();
            camera.SetRotation( eye );
            camera.SetCenter( Vector3f::ZERO );
            break;
        }

	//Toggle between systems
	case 't':
	{
	    systemToggle++;
	    switch(systemToggle%4){
	        case 0:
		    isCloth_ON = false;
	            system = new SimpleSystem();
		    cout << "SYSTEM_TYPE: SimpleSystem" << endl;
		    break;
	        case 1:
	            isCloth_ON = false;
		    system = new SimplePendulum();
		    cout << "SYSTEM_TYPE: SimplePendulum" << endl;
		    break;
	        case 2:
		    isCloth_ON = false;
	            system = new SimpleChain();
		    cout << "SYSTEM_TYPE: SimpleChain" << endl;
		    break;
	        case 3:
	            system = new ClothSystem(15);
	    	    pendulumSystem = static_cast<PendulumSystem*>(system);
		    isCloth_ON = true;
	    	    xTrans = 0.0f;
	    	    yTrans = 0.0f;
		    cout << "SYSTEM_TYPE: ClothSystem" << endl;
		    break;
	    }
	    break;
	} 

        default:
            cout << "Unhandled key press " << key << "." << endl;        
        }
	}

        glutPostRedisplay();
    }

    // This function is called whenever a "Special" key press is
    // received.  Right now, it's handling the arrow keys.
    void specialFunc( int key, int x, int y )
    {
	
	//Used for Ball Translation when viewing ClothSystem
	if(isCloth_ON){
            switch ( key )
            {
		case 101:
		    //cout << "up arrow" << endl;
		    yTrans=yTrans+.01f;
		    break;

		case 103:
		    //cout << "down arrow" << endl;
		    yTrans=yTrans-.01f;
		    break;

		case 100:
		    //cout << "left arrow" << endl;
		    xTrans=xTrans-.01f;
		    break;

		case 102:
		    //cout << "right arrow" << endl;
		    xTrans=xTrans+.01f;
		    break;
	    }
	}
        //glutPostRedisplay();
    }

    //  Called when mouse button is pressed.
    void mouseFunc(int button, int state, int x, int y)
    {
        if (state == GLUT_DOWN)
        {
            g_mousePressed = true;
            
            switch (button)
            {
            case GLUT_LEFT_BUTTON:
                camera.MouseClick(Camera::LEFT, x, y);
                break;
            case GLUT_MIDDLE_BUTTON:
                camera.MouseClick(Camera::MIDDLE, x, y);
                break;
            case GLUT_RIGHT_BUTTON:
                camera.MouseClick(Camera::RIGHT, x,y);
            default:
                break;
            }                       
        }
        else
        {
            camera.MouseRelease(x,y);
            g_mousePressed = false;
        }
        glutPostRedisplay();
    }

    // Called when mouse is moved while button pressed.
    void motionFunc(int x, int y)
    {
        camera.MouseDrag(x,y);        
    
        glutPostRedisplay();
    }

    // Called when the window is resized
    // w, h - width and height of the window in pixels.
    void reshapeFunc(int w, int h)
    {
        camera.SetDimensions(w,h);

        camera.SetViewport(0,0,w,h);
        camera.ApplyViewport();

        // Set up a perspective view, with square aspect ratio
        glMatrixMode(GL_PROJECTION);

        camera.SetPerspective(50);
        glLoadMatrixf( camera.projectionMatrix() );
    }

    // Initialize OpenGL's rendering modes
    void initRendering()
    {
        glEnable(GL_DEPTH_TEST);   // Depth testing must be turned on
        glEnable(GL_LIGHTING);     // Enable lighting calculations
        glEnable(GL_LIGHT0);       // Turn on light #0.

        glEnable(GL_NORMALIZE);

        // Setup polygon drawing
        glShadeModel(GL_SMOOTH);
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
        
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);

        // Clear to black
        glClearColor(0,0,0,1);
    }

    // This function is responsible for displaying the object.
    void drawScene(void)
    {
        // Clear the rendering window
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        glMatrixMode( GL_MODELVIEW );  
        glLoadIdentity();              

        // Light color (RGBA)
        GLfloat Lt0diff[] = {1.0,1.0,1.0,1.0};
        GLfloat Lt0pos[] = {3.0,3.0,5.0,1.0};
        glLightfv(GL_LIGHT0, GL_DIFFUSE, Lt0diff);
        glLightfv(GL_LIGHT0, GL_POSITION, Lt0pos);

        glLoadMatrixf( camera.viewMatrix() );

        // THIS IS WHERE THE DRAW CODE GOES.
        drawSystem();

        // This draws the coordinate axes when you're rotating, to
        // keep yourself oriented.
        if( g_mousePressed )
        {
            glPushMatrix();
            Vector3f eye = camera.GetCenter();
            glTranslatef( eye[0], eye[1], eye[2] );

            // Save current state of OpenGL
            glPushAttrib(GL_ALL_ATTRIB_BITS);

            // This is to draw the axes when the mouse button is down
            glDisable(GL_LIGHTING);
            glLineWidth(3);
            glPushMatrix();
            glScaled(5.0,5.0,5.0);
            glBegin(GL_LINES);
            glColor4f(1,0.5,0.5,1); glVertex3f(0,0,0); glVertex3f(1,0,0);
            glColor4f(0.5,1,0.5,1); glVertex3f(0,0,0); glVertex3f(0,1,0);
            glColor4f(0.5,0.5,1,1); glVertex3f(0,0,0); glVertex3f(0,0,1);

            glColor4f(0.5,0.5,0.5,1);
            glVertex3f(0,0,0); glVertex3f(-1,0,0);
            glVertex3f(0,0,0); glVertex3f(0,-1,0);
            glVertex3f(0,0,0); glVertex3f(0,0,-1);

            glEnd();
            glPopMatrix();

            glPopAttrib();
            glPopMatrix();
        }
                 
        // Dump the image to the screen.
        glutSwapBuffers();
    }

    void timerFunc(int t)
    {
        stepSystem();

        glutPostRedisplay();

        glutTimerFunc(t, &timerFunc, t);
    }

    

    
    
}

// Main routine.
// Set up OpenGL, define the callbacks and start the main loop
int main( int argc, char* argv[] )
{
    glutInit( &argc, argv );

    // We're going to animate it, so double buffer 
    glutInitDisplayMode( GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH );

    // Initial parameters for window position and size
    glutInitWindowPosition( 60, 60 );
    glutInitWindowSize( 600, 600 );
    
    camera.SetDimensions( 600, 600 );

    camera.SetDistance( 10 );
    camera.SetCenter( Vector3f::ZERO );
    
    glutCreateWindow("Assignment 4");

    // Initialize OpenGL parameters.
    initRendering();

    // Setup particle system
    initSystem(argc,argv);

    // Set up callback functions for key presses
    glutKeyboardFunc(keyboardFunc); // Handles "normal" ascii symbols
    glutSpecialFunc(specialFunc);   // Handles "special" keyboard keys

    // Set up callback functions for mouse
    glutMouseFunc(mouseFunc);
    glutMotionFunc(motionFunc);

    // Set up the callback function for resizing windows
    glutReshapeFunc( reshapeFunc );

    // Call this whenever window needs redrawing
    glutDisplayFunc( drawScene );

    // Trigger timerFunc every 20 msec
    glutTimerFunc(20, timerFunc, 20);
        
    // Start the main loop.  glutMainLoop never returns.
    glutMainLoop();

    return 0;	// This line is never reached.
}
