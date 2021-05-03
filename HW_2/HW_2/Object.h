#pragma once

int win_width = 0, win_height = 0;
float centerx = 0.0f, centery = 0.0f, rotate_angle = 0.0f;

GLfloat axes[4][2];
GLfloat axes_color[3] = { 0.0f, 0.0f, 0.0f };
GLuint VBO_axes, VAO_axes;

void prepare_axes(void) { // Draw axes in their MC.
	axes[0][0] = -win_width / 2.5f; axes[0][1] = 0.0f;
	axes[1][0] = win_width / 2.5f; axes[1][1] = 0.0f;
	axes[2][0] = 0.0f; axes[2][1] = -win_height / 2.5f;
	axes[3][0] = 0.0f; axes[3][1] = win_height / 2.5f;

	// Initialize vertex buffer object.
	glGenBuffers(1, &VBO_axes);

	glBindBuffer(GL_ARRAY_BUFFER, VBO_axes);
	glBufferData(GL_ARRAY_BUFFER, sizeof(axes), axes, GL_STATIC_DRAW);

	// Initialize vertex array object.
	glGenVertexArrays(1, &VAO_axes);
	glBindVertexArray(VAO_axes);

	glBindBuffer(GL_ARRAY_BUFFER, VBO_axes);
	glVertexAttribPointer(LOC_VERTEX, 2, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(0));

	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}

