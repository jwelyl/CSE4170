#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <GL/glew.h>
#include <GL/freeglut.h>

#include "Shaders/LoadShaders.h"
GLuint h_ShaderProgram; // handle to shader program
GLint loc_ModelViewProjectionMatrix, loc_primitive_color; // indices of uniform variables

														  // include glm/*.hpp only if necessary
														  //#include <glm/glm.hpp> 
#include <glm/gtc/matrix_transform.hpp> //translate, rotate, scale, ortho, etc.
glm::mat4 ModelViewProjectionMatrix;
glm::mat4 ViewMatrix, ProjectionMatrix, ViewProjectionMatrix;

#define TO_RADIAN 0.01745329252f  
#define TO_DEGREE 57.295779513f
#define BUFFER_OFFSET(offset) ((GLvoid *) (offset))

#define LOC_VERTEX 0

#include "Object.h"

GLfloat shear_x[9] = {
	1.0f, 0.0f, 0.0f,
	1.0f, 1.0f, 0.0f,
	0.0f, 0.0f, 1.0f
};

GLfloat shear_y[9] = {
	1.0f, 1.0f, 0.0f,
	0.0f, 1.0f, 0.0f,
	0.0f, 0.0f, 1.0f
};

unsigned int timestamp1 = 0;
unsigned int timestamp2 = 0;

int star_x_pos[60];
int star_y_pos[60];
int explosion_x_pos[6];
int explosion_y_pos[6];
int explosion_x_size[6];
int explosion_y_size[6];

void timer(int value) {
	int minusy, minusx;
	timestamp1 = (timestamp1 + 1) % UINT_MAX;
	timestamp2 = (timestamp2 + 5) % UINT_MAX;
	if (timestamp1 % 50 == 0) {
		for (int i = 0; i < 60; i++) {
			star_x_pos[i] = rand() % 1800 - 900;
			star_y_pos[i] = rand() % 900 - 450;
		}
	}

	if (timestamp1 % 70 == 0) {
		for (int i = 0; i < 6; i++) {
			minusy = rand() % 3;
			minusx = rand() % 3;

			if (minusy == 0 || minusy == 1) minusy = -1;
			else minusy = 1;

			if (minusx == 0 || minusx == 1) minusx = -1;
			else minusx = 1;
	

			explosion_y_size[i] = (rand() % 3 + 2) * minusy;
			explosion_x_size[i] = (rand() % 3 + 2) * minusx;

			explosion_y_pos[i] = (rand() % 250 + 150) * -1;
			if (-400 <= explosion_y_pos[i] && explosion_y_pos[i] <= -250)
				explosion_x_pos[i] = rand() % 1800 - 900;
			else
				explosion_x_pos[i] = rand() % 900 - 450;
		}
	}

	glutPostRedisplay();
	glutTimerFunc(10, timer, 0);
}

void display_objects(void) {
	glm::mat4 ModelMatrix;
	glClear(GL_COLOR_BUFFER_BIT);

	ModelMatrix = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, 1.0f));
	ModelMatrix = glm::scale(ModelMatrix, glm::vec3(5, 5, 1));
//	ModelMatrix = glm::rotate(ModelMatrix, 90 * TO_RADIAN, glm::vec3(0, 0, 1));
	
	ModelViewProjectionMatrix = ViewProjectionMatrix * ModelMatrix;
	glUniformMatrix4fv(loc_ModelViewProjectionMatrix, 1, GL_FALSE, &ModelViewProjectionMatrix[0][0]);
	draw_explosion();

	glColor3f(0, 0, 255);

	double rad = 600.0f;

	for (int i = 0; i < 360; i++) {
		double angle = i;
		double x = rad * cos(angle * TO_RADIAN);
		double y = rad * sin(angle * TO_RADIAN);
		glVertex2f(x, y);
	}

	glFlush();
}

