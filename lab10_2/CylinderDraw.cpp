//  ========================================================================
//  COSC363: Computer Graphics (2014)  University of Canterbury.
//
//  FILE NAME: CylinderDraw.cpp
//
//	See Lab10.pdf for details.
//  ========================================================================
#include <iostream>
#include <GL/glew.h>
#include <GL/freeglut.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "Shader.h"
#include "Cylinder.h"
#include "loadTGA.h"
using namespace std;

GLuint matrixLoc1, matrixLoc2, matrixLoc3, lgtLoc;
float angle = 0.0;
Cylinder *cylinder;


void initialise()
{
	GLuint program = createShaderProg("Cylinder.vert", "Cylinder.frag");
	matrixLoc1 = glGetUniformLocation(program, "mvMatrix");
	matrixLoc2 = glGetUniformLocation(program, "mvpMatrix");
	matrixLoc3 = glGetUniformLocation(program, "norMatrix");
	lgtLoc = glGetUniformLocation(program, "lightPos");

	cylinder = new Cylinder(6.0, 16.0, 36, 5);   //Radius, height, slices, stacks
	
    glClearColor(0.0f, 1.0f, 1.0f, 1.0f);
	glEnable(GL_DEPTH_TEST);
}


void update(int value)
{
	angle++;
	glutTimerFunc(50, update, 0);
	glutPostRedisplay();
}

void display()
{
	glm::vec4 light = glm::vec4(0.0, 10.0, 20.0, 1.0);
	glm::mat4 proj = glm::perspective(10.0f, 1.0f, 100.0f, 1000.0f);  //perspective projection matrix
	glm::mat4 view = glm::lookAt(glm::vec3(0.0, 30.0, 150.0),
		                         glm::vec3(0.0, 8.0, 0.0), glm::vec3(0.0, 1.0, 0.0)); //view matrix
	glm::mat4 matrix = glm::mat4(1.0);
	matrix = glm::rotate(matrix, angle, glm::vec3(0.0, 1.0, 0.0));  //rotation matrix
	glm::mat4 prodMatrix1 = view*matrix;        //Model-view matrix
	glm::mat4 prodMatrix2 = proj*prodMatrix1;   //The model-view-projection transformation
	glm::vec4 lightEye = view*light;     //Light position in eye coordinates
	glm::mat4 invMatrix = glm::inverse(prodMatrix1);  //Inverse of model-view matrix for normal transformation
	glUniformMatrix4fv(matrixLoc1, 1, GL_FALSE, &prodMatrix1[0][0]);
	glUniformMatrix4fv(matrixLoc2, 1, GL_FALSE, &prodMatrix2[0][0]);
	glUniformMatrix4fv(matrixLoc3, 1, GL_TRUE, &invMatrix[0][0]);  //Use transpose matrix here
	glUniform4fv(lgtLoc, 1, &lightEye[0]);

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	cylinder->render();

	glFlush();
}

int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(500, 500);
	glutCreateWindow("Cylinder");
	glutInitContextVersion (4, 2);
	glutInitContextProfile ( GLUT_CORE_PROFILE );

	if(glewInit() != GLEW_OK)
	{
		cerr << "Unable to initialize GLEW  ...exiting" << endl;
		exit(EXIT_FAILURE);
	}

	initialise();
	glutDisplayFunc(display);
	glutTimerFunc(50, update, 0);
	glutMainLoop();
}