void update_axes(void) {
	axes[0][0] = -win_width / 2.25f; axes[1][0] = win_width / 2.25f;
	axes[2][1] = -win_height / 2.25f;
	axes[3][1] = win_height / 2.25f;

	glBindBuffer(GL_ARRAY_BUFFER, VBO_axes);
	glBufferData(GL_ARRAY_BUFFER, sizeof(axes), axes, GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void draw_axes(void) {
	glUniform3fv(loc_primitive_color, 1, axes_color);
	glBindVertexArray(VAO_axes);
	glDrawArrays(GL_LINES, 0, 4);
	glBindVertexArray(0);
}

GLfloat line[2][2];
GLfloat line_color[3] = { 1.0f, 0.0f, 0.0f };
GLuint VBO_line, VAO_line;

void prepare_line(void) { 	// y = x - win_height/4
	line[0][0] = (1.0f / 4.0f - 1.0f / 2.5f) * win_height;
	line[0][1] = (1.0f / 4.0f - 1.0f / 2.5f) * win_height - win_height / 4.0f;
	line[1][0] = win_width / 2.5f;
	line[1][1] = win_width / 2.5f - win_height / 4.0f;

	// Initialize vertex buffer object.
	glGenBuffers(1, &VBO_line);

	glBindBuffer(GL_ARRAY_BUFFER, VBO_line);
	glBufferData(GL_ARRAY_BUFFER, sizeof(line), line, GL_STATIC_DRAW);

	// Initialize vertex array object.
	glGenVertexArrays(1, &VAO_line);
	glBindVertexArray(VAO_line);

	glBindBuffer(GL_ARRAY_BUFFER, VBO_line);
	glVertexAttribPointer(LOC_VERTEX, 2, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(0));

	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}

void update_line(void) { 	// y = x - win_height/4
	line[0][0] = (1.0f / 4.0f - 1.0f / 2.5f) * win_height;
	line[0][1] = (1.0f / 4.0f - 1.0f / 2.5f) * win_height - win_height / 4.0f;
	line[1][0] = win_width / 2.5f;
	line[1][1] = win_width / 2.5f - win_height / 4.0f;

	glBindBuffer(GL_ARRAY_BUFFER, VBO_line);
	glBufferData(GL_ARRAY_BUFFER, sizeof(line), line, GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void draw_line(void) { // Draw line in its MC.
					   // y = x - win_height/4
	glUniform3fv(loc_primitive_color, 1, line_color);
	glBindVertexArray(VAO_line);
	glDrawArrays(GL_LINES, 0, 2);
	glBindVertexArray(0);
}

#define AIRPLANE_BIG_WING 0
#define AIRPLANE_SMALL_WING 1
#define AIRPLANE_BODY 2
#define AIRPLANE_BACK 3
#define AIRPLANE_SIDEWINDER1 4
#define AIRPLANE_SIDEWINDER2 5
#define AIRPLANE_CENTER 6
GLfloat big_wing[6][2] = { { 0.0, 0.0 },{ -20.0, 15.0 },{ -20.0, 20.0 },{ 0.0, 23.0 },{ 20.0, 20.0 },{ 20.0, 15.0 } };
GLfloat small_wing[6][2] = { { 0.0, -18.0 },{ -11.0, -12.0 },{ -12.0, -7.0 },{ 0.0, -10.0 },{ 12.0, -7.0 },{ 11.0, -12.0 } };
GLfloat body[5][2] = { { 0.0, -25.0 },{ -6.0, 0.0 },{ -6.0, 22.0 },{ 6.0, 22.0 },{ 6.0, 0.0 } };
GLfloat back[5][2] = { { 0.0, 25.0 },{ -7.0, 24.0 },{ -7.0, 21.0 },{ 7.0, 21.0 },{ 7.0, 24.0 } };
GLfloat sidewinder1[5][2] = { { -20.0, 10.0 },{ -18.0, 3.0 },{ -16.0, 10.0 },{ -18.0, 20.0 },{ -20.0, 20.0 } };
GLfloat sidewinder2[5][2] = { { 20.0, 10.0 },{ 18.0, 3.0 },{ 16.0, 10.0 },{ 18.0, 20.0 },{ 20.0, 20.0 } };
GLfloat center[1][2] = { { 0.0, 0.0 } };
GLfloat airplane_color[7][3] = {
	{ 150 / 255.0f, 129 / 255.0f, 183 / 255.0f },  // big_wing
	{ 245 / 255.0f, 211 / 255.0f,   0 / 255.0f },  // small_wing	
	{ 111 / 255.0f,  85 / 255.0f, 157 / 255.0f },  // body
	{ 150 / 255.0f, 129 / 255.0f, 183 / 255.0f },  // back
	{ 245 / 255.0f, 211 / 255.0f,   0 / 255.0f },  // sidewinder1
	{ 245 / 255.0f, 211 / 255.0f,   0 / 255.0f },  // sidewinder2
	{ 255 / 255.0f,   0 / 255.0f,   0 / 255.0f }   // center
};

GLuint VBO_airplane, VAO_airplane;

int airplane_clock = 0;
float airplane_s_factor = 1.0f;

void prepare_airplane() {
	GLsizeiptr buffer_size = sizeof(big_wing) + sizeof(small_wing) + sizeof(body) + sizeof(back)
		+ sizeof(sidewinder1) + sizeof(sidewinder2) + sizeof(center);

	// Initialize vertex buffer object.
	glGenBuffers(1, &VBO_airplane);

	glBindBuffer(GL_ARRAY_BUFFER, VBO_airplane);
	glBufferData(GL_ARRAY_BUFFER, buffer_size, NULL, GL_STATIC_DRAW); // allocate buffer object memory

	glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(big_wing), big_wing);
	glBufferSubData(GL_ARRAY_BUFFER, sizeof(big_wing), sizeof(small_wing), small_wing);
	glBufferSubData(GL_ARRAY_BUFFER, sizeof(big_wing) + sizeof(small_wing), sizeof(body), body);
	glBufferSubData(GL_ARRAY_BUFFER, sizeof(big_wing) + sizeof(small_wing) + sizeof(body), sizeof(back), back);
	glBufferSubData(GL_ARRAY_BUFFER, sizeof(big_wing) + sizeof(small_wing) + sizeof(body) + sizeof(back),
		sizeof(sidewinder1), sidewinder1);
	glBufferSubData(GL_ARRAY_BUFFER, sizeof(big_wing) + sizeof(small_wing) + sizeof(body) + sizeof(back)
		+ sizeof(sidewinder1), sizeof(sidewinder2), sidewinder2);
	glBufferSubData(GL_ARRAY_BUFFER, sizeof(big_wing) + sizeof(small_wing) + sizeof(body) + sizeof(back)
		+ sizeof(sidewinder1) + sizeof(sidewinder2), sizeof(center), center);

	// Initialize vertex array object.
	glGenVertexArrays(1, &VAO_airplane);
	glBindVertexArray(VAO_airplane);

	glBindBuffer(GL_ARRAY_BUFFER, VBO_airplane);
	glVertexAttribPointer(LOC_VERTEX, 2, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(0));

	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}

void draw_airplane() { // Draw airplane in its MC.
	glBindVertexArray(VAO_airplane);

	glUniform3fv(loc_primitive_color, 1, airplane_color[AIRPLANE_BIG_WING]);
	glDrawArrays(GL_TRIANGLE_FAN, 0, 6);

	glUniform3fv(loc_primitive_color, 1, airplane_color[AIRPLANE_SMALL_WING]);
	glDrawArrays(GL_TRIANGLE_FAN, 6, 6);

	glUniform3fv(loc_primitive_color, 1, airplane_color[AIRPLANE_BODY]);
	glDrawArrays(GL_TRIANGLE_FAN, 12, 5);

	glUniform3fv(loc_primitive_color, 1, airplane_color[AIRPLANE_BACK]);
	glDrawArrays(GL_TRIANGLE_FAN, 17, 5);

	glUniform3fv(loc_primitive_color, 1, airplane_color[AIRPLANE_SIDEWINDER1]);
	glDrawArrays(GL_TRIANGLE_FAN, 22, 5);

	glUniform3fv(loc_primitive_color, 1, airplane_color[AIRPLANE_SIDEWINDER2]);
	glDrawArrays(GL_TRIANGLE_FAN, 27, 5);

	glUniform3fv(loc_primitive_color, 1, airplane_color[AIRPLANE_CENTER]);
	glPointSize(5.0);
	glDrawArrays(GL_POINTS, 32, 1);
	glPointSize(1.0);
	glBindVertexArray(0);
}

//	elite_airplane
#define ELITE_AIRPLANE_BIG_WING 0
#define ELITE_AIRPLANE_SMALL_WING 1
#define ELITE_AIRPLANE_BODY 2
#define ELITE_AIRPLANE_BACK 3
#define ELITE_AIRPLANE_SIDEWINDER1 4
#define ELITE_AIRPLANE_SIDEWINDER2 5
#define ELITE_AIRPLANE_CENTER 6
GLfloat e_big_wing[6][2] = { { 0.0, 0.0 },{ -20.0, 15.0 },{ -20.0, 20.0 },{ 0.0, 23.0 },{ 20.0, 20.0 },{ 20.0, 15.0 } };
GLfloat e_small_wing[6][2] = { { 0.0, -18.0 },{ -11.0, -12.0 },{ -12.0, -7.0 },{ 0.0, -10.0 },{ 12.0, -7.0 },{ 11.0, -12.0 } };
GLfloat e_body[5][2] = { { 0.0, -25.0 },{ -6.0, 0.0 },{ -6.0, 22.0 },{ 6.0, 22.0 },{ 6.0, 0.0 } };
GLfloat e_back[5][2] = { { 0.0, 25.0 },{ -7.0, 24.0 },{ -7.0, 21.0 },{ 7.0, 21.0 },{ 7.0, 24.0 } };
GLfloat e_sidewinder1[5][2] = { { -20.0, 10.0 },{ -18.0, 3.0 },{ -16.0, 10.0 },{ -18.0, 20.0 },{ -20.0, 20.0 } };
GLfloat e_sidewinder2[5][2] = { { 20.0, 10.0 },{ 18.0, 3.0 },{ 16.0, 10.0 },{ 18.0, 20.0 },{ 20.0, 20.0 } };
GLfloat e_center[1][2] = { { 0.0, 0.0 } };
GLfloat elite_airplane_color[7][3] = {
		{ 59 / 255.0f, 189 / 255.0f, 151 / 255.0f },
		{ 76 / 255.0f, 155 / 255.0f, 172 / 255.0f },
		{ 58 / 255.0f,  231 / 255.0f, 202 / 255.0f },  // body
		{ 31 / 255.0f, 81 / 255.0f, 202 / 255.0f },
		{ 54 / 255.0f, 48 / 255.0f,   237 / 255.0f },  // sidewinder1
		{ 115 / 255.0f, 82 / 255.0f,   247 / 255.0f },  // sidewinder2
		{ 255 / 255.0f,   0 / 255.0f,   255 / 255.0f }   // center
};

GLuint VBO_elite_airplane, VAO_elite_airplane;

int elite_airplane_clock = 0;
float elite_airplane_s_factor = 1.0f;

void prepare_elite_airplane() {
	GLsizeiptr buffer_size = sizeof(e_big_wing) + sizeof(e_small_wing) + sizeof(e_body) + sizeof(e_back)
		+ sizeof(e_sidewinder1) + sizeof(e_sidewinder2) + sizeof(e_center);

	// Initialize vertex buffer object.
	glGenBuffers(1, &VBO_elite_airplane);

	glBindBuffer(GL_ARRAY_BUFFER, VBO_elite_airplane);
	glBufferData(GL_ARRAY_BUFFER, buffer_size, NULL, GL_STATIC_DRAW); // allocate buffer object memory

	glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(e_big_wing), e_big_wing);
	glBufferSubData(GL_ARRAY_BUFFER, sizeof(e_big_wing), sizeof(e_small_wing), e_small_wing);
	glBufferSubData(GL_ARRAY_BUFFER, sizeof(e_big_wing) + sizeof(e_small_wing), sizeof(e_body), e_body);
	glBufferSubData(GL_ARRAY_BUFFER, sizeof(e_big_wing) + sizeof(e_small_wing) + sizeof(e_body), sizeof(e_back), e_back);
	glBufferSubData(GL_ARRAY_BUFFER, sizeof(e_big_wing) + sizeof(e_small_wing) + sizeof(e_body) + sizeof(e_back),
		sizeof(e_sidewinder1), e_sidewinder1);
	glBufferSubData(GL_ARRAY_BUFFER, sizeof(e_big_wing) + sizeof(e_small_wing) + sizeof(e_body) + sizeof(e_back)
		+ sizeof(e_sidewinder1), sizeof(e_sidewinder2), e_sidewinder2);
	glBufferSubData(GL_ARRAY_BUFFER, sizeof(e_big_wing) + sizeof(e_small_wing) + sizeof(e_body) + sizeof(e_back)
		+ sizeof(e_sidewinder1) + sizeof(e_sidewinder2), sizeof(e_center), e_center);

	// Initialize vertex array object.
	glGenVertexArrays(1, &VAO_elite_airplane);
	glBindVertexArray(VAO_elite_airplane);

	glBindBuffer(GL_ARRAY_BUFFER, VBO_elite_airplane);
	glVertexAttribPointer(LOC_VERTEX, 2, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(0));

	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}

void draw_elite_airplane() { // Draw elite_airplane in its MC.
	glBindVertexArray(VAO_elite_airplane);

	glUniform3fv(loc_primitive_color, 1, elite_airplane_color[ELITE_AIRPLANE_BIG_WING]);
	glDrawArrays(GL_TRIANGLE_FAN, 0, 6);

	glUniform3fv(loc_primitive_color, 1, elite_airplane_color[ELITE_AIRPLANE_SMALL_WING]);
	glDrawArrays(GL_TRIANGLE_FAN, 6, 6);

	glUniform3fv(loc_primitive_color, 1, elite_airplane_color[ELITE_AIRPLANE_BODY]);
	glDrawArrays(GL_TRIANGLE_FAN, 12, 5);

	glUniform3fv(loc_primitive_color, 1, elite_airplane_color[ELITE_AIRPLANE_BACK]);
	glDrawArrays(GL_TRIANGLE_FAN, 17, 5);

	glUniform3fv(loc_primitive_color, 1, elite_airplane_color[ELITE_AIRPLANE_SIDEWINDER1]);
	glDrawArrays(GL_TRIANGLE_FAN, 22, 5);

	glUniform3fv(loc_primitive_color, 1, elite_airplane_color[ELITE_AIRPLANE_SIDEWINDER2]);
	glDrawArrays(GL_TRIANGLE_FAN, 27, 5);

	glUniform3fv(loc_primitive_color, 1, elite_airplane_color[ELITE_AIRPLANE_CENTER]);
	glPointSize(5.0);
	glDrawArrays(GL_POINTS, 32, 1);
	glPointSize(1.0);
	glBindVertexArray(0);
}

//shirt
#define SHIRT_LEFT_BODY 0
#define SHIRT_RIGHT_BODY 1
#define SHIRT_LEFT_COLLAR 2
#define SHIRT_RIGHT_COLLAR 3
#define SHIRT_FRONT_POCKET 4
#define SHIRT_BUTTON1 5
#define SHIRT_BUTTON2 6
#define SHIRT_BUTTON3 7
#define SHIRT_BUTTON4 8
GLfloat left_body[6][2] = { { 0.0, -9.0 },{ -8.0, -9.0 },{ -11.0, 8.0 },{ -6.0, 10.0 },{ -3.0, 7.0 },{ 0.0, 9.0 } };
GLfloat right_body[6][2] = { { 0.0, -9.0 },{ 0.0, 9.0 },{ 3.0, 7.0 },{ 6.0, 10.0 },{ 11.0, 8.0 },{ 8.0, -9.0 } };
GLfloat left_collar[4][2] = { { 0.0, 9.0 },{ -3.0, 7.0 },{ -6.0, 10.0 },{ -4.0, 11.0 } };
GLfloat right_collar[4][2] = { { 0.0, 9.0 },{ 4.0, 11.0 },{ 6.0, 10.0 },{ 3.0, 7.0 } };
GLfloat front_pocket[6][2] = { { 5.0, 0.0 },{ 4.0, 1.0 },{ 4.0, 3.0 },{ 7.0, 3.0 },{ 7.0, 1.0 },{ 6.0, 0.0 } };
GLfloat button1[3][2] = { { -1.0, 6.0 },{ 1.0, 6.0 },{ 0.0, 5.0 } };
GLfloat button2[3][2] = { { -1.0, 3.0 },{ 1.0, 3.0 },{ 0.0, 2.0 } };
GLfloat button3[3][2] = { { -1.0, 0.0 },{ 1.0, 0.0 },{ 0.0, -1.0 } };
GLfloat button4[3][2] = { { -1.0, -3.0 },{ 1.0, -3.0 },{ 0.0, -4.0 } };

GLfloat shirt_color[9][3] = {
	{ 255 / 255.0f, 255 / 255.0f, 255 / 255.0f },
	{ 255 / 255.0f, 255 / 255.0f, 255 / 255.0f },
	{ 206 / 255.0f, 173 / 255.0f, 184 / 255.0f },
	{ 206 / 255.0f, 173 / 255.0f, 184 / 255.0f },
	{ 206 / 255.0f, 173 / 255.0f, 184 / 255.0f },
	{ 206 / 255.0f, 173 / 255.0f, 184 / 255.0f },
	{ 206 / 255.0f, 173 / 255.0f, 184 / 255.0f },
	{ 206 / 255.0f, 173 / 255.0f, 184 / 255.0f },
	{ 206 / 255.0f, 173 / 255.0f, 184 / 255.0f }
};

GLuint VBO_shirt, VAO_shirt;
void prepare_shirt() {
	GLsizeiptr buffer_size = sizeof(left_body) + sizeof(right_body) + sizeof(left_collar) + sizeof(right_collar)
		+ sizeof(front_pocket) + sizeof(button1) + sizeof(button2) + sizeof(button3) + sizeof(button4);

	// Initialize vertex buffer object.
	glGenBuffers(1, &VBO_shirt);

	glBindBuffer(GL_ARRAY_BUFFER, VBO_shirt);
	glBufferData(GL_ARRAY_BUFFER, buffer_size, NULL, GL_STATIC_DRAW); // allocate buffer object memory

	glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(left_body), left_body);
	glBufferSubData(GL_ARRAY_BUFFER, sizeof(left_body), sizeof(right_body), right_body);
	glBufferSubData(GL_ARRAY_BUFFER, sizeof(left_body) + sizeof(right_body), sizeof(left_collar), left_collar);
	glBufferSubData(GL_ARRAY_BUFFER, sizeof(left_body) + sizeof(right_body) + sizeof(left_collar), sizeof(right_collar), right_collar);
	glBufferSubData(GL_ARRAY_BUFFER, sizeof(left_body) + sizeof(right_body) + sizeof(left_collar) + sizeof(right_collar),
		sizeof(front_pocket), front_pocket);
	glBufferSubData(GL_ARRAY_BUFFER, sizeof(left_body) + sizeof(right_body) + sizeof(left_collar) + sizeof(right_collar)
		+ sizeof(front_pocket), sizeof(button1), button1);
	glBufferSubData(GL_ARRAY_BUFFER, sizeof(left_body) + sizeof(right_body) + sizeof(left_collar) + sizeof(right_collar)
		+ sizeof(front_pocket) + sizeof(button1), sizeof(button2), button2);
	glBufferSubData(GL_ARRAY_BUFFER, sizeof(left_body) + sizeof(right_body) + sizeof(left_collar) + sizeof(right_collar)
		+ sizeof(front_pocket) + sizeof(button1) + sizeof(button2), sizeof(button3), button3);
	glBufferSubData(GL_ARRAY_BUFFER, sizeof(left_body) + sizeof(right_body) + sizeof(left_collar) + sizeof(right_collar)
		+ sizeof(front_pocket) + sizeof(button1) + sizeof(button2) + sizeof(button3), sizeof(button4), button4);

	// Initialize vertex array object.
	glGenVertexArrays(1, &VAO_shirt);
	glBindVertexArray(VAO_shirt);

	glBindBuffer(GL_ARRAY_BUFFER, VBO_shirt);
	glVertexAttribPointer(LOC_VERTEX, 2, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(0));

	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}

void draw_shirt() {
	glBindVertexArray(VAO_shirt);

	glUniform3fv(loc_primitive_color, 1, shirt_color[SHIRT_LEFT_BODY]);
	glDrawArrays(GL_TRIANGLE_FAN, 0, 6);

	glUniform3fv(loc_primitive_color, 1, shirt_color[SHIRT_RIGHT_BODY]);
	glDrawArrays(GL_TRIANGLE_FAN, 6, 6);

	glUniform3fv(loc_primitive_color, 1, shirt_color[SHIRT_LEFT_COLLAR]);
	glDrawArrays(GL_TRIANGLE_FAN, 12, 4);

	glUniform3fv(loc_primitive_color, 1, shirt_color[SHIRT_RIGHT_COLLAR]);
	glDrawArrays(GL_TRIANGLE_FAN, 16, 4);

	glUniform3fv(loc_primitive_color, 1, shirt_color[SHIRT_FRONT_POCKET]);
	glDrawArrays(GL_TRIANGLE_FAN, 20, 6);

	glUniform3fv(loc_primitive_color, 1, shirt_color[SHIRT_BUTTON1]);
	glDrawArrays(GL_TRIANGLE_FAN, 26, 3);

	glUniform3fv(loc_primitive_color, 1, shirt_color[SHIRT_BUTTON2]);
	glDrawArrays(GL_TRIANGLE_FAN, 29, 3);

	glUniform3fv(loc_primitive_color, 1, shirt_color[SHIRT_BUTTON3]);
	glDrawArrays(GL_TRIANGLE_FAN, 32, 3);

	glUniform3fv(loc_primitive_color, 1, shirt_color[SHIRT_BUTTON4]);
	glDrawArrays(GL_TRIANGLE_FAN, 35, 3);
	glBindVertexArray(0);
}

//house
#define HOUSE_ROOF 0
#define HOUSE_BODY 1
#define HOUSE_CHIMNEY 2
#define HOUSE_DOOR 3
#define HOUSE_WINDOW 4

GLfloat roof[3][2] = { { -12.0, 0.0 },{ 0.0, 12.0 },{ 12.0, 0.0 } };
GLfloat house_body[4][2] = { { -12.0, -14.0 },{ -12.0, 0.0 },{ 12.0, 0.0 },{ 12.0, -14.0 } };
GLfloat chimney[4][2] = { { 6.0, 6.0 },{ 6.0, 14.0 },{ 10.0, 14.0 },{ 10.0, 2.0 } };
GLfloat door[4][2] = { { -8.0, -14.0 },{ -8.0, -8.0 },{ -4.0, -8.0 },{ -4.0, -14.0 } };
GLfloat window[4][2] = { { 4.0, -6.0 },{ 4.0, -2.0 },{ 8.0, -2.0 },{ 8.0, -6.0 } };

GLfloat house_color[5][3] = {
	{ 200 / 255.0f, 39 / 255.0f, 42 / 255.0f },
	{ 235 / 255.0f, 225 / 255.0f, 196 / 255.0f },
	{ 255 / 255.0f, 0 / 255.0f, 0 / 255.0f },
	{ 233 / 255.0f, 113 / 255.0f, 23 / 255.0f },
	{ 44 / 255.0f, 180 / 255.0f, 49 / 255.0f }
};

GLuint VBO_house, VAO_house;
void prepare_house() {
	GLsizeiptr buffer_size = sizeof(roof) + sizeof(house_body) + sizeof(chimney) + sizeof(door)
		+ sizeof(window);

	// Initialize vertex buffer object.
	glGenBuffers(1, &VBO_house);

	glBindBuffer(GL_ARRAY_BUFFER, VBO_house);
	glBufferData(GL_ARRAY_BUFFER, buffer_size, NULL, GL_STATIC_DRAW); // allocate buffer object memory

	glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(roof), roof);
	glBufferSubData(GL_ARRAY_BUFFER, sizeof(roof), sizeof(house_body), house_body);
	glBufferSubData(GL_ARRAY_BUFFER, sizeof(roof) + sizeof(house_body), sizeof(chimney), chimney);
	glBufferSubData(GL_ARRAY_BUFFER, sizeof(roof) + sizeof(house_body) + sizeof(chimney), sizeof(door), door);
	glBufferSubData(GL_ARRAY_BUFFER, sizeof(roof) + sizeof(house_body) + sizeof(chimney) + sizeof(door),
		sizeof(window), window);

	// Initialize vertex array object.
	glGenVertexArrays(1, &VAO_house);
	glBindVertexArray(VAO_house);

	glBindBuffer(GL_ARRAY_BUFFER, VBO_house);
	glVertexAttribPointer(LOC_VERTEX, 2, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(0));

	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}