void display(void) {
	glm::mat4 ModelMatrix, ModelMatrix2;
	glClear(GL_COLOR_BUFFER_BIT);
	
	for (int i = 0; i < 30; i++) {
		ModelMatrix = glm::translate(glm::mat4(1.0f), glm::vec3(star_x_pos[i], star_y_pos[i], 0.0f));
		ModelViewProjectionMatrix = ViewProjectionMatrix * ModelMatrix;
		glUniformMatrix4fv(loc_ModelViewProjectionMatrix, 1, GL_FALSE, &ModelViewProjectionMatrix[0][0]);
		draw_yellow_star();
	}

	for (int i = 30; i < 40; i++) {
		ModelMatrix = glm::translate(glm::mat4(1.0f), glm::vec3(star_x_pos[i], star_y_pos[i], 0.0f));
		ModelViewProjectionMatrix = ViewProjectionMatrix * ModelMatrix;
		glUniformMatrix4fv(loc_ModelViewProjectionMatrix, 1, GL_FALSE, &ModelViewProjectionMatrix[0][0]);
		draw_blue_star();
	}

	for (int i = 40; i < 60; i++) {
		ModelMatrix = glm::translate(glm::mat4(1.0f), glm::vec3(star_x_pos[i], star_y_pos[i], 0.0f));
		ModelViewProjectionMatrix = ViewProjectionMatrix * ModelMatrix;
		glUniformMatrix4fv(loc_ModelViewProjectionMatrix, 1, GL_FALSE, &ModelViewProjectionMatrix[0][0]);
		draw_red_star();
	}

	ModelMatrix = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, 0.0f));
	ModelViewProjectionMatrix = ViewProjectionMatrix * ModelMatrix;
	glUniformMatrix4fv(loc_ModelViewProjectionMatrix, 1, GL_FALSE, &ModelViewProjectionMatrix[0][0]);
	draw_earth();

	for (int i = 0; i < 6; i++) {
		ModelMatrix = glm::translate(glm::mat4(1.0f), glm::vec3(explosion_x_pos[i], explosion_y_pos[i], 0.0f));
		ModelMatrix = glm::scale(ModelMatrix, glm::vec3(explosion_x_size[i], explosion_y_size[i], 1.0f));
		ModelViewProjectionMatrix = ViewProjectionMatrix * ModelMatrix;
		glUniformMatrix4fv(loc_ModelViewProjectionMatrix, 1, GL_FALSE, &ModelViewProjectionMatrix[0][0]);
		draw_explosion();
	}
	
	float cc = (float)timestamp1;
	
	//	cycloid

	ModelMatrix = glm::translate(glm::mat4(1.0f), glm::vec3(-550.0f, -200.0f, 0.0f));
	ModelMatrix = glm::translate(ModelMatrix, glm::vec3(100 * (timestamp1 % 1080 * TO_RADIAN - sin(timestamp1 % 1080 * TO_RADIAN)), 100 * (1 - cos(timestamp1 % 1080 * TO_RADIAN)), 0.0f));
	if ((0 <= timestamp1 % 1080 && timestamp1 % 1080 <= 180) || (360 <= timestamp1 % 1080 && timestamp1 % 1080 <= 540) || (720 <= timestamp1 % 1080 && timestamp1 % 1080 <= 900)) {
		ModelMatrix = glm::scale(ModelMatrix, glm::vec3(1 + (timestamp1 % 180) / 22.5, 1 + (timestamp1 % 180) / 22.5, 1.0f));
	}
	else if ((181 <= timestamp1 % 1080 && timestamp1 % 1080 <= 359) || (481 <= timestamp1 % 1080 && timestamp1 % 1080 <= 719) || (901 <= timestamp1 % 1080 && timestamp1 % 1080 <= 1079)) {
		ModelMatrix = glm::scale(ModelMatrix, glm::vec3(1 + (180 - (timestamp1 % 180)) /22.5, 1 + (180 - (timestamp1 % 180)) / 22.5, 1));
	}

	if (0 <= (int)cc % 90 && (int)cc % 90 < 90) {
		ModelMatrix = glm::rotate(ModelMatrix, 8 * ((int)cc % 90) * TO_RADIAN, glm::vec3(0.0f, 0.0f, 1.0f));
		
	}
	
	ModelViewProjectionMatrix = ViewProjectionMatrix * ModelMatrix;
	glUniformMatrix4fv(loc_ModelViewProjectionMatrix, 1, GL_FALSE, &ModelViewProjectionMatrix[0][0]);
	draw_car2();

	float hc = (float)timestamp2 / 40;

	ModelMatrix = glm::translate(glm::mat4(1.0f), glm::vec3(-25.0f, -300.0f, 0.0f));
	if (0 <= (int)hc % 180 && (int)hc % 180 < 90) {
		ModelMatrix = glm::translate(ModelMatrix, glm::vec3((int)hc % 180, 4000 * sin((int)hc % 180 * TO_RADIAN), 0.0f));
		ModelMatrix = glm::scale(ModelMatrix, glm::vec3(100 * sin((int)hc % 180 * TO_RADIAN), 100 * sin((int)hc % 180 * TO_RADIAN), 1.0f));
	}

	if (90 <= (int)hc % 180 && (int)hc % 180 < 180) {
		ModelMatrix = glm::translate(ModelMatrix, glm::vec3((int)hc % 180, 4000 * sin((int)hc % 180 * TO_RADIAN), 0.0f));
		ModelMatrix = glm::scale(ModelMatrix, glm::vec3(100 * sin((int)hc % 180 * TO_RADIAN), -100 * sin((int)hc % 180 * TO_RADIAN), 1.0f));
	}

	ModelViewProjectionMatrix = ViewProjectionMatrix * ModelMatrix;
	glUniformMatrix4fv(loc_ModelViewProjectionMatrix, 1, GL_FALSE, &ModelViewProjectionMatrix[0][0]);
	draw_house();

	float shc;
	float hatc;

	ModelMatrix = glm::translate(glm::mat4(1.0f), glm::vec3(90, 450.0f, 0.0f));
	if (90 <= (int)hc % 180 && (int)hc % 180 < 180) {
		//	parabola
		shc = (int)hc % 180 - 90;
		ModelMatrix = glm::translate(ModelMatrix, glm::vec3(shc * 2, -0.1 * shc * shc, 0.0f));

		if (0 <= shc && shc <= 15) {
			ModelMatrix = glm::rotate(ModelMatrix, (-30 - shc * 120 / 15.0f) * TO_RADIAN, glm::vec3(0.0f, 0.0f, 1.0f));
			ModelMatrix = glm::translate(ModelMatrix, glm::vec3(50, 0.0f, 0.0f));
		}
		else if (15 <= shc && shc <= 30) {
			ModelMatrix = glm::rotate(ModelMatrix, (-150 + (shc - 15) * 120 / 15.0f) * TO_RADIAN, glm::vec3(0.0f, 0.0f, 1.0f));
			ModelMatrix = glm::translate(ModelMatrix, glm::vec3(60, 0.0f, 0.0f));
		}
		else if (30 <= shc && shc <= 45) {
			ModelMatrix = glm::rotate(ModelMatrix, (-30 - (shc - 30) * 120 / 15.0f) * TO_RADIAN, glm::vec3(0.0f, 0.0f, 1.0f));
			ModelMatrix = glm::translate(ModelMatrix, glm::vec3(70, 0.0f, 0.0f));
		}
		else if (45 <= shc && shc <= 60) {
			ModelMatrix = glm::rotate(ModelMatrix, (-150 + (shc - 45) * 120 / 15.0f) * TO_RADIAN, glm::vec3(0.0f, 0.0f, 1.0f));
			ModelMatrix = glm::translate(ModelMatrix, glm::vec3(80, 0.0f, 0.0f));
		}
		else if (60 <= shc && shc <= 90) {
			ModelMatrix = glm::rotate(ModelMatrix, (-30 - (shc - 60) * 120 / 30.0f) * TO_RADIAN, glm::vec3(0.0f, 0.0f, 1.0f));
			ModelMatrix = glm::translate(ModelMatrix, glm::vec3(100, 0.0f, 0.0f));
		}
		ModelMatrix = glm::scale(ModelMatrix, glm::vec3(0.1 * shc, 0.1 * shc, 1.0f));

		ModelViewProjectionMatrix = ViewProjectionMatrix * ModelMatrix;
		glUniformMatrix4fv(loc_ModelViewProjectionMatrix, 1, GL_FALSE, &ModelViewProjectionMatrix[0][0]);
		draw_shirt(); 
	}

	ModelMatrix = glm::translate(glm::mat4(1.0f), glm::vec3(90, 450.0f, 0.0f));
	if (90 <= (int)hc % 180 && (int)hc % 180 < 180) {
		hatc = (int)hc % 180 - 90;
		ModelMatrix = glm::translate(ModelMatrix, glm::vec3(-hatc * 6, -0.1 * hatc * hatc, 0.0f));

		if (0 <= hatc && hatc < 15) {
			ModelMatrix = glm::rotate(ModelMatrix, (-30 - hatc * 120 / 15.0f) * TO_RADIAN, glm::vec3(0.0f, 0.0f, 1.0f));
			ModelMatrix = glm::translate(ModelMatrix, glm::vec3(50, 0.0f, 0.0f));
			ModelMatrix = glm::rotate(ModelMatrix, hatc * (180 / 15.0f) * TO_RADIAN, glm::vec3(1.0f, 0.0f, 0.0f));
		}
		else if (15 <= hatc && hatc < 30) {
			ModelMatrix = glm::rotate(ModelMatrix, (-150 + (hatc - 15) * 120 / 15.0f) * TO_RADIAN, glm::vec3(0.0f, 0.0f, 1.0f));
			ModelMatrix = glm::translate(ModelMatrix, glm::vec3(60, 0.0f, 0.0f));
			ModelMatrix = glm::rotate(ModelMatrix, -(hatc - 15) * (180 / 15.0f) * TO_RADIAN, glm::vec3(0.0f, 1.0f, 0.0f));
		}
		else if (30 <= hatc && hatc < 45) {
			ModelMatrix = glm::rotate(ModelMatrix, (-30 - (hatc - 30) * 120 / 15.0f) * TO_RADIAN, glm::vec3(0.0f, 0.0f, 1.0f));
			ModelMatrix = glm::translate(ModelMatrix, glm::vec3(70, 0.0f, 0.0f));
			ModelMatrix = glm::rotate(ModelMatrix, -(hatc - 30) * (180 / 15.0f) * TO_RADIAN, glm::vec3(1.0f, 0.0f, 0.0f));
		}
		else if (45 <= hatc && hatc < 60) {
			ModelMatrix = glm::rotate(ModelMatrix, (-150 + (hatc - 45) * 120 / 15.0f) * TO_RADIAN, glm::vec3(0.0f, 0.0f, 1.0f));
			ModelMatrix = glm::translate(ModelMatrix, glm::vec3(80, 0.0f, 0.0f));
			ModelMatrix = glm::rotate(ModelMatrix, -(hatc - 45) * (180 / 15.0f) * TO_RADIAN, glm::vec3(0.0f, 1.0f, 0.0f));
		}
		else if (60 <= hatc && hatc <= 90) {
			ModelMatrix = glm::rotate(ModelMatrix, (-30 - (hatc - 60) * 120 / 30.0f) * TO_RADIAN, glm::vec3(0.0f, 0.0f, 1.0f));
			ModelMatrix = glm::translate(ModelMatrix, glm::vec3(100, 0.0f, 0.0f));
			ModelMatrix = glm::rotate(ModelMatrix, -(hatc - 60) * (180 / 30.0f) * TO_RADIAN, glm::vec3(1.0f, 0.0f, 0.0f));
		}

		ModelMatrix = glm::scale(ModelMatrix, glm::vec3(0.1 * hatc, 0.1 * hatc, 1.0f));
		ModelViewProjectionMatrix = ViewProjectionMatrix * ModelMatrix;
		glUniformMatrix4fv(loc_ModelViewProjectionMatrix, 1, GL_FALSE, &ModelViewProjectionMatrix[0][0]);
		draw_hat();
	}

	float ac = (float)timestamp1 / 2;
	float a_ratio;

	ModelMatrix = glm::translate(glm::mat4(1.0f), glm::vec3(-1100, 200, 0.0f));
	if (0 <= (int)ac % 120 && (int)ac % 120 < 120) {
		ModelMatrix = glm::translate(ModelMatrix, glm::vec3((-1 / 8.0f) * ((int)ac % 120) * ((int)ac % 120) + 30 * ((int)ac % 120), 100, 0.0f));
		ModelMatrix = glm::rotate(ModelMatrix, 90 * TO_RADIAN, glm::vec3(0.0f, 0.0f, 1.0f));
		ModelMatrix = glm::scale(ModelMatrix, glm::vec3(2, 2, 0.0f));
	
		if (50 <= (int)ac % 120 && (int)ac % 120 < 70) {
			ModelMatrix = glm::translate(glm::mat4(1.0f), glm::vec3(-1100, 200, 0.0f));
			ModelMatrix = glm::translate(ModelMatrix, glm::vec3((-1 / 8.0f) * ((int)ac % 120) * ((int)ac % 120) + 30 * ((int)ac % 120), 100, 0.0f));
			ModelMatrix = glm::scale(ModelMatrix, glm::vec3((((int)ac % 120) - 50 + 1) * 0.5, (((int)ac % 120) - 50 + 1) * 0.5, 0.0f));
			ModelViewProjectionMatrix = ViewProjectionMatrix * ModelMatrix;
			glUniformMatrix4fv(loc_ModelViewProjectionMatrix, 1, GL_FALSE, &ModelViewProjectionMatrix[0][0]);
			draw_explosion();
		}

		else if(0 <= (int)ac % 120 && (int)ac % 120 < 50) {
			ModelViewProjectionMatrix = ViewProjectionMatrix * ModelMatrix;
			glUniformMatrix4fv(loc_ModelViewProjectionMatrix, 1, GL_FALSE, &ModelViewProjectionMatrix[0][0]);
			draw_airplane();
		}

		else if (70 <= (int)ac % 120 && (int)ac % 120 < 120) {
			ModelMatrix = glm::scale(ModelMatrix, glm::vec3(0,0,0));
			ModelViewProjectionMatrix = ViewProjectionMatrix * ModelMatrix;
			glUniformMatrix4fv(loc_ModelViewProjectionMatrix, 1, GL_FALSE, &ModelViewProjectionMatrix[0][0]);
			draw_airplane();
		}
	}

	ModelMatrix = glm::translate(glm::mat4(1.0f), glm::vec3(-900, 50, 0.0f));
	if (0 <= (int)ac % 120 && (int)ac % 120 < 120) {
		ModelMatrix = glm::translate(ModelMatrix, glm::vec3((-1/8.0f) * ((int)ac % 120) * ((int)ac % 120) + 30 * ((int)ac % 120), 100, 0.0f));
		if (30 <= (int)ac % 120 && (int)ac % 120 < 60) {
			ModelMatrix = glm::rotate(ModelMatrix, ((int)ac % 90 - 15) * 12 * TO_RADIAN, glm::vec3(1.0f, 0.0f, 0.0f));
		}
		ModelMatrix = glm::rotate(ModelMatrix, 90 * TO_RADIAN, glm::vec3(0.0f, 0.0f, 1.0f));
		ModelMatrix = glm::scale(ModelMatrix, glm::vec3(2, 2, 0.0f));
	}

	ModelViewProjectionMatrix = ViewProjectionMatrix * ModelMatrix;
	glUniformMatrix4fv(loc_ModelViewProjectionMatrix, 1, GL_FALSE, &ModelViewProjectionMatrix[0][0]);
	draw_airplane();

	ModelMatrix = glm::translate(glm::mat4(1.0f), glm::vec3(-1100, -100, 0.0f));
	if (0 <= (int)ac % 120 && (int)ac % 120 < 120) {
		ModelMatrix = glm::translate(ModelMatrix, glm::vec3((-1 / 8.0f) * ((int)ac % 120) * ((int)ac % 120) + 30 * ((int)ac % 120), 100, 0.0f));
		ModelMatrix = glm::rotate(ModelMatrix, 90 * TO_RADIAN, glm::vec3(0.0f, 0.0f, 1.0f));
		ModelMatrix = glm::scale(ModelMatrix, glm::vec3(2, 2, 0.0f));

		if (100 <= (int)ac % 120 && (int)ac % 120 < 120) {
			ModelMatrix = glm::translate(glm::mat4(1.0f), glm::vec3(-1100, -100, 0.0f));
			ModelMatrix = glm::translate(ModelMatrix, glm::vec3((-1 / 8.0f) * ((int)ac % 120) * ((int)ac % 120) + 30 * ((int)ac % 120), 100, 0.0f));
			ModelMatrix = glm::scale(ModelMatrix, glm::vec3((((int)ac % 120) - 100 + 1) * 0.5, (((int)ac % 120) - 100 + 1) * 0.5, 0.0f));
			ModelViewProjectionMatrix = ViewProjectionMatrix * ModelMatrix;
			glUniformMatrix4fv(loc_ModelViewProjectionMatrix, 1, GL_FALSE, &ModelViewProjectionMatrix[0][0]);
			draw_explosion();
		}

		else {
			ModelViewProjectionMatrix = ViewProjectionMatrix * ModelMatrix;
			glUniformMatrix4fv(loc_ModelViewProjectionMatrix, 1, GL_FALSE, &ModelViewProjectionMatrix[0][0]);
			draw_airplane();
		}
	}

	float sc = (float)timestamp1 / 3;
	float s_ratio;

	ModelMatrix = glm::translate(glm::mat4(1.0f), glm::vec3(600, 140, 0.0f));
	if (0 <= (int)sc % 90 && (int)sc % 90 < 90) {
		ModelMatrix = glm::translate(ModelMatrix, glm::vec3(-(int)sc % 90 * 20, 140.0f, 0.0f));
		ModelMatrix = glm::rotate(ModelMatrix, 90 * TO_RADIAN, glm::vec3(0.0f, 0.0f, 1.0f));
		ModelMatrix = glm::scale(ModelMatrix, glm::vec3(6, 6, 0.0f));
	}

	ModelViewProjectionMatrix = ViewProjectionMatrix * ModelMatrix;
	glUniformMatrix4fv(loc_ModelViewProjectionMatrix, 1, GL_FALSE, &ModelViewProjectionMatrix[0][0]);
	draw_scourge();
	
	ModelMatrix = glm::translate(glm::mat4(1.0f), glm::vec3(750, 100, 0.0f));
	if (0 <= (int)sc % 90 && (int)sc % 90 < 90) {
		ModelMatrix = glm::translate(ModelMatrix, glm::vec3(-(int)sc % 90 * 20, 100.0f, 0.0f));
		ModelMatrix = glm::rotate(ModelMatrix, 90 * TO_RADIAN, glm::vec3(0.0f, 0.0f, 1.0f));
		ModelMatrix = glm::scale(ModelMatrix, glm::vec3(6, 6, 0.0f));
	}

	ModelViewProjectionMatrix = ViewProjectionMatrix * ModelMatrix;
	glUniformMatrix4fv(loc_ModelViewProjectionMatrix, 1, GL_FALSE, &ModelViewProjectionMatrix[0][0]);
	draw_scourge();

	ModelMatrix = glm::translate(glm::mat4(1.0f), glm::vec3(900, 70, 0.0f));
	if (0 <= (int)sc % 90 && (int)sc % 90 < 90) {
		ModelMatrix = glm::translate(ModelMatrix, glm::vec3(-(int)sc % 90 * 20, 70.0f, 0.0f));
		if (15 <= (int)sc % 90 && (int)sc % 90 < 45) {
			ModelMatrix = glm::rotate(ModelMatrix, -1 * ((int)sc % 90 - 15) * 12 * TO_RADIAN, glm::vec3(1.0f, 0.0f, 0.0f));
		}
		ModelMatrix = glm::rotate(ModelMatrix, 90 * TO_RADIAN, glm::vec3(0.0f, 0.0f, 1.0f));
		ModelMatrix = glm::scale(ModelMatrix, glm::vec3(6, 6, 0.0f));
	}

	ModelViewProjectionMatrix = ViewProjectionMatrix * ModelMatrix;
	glUniformMatrix4fv(loc_ModelViewProjectionMatrix, 1, GL_FALSE, &ModelViewProjectionMatrix[0][0]);
	draw_scourge();

	ModelMatrix = glm::translate(glm::mat4(1.0f), glm::vec3(750, 40, 0.0f));
	if (0 <= (int)sc % 90 && (int)sc % 90 < 90) {
		ModelMatrix = glm::translate(ModelMatrix, glm::vec3(-(int)sc % 90 * 20, 40.0f, 0.0f));
		ModelMatrix = glm::rotate(ModelMatrix, 90 * TO_RADIAN, glm::vec3(0.0f, 0.0f, 1.0f));
		ModelMatrix = glm::scale(ModelMatrix, glm::vec3(6, 6, 0.0f));
	}

	ModelViewProjectionMatrix = ViewProjectionMatrix * ModelMatrix;
	glUniformMatrix4fv(loc_ModelViewProjectionMatrix, 1, GL_FALSE, &ModelViewProjectionMatrix[0][0]);
	draw_scourge();

	ModelMatrix = glm::translate(glm::mat4(1.0f), glm::vec3(600, -0, 0.0f));
	if (0 <= (int)sc % 90 && (int)sc % 90 < 90) {
		ModelMatrix = glm::translate(ModelMatrix, glm::vec3(-(int)sc % 90 * 20, 0.0f, 0.0f));
		ModelMatrix = glm::rotate(ModelMatrix, 90 * TO_RADIAN, glm::vec3(0.0f, 0.0f, 1.0f));
		ModelMatrix = glm::scale(ModelMatrix, glm::vec3(6, 6, 0.0f));
	}

	ModelViewProjectionMatrix = ViewProjectionMatrix * ModelMatrix;
	glUniformMatrix4fv(loc_ModelViewProjectionMatrix, 1, GL_FALSE, &ModelViewProjectionMatrix[0][0]);
	draw_scourge();

	float esc = (float)timestamp1 / 2;
	float es_ratio;

	//	ellipse
	ModelMatrix = glm::translate(glm::mat4(1.0f), glm::vec3(1000 * cos(((int)esc % 180) * TO_RADIAN), 300 * sin(((int)esc % 180) * TO_RADIAN), 0.0f));
	if (0 <= (int)esc % 180 && (int)esc % 180 <= 90) {
		es_ratio = ((int)esc % 180) / 6.0f;
		ModelMatrix = glm::scale(ModelMatrix, glm::vec3(es_ratio, es_ratio, 1.0f));
	}
	if (91 <= (int)esc % 180 && (int)esc % 180 < 180) {
		es_ratio = (181 - (int)esc % 180) / 6.0f;
		ModelMatrix = glm::scale(ModelMatrix, glm::vec3(es_ratio, es_ratio, 1.0f));
	}
	
	if (0 <= (int)esc % 180 && (int)esc % 180 < 180) {
		if (0 <= (int)esc % 180 && (int)esc % 180 < 90) {
			ModelMatrix = glm::rotate(ModelMatrix, 8 * ((int)esc % 180) * TO_RADIAN, glm::vec3(0.0f, 0.0f, 1.0f));
			//if(30 <= (int)esc % 180 && (int)esc % 180 <= 50)
			//	ModelMatrix = glm::scale(ModelMatrix, glm::vec3(1, -1, 1.0f));
		}
		else if (90 <= (int)esc % 180 && (int)esc % 180 < 180) {
			ModelMatrix = glm::rotate(ModelMatrix, -4 * ((int)esc % 180) * TO_RADIAN, glm::vec3(0.0f, 0.0f, 1.0f));
			//if ((75 <= (int)esc % 180 && (int)esc % 180 <= 105) || (120 <= (int)esc % 180 && (int)esc % 180 <= 150))
			//	ModelMatrix = glm::scale(ModelMatrix, glm::vec3(1, -1, 1.0f));
		}
		ModelMatrix = glm::translate(ModelMatrix, glm::vec3(((int)esc % 180) / 10.0f, 0.0f, 0.0f));
	}

	ModelViewProjectionMatrix = ViewProjectionMatrix * ModelMatrix;
	glUniformMatrix4fv(loc_ModelViewProjectionMatrix, 1, GL_FALSE, &ModelViewProjectionMatrix[0][0]);
	draw_elite_scourge();

	float eac = (float)timestamp1 / 2;
	float ea_ratio;

	//	ellipse
	ModelMatrix = glm::translate(glm::mat4(1.0f), glm::vec3(900 * cos(((int)eac % 180) * TO_RADIAN), 75 * sin(((int)eac % 180) * TO_RADIAN), 0.0f));
	if (0 <= (int)eac % 180 && (int)eac % 180 <= 90) {
		ea_ratio = ((int)eac % 180) / 14.0f;
		ModelMatrix = glm::scale(ModelMatrix, glm::vec3(ea_ratio, ea_ratio, 1.0f));
	}
	if (91 <= (int)eac % 180 && (int)eac % 180 < 180) {
		ea_ratio = (181 - (int)eac % 180) / 14.0f;
		ModelMatrix = glm::scale(ModelMatrix, glm::vec3(ea_ratio, ea_ratio, 1.0f));
	}

	if (0 <= (int)eac % 180 && (int)eac % 180 < 180) {
		ModelMatrix = glm::rotate(ModelMatrix, -8 * ((int)eac % 180) * TO_RADIAN, glm::vec3(0.0f, 0.0f, 1.0f));
		ModelMatrix = glm::translate(ModelMatrix, glm::vec3(((int)eac % 180) / 10.0f, 0.0f, 0.0f));
		ModelMatrix = glm::rotate(ModelMatrix, -8 * ((int)eac % 360) * TO_RADIAN, glm::vec3(0.0f, 1.0f, 0.0f));
	}

	ModelViewProjectionMatrix = ViewProjectionMatrix * ModelMatrix;
	glUniformMatrix4fv(loc_ModelViewProjectionMatrix, 1, GL_FALSE, &ModelViewProjectionMatrix[0][0]);
	draw_elite_airplane();

	glColor3f(0, 0, 255);

	double rad = 600.0f;

	for (int i = 0; i < 360; i++) {
		double angle = i;
		double x = rad * cos(angle * TO_RADIAN);
		double y = rad * sin(angle * TO_RADIAN);
		glVertex2f(x, y);
	}

	glFlush();
}

