//#include <Windows.h>
//#include <gl/GL.h>
//#include <gl/GLU.h>
//#include <GL/glut.h>

#include <GL/freeglut.h>

#include "Camera.h"
#include "Scene.h"

#include <iostream>
using namespace std;

//---------- Global variables -------------------------------------------------------------

// Viewport position and size
Viewport viewPort(800, 600);   

// Camera position, view volume and projection
Camera camera(&viewPort);    

// Scene entities
Scene scene(&camera);   

// Variable for update entities
GLuint last_update_tick = 0;

// Variable to activate animation
bool anim = false;

// Variable to save the mouse coords
glm::dvec2 mCoord;

// Variable to save the scene lights
enum LightTypes { CAMERA_SPOTLIGHT, DIRECTIONAL_LIGHT, SPHERE1_SPOTLIGHT};
vector<Light*> lights_;

//----------- Callbacks ----------------------------------------------------

void display();
void resize(int newWidth, int newHeight);
void key(unsigned char key, int x, int y);
void specialKey(int key, int x, int y);
void update();
void mouse(int button, int state, int x, int y);
void motion(int x, int y);

//-------------------------------------------------------------------------

int main(int argc, char *argv[])
{
  cout << "Starting console..." << '\n';

  // Initialization
  glutInit(&argc, argv);

  glutInitContextVersion(3, 3);
  glutInitContextProfile(GLUT_COMPATIBILITY_PROFILE);   
  glutSetOption(GLUT_ACTION_ON_WINDOW_CLOSE, GLUT_ACTION_GLUTMAINLOOP_RETURNS); 
  glutInitWindowSize(800, 600);   // window size
  //glutInitWindowPosition (140, 140);
  glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);   // | GLUT_STENCIL  


  int win = glutCreateWindow( "Freeglut-project" );  // window's identifier
  
  // Callback registration
  glutReshapeFunc(resize);
  glutKeyboardFunc(key);
  glutSpecialFunc(specialKey);
  glutIdleFunc(update);
  glutDisplayFunc(display);
  glutMouseFunc(mouse);
  glutMotionFunc(motion);
 
 
  cout << glGetString(GL_VERSION) << '\n';
  cout << glGetString(GL_VENDOR) << '\n';
 
  scene.init();    // after creating the context
  glutMainLoop(); 

  lights_ = scene.getLights();	// to get the scene lights
    
  //cin.sync();   cin.get();
  glutDestroyWindow(win);  // Destroy the context 

  return 0;
}
//-------------------------------------------------------------------------

void display()   // double buffer
{
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);  
  
  scene.render();   
  glutSwapBuffers();  
}
//-------------------------------------------------------------------------

void resize(int newWidth, int newHeight)
{
  // Resize Viewport 
  viewPort.setSize(newWidth, newHeight);  
  // Resize Scene Visible Area 
  camera.setSize(viewPort.getW(), viewPort.getH());    // scale unchanged
}
//-------------------------------------------------------------------------

void key(unsigned char key, int x, int y)
{
  bool need_redisplay = true;

  switch (key) {
  case 27:  // Escape key 
    glutLeaveMainLoop();  // Freeglut's sentence for stopping glut's main loop 
    break;
  case '+': 
    camera.scale(+0.01);   // zoom in  
    break;
  case '-':
    camera.scale(-0.01);   // zoom out
    break;
  case 'l':
	  camera.set3D(); 
	  break;
  case 'o':
	  camera.setAZ();
	  break;
  case 'u':
	  scene.getDiabolo()->suma_ang();
	  break;
  case 'F':
	{
	  Texture t;
	  t.loadColorBuffer(glutGet(GLUT_WINDOW_WIDTH), glutGet(GLUT_WINDOW_HEIGHT));
	  t.save("..\\Bmps\\Screenshot.bmp");
	}
	  break;
  case 'f':
	  scene.getPhoto()->update(0);
	  break;
  case 'a':
	  camera.moveLR(-50);
	  break;
  case 'd' :
	  camera.moveLR(50);
	  break;
  case 'w' :
	  camera.moveUD(50);
	  break;
  case 's' :
	  camera.moveUD(-50);
	  break;
  case 'q' :
	  camera.moveFB(50);
	  break;
  case 'e' :
	  camera.moveFB(-50);
	  break;
  case 'p' :
	  camera.setPrj();
	  break;
  case 'z':
	  anim = !anim;
	  break;
  case 'b' :
	  lights_ = scene.getLights();
	  lights_[CAMERA_SPOTLIGHT]->enable();
	  break;
  case 'B' :
	  lights_ = scene.getLights();
	  lights_[CAMERA_SPOTLIGHT]->disable();
	  break;
  case 'n' :
	  lights_ = scene.getLights();
	  lights_[DIRECTIONAL_LIGHT]->enable();
	  break;
  case 'N' :
	  lights_ = scene.getLights();
	  lights_[DIRECTIONAL_LIGHT]->disable();
	  break;
  case 'm':
	  lights_ = scene.getLights();
	  lights_[SPHERE1_SPOTLIGHT]->enable();
	  break;
  case 'M':
	  lights_ = scene.getLights();
	  lights_[SPHERE1_SPOTLIGHT]->disable();
	  break;
  default:
    need_redisplay = false;
    break;
  }//switch

  if (need_redisplay)
    glutPostRedisplay();
}
//-------------------------------------------------------------------------

void specialKey(int key, int x, int y)
{
  bool need_redisplay = true;

  switch (key) {
  case GLUT_KEY_RIGHT:
    camera.pitch(4);   // rotate 4 on the X axis
    break;
  case GLUT_KEY_LEFT:
    camera.yaw(4);     // rotate 4 on the Y axis 
    break;
  case GLUT_KEY_UP:
    camera.roll(4);    // rotate 4 on the Z axis
    break;
  case GLUT_KEY_DOWN:
    camera.roll(-4);   // rotate -4 on the Z axis
    break;
  default:
    need_redisplay = false;
    break;
  }//switch

  if (need_redisplay)
    glutPostRedisplay();
}
//-------------------------------------------------------------------------

void update()
{	
	//glutGet(GLUT_ELAPSED_TIME) devuelve el tiempo en milisegundos desde que se llamo a glut init

	if (anim && glutGet(GLUT_ELAPSED_TIME) - last_update_tick > 0)	// si en vez de 0 es 1500 es la 'velocidad' de la practica 1
	{
		GLuint deltaTime = glutGet(GLUT_ELAPSED_TIME) - last_update_tick;
		scene.update(deltaTime);
		last_update_tick = glutGet(GLUT_ELAPSED_TIME);
		glutPostRedisplay();
	}

}
//-------------------------------------------------------------------------

void mouse(int button, int state, int x, int y)
{
	mCoord.x = x;
	mCoord.y = -y;
}
//-------------------------------------------------------------------------

void motion(int x, int y)
{
	glm::dvec2 mOffset = mCoord; // var. global
	mCoord = glm::dvec2(x, -y);
	mOffset = (mCoord - mOffset) * 0.05; // sensitivity = 0.05
	camera.rotatePY(mOffset.y, mOffset.x);
	glutPostRedisplay();
}