void draw_house() {
	glBindVertexArray(VAO_house);

	glUniform3fv(loc_primitive_color, 1, house_color[HOUSE_ROOF]);
	glDrawArrays(GL_TRIANGLE_FAN, 0, 3);

	glUniform3fv(loc_primitive_color, 1, house_color[HOUSE_BODY]);
	glDrawArrays(GL_TRIANGLE_FAN, 3, 4);

	glUniform3fv(loc_primitive_color, 1, house_color[HOUSE_CHIMNEY]);
	glDrawArrays(GL_TRIANGLE_FAN, 7, 4);

	glUniform3fv(loc_primitive_color, 1, house_color[HOUSE_DOOR]);
	glDrawArrays(GL_TRIANGLE_FAN, 11, 4);

	glUniform3fv(loc_primitive_color, 1, house_color[HOUSE_WINDOW]);
	glDrawArrays(GL_TRIANGLE_FAN, 15, 4);

	glBindVertexArray(0);
}

//car
#define CAR_BODY 0
#define CAR_FRAME 1
#define CAR_WINDOW 2
#define CAR_LEFT_LIGHT 3
#define CAR_RIGHT_LIGHT 4
#define CAR_LEFT_WHEEL 5
#define CAR_RIGHT_WHEEL 6

GLfloat car_body[4][2] = { { -16.0, -8.0 },{ -16.0, 0.0 },{ 16.0, 0.0 },{ 16.0, -8.0 } };
GLfloat car_frame[4][2] = { { -10.0, 0.0 },{ -10.0, 10.0 },{ 10.0, 10.0 },{ 10.0, 0.0 } };
GLfloat car_window[4][2] = { { -8.0, 0.0 },{ -8.0, 8.0 },{ 8.0, 8.0 },{ 8.0, 0.0 } };
GLfloat car_left_light[4][2] = { { -9.0, -6.0 },{ -10.0, -5.0 },{ -9.0, -4.0 },{ -8.0, -5.0 } };
GLfloat car_right_light[4][2] = { { 9.0, -6.0 },{ 8.0, -5.0 },{ 9.0, -4.0 },{ 10.0, -5.0 } };
GLfloat car_left_wheel[4][2] = { { -10.0, -12.0 },{ -10.0, -8.0 },{ -6.0, -8.0 },{ -6.0, -12.0 } };
GLfloat car_right_wheel[4][2] = { { 6.0, -12.0 },{ 6.0, -8.0 },{ 10.0, -8.0 },{ 10.0, -12.0 } };

GLfloat car_color[7][3] = {
	{ 0 / 255.0f, 149 / 255.0f, 159 / 255.0f },
	{ 0 / 255.0f, 149 / 255.0f, 159 / 255.0f },
	{ 216 / 255.0f, 208 / 255.0f, 174 / 255.0f },
	{ 249 / 255.0f, 244 / 255.0f, 0 / 255.0f },
	{ 249 / 255.0f, 244 / 255.0f, 0 / 255.0f },
	{ 21 / 255.0f, 30 / 255.0f, 26 / 255.0f },
	{ 21 / 255.0f, 30 / 255.0f, 26 / 255.0f }
};

GLuint VBO_car, VAO_car;
void prepare_car() {
	GLsizeiptr buffer_size = sizeof(car_body) + sizeof(car_frame) + sizeof(car_window) + sizeof(car_left_light)
		+ sizeof(car_right_light) + sizeof(car_left_wheel) + sizeof(car_right_wheel);

	// Initialize vertex buffer object.
	glGenBuffers(1, &VBO_car);

	glBindBuffer(GL_ARRAY_BUFFER, VBO_car);
	glBufferData(GL_ARRAY_BUFFER, buffer_size, NULL, GL_STATIC_DRAW); // allocate buffer object memory

	glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(car_body), car_body);
	glBufferSubData(GL_ARRAY_BUFFER, sizeof(car_body), sizeof(car_frame), car_frame);
	glBufferSubData(GL_ARRAY_BUFFER, sizeof(car_body) + sizeof(car_frame), sizeof(car_window), car_window);
	glBufferSubData(GL_ARRAY_BUFFER, sizeof(car_body) + sizeof(car_frame) + sizeof(car_window), sizeof(car_left_light), car_left_light);
	glBufferSubData(GL_ARRAY_BUFFER, sizeof(car_body) + sizeof(car_frame) + sizeof(car_window) + sizeof(car_left_light),
		sizeof(car_right_light), car_right_light);
	glBufferSubData(GL_ARRAY_BUFFER, sizeof(car_body) + sizeof(car_frame) + sizeof(car_window) + sizeof(car_left_light)
		+ sizeof(car_right_light), sizeof(car_left_wheel), car_left_wheel);
	glBufferSubData(GL_ARRAY_BUFFER, sizeof(car_body) + sizeof(car_frame) + sizeof(car_window) + sizeof(car_left_light)
		+ sizeof(car_right_light) + sizeof(car_left_wheel), sizeof(car_right_wheel), car_right_wheel);

	// Initialize vertex array object.
	glGenVertexArrays(1, &VAO_car);
	glBindVertexArray(VAO_car);

	glBindBuffer(GL_ARRAY_BUFFER, VBO_car);
	glVertexAttribPointer(LOC_VERTEX, 2, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(0));

	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}

void draw_car() {
	glBindVertexArray(VAO_car);

	glUniform3fv(loc_primitive_color, 1, car_color[CAR_BODY]);
	glDrawArrays(GL_TRIANGLE_FAN, 0, 4);

	glUniform3fv(loc_primitive_color, 1, car_color[CAR_FRAME]);
	glDrawArrays(GL_TRIANGLE_FAN, 4, 4);

	glUniform3fv(loc_primitive_color, 1, car_color[CAR_WINDOW]);
	glDrawArrays(GL_TRIANGLE_FAN, 8, 4);

	glUniform3fv(loc_primitive_color, 1, car_color[CAR_LEFT_LIGHT]);
	glDrawArrays(GL_TRIANGLE_FAN, 12, 4);

	glUniform3fv(loc_primitive_color, 1, car_color[CAR_RIGHT_LIGHT]);
	glDrawArrays(GL_TRIANGLE_FAN, 16, 4);

	glUniform3fv(loc_primitive_color, 1, car_color[CAR_LEFT_WHEEL]);
	glDrawArrays(GL_TRIANGLE_FAN, 20, 4);

	glUniform3fv(loc_primitive_color, 1, car_color[CAR_RIGHT_WHEEL]);
	glDrawArrays(GL_TRIANGLE_FAN, 24, 4);

	glBindVertexArray(0);
}

//draw cocktail
#define COCKTAIL_NECK 0
#define COCKTAIL_LIQUID 1
#define COCKTAIL_REMAIN 2
#define COCKTAIL_STRAW 3
#define COCKTAIL_DECO 4

GLfloat neck[6][2] = { { -6.0, -12.0 },{ -6.0, -11.0 },{ -1.0, 0.0 },{ 1.0, 0.0 },{ 6.0, -11.0 },{ 6.0, -12.0 } };
GLfloat liquid[6][2] = { { -1.0, 0.0 },{ -9.0, 4.0 },{ -12.0, 7.0 },{ 12.0, 7.0 },{ 9.0, 4.0 },{ 1.0, 0.0 } };
GLfloat remain[4][2] = { { -12.0, 7.0 },{ -12.0, 10.0 },{ 12.0, 10.0 },{ 12.0, 7.0 } };
GLfloat straw[4][2] = { { 7.0, 7.0 },{ 12.0, 12.0 },{ 14.0, 12.0 },{ 9.0, 7.0 } };
GLfloat deco[8][2] = { { 12.0, 12.0 },{ 10.0, 14.0 },{ 10.0, 16.0 },{ 12.0, 18.0 },{ 14.0, 18.0 },{ 16.0, 16.0 },{ 16.0, 14.0 },{ 14.0, 12.0 } };

GLfloat cocktail_color[5][3] = {
	{ 235 / 255.0f, 225 / 255.0f, 196 / 255.0f },
	{ 0 / 255.0f, 63 / 255.0f, 122 / 255.0f },
	{ 235 / 255.0f, 225 / 255.0f, 196 / 255.0f },
	{ 191 / 255.0f, 255 / 255.0f, 0 / 255.0f },
	{ 218 / 255.0f, 165 / 255.0f, 32 / 255.0f }
};

GLuint VBO_cocktail, VAO_cocktail;
void prepare_cocktail() {
	GLsizeiptr buffer_size = sizeof(neck) + sizeof(liquid) + sizeof(remain) + sizeof(straw)
		+ sizeof(deco);

	// Initialize vertex buffer object.
	glGenBuffers(1, &VBO_cocktail);

	glBindBuffer(GL_ARRAY_BUFFER, VBO_cocktail);
	glBufferData(GL_ARRAY_BUFFER, buffer_size, NULL, GL_STATIC_DRAW); // allocate buffer object memory

	glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(neck), neck);
	glBufferSubData(GL_ARRAY_BUFFER, sizeof(neck), sizeof(liquid), liquid);
	glBufferSubData(GL_ARRAY_BUFFER, sizeof(neck) + sizeof(liquid), sizeof(remain), remain);
	glBufferSubData(GL_ARRAY_BUFFER, sizeof(neck) + sizeof(liquid) + sizeof(remain), sizeof(straw), straw);
	glBufferSubData(GL_ARRAY_BUFFER, sizeof(neck) + sizeof(liquid) + sizeof(remain) + sizeof(straw),
		sizeof(deco), deco);

	// Initialize vertex array object.
	glGenVertexArrays(1, &VAO_cocktail);
	glBindVertexArray(VAO_cocktail);

	glBindBuffer(GL_ARRAY_BUFFER, VBO_cocktail);
	glVertexAttribPointer(LOC_VERTEX, 2, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(0));

	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}