void keyboard(unsigned char key, int x, int y) {
	switch (key) {
	case 27: // ESC key
		glutLeaveMainLoop(); // Incur destuction callback for cleanups.
		break;
	}
}

void reshape(int width, int height) {
	win_width = width, win_height = height;

	glViewport(0, 0, win_width, win_height);
	ProjectionMatrix = glm::ortho(-win_width / 2.0, win_width / 2.0,
		-win_height / 2.0, win_height / 2.0, -1000.0, 1000.0);
	ViewProjectionMatrix = ProjectionMatrix * ViewMatrix;

	update_axes();
	update_line();

	glutPostRedisplay();
}

void cleanup(void) {
	glDeleteVertexArrays(1, &VAO_hat);
	glDeleteBuffers(1, &VBO_hat);
	glDeleteVertexArrays(1, &VAO_shirt);
	glDeleteBuffers(1, &VBO_shirt);
	glDeleteVertexArrays(1, &VAO_car2);
	glDeleteBuffers(1, &VBO_car2);
	glDeleteVertexArrays(1, &VAO_house);
	glDeleteBuffers(1, &VBO_house);
	glDeleteVertexArrays(1, &VAO_airplane);
	glDeleteBuffers(1, &VBO_airplane);
	glDeleteVertexArrays(1, &VAO_elite_airplane);
	glDeleteBuffers(1, &VBO_elite_airplane);
	glDeleteVertexArrays(1, &VAO_scourge);
	glDeleteBuffers(1, &VBO_scourge);
	glDeleteVertexArrays(1, &VAO_elite_scourge);
	glDeleteBuffers(1, &VBO_elite_scourge);
	glDeleteVertexArrays(1, &VAO_yellow_star);
	glDeleteBuffers(1, &VBO_yellow_star);
	glDeleteVertexArrays(1, &VAO_blue_star);
	glDeleteBuffers(1, &VBO_blue_star);
	glDeleteVertexArrays(1, &VAO_red_star);
	glDeleteBuffers(1, &VBO_red_star);
	glDeleteVertexArrays(1, &VAO_explosion);
	glDeleteBuffers(1, &VBO_explosion);
	glDeleteVertexArrays(1, &VAO_earth);
	glDeleteBuffers(1, &VBO_earth);

	// Delete others here too!!!
}

