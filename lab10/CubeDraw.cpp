//  ============================================================================
//  COSC363  Computer Graphics (2014);  University of Canterbury.
//
//  FILE NAME: CubeDraw.cpp
//
//	Please see Lab10.pdf for details
//  =============================================================================

#include <iostream>
#include <GL/glew.h>
#include <GL/freeglut.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "Shader.h"
#include "Cube.h"
#include "loadTGA.h"
using namespace std;

GLuint vaoID, texID;
GLuint theProgram;
GLuint matrixLoc1, matrixLoc2, matrixLoc3;
float angle = 0.0;
glm::mat4 proj, view, projView;  //Matrices

void loadTextures()
{
    glGenTextures(1, &texID);   //Generate 1 texture ID
    //glUniformi();// Load brick texture
    glActiveTexture(GL_TEXTURE0);  //Texture unit 0
    glBindTexture(GL_TEXTURE_2D, texID);
	loadTGA("Brick.tga");

    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
}

void initialise()
{
	loadTextures();
	GLuint program = createShaderProg("Cube.vert", "Cube.frag");
	matrixLoc1 = glGetUniformLocation(program, "mvMatrix");
	matrixLoc2 = glGetUniformLocation(program, "mvpMatrix");
	matrixLoc3 = glGetUniformLocation(program, "norMatrix");
	GLuint lgtLoc = glGetUniformLocation(program, "lightPos");

	GLuint texLoc = glGetUniformLocation(program, "tex1");  //tex1 is a uniform variable of type Sampler2D in the fragment shader
	glUniform1i(texLoc, 0);    //Assign a value 0 to the variable tex1 to specify that it should use the texture from unit 0.

	glm::vec4 light = glm::vec4(10.0, 10.0, 10.0, 1.0);
	proj = glm::perspective(20.0f, 1.0f, 10.0f, 1000.0f);  //perspective projection matrix
	view = glm::lookAt(glm::vec3(0.0, 5.0, 12.0), glm::vec3(0.0, 0.0, 0.0), glm::vec3(0.0, 1.0, 0.0)); //view matrix
	glm::vec4 lightEye = view*light;     //Light position in eye coordinates
	glUniform4fv(lgtLoc, 1, &lightEye[0]);
	projView = proj*view;  //Product matrix

	GLuint vboID[4];

	glGenVertexArrays(1, &vaoID);
    glBindVertexArray(vaoID);

    glGenVertexArrays(4, vboID);

    glBindBuffer(GL_ARRAY_BUFFER, vboID[0]);
    glBufferData(GL_ARRAY_BUFFER, 24 * 3 * sizeof(float), vert, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, NULL);
    glEnableVertexAttribArray(0);  // Vertex position

    glBindBuffer(GL_ARRAY_BUFFER, vboID[1]);
    glBufferData(GL_ARRAY_BUFFER, 24 * 3 * sizeof(float), norm, GL_STATIC_DRAW);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, NULL);
    glEnableVertexAttribArray(1);  // Vertex normal

    glBindBuffer(GL_ARRAY_BUFFER, vboID[2]);
    glBufferData(GL_ARRAY_BUFFER, 24 * 2 * sizeof(float), tex, GL_STATIC_DRAW);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 0, NULL);
    glEnableVertexAttribArray(2);  // texture coords

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vboID[3]);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, 36 * sizeof(GLushort), elem, GL_STATIC_DRAW);

    glBindVertexArray(0);

	glEnable(GL_DEPTH_TEST);
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
}

void update(int value)
{
	angle++;
	glutTimerFunc(50, update, 0);
	glutPostRedisplay();
}

void display()
{
	glm::mat4 matrix = glm::mat4(1.0);
	matrix = glm::rotate(matrix, angle, glm::vec3(0.0, 1.0, 0.0));  //rotation matrix
	glm::mat4 prodMatrix1 = view*matrix;        //Model-view matrix
	glm::mat4 prodMatrix2 = proj*prodMatrix1;   //The model-view-projection transformation

	glm::mat4 invMatrix = glm::inverse(prodMatrix1);  //Inverse of model-view matrix for normal transformation
	glUniformMatrix4fv(matrixLoc1, 1, GL_FALSE, &prodMatrix1[0][0]);
	glUniformMatrix4fv(matrixLoc2, 1, GL_FALSE, &prodMatrix2[0][0]);
	glUniformMatrix4fv(matrixLoc3, 1, GL_TRUE, &invMatrix[0][0]);  //Use transpose matrix here

	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
	glBindVertexArray(vaoID);
	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_SHORT, NULL);
	glFlush();
}

int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGB|GLUT_DEPTH);
	glutInitWindowSize(500, 500);
	glutCreateWindow("Multi-Textured Cube");
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