void draw_cocktail() {
	glBindVertexArray(VAO_cocktail);

	glUniform3fv(loc_primitive_color, 1, cocktail_color[COCKTAIL_NECK]);
	glDrawArrays(GL_TRIANGLE_FAN, 0, 6);

	glUniform3fv(loc_primitive_color, 1, cocktail_color[COCKTAIL_LIQUID]);
	glDrawArrays(GL_TRIANGLE_FAN, 6, 6);

	glUniform3fv(loc_primitive_color, 1, cocktail_color[COCKTAIL_REMAIN]);
	glDrawArrays(GL_TRIANGLE_FAN, 12, 4);

	glUniform3fv(loc_primitive_color, 1, cocktail_color[COCKTAIL_STRAW]);
	glDrawArrays(GL_TRIANGLE_FAN, 16, 4);

	glUniform3fv(loc_primitive_color, 1, cocktail_color[COCKTAIL_DECO]);
	glDrawArrays(GL_TRIANGLE_FAN, 20, 8);

	glBindVertexArray(0);
}

//draw car2
#define CAR2_BODY 0
#define CAR2_FRONT_WINDOW 1
#define CAR2_BACK_WINDOW 2
#define CAR2_FRONT_WHEEL 3
#define CAR2_BACK_WHEEL 4
#define CAR2_LIGHT1 5
#define CAR2_LIGHT2 6

GLfloat car2_body[8][2] = { { -18.0, -7.0 },{ -18.0, 0.0 },{ -13.0, 0.0 },{ -10.0, 8.0 },{ 10.0, 8.0 },{ 13.0, 0.0 },{ 18.0, 0.0 },{ 18.0, -7.0 } };
GLfloat car2_front_window[4][2] = { { -10.0, 0.0 },{ -8.0, 6.0 },{ -2.0, 6.0 },{ -2.0, 0.0 } };
GLfloat car2_back_window[4][2] = { { 0.0, 0.0 },{ 0.0, 6.0 },{ 8.0, 6.0 },{ 10.0, 0.0 } };
GLfloat car2_front_wheel[8][2] = { { -11.0, -11.0 },{ -13.0, -8.0 },{ -13.0, -7.0 },{ -11.0, -4.0 },{ -7.0, -4.0 },{ -5.0, -7.0 },{ -5.0, -8.0 },{ -7.0, -11.0 } };
GLfloat car2_back_wheel[8][2] = { { 7.0, -11.0 },{ 5.0, -8.0 },{ 5.0, -7.0 },{ 7.0, -4.0 },{ 11.0, -4.0 },{ 13.0, -7.0 },{ 13.0, -8.0 },{ 11.0, -11.0 } };
GLfloat car2_light1[3][2] = { { -18.0, -1.0 },{ -17.0, -2.0 },{ -18.0, -3.0 } };
GLfloat car2_light2[3][2] = { { -18.0, -4.0 },{ -17.0, -5.0 },{ -18.0, -6.0 } };

GLfloat car2_color[7][3] = {
	{ 100 / 255.0f, 141 / 255.0f, 159 / 255.0f },
	{ 235 / 255.0f, 219 / 255.0f, 208 / 255.0f },
	{ 235 / 255.0f, 219 / 255.0f, 208 / 255.0f },
	{ 0 / 255.0f, 0 / 255.0f, 0 / 255.0f },
	{ 0 / 255.0f, 0 / 255.0f, 0 / 255.0f },
	{ 249 / 255.0f, 244 / 255.0f, 0 / 255.0f },
	{ 249 / 255.0f, 244 / 255.0f, 0 / 255.0f }
};

GLuint VBO_car2, VAO_car2;
void prepare_car2() {
	GLsizeiptr buffer_size = sizeof(car2_body) + sizeof(car2_front_window) + sizeof(car2_back_window) + sizeof(car2_front_wheel)
		+ sizeof(car2_back_wheel) + sizeof(car2_light1) + sizeof(car2_light2);

	// Initialize vertex buffer object.
	glGenBuffers(1, &VBO_car2);

	glBindBuffer(GL_ARRAY_BUFFER, VBO_car2);
	glBufferData(GL_ARRAY_BUFFER, buffer_size, NULL, GL_STATIC_DRAW); // allocate buffer object memory

	glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(car2_body), car2_body);
	glBufferSubData(GL_ARRAY_BUFFER, sizeof(car2_body), sizeof(car2_front_window), car2_front_window);
	glBufferSubData(GL_ARRAY_BUFFER, sizeof(car2_body) + sizeof(car2_front_window), sizeof(car2_back_window), car2_back_window);
	glBufferSubData(GL_ARRAY_BUFFER, sizeof(car2_body) + sizeof(car2_front_window) + sizeof(car2_back_window), sizeof(car2_front_wheel), car2_front_wheel);
	glBufferSubData(GL_ARRAY_BUFFER, sizeof(car2_body) + sizeof(car2_front_window) + sizeof(car2_back_window) + sizeof(car2_front_wheel),
		sizeof(car2_back_wheel), car2_back_wheel);
	glBufferSubData(GL_ARRAY_BUFFER, sizeof(car2_body) + sizeof(car2_front_window) + sizeof(car2_back_window) + sizeof(car2_front_wheel)
		+ sizeof(car2_back_wheel), sizeof(car2_light1), car2_light1);
	glBufferSubData(GL_ARRAY_BUFFER, sizeof(car2_body) + sizeof(car2_front_window) + sizeof(car2_back_window) + sizeof(car2_front_wheel)
		+ sizeof(car2_back_wheel) + sizeof(car2_light1), sizeof(car2_light2), car2_light2);

	// Initialize vertex array object.
	glGenVertexArrays(1, &VAO_car2);
	glBindVertexArray(VAO_car2);

	glBindBuffer(GL_ARRAY_BUFFER, VBO_car2);
	glVertexAttribPointer(LOC_VERTEX, 2, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(0));

	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}

void draw_car2() {
	glBindVertexArray(VAO_car2);

	glUniform3fv(loc_primitive_color, 1, car2_color[CAR2_BODY]);
	glDrawArrays(GL_TRIANGLE_FAN, 0, 8);

	glUniform3fv(loc_primitive_color, 1, car2_color[CAR2_FRONT_WINDOW]);
	glDrawArrays(GL_TRIANGLE_FAN, 8, 4);

	glUniform3fv(loc_primitive_color, 1, car2_color[CAR2_BACK_WINDOW]);
	glDrawArrays(GL_TRIANGLE_FAN, 12, 4);

	glUniform3fv(loc_primitive_color, 1, car2_color[CAR2_FRONT_WHEEL]);
	glDrawArrays(GL_TRIANGLE_FAN, 16, 8);

	glUniform3fv(loc_primitive_color, 1, car2_color[CAR2_BACK_WHEEL]);
	glDrawArrays(GL_TRIANGLE_FAN, 24, 8);

	glUniform3fv(loc_primitive_color, 1, car2_color[CAR2_LIGHT1]);
	glDrawArrays(GL_TRIANGLE_FAN, 32, 3);

	glUniform3fv(loc_primitive_color, 1, car2_color[CAR2_LIGHT2]);
	glDrawArrays(GL_TRIANGLE_FAN, 35, 3);

	glBindVertexArray(0);
}

// hat
#define HAT_LEAF 0
#define HAT_BODY 1
#define HAT_STRIP 2
#define HAT_BOTTOM 3

GLfloat hat_leaf[4][2] = { { 3.0, 20.0 },{ 3.0, 28.0 },{ 9.0, 32.0 },{ 9.0, 24.0 } };
GLfloat hat_body[4][2] = { { -19.5, 2.0 },{ 19.5, 2.0 },{ 15.0, 20.0 },{ -15.0, 20.0 } };
GLfloat hat_strip[4][2] = { { -20.0, 0.0 },{ 20.0, 0.0 },{ 19.5, 2.0 },{ -19.5, 2.0 } };
GLfloat hat_bottom[4][2] = { { 25.0, 0.0 },{ -25.0, 0.0 },{ -25.0, -4.0 },{ 25.0, -4.0 } };

GLfloat hat_color[4][3] = {
	{ 167 / 255.0f, 255 / 255.0f, 55 / 255.0f },
{ 255 / 255.0f, 144 / 255.0f, 32 / 255.0f },
{ 255 / 255.0f, 40 / 255.0f, 33 / 255.0f },
{ 255 / 255.0f, 144 / 255.0f, 32 / 255.0f }
};

GLuint VBO_hat, VAO_hat;

void prepare_hat() {
	GLsizeiptr buffer_size = sizeof(hat_leaf) + sizeof(hat_body) + sizeof(hat_strip) + sizeof(hat_bottom);

	// Initialize vertex buffer object.
	glGenBuffers(1, &VBO_hat);

	glBindBuffer(GL_ARRAY_BUFFER, VBO_hat);
	glBufferData(GL_ARRAY_BUFFER, buffer_size, NULL, GL_STATIC_DRAW); // allocate buffer object memory

	glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(hat_leaf), hat_leaf);
	glBufferSubData(GL_ARRAY_BUFFER, sizeof(hat_leaf), sizeof(hat_body), hat_body);
	glBufferSubData(GL_ARRAY_BUFFER, sizeof(hat_leaf) + sizeof(hat_body), sizeof(hat_strip), hat_strip);
	glBufferSubData(GL_ARRAY_BUFFER, sizeof(hat_leaf) + sizeof(hat_body) + sizeof(hat_strip), sizeof(hat_bottom), hat_bottom);

	// Initialize vertex array object.
	glGenVertexArrays(1, &VAO_hat);
	glBindVertexArray(VAO_hat);

	glBindBuffer(GL_ARRAY_BUFFER, VBO_hat);
	glVertexAttribPointer(LOC_VERTEX, 2, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(0));

	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}

void draw_hat() {
	glBindVertexArray(VAO_hat);

	glUniform3fv(loc_primitive_color, 1, hat_color[HAT_LEAF]);
	glDrawArrays(GL_TRIANGLE_FAN, 0, 4);

	glUniform3fv(loc_primitive_color, 1, hat_color[HAT_BODY]);
	glDrawArrays(GL_TRIANGLE_FAN, 4, 4);

	glUniform3fv(loc_primitive_color, 1, hat_color[HAT_STRIP]);
	glDrawArrays(GL_TRIANGLE_FAN, 8, 4);

	glUniform3fv(loc_primitive_color, 1, hat_color[HAT_BOTTOM]);
	glDrawArrays(GL_TRIANGLE_FAN, 12, 4);

	glBindVertexArray(0);
}

// cake
#define CAKE_FIRE 0
#define CAKE_CANDLE 1
#define CAKE_BODY 2
#define CAKE_BOTTOM 3
#define CAKE_DECORATE 4

GLfloat cake_fire[4][2] = { { -0.5, 14.0 },{ -0.5, 13.0 },{ 0.5, 13.0 },{ 0.5, 14.0 } };
GLfloat cake_candle[4][2] = { { -1.0, 8.0 } ,{ -1.0, 13.0 },{ 1.0, 13.0 },{ 1.0, 8.0 } };
GLfloat cake_body[4][2] = { { 8.0, 5.0 },{ -8.0, 5.0 } ,{ -8.0, 8.0 },{ 8.0, 8.0 } };
GLfloat cake_bottom[4][2] = { { -10.0, 1.0 },{ -10.0, 5.0 },{ 10.0, 5.0 },{ 10.0, 1.0 } };
GLfloat cake_decorate[4][2] = { { -10.0, 0.0 },{ -10.0, 1.0 },{ 10.0, 1.0 },{ 10.0, 0.0 } };

GLfloat cake_color[5][3] = {
	{ 255 / 255.0f, 0 / 255.0f, 0 / 255.0f },
{ 255 / 255.0f, 204 / 255.0f, 0 / 255.0f },
{ 255 / 255.0f, 102 / 255.0f, 255 / 255.0f },
{ 255 / 255.0f, 102 / 255.0f, 255 / 255.0f },
{ 102 / 255.0f, 51 / 255.0f, 0 / 255.0f }
};

GLuint VBO_cake, VAO_cake;