void register_callbacks(void) {
	glutDisplayFunc(display);
	glutKeyboardFunc(keyboard);
	glutReshapeFunc(reshape);
	glutCloseFunc(cleanup);
	glutTimerFunc(10, timer, 0);
}

void prepare_shader_program(void) {
	ShaderInfo shader_info[3] = {
		{ GL_VERTEX_SHADER, "Shaders/simple.vert" },
		{ GL_FRAGMENT_SHADER, "Shaders/simple.frag" },
		{ GL_NONE, NULL }
	};

	h_ShaderProgram = LoadShaders(shader_info);
	glUseProgram(h_ShaderProgram);

	loc_ModelViewProjectionMatrix = glGetUniformLocation(h_ShaderProgram, "u_ModelViewProjectionMatrix");
	loc_primitive_color = glGetUniformLocation(h_ShaderProgram, "u_primitive_color");
}

void initialize_OpenGL(void) {
	glEnable(GL_MULTISAMPLE);
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

	glClearColor(4 / 255.0f, 5 / 255.0f, 51 / 255.0f, 1.0f);
	ViewMatrix = glm::mat4(1.0f);
}

void prepare_scene(void) {
	prepare_axes();
	prepare_line();
	prepare_airplane();
	prepare_elite_airplane();
	prepare_shirt();
	prepare_house();
	prepare_car();
	prepare_cocktail();
	prepare_car2();
	prepare_hat();
	prepare_cake();
	prepare_sword();
	prepare_scourge();
	prepare_elite_scourge();
	prepare_yello_star();
	prepare_blue_star();
	prepare_red_star();
	prepare_earth();
	prepare_explosion();
}

