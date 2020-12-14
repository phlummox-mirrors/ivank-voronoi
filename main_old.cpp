#include <GL/glew.h> // Include the GLEW header file
#include <GL/glut.h> // Include the GLUT header file
#include <iostream>
#include <math.h>
#include <algorithm>

#define PI 3.14159265
#define gd 10
#define gr 6
#define fn 3000


int tim = 0;

struct sf // snowflake
{
	float size, rot, x, y, z;
	sf()
	{
		size = 0.3 + 0.7*rand()/RAND_MAX;
		x = 8.0 * rand()/RAND_MAX - 4;
		y = 4.0 * rand()/RAND_MAX - 2;
		z = 4.0 * rand()/RAND_MAX - 2;
		rot = 0;
	}
	void iterate()
	{
		y -= gd * 0.0005;
		x += gr * 0.0005;
		if(y<-2) y = 2 + 0.3*rand()/RAND_MAX;
		if(x>4) x = -4 + 0.3*rand()/RAND_MAX;
		rot -= 0.03;
	}
	bool operator < (sf & a) {	return z < a.z; }

} flakes [fn];

void dl(GLfloat x1, GLfloat y1, GLfloat x2, GLfloat y2);
void dc(GLfloat x, GLfloat y, float r);
void df(sf & f);

void display (void) 
{
	std::cout << "display\n";
	glLoadIdentity(); // Load the Identity Matrix to reset our drawing locations  
	glTranslatef(0.0f, 0.0f, -5.0f); 
}

void onEF(int n)
{
	glutTimerFunc(5, onEF, 0);
	glClear(GL_COLOR_BUFFER_BIT);//Clear the screen
	glClearColor(0.0f, 0.0f, 0.2f, 1.0f); // Clear the background of our window to red  
	tim ++;

	glHint (GL_POLYGON_SMOOTH, GL_DONT_CARE);
	glLineWidth (1.5);
	
	double c;
	for(int i=0; i<fn; i++)
	{
		flakes[i].iterate();
		df(flakes[i]);
	}


	glutSwapBuffers();//Draw everything to the screen
}

void reshape (int width, int height) 
{
	glViewport(0, 0, (GLsizei)width, (GLsizei)height); // Set our viewport to the size of our window
	glMatrixMode(GL_PROJECTION); // Switch to the projection matrix so that we can manipulate how our scene is viewed
	glLoadIdentity(); // Reset the projection matrix to the identity matrix so that we don't get any artifacts (cleaning up)
	gluPerspective(22.5, (GLfloat)width / (GLfloat)height, 1.0, 100.0); // Set the Field of view angle (in degrees), the aspect ratio of our window, and the new and far planes
	glMatrixMode(GL_MODELVIEW); // Switch back to the model view matrix, so that we can start drawing shapes correctly
}


int main (int argc, char **argv) 
{
	glutInit(&argc, argv); // Initialize GLUT
	glutInitDisplayMode (GLUT_DOUBLE); // Set up a basic display buffer (only single buffered for now)
	glutInitWindowSize (600, 600); // Set the width and height of the window
	glutInitWindowPosition (100, 100); // Set the position of the window
	glutCreateWindow ("Snìžení od Ivana"); // Set the title for the window

	glutDisplayFunc(display); // Tell GLUT to use the method "display" for 
	glutTimerFunc(5, onEF, 0);
	glutReshapeFunc(reshape); // Tell GLUT to use the method "reshape" for rendering  

	std::sort(flakes, flakes + fn);

	glutMainLoop(); // Enter GLUT's main loop
}


void dl(GLfloat x1, GLfloat y1, GLfloat x2, GLfloat y2)
{
    glColor3f(0.8f,0.8f,0.8f);//black color 
	glLineWidth(7); //5 pixels 
	glBegin(GL_LINES);
    glVertex2f(x1+0.006,y1-0.006); 
    glVertex2f(x2+0.006,y2-0.006); 
	glColor3f(0,0,0);//black color
    glVertex2f(x1,y1); 
    glVertex2f(x2,y2); 
    glEnd(); 
}

void dc(GLfloat x, GLfloat y, float r)
{  
    glBegin(GL_TRIANGLE_FAN); 
    glLineWidth(3); 
    
	float deg;
    for(int i=0;i<=360;i += 20) //no of short lines to be drawn 
    { 
		deg = i*(2*PI/360);
        glVertex2f(x + r * cos(deg), y + r * sin(deg)); 
    } 
    glEnd(); 
}

void df(sf & f)
{  
    glLineWidth(3); 
	float c = (f.z + 2)/4;
	float deg, r, nx, ny;
	glColor3f(0.2+c,0.2+c,0.4+c);

	glBegin(GL_LINES);
	for(int i=0; i<3; i++)
	{
		deg = (360/6)*i*(2*PI/360) + f.rot;
		r = (0.5+c/2)*f.size/50;
		glVertex3f(f.x + r*cos(deg), f.y + r * sin(deg), f.z);
		glVertex3f(f.x - r*cos(deg), f.y - r * sin(deg), f.z);
	}
	glEnd();
}