void prepare_cake() {
	int size = sizeof(cake_fire);
	GLsizeiptr buffer_size = sizeof(cake_fire) * 5;

	// Initialize vertex buffer object.
	glGenBuffers(1, &VBO_cake);

	glBindBuffer(GL_ARRAY_BUFFER, VBO_cake);
	glBufferData(GL_ARRAY_BUFFER, buffer_size, NULL, GL_STATIC_DRAW); // allocate buffer object memory

	glBufferSubData(GL_ARRAY_BUFFER, 0, size, cake_fire);
	glBufferSubData(GL_ARRAY_BUFFER, size, size, cake_candle);
	glBufferSubData(GL_ARRAY_BUFFER, size * 2, size, cake_body);
	glBufferSubData(GL_ARRAY_BUFFER, size * 3, size, cake_bottom);
	glBufferSubData(GL_ARRAY_BUFFER, size * 4, size, cake_decorate);

	// Initialize vertex array object.
	glGenVertexArrays(1, &VAO_cake);
	glBindVertexArray(VAO_cake);

	glBindBuffer(GL_ARRAY_BUFFER, VBO_cake);
	glVertexAttribPointer(LOC_VERTEX, 2, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(0));

	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}

void draw_cake() {
	glBindVertexArray(VAO_cake);

	glUniform3fv(loc_primitive_color, 1, cake_color[CAKE_FIRE]);
	glDrawArrays(GL_TRIANGLE_FAN, 0, 4);

	glUniform3fv(loc_primitive_color, 1, cake_color[CAKE_CANDLE]);
	glDrawArrays(GL_TRIANGLE_FAN, 4, 4);

	glUniform3fv(loc_primitive_color, 1, cake_color[CAKE_BODY]);
	glDrawArrays(GL_TRIANGLE_FAN, 8, 4);

	glUniform3fv(loc_primitive_color, 1, cake_color[CAKE_BOTTOM]);
	glDrawArrays(GL_TRIANGLE_FAN, 12, 4);

	glUniform3fv(loc_primitive_color, 1, cake_color[CAKE_DECORATE]);
	glDrawArrays(GL_TRIANGLE_FAN, 16, 4);

	glBindVertexArray(0);
}

// sword

#define SWORD_BODY 0
#define SWORD_BODY2 1
#define SWORD_HEAD 2
#define SWORD_HEAD2 3
#define SWORD_IN 4
#define SWORD_DOWN 5
#define SWORD_BODY_IN 6

GLfloat sword_body[4][2] = { { -6.0, 0.0 },{ -6.0, -4.0 },{ 6.0, -4.0 },{ 6.0, 0.0 } };
GLfloat sword_body2[4][2] = { { -2.0, -4.0 },{ -2.0, -6.0 } ,{ 2.0, -6.0 },{ 2.0, -4.0 } };
GLfloat sword_head[4][2] = { { -2.0, 0.0 },{ -2.0, 16.0 } ,{ 2.0, 16.0 },{ 2.0, 0.0 } };
GLfloat sword_head2[3][2] = { { -2.0, 16.0 },{ 0.0, 19.46 } ,{ 2.0, 16.0 } };
GLfloat sword_in[4][2] = { { -0.3, 0.7 },{ -0.3, 15.3 } ,{ 0.3, 15.3 },{ 0.3, 0.7 } };
GLfloat sword_down[4][2] = { { -2.0, -6.0 } ,{ 2.0, -6.0 },{ 4.0, -8.0 },{ -4.0, -8.0 } };
GLfloat sword_body_in[4][2] = { { 0.0, -1.0 } ,{ 1.0, -2.732 },{ 0.0, -4.464 },{ -1.0, -2.732 } };

GLfloat sword_color[7][3] = {
	{ 139 / 255.0f, 69 / 255.0f, 19 / 255.0f },
{ 139 / 255.0f, 69 / 255.0f, 19 / 255.0f },
{ 155 / 255.0f, 155 / 255.0f, 155 / 255.0f },
{ 155 / 255.0f, 155 / 255.0f, 155 / 255.0f },
{ 0 / 255.0f, 0 / 255.0f, 0 / 255.0f },
{ 139 / 255.0f, 69 / 255.0f, 19 / 255.0f },
{ 255 / 255.0f, 0 / 255.0f, 0 / 255.0f }
};

GLuint VBO_sword, VAO_sword;

void prepare_sword() {
	GLsizeiptr buffer_size = sizeof(sword_body) + sizeof(sword_body2) + sizeof(sword_head) + sizeof(sword_head2) + sizeof(sword_in) + sizeof(sword_down) + sizeof(sword_body_in);

	// Initialize vertex buffer object.
	glGenBuffers(1, &VBO_sword);

	glBindBuffer(GL_ARRAY_BUFFER, VBO_sword);
	glBufferData(GL_ARRAY_BUFFER, buffer_size, NULL, GL_STATIC_DRAW); // allocate buffer object memory

	glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(sword_body), sword_body);
	glBufferSubData(GL_ARRAY_BUFFER, sizeof(sword_body), sizeof(sword_body2), sword_body2);
	glBufferSubData(GL_ARRAY_BUFFER, sizeof(sword_body) + sizeof(sword_body2), sizeof(sword_head), sword_head);
	glBufferSubData(GL_ARRAY_BUFFER, sizeof(sword_body) + sizeof(sword_body2) + sizeof(sword_head), sizeof(sword_head2), sword_head2);
	glBufferSubData(GL_ARRAY_BUFFER, sizeof(sword_body) + sizeof(sword_body2) + sizeof(sword_head) + sizeof(sword_head2), sizeof(sword_in), sword_in);
	glBufferSubData(GL_ARRAY_BUFFER, sizeof(sword_body) + sizeof(sword_body2) + sizeof(sword_head) + sizeof(sword_head2) + sizeof(sword_in), sizeof(sword_down), sword_down);
	glBufferSubData(GL_ARRAY_BUFFER, sizeof(sword_body) + sizeof(sword_body2) + sizeof(sword_head) + sizeof(sword_head2) + sizeof(sword_in) + sizeof(sword_down), sizeof(sword_body_in), sword_body_in);

	// Initialize vertex array object.
	glGenVertexArrays(1, &VAO_sword);
	glBindVertexArray(VAO_sword);

	glBindBuffer(GL_ARRAY_BUFFER, VBO_sword);
	glVertexAttribPointer(LOC_VERTEX, 2, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(0));

	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}

void draw_sword() {
	glBindVertexArray(VAO_sword);

	glUniform3fv(loc_primitive_color, 1, sword_color[SWORD_BODY]);
	glDrawArrays(GL_TRIANGLE_FAN, 0, 4);

	glUniform3fv(loc_primitive_color, 1, sword_color[SWORD_BODY2]);
	glDrawArrays(GL_TRIANGLE_FAN, 4, 4);

	glUniform3fv(loc_primitive_color, 1, sword_color[SWORD_HEAD]);
	glDrawArrays(GL_TRIANGLE_FAN, 8, 4);

	glUniform3fv(loc_primitive_color, 1, sword_color[SWORD_HEAD2]);
	glDrawArrays(GL_TRIANGLE_FAN, 12, 3);

	glUniform3fv(loc_primitive_color, 1, sword_color[SWORD_IN]);
	glDrawArrays(GL_TRIANGLE_FAN, 15, 4);

	glUniform3fv(loc_primitive_color, 1, sword_color[SWORD_DOWN]);
	glDrawArrays(GL_TRIANGLE_FAN, 19, 4);

	glUniform3fv(loc_primitive_color, 1, sword_color[SWORD_BODY_IN]);
	glDrawArrays(GL_TRIANGLE_FAN, 23, 4);

	glBindVertexArray(0);
}

//	my object SCOURGE-NORMAL
#define SCOURGE_BODY			0
#define SCOURGE_LEFTWING		1
#define SCOURGE_RIGHTWING		2
#define SCOURGE_TOOTH1			3
#define SCOURGE_TOOTH2			4
#define SCOURGE_TOOTH3			5
#define SCOURGE_TOOTH4			6
#define SCOURGE_LEFTTAIL		7
#define SCOURGE_RIGHTTAIL		8
#define SCOURGE_SCAR1			9
#define SCOURGE_SCAR2			10
#define SCOURGE_SCAR3			11

float sr = 1.0f;

GLfloat scourge_body[14][2] = { { 0.0 * sr, 4.0 * sr },{ -1.5 * sr, 3.6 * sr },{ -2.3 * sr, 2.0 * sr },{ -2.7 * sr, 0.1 * sr },{ -2.5 * sr, -2.0 * sr },{ -1.9 * sr, -3.7 * sr },{-1.1 * sr, -4.7 * sr},
								{0.0 * sr, -5.1 * sr}, {1.1 * sr, -4.7 * sr},{1.9 * sr,-3.7 * sr},{2.5 * sr,-2.0 * sr},{2.7 * sr,0.1 * sr},{2.3 * sr,2.0 * sr},{1.5 * sr,3.6 * sr } };

GLfloat scourge_leftwing[11][2] = { { -2.3 * sr, 2.0 * sr },{ -2.7 * sr, 0.1 * sr },{ -2.5 * sr, -2.0 * sr },{ -1.9 * sr, -3.7 * sr },{-3.3 * sr,-4.4 * sr},
									{-5.1 * sr,-3.1 * sr},{-6.4 * sr,-0.7 * sr},{-6.7 * sr,3 * sr},{-6.3 * sr,7 * sr},{-5.6 * sr,4.9 * sr},{-4.8 * sr,2.7 * sr} };
GLfloat scourge_rightwing[11][2] = { { 2.3 * sr, 2.0 * sr },{ 2.7 * sr, 0.1 * sr },{ 2.5 * sr, -2.0 * sr },{ 1.9 * sr, -3.7 * sr },{3.3 * sr,-4.4 * sr},
									{5.1 * sr,-3.1 * sr},{6.4 * sr,-0.7 * sr},{6.7 * sr,3 * sr},{6.3 * sr,7 * sr},{5.6 * sr,4.9 * sr},{4.8 * sr,2.7 * sr} };
GLfloat scourge_tooth1[3][2] = { {-0.8 * sr,3.8 * sr},{-1.5 * sr,3.6 * sr},{-1.6 * sr,5.4 * sr} };
GLfloat scourge_tooth2[3][2] = { {-0.8 * sr,3.8 * sr},{0.0 * sr,4.0 * sr},{-0.5 * sr,6 * sr} };
GLfloat scourge_tooth3[3][2] = { {0.8 * sr,3.8 * sr},{1.5 * sr,3.6 * sr},{1.6 * sr,5.4 * sr} };
GLfloat scourge_tooth4[3][2] = { {0.8 * sr,3.8 * sr},{0.0 * sr,4.0 * sr},{0.5 * sr,6 * sr} };
GLfloat scourge_lefttail[7][2] = { {-1.9 * sr,-3.7 * sr},{-1.1 * sr,-4.7 * sr},{0 * sr,-5.1 * sr},{-0.8 * sr,-7.2 * sr},{-1.2 * sr,-9.3 * sr},{-1.6 * sr,-8 * sr},{-2 * sr,-6 * sr} };
GLfloat scourge_righttail[7][2] = { {1.9 * sr,-3.7 * sr},{1.1 * sr,-4.7 * sr},{0 * sr,-5.1 * sr},{0.8 * sr,-7.2 * sr},{1.2 * sr,-9.3 * sr},{1.6 * sr,-8 * sr},{2 * sr,-6 * sr} };
GLfloat scourge_scar1[4][2] = { { -1.7 * sr, 0.1 * sr }, {0.0 * sr, 0.5 * sr}, {1.7 * sr, 0.4 * sr }, {0.3 * sr, 0.0 * sr} };
GLfloat scourge_scar2[4][2] = { { -2.0 * sr, -0.7 * sr }, {0.0 * sr, -0.3 * sr}, {2.2 * sr, -0.4 * sr }, {0.3 * sr, -0.8 * sr} };
GLfloat scourge_scar3[4][2] = { { -1.2 * sr, -1.5 * sr }, {0.0 * sr, -1.1 * sr}, {1.7 * sr, -1.0 * sr }, {0.3 * sr, -1.6 * sr} };