void initialize_renderer(void) {
	register_callbacks();
	prepare_shader_program();
	initialize_OpenGL();
	prepare_scene();
}

void initialize_glew(void) {
	GLenum error;

	glewExperimental = GL_TRUE;

	error = glewInit();
	if (error != GLEW_OK) {
		fprintf(stderr, "Error: %s\n", glewGetErrorString(error));
		exit(-1);
	}
	fprintf(stdout, "*********************************************************\n");
	fprintf(stdout, " - GLEW version supported: %s\n", glewGetString(GLEW_VERSION));
	fprintf(stdout, " - OpenGL renderer: %s\n", glGetString(GL_RENDERER));
	fprintf(stdout, " - OpenGL version supported: %s\n", glGetString(GL_VERSION));
	fprintf(stdout, "*********************************************************\n\n");
}

void greetings(char *program_name, char messages[][256], int n_message_lines) {
	fprintf(stdout, "**************************************************************\n\n");
	fprintf(stdout, "  PROGRAM NAME: %s\n\n", program_name);
	fprintf(stdout, "    This program was coded for CSE4170 students\n");
	fprintf(stdout, "      of Dept. of Comp. Sci. & Eng., Sogang University.\n\n");

	for (int i = 0; i < n_message_lines; i++)
		fprintf(stdout, "%s\n", messages[i]);
	fprintf(stdout, "\n**************************************************************\n\n");

	initialize_glew();
}

#define N_MESSAGE_LINES 1
void main(int argc, char *argv[]) {
	char program_name[64] = "Sogang CSE4170 2DObjects_GLSL_3.0.1.3";
	char messages[N_MESSAGE_LINES][256] = {
		"    - Keys used: 'ESC' "
	};
	srand(time(NULL));

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGBA | GLUT_MULTISAMPLE);
	glutInitWindowSize(1800, 900);
	glutInitContextVersion(3, 3);
	glutInitContextProfile(GLUT_CORE_PROFILE);
	glutCreateWindow(program_name);

	greetings(program_name, messages, N_MESSAGE_LINES);
	initialize_renderer();

	glutSetOption(GLUT_ACTION_ON_WINDOW_CLOSE, GLUT_ACTION_GLUTMAINLOOP_RETURNS);
	glutMainLoop();
}