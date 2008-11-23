#include <iostream>
#include <stdlib.h>

#ifdef __APPLE__
#include <OpenGL/OpenGL.h>
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

using namespace std;

float _angle1 = 0.0f;
float _angle2 = 0.0f;
float _angle3 = 0.0f;
float _angle4 = 0.0f; 
float *_angle = &_angle1;
float *_next = _angle; 
float _increment = 2.0f;
bool _rotating = false;

/* inits OpenGL rendering */
void initRendering() {
	glEnable(GL_DEPTH_TEST);
}

void update(int value) {
	if (value <= 0) {
		_angle = _next;
		_rotating = false;
		return;
	}
	
	_rotating = true;

	*_angle += _increment;
	if (*_angle > 360) {
		*_angle -= 360;
	}
	
	glutPostRedisplay(); //Tell GLUT that the display has changed
	
	//Tell GLUT to call update again in 25 milliseconds
	glutTimerFunc(5, update, value - _increment);
}

/* handles key presses */
void handleKeyPress(unsigned char key, int x, int y) {
	switch (key) {
		case 49:	// ASCII code for '1'
			_next = &_angle1;
			break;
		case 50:	// ASCII code for '2'
			_next = &_angle2;
			break;
		case 51:	// ASCII code for '3'
			_next = &_angle3;
			break;
		case 52:	// ASCII code for '4'
			_next = &_angle4;
			break;
		case 32:
			if (!_rotating)
				update(180.0f);
	}
	
}

/* handles window resizing */
void handleResize(int width, int height) {
	glViewport(0, 0, width, height);
	glMatrixMode(GL_PROJECTION); /* specify which matrix should be target of subsequent 
															    matrix operations */
	glLoadIdentity();						 /* load the identity matrix */
	gluPerspective(45.0, (double)width / (double)height, 1.0, 200.0); 
}

void drawScene() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glPushMatrix();
	
	glTranslatef(-0.85f, 0.6f, -3.0f);
	glRotatef(_angle1, 0.0f, 1.0f, 0.0f);
	
	/* rectangle 1 */
	glBegin(GL_QUADS);
	
	glVertex3f(-0.8f, -0.5f, 0.0f);
	glVertex3f(0.8f, -0.5f, 0.0f);
	glVertex3f(0.8f, 0.5f, 0.0f);
	glVertex3f(-0.8f, 0.5f, 0.0f);
	
	glEnd();
	
	glPopMatrix();	// undo the translated matrix
	glPushMatrix();
	glTranslatef(0.85f, 0.6f, -3.0f); 
	glRotatef(_angle2, 0.0f, 1.0f, 0.0f);
	
	/* rectangle 2 */
	glBegin(GL_QUADS);
	
	glVertex3f(-0.8f, -0.5f, 0.0f);
	glVertex3f(0.8f, -0.5f, 0.0f);
	glVertex3f(0.8f, 0.5f, 0.0f);
	glVertex3f(-0.8f, 0.5f, 0.0f);
	
	glEnd();
	glPopMatrix();	// undo the translated matrix
	glPushMatrix();
	
	glTranslatef(-0.85f, -0.6f, -3.0f);
	glRotatef(_angle3, 0.0f, 1.0f, 0.0f);
	
	/* rectangle 3 */
	glBegin(GL_QUADS);
	
	glVertex3f(-0.8f, -0.5f, 0.0f);
	glVertex3f(0.8f, -0.5f, 0.0f);
	glVertex3f(0.8f, 0.5f, 0.0f);
	glVertex3f(-0.8f, 0.5f, 0.0f);
	
	glEnd();
	glPopMatrix();	// undo the translated matrix
	glPushMatrix();
	
	glTranslatef(0.85f, -0.6f, -3.0f);
	glRotatef(_angle4, 0.0f, 1.0f, 0.0f); 
	
	/* rectangle 4 */
	glBegin(GL_QUADS);
	
	glVertex3f(-0.8f, -0.5f, 0.0f);
	glVertex3f(0.8f, -0.5f, 0.0f);
	glVertex3f(0.8f, 0.5f, 0.0f);
	glVertex3f(-0.8f, 0.5f, 0.0f);
	
	glEnd();
	glPopMatrix();
	
	glutSwapBuffers();
}

int main(int argc, char *argv[]) {

	/* initialize GLUT */
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(1024, 768);
	
	glutCreateWindow("OpenGL test");
	initRendering();
	
	/* set handler functions */
	glutDisplayFunc(drawScene);
	glutKeyboardFunc(handleKeyPress);
	glutReshapeFunc(handleResize);
	
	//glutTimerFunc(25, update, 0);
	glutMainLoop();

	return 0;
}