GLfloat scourge_color[12][3] = {
	{ 163 / 255.0f, 122 / 255.0f, 88 / 255.0f },  // scourge_body
	{ 197 / 255.0f, 53 / 255.0f,  139 / 255.0f },  // scourge_leftwing
	{ 211 / 255.0f, 29 / 255.0f,  173 / 255.0f },  // scourge_rightwing
	{ 198 / 255.0f, 187 / 255.0f, 175 / 255.0f },  // scourge_tooth1
	{ 198 / 255.0f, 187 / 255.0f, 175 / 255.0f },  // scourge_tooth2
	{ 198 / 255.0f, 187 / 255.0f, 175 / 255.0f },  // scourge_tooth3
	{ 198 / 255.0f, 187 / 255.0f, 175 / 255.0f },  // scourge_tooth4
	{ 148 / 255.0f,   116 / 255.0f,   139 / 255.0f },  // scourge_lefttail
	{ 151 / 255.0f,   131 / 255.0f,   152 / 255.0f },  // scourge_righttail
	{ 58 / 255.0f, 239 / 255.0f, 104 / 255.0f },   // scourge_scar1
	{ 58 / 255.0f, 239 / 255.0f, 104 / 255.0f },   // scourge_scar2
	{ 58 / 255.0f, 239 / 255.0f, 104 / 255.0f }    // scourge_scar2
};

GLuint VBO_scourge, VAO_scourge;

void prepare_scourge() {
	GLsizeiptr buffer_size = sizeof(scourge_body) + sizeof(scourge_leftwing) + sizeof(scourge_rightwing) + sizeof(scourge_tooth1) + sizeof(scourge_tooth2) 
							+ sizeof(scourge_tooth3) + sizeof(scourge_tooth4) + sizeof(scourge_lefttail) + sizeof(scourge_righttail) + sizeof(scourge_scar1) + sizeof(scourge_scar2) + sizeof(scourge_scar3);

	// Initialize vertex buffer object.
	glGenBuffers(1, &VBO_scourge);

	glBindBuffer(GL_ARRAY_BUFFER, VBO_scourge);
	glBufferData(GL_ARRAY_BUFFER, buffer_size, NULL, GL_STATIC_DRAW); // allocate buffer object memory

	glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(scourge_body), scourge_body);
	glBufferSubData(GL_ARRAY_BUFFER, sizeof(scourge_body), sizeof(scourge_leftwing), scourge_leftwing);
	glBufferSubData(GL_ARRAY_BUFFER, sizeof(scourge_body) + sizeof(scourge_leftwing), sizeof(scourge_rightwing), scourge_rightwing);
	glBufferSubData(GL_ARRAY_BUFFER, sizeof(scourge_body) + sizeof(scourge_leftwing) + sizeof(scourge_rightwing), sizeof(scourge_tooth1), scourge_tooth1);
	glBufferSubData(GL_ARRAY_BUFFER, sizeof(scourge_body) + sizeof(scourge_leftwing) + sizeof(scourge_rightwing) + sizeof(scourge_tooth1), sizeof(scourge_tooth2), scourge_tooth2);
	glBufferSubData(GL_ARRAY_BUFFER, sizeof(scourge_body) + sizeof(scourge_leftwing) + sizeof(scourge_rightwing) + sizeof(scourge_tooth1) + sizeof(scourge_tooth2), sizeof(scourge_tooth3), scourge_tooth3);
	glBufferSubData(GL_ARRAY_BUFFER, sizeof(scourge_body) + sizeof(scourge_leftwing) + sizeof(scourge_rightwing) + sizeof(scourge_tooth1) + sizeof(scourge_tooth2) + sizeof(scourge_tooth3), sizeof(scourge_tooth4), scourge_tooth4);
	glBufferSubData(GL_ARRAY_BUFFER, sizeof(scourge_body) + sizeof(scourge_leftwing) + sizeof(scourge_rightwing) + sizeof(scourge_tooth1) + sizeof(scourge_tooth2) + sizeof(scourge_tooth3) + sizeof(scourge_tooth4), sizeof(scourge_lefttail), scourge_lefttail);
	glBufferSubData(GL_ARRAY_BUFFER, sizeof(scourge_body) + sizeof(scourge_leftwing) + sizeof(scourge_rightwing) + sizeof(scourge_tooth1) + sizeof(scourge_tooth2) + sizeof(scourge_tooth3) + sizeof(scourge_tooth4) + sizeof(scourge_lefttail), sizeof(scourge_righttail), scourge_righttail);
	glBufferSubData(GL_ARRAY_BUFFER, sizeof(scourge_body) + sizeof(scourge_leftwing) + sizeof(scourge_rightwing) + sizeof(scourge_tooth1) + sizeof(scourge_tooth2) + sizeof(scourge_tooth3) + sizeof(scourge_tooth4) + sizeof(scourge_lefttail) + sizeof(scourge_righttail), sizeof(scourge_scar1), scourge_scar1);
	glBufferSubData(GL_ARRAY_BUFFER, sizeof(scourge_body) + sizeof(scourge_leftwing) + sizeof(scourge_rightwing) + sizeof(scourge_tooth1) + sizeof(scourge_tooth2) + sizeof(scourge_tooth3) + sizeof(scourge_tooth4) + sizeof(scourge_lefttail) + sizeof(scourge_righttail) + sizeof(scourge_scar1), sizeof(scourge_scar2), scourge_scar2);
	glBufferSubData(GL_ARRAY_BUFFER, sizeof(scourge_body) + sizeof(scourge_leftwing) + sizeof(scourge_rightwing) + sizeof(scourge_tooth1) + sizeof(scourge_tooth2) + sizeof(scourge_tooth3) + sizeof(scourge_tooth4) + sizeof(scourge_lefttail) + sizeof(scourge_righttail) + sizeof(scourge_scar1) + sizeof(scourge_scar2), sizeof(scourge_scar3), scourge_scar3);
	// Initialize vertex array object.
	glGenVertexArrays(1, &VAO_scourge);
	glBindVertexArray(VAO_scourge);

	glBindBuffer(GL_ARRAY_BUFFER, VBO_scourge);
	glVertexAttribPointer(LOC_VERTEX, 2, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(0));

	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}

void draw_scourge() {
	glBindVertexArray(VAO_scourge);
	
	glUniform3fv(loc_primitive_color, 1, scourge_color[SCOURGE_BODY]);
	glDrawArrays(GL_TRIANGLE_FAN, 0, 14);

	glUniform3fv(loc_primitive_color, 1, scourge_color[SCOURGE_LEFTWING]);
	glDrawArrays(GL_TRIANGLE_FAN, 14, 11);

	glUniform3fv(loc_primitive_color, 1, scourge_color[SCOURGE_RIGHTWING]);
	glDrawArrays(GL_TRIANGLE_FAN, 25, 11);

	glUniform3fv(loc_primitive_color, 1, scourge_color[SCOURGE_TOOTH1]);
	glDrawArrays(GL_TRIANGLE_FAN, 36, 3);

	glUniform3fv(loc_primitive_color, 1, scourge_color[SCOURGE_TOOTH2]);
	glDrawArrays(GL_TRIANGLE_FAN, 39, 3);

	glUniform3fv(loc_primitive_color, 1, scourge_color[SCOURGE_TOOTH3]);
	glDrawArrays(GL_TRIANGLE_FAN, 42, 3);

	glUniform3fv(loc_primitive_color, 1, scourge_color[SCOURGE_TOOTH4]);
	glDrawArrays(GL_TRIANGLE_FAN, 45, 3);

	glUniform3fv(loc_primitive_color, 1, scourge_color[SCOURGE_LEFTTAIL]);
	glDrawArrays(GL_TRIANGLE_FAN, 48, 7);

	glUniform3fv(loc_primitive_color, 1, scourge_color[SCOURGE_RIGHTTAIL]);
	glDrawArrays(GL_TRIANGLE_FAN, 55, 7);

	glUniform3fv(loc_primitive_color, 1, scourge_color[SCOURGE_SCAR1]);
	glDrawArrays(GL_TRIANGLE_FAN, 62, 4);

	glUniform3fv(loc_primitive_color, 1, scourge_color[SCOURGE_SCAR2]);
	glDrawArrays(GL_TRIANGLE_FAN, 66, 4);

	glUniform3fv(loc_primitive_color, 1, scourge_color[SCOURGE_SCAR3]);
	glDrawArrays(GL_TRIANGLE_FAN, 70, 4);

	glBindVertexArray(0);
}

//	my object SCOURGE-ELITE
#define ELITE_SCOURGE_BODY			0
#define ELITE_SCOURGE_LEFTWING		1
#define ELITE_SCOURGE_RIGHTWING		2
#define ELITE_SCOURGE_TOOTH1			3
#define ELITE_SCOURGE_TOOTH2			4
#define ELITE_SCOURGE_TOOTH3			5
#define ELITE_SCOURGE_TOOTH4			6
#define ELITE_SCOURGE_LEFTTAIL		7
#define ELITE_SCOURGE_RIGHTTAIL		8
#define ELITE_SCOURGE_SCAR1			9
#define ELITE_SCOURGE_SCAR2			10
#define ELITE_SCOURGE_SCAR3			11

float esr = 1.0f;

GLfloat elite_scourge_body[14][2] = { { 0.0 * esr, 4.0 * esr },{ -1.5 * esr, 3.6 * esr },{ -2.3 * esr, 2.0 * esr },{ -2.7 * esr, 0.1 * esr },{ -2.5 * esr, -2.0 * esr },{ -1.9 * esr, -3.7 * esr },{-1.1 * esr, -4.7 * esr},
								{0.0 * esr, -5.1 * esr}, {1.1 * esr, -4.7 * esr},{1.9 * esr,-3.7 * esr},{2.5 * esr,-2.0 * esr},{2.7 * esr,0.1 * esr},{2.3 * esr,2.0 * esr},{1.5 * esr,3.6 * esr } };

GLfloat elite_scourge_leftwing[11][2] = { { -2.3 * esr, 2.0 * esr },{ -2.7 * esr, 0.1 * esr },{ -2.5 * esr, -2.0 * esr },{ -1.9 * esr, -3.7 * esr },{-3.3 * esr,-4.4 * esr},
									{-5.1 * esr,-3.1 * esr},{-6.4 * esr,-0.7 * esr},{-6.7 * esr,3 * esr},{-6.3 * esr,7 * esr},{-5.6 * esr,4.9 * esr},{-4.8 * esr,2.7 * esr} };
GLfloat elite_scourge_rightwing[11][2] = { { 2.3 * esr, 2.0 * esr },{ 2.7 * esr, 0.1 * esr },{ 2.5 * esr, -2.0 * esr },{ 1.9 * esr, -3.7 * esr },{3.3 * esr,-4.4 * esr},
									{5.1 * esr,-3.1 * esr},{6.4 * esr,-0.7 * esr},{6.7 * esr,3 * esr},{6.3 * esr,7 * esr},{5.6 * esr,4.9 * esr},{4.8 * esr,2.7 * esr} };
GLfloat elite_scourge_tooth1[3][2] = { {-0.8 * esr,3.8 * esr},{-1.5 * esr,3.6 * esr},{-1.6 * esr,5.4 * esr} };
GLfloat elite_scourge_tooth2[3][2] = { {-0.8 * esr,3.8 * esr},{0.0 * esr,4.0 * esr},{-0.5 * esr,6 * esr} };
GLfloat elite_scourge_tooth3[3][2] = { {0.8 * esr,3.8 * esr},{1.5 * esr,3.6 * esr},{1.6 * esr,5.4 * esr} };
GLfloat elite_scourge_tooth4[3][2] = { {0.8 * esr,3.8 * esr},{0.0 * esr,4.0 * esr},{0.5 * esr,6 * esr} };
GLfloat elite_scourge_lefttail[7][2] = { {-1.9 * esr,-3.7 * esr},{-1.1 * esr,-4.7 * esr},{0 * esr,-5.1 * esr},{-0.8 * esr,-7.2 * esr},{-1.2 * esr,-9.3 * esr},{-1.6 * esr,-8 * esr},{-2 * esr,-6 * esr} };
GLfloat elite_scourge_righttail[7][2] = { {1.9 * esr,-3.7 * esr},{1.1 * esr,-4.7 * esr},{0 * esr,-5.1 * esr},{0.8 * esr,-7.2 * esr},{1.2 * esr,-9.3 * esr},{1.6 * esr,-8 * esr},{2 * esr,-6 * esr} };
GLfloat elite_scourge_scar1[4][2] = { { -1.7 * esr, 0.1 * esr }, {0.0 * esr, 0.5 * esr}, {1.7 * esr, 0.4 * esr }, {0.3 * esr, 0.0 * esr} };
GLfloat elite_scourge_scar2[4][2] = { { -2.0 * esr, -0.7 * esr }, {0.0 * esr, -0.3 * esr}, {2.2 * esr, -0.4 * esr }, {0.3 * esr, -0.8 * esr} };
GLfloat elite_scourge_scar3[4][2] = { { -1.2 * esr, -1.5 * esr }, {0.0 * esr, -1.1 * esr}, {1.7 * esr, -1.0 * esr }, {0.3 * esr, -1.6 * esr} };

GLfloat elite_scourge_color[12][3] = {
	{ 187 / 255.0f, 107 / 255.0f, 118 / 255.0f },  // elite_scourge_body
	{ 232 / 255.0f, 60 / 255.0f,  59 / 255.0f },  // elite_scourge_leftwing
	{ 247 / 255.0f, 36 / 255.0f,  39 / 255.0f },  // elite_scourge_rightwing
	{ 198 / 255.0f, 187 / 255.0f, 175 / 255.0f },  // elite_scourge_tooth1
	{ 198 / 255.0f, 187 / 255.0f, 175 / 255.0f },  // elite_scourge_tooth2
	{ 198 / 255.0f, 187 / 255.0f, 175 / 255.0f },  // elite_scourge_tooth3
	{ 198 / 255.0f, 187 / 255.0f, 175 / 255.0f },  // elite_scourge_tooth4
	{ 148 / 255.0f,   116 / 255.0f,   139 / 255.0f },  // elite_scourge_lefttail
	{ 151 / 255.0f,   131 / 255.0f,   152 / 255.0f },  // elite_scourge_righttail
	{ 191 / 255.0f, 1 / 255.0f, 0 / 255.0f },   // elite_scourge_scar1
	{ 223 / 255.0f, 2 / 255.0f, 9 / 255.0f },   // elite_scourge_scar2
	{ 188 / 255.0f, 1 / 255.0f, 7 / 255.0f }    // elite_scourge_scar2
};

GLuint VBO_elite_scourge, VAO_elite_scourge;

void prepare_elite_scourge() {
	GLsizeiptr buffer_size = sizeof(elite_scourge_body) + sizeof(elite_scourge_leftwing) + sizeof(elite_scourge_rightwing) + sizeof(elite_scourge_tooth1) + sizeof(elite_scourge_tooth2)
		+ sizeof(elite_scourge_tooth3) + sizeof(elite_scourge_tooth4) + sizeof(elite_scourge_lefttail) + sizeof(elite_scourge_righttail) + sizeof(elite_scourge_scar1) + sizeof(elite_scourge_scar2) + sizeof(elite_scourge_scar3);

	// Initialize vertex buffer object.
	glGenBuffers(1, &VBO_elite_scourge);

	glBindBuffer(GL_ARRAY_BUFFER, VBO_elite_scourge);
	glBufferData(GL_ARRAY_BUFFER, buffer_size, NULL, GL_STATIC_DRAW); // allocate buffer object memory

	glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(elite_scourge_body), elite_scourge_body);
	glBufferSubData(GL_ARRAY_BUFFER, sizeof(elite_scourge_body), sizeof(elite_scourge_leftwing), elite_scourge_leftwing);
	glBufferSubData(GL_ARRAY_BUFFER, sizeof(elite_scourge_body) + sizeof(elite_scourge_leftwing), sizeof(elite_scourge_rightwing), elite_scourge_rightwing);
	glBufferSubData(GL_ARRAY_BUFFER, sizeof(elite_scourge_body) + sizeof(elite_scourge_leftwing) + sizeof(elite_scourge_rightwing), sizeof(elite_scourge_tooth1), elite_scourge_tooth1);
	glBufferSubData(GL_ARRAY_BUFFER, sizeof(elite_scourge_body) + sizeof(elite_scourge_leftwing) + sizeof(elite_scourge_rightwing) + sizeof(elite_scourge_tooth1), sizeof(elite_scourge_tooth2), elite_scourge_tooth2);
	glBufferSubData(GL_ARRAY_BUFFER, sizeof(elite_scourge_body) + sizeof(elite_scourge_leftwing) + sizeof(elite_scourge_rightwing) + sizeof(elite_scourge_tooth1) + sizeof(elite_scourge_tooth2), sizeof(elite_scourge_tooth3), elite_scourge_tooth3);
	glBufferSubData(GL_ARRAY_BUFFER, sizeof(elite_scourge_body) + sizeof(elite_scourge_leftwing) + sizeof(elite_scourge_rightwing) + sizeof(elite_scourge_tooth1) + sizeof(elite_scourge_tooth2) + sizeof(elite_scourge_tooth3), sizeof(elite_scourge_tooth4), elite_scourge_tooth4);
	glBufferSubData(GL_ARRAY_BUFFER, sizeof(elite_scourge_body) + sizeof(elite_scourge_leftwing) + sizeof(elite_scourge_rightwing) + sizeof(elite_scourge_tooth1) + sizeof(elite_scourge_tooth2) + sizeof(elite_scourge_tooth3) + sizeof(elite_scourge_tooth4), sizeof(elite_scourge_lefttail), elite_scourge_lefttail);
	glBufferSubData(GL_ARRAY_BUFFER, sizeof(elite_scourge_body) + sizeof(elite_scourge_leftwing) + sizeof(elite_scourge_rightwing) + sizeof(elite_scourge_tooth1) + sizeof(elite_scourge_tooth2) + sizeof(elite_scourge_tooth3) + sizeof(elite_scourge_tooth4) + sizeof(elite_scourge_lefttail), sizeof(elite_scourge_righttail), elite_scourge_righttail);
	glBufferSubData(GL_ARRAY_BUFFER, sizeof(elite_scourge_body) + sizeof(elite_scourge_leftwing) + sizeof(elite_scourge_rightwing) + sizeof(elite_scourge_tooth1) + sizeof(elite_scourge_tooth2) + sizeof(elite_scourge_tooth3) + sizeof(elite_scourge_tooth4) + sizeof(elite_scourge_lefttail) + sizeof(elite_scourge_righttail), sizeof(elite_scourge_scar1), elite_scourge_scar1);
	glBufferSubData(GL_ARRAY_BUFFER, sizeof(elite_scourge_body) + sizeof(elite_scourge_leftwing) + sizeof(elite_scourge_rightwing) + sizeof(elite_scourge_tooth1) + sizeof(elite_scourge_tooth2) + sizeof(elite_scourge_tooth3) + sizeof(elite_scourge_tooth4) + sizeof(elite_scourge_lefttail) + sizeof(elite_scourge_righttail) + sizeof(elite_scourge_scar1), sizeof(elite_scourge_scar2), elite_scourge_scar2);
	glBufferSubData(GL_ARRAY_BUFFER, sizeof(elite_scourge_body) + sizeof(elite_scourge_leftwing) + sizeof(elite_scourge_rightwing) + sizeof(elite_scourge_tooth1) + sizeof(elite_scourge_tooth2) + sizeof(elite_scourge_tooth3) + sizeof(elite_scourge_tooth4) + sizeof(elite_scourge_lefttail) + sizeof(elite_scourge_righttail) + sizeof(elite_scourge_scar1) + sizeof(elite_scourge_scar2), sizeof(elite_scourge_scar3), elite_scourge_scar3);
	// Initialize vertex array object.
	glGenVertexArrays(1, &VAO_elite_scourge);
	glBindVertexArray(VAO_elite_scourge);

	glBindBuffer(GL_ARRAY_BUFFER, VBO_elite_scourge);
	glVertexAttribPointer(LOC_VERTEX, 2, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(0));

	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}

void draw_elite_scourge() {
	glBindVertexArray(VAO_elite_scourge);

	glUniform3fv(loc_primitive_color, 1, elite_scourge_color[ELITE_SCOURGE_BODY]);
	glDrawArrays(GL_TRIANGLE_FAN, 0, 14);

	glUniform3fv(loc_primitive_color, 1, elite_scourge_color[ELITE_SCOURGE_LEFTWING]);
	glDrawArrays(GL_TRIANGLE_FAN, 14, 11);

	glUniform3fv(loc_primitive_color, 1, elite_scourge_color[ELITE_SCOURGE_RIGHTWING]);
	glDrawArrays(GL_TRIANGLE_FAN, 25, 11);

	glUniform3fv(loc_primitive_color, 1, elite_scourge_color[ELITE_SCOURGE_TOOTH1]);
	glDrawArrays(GL_TRIANGLE_FAN, 36, 3);

	glUniform3fv(loc_primitive_color, 1, elite_scourge_color[ELITE_SCOURGE_TOOTH2]);
	glDrawArrays(GL_TRIANGLE_FAN, 39, 3);

	glUniform3fv(loc_primitive_color, 1, elite_scourge_color[ELITE_SCOURGE_TOOTH3]);
	glDrawArrays(GL_TRIANGLE_FAN, 42, 3);

	glUniform3fv(loc_primitive_color, 1, elite_scourge_color[ELITE_SCOURGE_TOOTH4]);
	glDrawArrays(GL_TRIANGLE_FAN, 45, 3);

	glUniform3fv(loc_primitive_color, 1, elite_scourge_color[ELITE_SCOURGE_LEFTTAIL]);
	glDrawArrays(GL_TRIANGLE_FAN, 48, 7);

	glUniform3fv(loc_primitive_color, 1, elite_scourge_color[ELITE_SCOURGE_RIGHTTAIL]);
	glDrawArrays(GL_TRIANGLE_FAN, 55, 7);

	glUniform3fv(loc_primitive_color, 1, elite_scourge_color[ELITE_SCOURGE_SCAR1]);
	glDrawArrays(GL_TRIANGLE_FAN, 62, 4);

	glUniform3fv(loc_primitive_color, 1, elite_scourge_color[ELITE_SCOURGE_SCAR2]);
	glDrawArrays(GL_TRIANGLE_FAN, 66, 4);

	glUniform3fv(loc_primitive_color, 1, elite_scourge_color[ELITE_SCOURGE_SCAR3]);
	glDrawArrays(GL_TRIANGLE_FAN, 70, 4);

	glBindVertexArray(0);
}

//	my object 
float ys_r = 3.0f;

#define YELLOW_STAR			0

GLfloat yellow_star[10][2] = 
		{
			{2.12 * ys_r, 0.73 * ys_r}, {0.4914 * ys_r, 0.6994 * ys_r},
			{-0.04 * ys_r, 2.24 * ys_r}, {-0.5140 * ys_r, 0.6805 * ys_r},
			{-2.14 * ys_r, 0.65 * ys_r}, {-0.8066 * ys_r, -0.2823 * ys_r},
			{-1.28 * ys_r, -1.84 * ys_r}, {-0.0181 * ys_r, -0.8588 * ys_r},
			{1.35 * ys_r, -1.79 * ys_r}, {0.8198 * ys_r, -0.2528 * ys_r}
		};
GLfloat yellow_star_color[1][3] = {
	{ 250 / 255.0f, 254 / 255.0f, 100 / 255.0f },  // yello_star
};

GLuint VBO_yellow_star, VAO_yellow_star;

void prepare_yello_star() {
	GLsizeiptr buffer_size = sizeof(yellow_star);

	// Initialize vertex buffer object.
	glGenBuffers(1, &VBO_yellow_star);

	glBindBuffer(GL_ARRAY_BUFFER, VBO_yellow_star);
	glBufferData(GL_ARRAY_BUFFER, buffer_size, NULL, GL_STATIC_DRAW); // allocate buffer object memory

	glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(yellow_star), yellow_star);
	// Initialize vertex array object.
	glGenVertexArrays(1, &VAO_yellow_star);
	glBindVertexArray(VAO_yellow_star);

	glBindBuffer(GL_ARRAY_BUFFER, VBO_yellow_star);
	glVertexAttribPointer(LOC_VERTEX, 2, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(0));

	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}

void draw_yellow_star() {
	glBindVertexArray(VAO_yellow_star);

	glUniform3fv(loc_primitive_color, 1, yellow_star_color[YELLOW_STAR]);
	glDrawArrays(GL_TRIANGLE_FAN, 0, 10);
	glBindVertexArray(0);
}

//	my object 
float bs_r = 3.5f;

#define BLUE_STAR			0

GLfloat blue_star[10][2] =
{
	{2.12 * bs_r, 0.73 * bs_r}, {0.4914 * bs_r, 0.6994 * bs_r},
	{-0.04 * bs_r, 2.24 * bs_r}, {-0.5140 * bs_r, 0.6805 * bs_r},
	{-2.14 * bs_r, 0.65 * bs_r}, {-0.8066 * bs_r, -0.2823 * bs_r},
	{-1.28 * bs_r, -1.84 * bs_r}, {-0.0181 * bs_r, -0.8588 * bs_r},
	{1.35 * bs_r, -1.79 * bs_r}, {0.8198 * bs_r, -0.2528 * bs_r}
};
GLfloat blue_star_color[1][3] = {
	{ 33 / 255.0f, 252 / 255.0f, 215 / 255.0f },  // blue_star
};

GLuint VBO_blue_star, VAO_blue_star;

void prepare_blue_star() {
	GLsizeiptr buffer_size = sizeof(blue_star);

	// Initialize vertex buffer object.
	glGenBuffers(1, &VBO_blue_star);

	glBindBuffer(GL_ARRAY_BUFFER, VBO_blue_star);
	glBufferData(GL_ARRAY_BUFFER, buffer_size, NULL, GL_STATIC_DRAW); // allocate buffer object memory

	glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(blue_star), blue_star);
	// Initialize vertex array object.
	glGenVertexArrays(1, &VAO_blue_star);
	glBindVertexArray(VAO_blue_star);

	glBindBuffer(GL_ARRAY_BUFFER, VBO_blue_star);
	glVertexAttribPointer(LOC_VERTEX, 2, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(0));

	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}

void draw_blue_star() {
	glBindVertexArray(VAO_blue_star);

	glUniform3fv(loc_primitive_color, 1, blue_star_color[BLUE_STAR]);
	glDrawArrays(GL_TRIANGLE_FAN, 0, 10);
	glBindVertexArray(0);
}

//	my object 
float rs_r = 2.0f;

#define RED_STAR			0

GLfloat red_star[10][2] =
{
	{2.12 * rs_r, 0.73 * rs_r}, {0.4914 * rs_r, 0.6994 * rs_r},
	{-0.04 * rs_r, 2.24 * rs_r}, {-0.5140 * rs_r, 0.6805 * rs_r},
	{-2.14 * rs_r, 0.65 * rs_r}, {-0.8066 * rs_r, -0.2823 * rs_r},
	{-1.28 * rs_r, -1.84 * rs_r}, {-0.0181 * rs_r, -0.8588 * rs_r},
	{1.35 * rs_r, -1.79 * rs_r}, {0.8198 * rs_r, -0.2528 * rs_r}
};
GLfloat red_star_color[1][3] = {
	{ 246 / 255.0f, 70 / 255.0f, 41 / 255.0f },  // red_star
};

GLuint VBO_red_star, VAO_red_star;

void prepare_red_star() {
	GLsizeiptr buffer_size = sizeof(red_star);

	// Initialize vertex buffer object.
	glGenBuffers(1, &VBO_red_star);

	glBindBuffer(GL_ARRAY_BUFFER, VBO_red_star);
	glBufferData(GL_ARRAY_BUFFER, buffer_size, NULL, GL_STATIC_DRAW); // allocate buffer object memory

	glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(red_star), red_star);
	// Initialize vertex array object.
	glGenVertexArrays(1, &VAO_red_star);
	glBindVertexArray(VAO_red_star);

	glBindBuffer(GL_ARRAY_BUFFER, VBO_red_star);
	glVertexAttribPointer(LOC_VERTEX, 2, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(0));

	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}

void draw_red_star() {
	glBindVertexArray(VAO_red_star);

	glUniform3fv(loc_primitive_color, 1, red_star_color[BLUE_STAR]);
	glDrawArrays(GL_TRIANGLE_FAN, 0, 10);
	glBindVertexArray(0);
}

//	my object 
float ex_r = 5.0f;

#define EXPLOSION_BIG			0
#define EXPLOSION_SMALL			1

GLfloat explosion_big[24][2] =
{
	{-1.52 * ex_r, 1.23 * ex_r}, {-2.26 * ex_r, 2.57 * ex_r},
	{-1.0 * ex_r, 2.0 * ex_r}, {-1.3 * ex_r, 3.59 * ex_r},
	{-0.36 * ex_r, 2.21 * ex_r}, {-0.16 * ex_r, 3.45 * ex_r},
	{0.32 * ex_r, 2.33 * ex_r}, {1.42 * ex_r, 3.49 * ex_r},
	{1.18 * ex_r, 2.29 * ex_r}, {2.74 * ex_r, 2.59 * ex_r},
	{1.92 * ex_r, 1.39 * ex_r}, {3.44 * ex_r, 1.39 * ex_r},
	{1.72 * ex_r, 0.21 * ex_r}, {2.8 * ex_r, -1.11 * ex_r},
	{1.22 * ex_r, -0.67 * ex_r}, {2.24 * ex_r, -2.61 * ex_r},
	{0.84 * ex_r, -1.55 * ex_r}, {0.5 * ex_r, -3.29 * ex_r},
	{-0.08 * ex_r, -1.55 * ex_r}, {-1.56 * ex_r, -2.45 * ex_r},
	{-1 * ex_r, -1 * ex_r}, {-2.8 * ex_r, -1.23 * ex_r},
	{-1.54 * ex_r, -0.15 * ex_r}, {-3.46 * ex_r, 0.95 * ex_r}
};

GLfloat explosion_small[24][2] =
{
	{-1.52 * ex_r * 0.55 * 0.55, 1.23 * ex_r * 0.55}, {-2.26 * ex_r * 0.55, 2.57 * ex_r * 0.55},
	{-1.0 * ex_r * 0.55, 2.0 * ex_r * 0.55}, {-1.3 * ex_r * 0.55, 3.59 * ex_r * 0.55},
	{-0.36 * ex_r * 0.55, 2.21 * ex_r * 0.55}, {-0.16 * ex_r * 0.55, 3.45 * ex_r * 0.55},
	{0.32 * ex_r * 0.55, 2.33 * ex_r * 0.55}, {1.42 * ex_r * 0.55, 3.49 * ex_r * 0.55},
	{1.18 * ex_r * 0.55, 2.29 * ex_r * 0.55}, {2.74 * ex_r * 0.55, 2.59 * ex_r * 0.55},
	{1.92 * ex_r * 0.55, 1.39 * ex_r * 0.55}, {3.44 * ex_r * 0.55, 1.39 * ex_r * 0.55},
	{1.72 * ex_r * 0.55, 0.21 * ex_r * 0.55}, {2.8 * ex_r * 0.55, -1.11 * ex_r * 0.55},
	{1.22 * ex_r * 0.55, -0.67 * ex_r * 0.55}, {2.24 * ex_r * 0.55, -2.61 * ex_r * 0.55},
	{0.84 * ex_r * 0.55, -1.55 * ex_r * 0.55}, {0.5 * ex_r * 0.55, -3.29 * ex_r * 0.55},
	{-0.08 * ex_r * 0.55, -1.55 * ex_r * 0.55}, {-1.56 * ex_r * 0.55, -2.45 * ex_r * 0.55},
	{-1 * ex_r * 0.55, -1 * ex_r * 0.55}, {-2.8 * ex_r * 0.55, -1.23 * ex_r * 0.55},
	{-1.54 * ex_r * 0.55, -0.15 * ex_r * 0.55}, {-3.46 * ex_r * 0.55, 0.95 * ex_r * 0.55}
};

GLfloat explosion_color[2][3] = {
	{ 251 / 255.0f, 154 / 255.0f, 40 / 255.0f },  // explosion_big
	{ 255 / 255.0f, 17 / 255.0f, 57 / 255.0f },  // explosion_small
};

GLuint VBO_explosion, VAO_explosion;

void prepare_explosion() {
	GLsizeiptr buffer_size = sizeof(explosion_big) + sizeof(explosion_small);

	// Initialize vertex buffer object.
	glGenBuffers(1, &VBO_explosion);

	glBindBuffer(GL_ARRAY_BUFFER, VBO_explosion);
	glBufferData(GL_ARRAY_BUFFER, buffer_size, NULL, GL_STATIC_DRAW); // allocate buffer object memory

	glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(explosion_big), explosion_big);
	glBufferSubData(GL_ARRAY_BUFFER, sizeof(explosion_big), sizeof(explosion_small), explosion_small);
	// Initialize vertex array object.
	glGenVertexArrays(1, &VAO_explosion);
	glBindVertexArray(VAO_explosion);

	glBindBuffer(GL_ARRAY_BUFFER, VBO_explosion);
	glVertexAttribPointer(LOC_VERTEX, 2, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(0));

	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}

void draw_explosion() {
	glBindVertexArray(VAO_explosion);

	glUniform3fv(loc_primitive_color, 1, explosion_color[EXPLOSION_BIG]);
	glDrawArrays(GL_TRIANGLE_FAN, 0, 24);
	glUniform3fv(loc_primitive_color, 1, explosion_color[EXPLOSION_SMALL]);
	glDrawArrays(GL_TRIANGLE_FAN, 24, 24);
	glBindVertexArray(0);
}


#define EARTH_SEA			0
#define EARTH_LAND			1

GLfloat earth_sea[12][2] =
{
	{-900, -450}, {-900, -250}, {-736, -190}, {-535, -149}, {-227, -113}, {-50, -100},
	{50, -100}, {227, -113}, {535, -149}, {736, -190}, {900, -250}, {900, -450}
};

GLfloat earth_land[12][2] = {
	{-50, -100}, {-227, -113}, {-535, -149}, {-736, -190},
	{-710, -272}, {-497, -359}, {-222, -316}, 
	{73, -388}, {227, -318}, {307, -216}, {200, -200}, {124, -121}
};

GLfloat earth_color[2][3] = {
	{ 49 / 255.0f, 197 / 255.0f, 228 / 255.0f },  // earth_sea
	{102 / 255.0f, 232.0f / 255.0f, 140 /255.0f}   // earth_land	
};

GLuint VBO_earth, VAO_earth;

void prepare_earth() {
	GLsizeiptr buffer_size = sizeof(earth_sea) + sizeof(earth_land);

	// Initialize vertex buffer object.
	glGenBuffers(1, &VBO_earth);

	glBindBuffer(GL_ARRAY_BUFFER, VBO_earth);
	glBufferData(GL_ARRAY_BUFFER, buffer_size, NULL, GL_STATIC_DRAW); // allocate buffer object memory

	glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(earth_sea), earth_sea);
	glBufferSubData(GL_ARRAY_BUFFER, sizeof(earth_sea), sizeof(earth_land), earth_land);
	// Initialize vertex array object.
	glGenVertexArrays(1, &VAO_earth);
	glBindVertexArray(VAO_earth);

	glBindBuffer(GL_ARRAY_BUFFER, VBO_earth);
	glVertexAttribPointer(LOC_VERTEX, 2, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(0));

	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}

void draw_earth() {
	glBindVertexArray(VAO_earth);

	glUniform3fv(loc_primitive_color, 1, earth_color[EARTH_SEA]);
	glDrawArrays(GL_TRIANGLE_FAN, 0, 12);
	glUniform3fv(loc_primitive_color, 1, earth_color[EARTH_LAND]);
	glDrawArrays(GL_TRIANGLE_FAN, 12, 12);
	glBindVertexArray(0);
}
