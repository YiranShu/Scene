#include "Angel.h"
#include "constant.h"
#include "stb_image.h"

vec3 CubeVertices[36];
vec3 CubeNormals[36];
vec3 texture_vertices[4];
vec3 texture_colors[4];
vec2 texture_coord[4];
GLuint texture_indices[6];
GLuint vao;
GLuint texture;
GLuint textureVAO, textureEBO;
GLuint myTexture;
mat4 view(1.0f);
mat4 model(1.0f);
mat4 projection(1.0f);
mat4 textureView;
mat4 textureProjection;
mat4 textureModel;
GLuint Projection, View, Model;
GLuint TextureProjection, TextureView, TextureModel;
GLint objectColorLoc;
vec3 tableColor(0.51f, 0.367f, 0.204f);
vec3 bookColor1(0.0f, 0.0f, 0.804f);
vec3 bookColor2(1.0f, 0.843f, 0.0f);
vec3 bookColor3(0.698f, 0.133f, 0.133f);
vec3 bookColor4(0.33f, 0.33f, 0.33f);
vec3 laptopColor(0.23f, 0.23f, 0.23f);
vec3 penColor(0.667f, 0.667f, 0.667f);
vec3 legColor(0.192f, 0.192f, 0.192f);
vec3 pageColor(1.0f, 1.0f, 1.0f);

void init() {
	for (int i = 0; i < 6; i++) {
		CubeNormals[i] = vec3(0.0f, 0.0f, -1.0f);
	}
	for(int i = 6; i < 12; i++) {
		CubeNormals[i] = vec3(0.0f, 0.0f, 1.0f);
	}
	for(int i = 12; i < 18; i++) {
		CubeNormals[i] = vec3(-1.0f, 0.0f, 0.0f);
	}
	for(int i = 18; i < 24; i++) {
		CubeNormals[i] = vec3(1.0f, 0.0f, 0.0f);
	}
	for(int i = 24; i < 30; i++) {
		CubeNormals[i] = vec3(0.0f, -1.0f, 0.0f);
	}
	for(int i = 30; i < 36; i++) {
		CubeNormals[i] = vec3(0.0f, 1.0f, 0.0f);
	}

	CubeVertices[0] = vec3(-0.5f, -0.5f, -0.5f);
	CubeVertices[1] = vec3(0.5f, -0.5f, -0.5f);
	CubeVertices[2] = vec3(0.5f, 0.5f, -0.5f);
	CubeVertices[3] = vec3(0.5f, 0.5f, -0.5f);
	CubeVertices[4] = vec3(-0.5f, 0.5f, -0.5f);
	CubeVertices[5] = vec3(-0.5f, -0.5f, -0.5f);

	CubeVertices[6] = vec3(-0.5f, -0.5f, 0.5f);
	CubeVertices[7] = vec3(0.5f, -0.5f, 0.5f);
	CubeVertices[8] = vec3(0.5f, 0.5f, 0.5f);
	CubeVertices[9] = vec3(0.5f, 0.5f, 0.5f);
	CubeVertices[10] = vec3(-0.5f, 0.5f, 0.5f);
	CubeVertices[11] = vec3(-0.5f, -0.5f, 0.5f);
	
	CubeVertices[12] = vec3(-0.5f, 0.5f, 0.5f);
	CubeVertices[13] = vec3(-0.5f, 0.5f, -0.5f);
	CubeVertices[14] = vec3(-0.5f, -0.5f, -0.5f);
	CubeVertices[15] = vec3(-0.5f, -0.5f, -0.5f);
	CubeVertices[16] = vec3(-0.5f, -0.5f, 0.5f);
	CubeVertices[17] = vec3(-0.5f, 0.5f, 0.5f);

	CubeVertices[18] = vec3(0.5f, 0.5f, 0.5f);
	CubeVertices[19] = vec3(0.5f, 0.5f, -0.5f);
	CubeVertices[20] = vec3(0.5f, -0.5f, -0.5f);
	CubeVertices[21] = vec3(0.5f, -0.5f, -0.5f);
	CubeVertices[22] = vec3(0.5f, -0.5f, 0.5f);
	CubeVertices[23] = vec3(0.5f, 0.5f, 0.5f);

	CubeVertices[24] = vec3(-0.5f, -0.5f, -0.5f);
	CubeVertices[25] = vec3(0.5f, -0.5f, -0.5f);
	CubeVertices[26] = vec3(0.5f, -0.5f, 0.5f);
	CubeVertices[27] = vec3(0.5f, -0.5f, 0.5f);
	CubeVertices[28] = vec3(-0.5f, -0.5f, 0.5f);
	CubeVertices[29] = vec3(-0.5f, -0.5f, -0.5f);

	CubeVertices[30] = vec3(-0.5f, 0.5f, -0.5f);
	CubeVertices[31] = vec3(0.5f, 0.5f, -0.5f);
	CubeVertices[32] = vec3(0.5f, 0.5f, 0.5f);
	CubeVertices[33] = vec3(0.5f, 0.5f, 0.5f);
	CubeVertices[34] = vec3(-0.5f, 0.5f, 0.5f);
	CubeVertices[35] = vec3(-0.5f, 0.5f, -0.5f);

	const vec3 lightPos(8.0f, 12.0f, 0.0f);
	const vec3 viewPos(2.0f, 1.0f, 5.0f);
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	GLuint buffer;
	glGenBuffers(1, &buffer);
	glBindBuffer(GL_ARRAY_BUFFER, buffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(CubeVertices) + sizeof(CubeNormals), CubeVertices, GL_STATIC_DRAW);
	glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(CubeVertices), CubeVertices);
	glBufferSubData(GL_ARRAY_BUFFER, sizeof(CubeVertices), sizeof(CubeNormals), CubeNormals);

	GLuint program = InitShader("lightV.glsl", "lightF.glsl");
	glUseProgram(program);

	// Position attribute
	GLuint verticesLoc = glGetAttribLocation(program, "position");
	glEnableVertexAttribArray(verticesLoc);
	glVertexAttribPointer(verticesLoc, 3, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(0));
	
	// Normal attribute
	GLuint normalsLoc = glGetAttribLocation(program, "normal");
	glEnableVertexAttribArray(normalsLoc);
	glVertexAttribPointer(normalsLoc, 3, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(sizeof(CubeVertices)));
	glBindVertexArray(0);

	objectColorLoc = glGetUniformLocation(program, "objectColor");
	GLint lightColorLoc = glGetUniformLocation(program, "lightColor");
	GLint lightPosLoc = glGetUniformLocation(program, "lightPos");
	GLint viewPosLoc = glGetUniformLocation(program, "viewPos");
	//glUniform3f(objectColorLoc, 1.0f, 0.5f, 0.31f);
	glUniform3f(lightColorLoc, 1.0f, 1.0f, 1.0f);
	glUniform3f(lightPosLoc, lightPos.x, lightPos.y, lightPos.z);
	glUniform3f(viewPosLoc, viewPos.x, viewPos.y, viewPos.z);

	view = LookAt(vec4(viewPos, 1.0f), vec4(0.0f, 0.0f, 0.0f, 1.0f), vec4(0.0f, 1.0f, 0.0f, 0.0f));

	Model = glGetUniformLocation(program, "model");
	View = glGetUniformLocation(program, "view");
	Projection = glGetUniformLocation(program, "projection");

	glClearColor(0.21f, 0.39f, 0.545f, 1.0f);
	glEnable(GL_DEPTH_TEST);

	glUniformMatrix4fv(View, 1, GL_TRUE, view);
	glUniformMatrix4fv(Projection, 1, GL_TRUE, projection);
	glUniformMatrix4fv(Model, 1, GL_TRUE, model);
}

void initTexture(int option) {
	if (option == 0) {
		texture_vertices[0] = vec3(0.5f,  0.5f, 0.0f);
		texture_vertices[1] = vec3(0.5f, -0.5f, 0.0f);
		texture_vertices[2] = vec3(-0.5f, -0.5f, 0.0f);
		texture_vertices[3] = vec3(-0.5f,  0.5f, 0.0f);
	}

	else if (option == 1) {
		texture_vertices[0] = vec3(0.5f,  0.0f, -0.5f);
		texture_vertices[1] = vec3(0.5f, 0.0f, 0.5f);
		texture_vertices[2] = vec3(-0.5f, 0.0f, 0.5f);
		texture_vertices[3] = vec3(-0.5f,  0.0f, -0.5f);
	}

	else {
		texture_vertices[0] = vec3(0.0f,  0.5f, -0.5f);
		texture_vertices[1] = vec3(0.0f, -0.5f, -0.5f);
		texture_vertices[2] = vec3(0.0f, -0.5f, 0.5f);
		texture_vertices[3] = vec3(0.0f,  0.5f, 0.5f);
	}

	texture_colors[0] = vec3(1.0f, 0.0f, 0.0f);
	texture_colors[1] = vec3(0.0f, 1.0f, 0.0f);
	texture_colors[2] = vec3(0.0f, 0.0f, 1.0f);
	texture_colors[3] = vec3(1.0f, 1.0f, 0.0f);

	texture_coord[0] = vec2(1.0f, 1.0f);
	texture_coord[1] = vec2(1.0f, 0.0f);
	texture_coord[2] = vec2(0.0f, 0.0f);
	texture_coord[3] = vec2(0.0f, 1.0f);
	
	texture_indices[0] = 0;
	texture_indices[1] = 1;
	texture_indices[2] = 3;
	texture_indices[3] = 1;
	texture_indices[4] = 2;
	texture_indices[5] = 3;

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	glGenVertexArrays(1, &textureVAO);
	glBindVertexArray(textureVAO);

	GLuint textureBuffer;
	glGenBuffers(1, &textureBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, textureBuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(texture_vertices) + sizeof(texture_colors) + sizeof(texture_coord), texture_vertices, GL_STATIC_DRAW);
	glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(texture_vertices), texture_vertices);
	glBufferSubData(GL_ARRAY_BUFFER, sizeof(texture_vertices), sizeof(texture_colors), texture_colors);
	glBufferSubData(GL_ARRAY_BUFFER, sizeof(texture_vertices) + sizeof(texture_colors), sizeof(texture_coord), texture_coord);

	glGenBuffers(1, &textureEBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, textureEBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(texture_indices), texture_indices, GL_STATIC_DRAW);

	GLuint textureProgram = InitShader("vshader.glsl", "fshader.glsl");
	glUseProgram(textureProgram);

	GLuint textureVerticesLoc = glGetAttribLocation(textureProgram, "position");
	glEnableVertexAttribArray(textureVerticesLoc);
	glVertexAttribPointer(textureVerticesLoc, 3, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(0));
	
	GLuint textureColorsLoc = glGetAttribLocation(textureProgram, "color");
	glEnableVertexAttribArray(textureColorsLoc);
	glVertexAttribPointer(textureColorsLoc, 3, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(sizeof(texture_vertices)));

	GLuint textureTextureCoordLoc = glGetAttribLocation(textureProgram, "texCoord");
	glEnableVertexAttribArray(textureTextureCoordLoc);
	glVertexAttribPointer(textureTextureCoordLoc, 2, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(sizeof(texture_vertices) + sizeof(texture_colors)));
	glBindVertexArray(0);

	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);
	// Set our texture parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	// Set texture filtering
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	// Load, create texture and generate mipmaps
	// unsigned char *image = stbi_load("images/screen.png", &width, &height, 0, 4);
	// glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);
	// glGenerateMipmap(GL_TEXTURE_2D);
	// stbi_image_free(image);
	// glBindTexture(GL_TEXTURE_2D, 0);

	TextureModel = glGetUniformLocation(textureProgram, "Model");
	TextureView = glGetUniformLocation(textureProgram, "View");
	TextureProjection = glGetUniformLocation(textureProgram, "Projection");
	myTexture = glGetUniformLocation(textureProgram, "myTexture");

	textureView = view;
	textureProjection = projection;
	textureModel = model;
	glUniformMatrix4fv(TextureView, 1, GL_TRUE, textureView);
	glUniformMatrix4fv(TextureProjection, 1, GL_TRUE, textureProjection);
	glUniformMatrix4fv(TextureModel, 1, GL_TRUE, textureModel);
}

void table() {
	mat4 instance = Translate(0.0f, 0.5 * BASE_HEIGHT, 0.0f) * Scale(BASE_LENGTH, BASE_HEIGHT, BASE_WIDTH);

	glUniform3f(objectColorLoc, tableColor.x, tableColor.y, tableColor.z);
	glUniformMatrix4fv(Model, 1, GL_TRUE, model * instance);
	glBindVertexArray(vao);
	glDrawArrays(GL_TRIANGLES, 0, 36);
	glBindVertexArray(0);
}

void wall() {
	mat4 instance = Translate(0.0f, 0.5 * WALL_HEIGHT, -0.5 * BASE_WIDTH + 0.5 * WALL_WIDTH) * Scale(WALL_LENGTH, WALL_HEIGHT, WALL_WIDTH);

	glUniform3f(objectColorLoc, tableColor.x, tableColor.y, tableColor.z);
	glUniformMatrix4fv(Model, 1, GL_TRUE, model * instance);
	glBindVertexArray(vao);
	glDrawArrays(GL_TRIANGLES, 0, 36);
	glBindVertexArray(0);
}

void sideWall() {
	mat4 instance = Translate(-0.5 * BASE_LENGTH + 0.5 * SIDE_WALL_LENGTH, 0.5 * SIDE_WALL_HEIGHT, -0.5 * BASE_WIDTH + WALL_WIDTH + 0.5 * SIDE_WALL_WIDTH) * Scale(SIDE_WALL_LENGTH, SIDE_WALL_HEIGHT, SIDE_WALL_WIDTH);

	glUniform3f(objectColorLoc, tableColor.x, tableColor.y, tableColor.z);
	glUniformMatrix4fv(Model, 1, GL_TRUE, model * instance);
	glBindVertexArray(vao);
	glDrawArrays(GL_TRIANGLES, 0, 36);
	glBindVertexArray(0);
}

void legs() {
	mat4 instance = Translate(-0.5 * BASE_LENGTH + 0.5 * SIDE_WALL_LENGTH + 1.0f, -0.5 * LEG_HEIGHT - BASE_HEIGHT, 0.5 * BASE_WIDTH - 1.0f) * Scale(LEG_WIDTH, LEG_HEIGHT, LEG_WIDTH);

	glUniform3f(objectColorLoc, legColor.x, legColor.y, legColor.z);
	glUniformMatrix4fv(Model, 1, GL_TRUE, model * instance);
	glBindVertexArray(vao);
	glDrawArrays(GL_TRIANGLES, 0, 36);
	glBindVertexArray(0);

	instance = Translate(0.5 * BASE_LENGTH + -0.5 * SIDE_WALL_LENGTH - 1.0f, -0.5 * LEG_HEIGHT - BASE_HEIGHT, 0.5 * BASE_WIDTH - 1.0f) * Scale(LEG_WIDTH, LEG_HEIGHT, LEG_WIDTH);

	glUniform3f(objectColorLoc, legColor.x, legColor.y, legColor.z);
	glUniformMatrix4fv(Model, 1, GL_TRUE, model * instance);
	glBindVertexArray(vao);
	glDrawArrays(GL_TRIANGLES, 0, 36);
	glBindVertexArray(0);

	instance = Translate(0.5 * BASE_LENGTH + -0.5 * SIDE_WALL_LENGTH - 1.0f, -0.5 * LEG_HEIGHT - BASE_HEIGHT, -0.5 * BASE_WIDTH + -0.5f) * Scale(LEG_WIDTH, LEG_HEIGHT, LEG_WIDTH);

	glUniform3f(objectColorLoc, legColor.x, legColor.y, legColor.z);
	glUniformMatrix4fv(Model, 1, GL_TRUE, model * instance);
	glBindVertexArray(vao);
	glDrawArrays(GL_TRIANGLES, 0, 36);
	glBindVertexArray(0);

	instance = Translate(-0.5 * BASE_LENGTH + 0.5 * SIDE_WALL_LENGTH + 5.0f, -0.5 * LEG_HEIGHT - BASE_HEIGHT, 0.5 * BASE_WIDTH - 1.0f) * Scale(LEG_WIDTH, LEG_HEIGHT, LEG_WIDTH);

	glUniform3f(objectColorLoc, legColor.x, legColor.y, legColor.z);
	glUniformMatrix4fv(Model, 1, GL_TRUE, model * instance);
	glBindVertexArray(vao);
	glDrawArrays(GL_TRIANGLES, 0, 36);
	glBindVertexArray(0);
}

void books() {
	mat4 instance = Translate(-0.5 * BASE_LENGTH + 1.0 * (SIDE_WALL_LENGTH + BOOK_LENGTH), 0.5 * BOOK_HEIGHT, -0.5 * BASE_WIDTH + WALL_WIDTH + 0.5 * BOOK_WIDTH) * Scale(BOOK_LENGTH, BOOK_HEIGHT, BOOK_WIDTH);

	glUniform3f(objectColorLoc, bookColor1.x, bookColor1.y, bookColor1.z);
	glUniformMatrix4fv(Model, 1, GL_TRUE, model * instance);
	glBindVertexArray(vao);
	glDrawArrays(GL_TRIANGLES, 0, 36);
	glBindVertexArray(0);

	instance = Translate(-0.5 * BASE_LENGTH + 2.0 * BOOK_LENGTH + 0.5 * (SIDE_WALL_LENGTH + BOOK_LENGTH), 0.5 * BOOK_HEIGHT, -0.5 * BASE_WIDTH + WALL_WIDTH + 0.5 * BOOK_WIDTH) * Scale(BOOK_LENGTH, BOOK_HEIGHT, BOOK_WIDTH);

	glUniform3f(objectColorLoc, bookColor2.x, bookColor2.y, bookColor2.z);
	glUniformMatrix4fv(Model, 1, GL_TRUE, model * instance);
	glBindVertexArray(vao);
	glDrawArrays(GL_TRIANGLES, 0, 36);
	glBindVertexArray(0);

	instance = Translate(-0.5 * BASE_LENGTH + 3.0 * BOOK_LENGTH + 0.5 * (SIDE_WALL_LENGTH + BOOK_LENGTH), 0.5 * BOOK_HEIGHT, -0.5 * BASE_WIDTH + WALL_WIDTH + 0.5 * BOOK_WIDTH) * Scale(BOOK_LENGTH, BOOK_HEIGHT, BOOK_WIDTH);

	glUniform3f(objectColorLoc, bookColor3.x, bookColor3.y, bookColor3.z);
	glUniformMatrix4fv(Model, 1, GL_TRUE, model * instance);
	glBindVertexArray(vao);
	glDrawArrays(GL_TRIANGLES, 0, 36);
	glBindVertexArray(0);

	instance = Translate(-0.5 * BASE_LENGTH + 4.0 * BOOK_LENGTH + 0.5 * (SIDE_WALL_LENGTH + BOOK_LENGTH), 0.5 * BOOK_HEIGHT, -0.5 * BASE_WIDTH + WALL_WIDTH + 0.5 * BOOK_WIDTH) * Scale(BOOK_LENGTH, BOOK_HEIGHT, BOOK_WIDTH);

	glUniform3f(objectColorLoc, bookColor4.x, bookColor4.y, bookColor4.z);
	glUniformMatrix4fv(Model, 1, GL_TRUE, model * instance);
	glBindVertexArray(vao);
	glDrawArrays(GL_TRIANGLES, 0, 36);
	glBindVertexArray(0);
}

void pages() {
	mat4 instance = Translate(-0.5 * BASE_LENGTH + 1.0 * (SIDE_WALL_LENGTH + BOOK_LENGTH), BOOK_HEIGHT, -0.5 * BASE_WIDTH + WALL_WIDTH + 0.5 * BOOK_WIDTH - 0.15f) * Scale(PAGE_LENGTH, PAGE_HEIGHT, PAGE_WIDTH);

	glUniform3f(objectColorLoc, pageColor.x, pageColor.y, pageColor.z);
	glUniformMatrix4fv(Model, 1, GL_TRUE, model * instance);
	glBindVertexArray(vao);
	glDrawArrays(GL_TRIANGLES, 0, 36);
	glBindVertexArray(0);

	instance = Translate(-0.5 * BASE_LENGTH + 1.5 * (SIDE_WALL_LENGTH + BOOK_LENGTH), BOOK_HEIGHT, -0.5 * BASE_WIDTH + WALL_WIDTH + 0.5 * BOOK_WIDTH - 0.15f) * Scale(PAGE_LENGTH, PAGE_HEIGHT, PAGE_WIDTH);

	glUniform3f(objectColorLoc, pageColor.x, pageColor.y, pageColor.z);
	glUniformMatrix4fv(Model, 1, GL_TRUE, model * instance);
	glBindVertexArray(vao);
	glDrawArrays(GL_TRIANGLES, 0, 36);
	glBindVertexArray(0);

	instance = Translate(-0.5 * BASE_LENGTH + 2.0 * (SIDE_WALL_LENGTH + BOOK_LENGTH), BOOK_HEIGHT + 0.01f, -0.5 * BASE_WIDTH + WALL_WIDTH + 0.5 * BOOK_WIDTH - 0.15f) * Scale(PAGE_LENGTH, PAGE_HEIGHT, PAGE_WIDTH);

	glUniform3f(objectColorLoc, pageColor.x, pageColor.y, pageColor.z);
	glUniformMatrix4fv(Model, 1, GL_TRUE, model * instance);
	glBindVertexArray(vao);
	glDrawArrays(GL_TRIANGLES, 0, 36);
	glBindVertexArray(0);

	instance = Translate(-0.5 * BASE_LENGTH + 2.5 * (SIDE_WALL_LENGTH + BOOK_LENGTH), BOOK_HEIGHT + 0.01f, -0.5 * BASE_WIDTH + WALL_WIDTH + 0.5 * BOOK_WIDTH - 0.15f) * Scale(PAGE_LENGTH, PAGE_HEIGHT, PAGE_WIDTH);

	glUniform3f(objectColorLoc, pageColor.x, pageColor.y, pageColor.z);
	glUniformMatrix4fv(Model, 1, GL_TRUE, model * instance);
	glBindVertexArray(vao);
	glDrawArrays(GL_TRIANGLES, 0, 36);
	glBindVertexArray(0);
}

void pen() {
	mat4 instance = Translate(0.5 * LAPTOP_LENGTH + 1.7f, 0.5 * PEN_WIDTH, 0.0f) * Scale(PEN_WIDTH, PEN_WIDTH, PEN_LENGTH);

	glUniform3f(objectColorLoc, penColor.x, penColor.y, penColor.z);
	glUniformMatrix4fv(Model, 1, GL_TRUE, model * instance);
	glBindVertexArray(vao);
	glDrawArrays(GL_TRIANGLES, 0, 36);
	glBindVertexArray(0);
}

void laptop() {
	mat4 instance = Translate(0.0f, 0.5 * LAPTOP_HEIGHT, 0.0f) * Scale(LAPTOP_LENGTH, LAPTOP_HEIGHT, LAPTOP_WIDTH);

	glUniform3f(objectColorLoc, laptopColor.x, laptopColor.y, laptopColor.z);
	glUniformMatrix4fv(Model, 1, GL_TRUE, model * instance);
	glBindVertexArray(vao);
	glDrawArrays(GL_TRIANGLES, 0, 36);
	glBindVertexArray(0);

	instance = Translate(0.0f, 0.5 * LAPTOP_WIDTH, -0.5 * LAPTOP_WIDTH) * Scale(LAPTOP_LENGTH, LAPTOP_WIDTH, LAPTOP_HEIGHT);

	glUniform3f(objectColorLoc, laptopColor.x, laptopColor.y, laptopColor.z);
	glUniformMatrix4fv(Model, 1, GL_TRUE, model * instance);
	glBindVertexArray(vao);
	glDrawArrays(GL_TRIANGLES, 0, 36);
	glBindVertexArray(0);
}

void screenTexture() {
	//screen
	int screenWidth, screenHeight;
	unsigned char *image = stbi_load("images/screen.png", &screenWidth, &screenHeight, 0, 4);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, screenWidth, screenHeight, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);
	glGenerateMipmap(GL_TEXTURE_2D);
	stbi_image_free(image);
	glBindTexture(GL_TEXTURE_2D, 0);

	mat4 instance = Translate(0.0f, 0.5 * LAPTOP_WIDTH, -0.5 * LAPTOP_WIDTH + 0.5 * LAPTOP_HEIGHT + 0.01f) * Scale(LAPTOP_LENGTH - 0.2, LAPTOP_WIDTH - 0.1, LAPTOP_HEIGHT);
	glUniformMatrix4fv(TextureModel, 1, GL_TRUE, textureModel * instance);

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texture);
	glUniform1i(myTexture, 0);
	glBindVertexArray(textureVAO);
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);
}

void keyboardTexture() {
	//keyboard
	int keyboardWidth, keyboardHeight;
	unsigned char *image = stbi_load("images/keyboard.png", &keyboardWidth, &keyboardHeight, 0, 4);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, keyboardWidth, keyboardHeight, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);
	glGenerateMipmap(GL_TEXTURE_2D);
	stbi_image_free(image);
	glBindTexture(GL_TEXTURE_2D, 0);

	mat4 instance = Translate(0.0f, LAPTOP_HEIGHT + 0.01f, 0.0f) * Scale(LAPTOP_LENGTH, LAPTOP_HEIGHT, LAPTOP_WIDTH);
	glUniformMatrix4fv(TextureModel, 1, GL_TRUE, textureModel * instance);

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texture);
	glUniform1i(myTexture, 0);
	glBindVertexArray(textureVAO);
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);
}

void bookTexture() {
	//keyboard
	int bookWidth, bookHeight;
	unsigned char *image = stbi_load("images/book.png", &bookWidth, &bookHeight, 0, 4);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, bookWidth, bookHeight, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);
	glGenerateMipmap(GL_TEXTURE_2D);
	stbi_image_free(image);
	glBindTexture(GL_TEXTURE_2D, 0);

	//instance = Translate(-0.5 * BASE_LENGTH + 4.0 * BOOK_LENGTH + 0.5 * (SIDE_WALL_LENGTH + BOOK_LENGTH), 0.5 * BOOK_HEIGHT, -0.5 * BASE_WIDTH + WALL_WIDTH + 0.5 * BOOK_WIDTH) * Scale(BOOK_LENGTH, BOOK_HEIGHT, BOOK_WIDTH);

	mat4 instance = Translate(-0.5 * BASE_LENGTH + 4.0 * BOOK_LENGTH + 0.5 * (SIDE_WALL_LENGTH + BOOK_LENGTH * 2) + 0.01f, 0.5 * BOOK_HEIGHT, -0.5 * BASE_WIDTH + WALL_WIDTH + 0.5 * BOOK_WIDTH) * Scale(BOOK_LENGTH, BOOK_HEIGHT, BOOK_WIDTH);
	glUniformMatrix4fv(TextureModel, 1, GL_TRUE, textureModel * instance);

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texture);
	glUniform1i(myTexture, 0);
	glBindVertexArray(textureVAO);
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);
}

void display() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	init();
	model = Translate(2.0f, 0.0f, 5.0f);
	table();

	model *= Translate(0.0f, BASE_HEIGHT, 0.0f);
	wall();
	sideWall();
	books();
	pages();
	laptop();
	pen();
	legs();
	initTexture(0);
	screenTexture();
	initTexture(1);
	keyboardTexture();
	initTexture(2);
	bookTexture();

	glutSwapBuffers();
}

void reshape(int width, int height) {
	glViewport(0, 0, width, height);

	GLfloat  left = -10.0, right = 10.0;
	GLfloat  bottom = -5.0, top = 15.0;
	GLfloat  zNear = -10.0, zFar = 10.0;

	GLfloat aspect = GLfloat(width) / height;

	if (aspect > 1.0) {
		left *= aspect;
		right *= aspect;
	} else {
		bottom /= aspect;
		top /= aspect;
	}

	projection = Ortho(left, right, bottom, top, zNear, zFar);
	glUniformMatrix4fv(Projection, 1, GL_TRUE, projection);
	textureProjection = Ortho(left, right, bottom, top, zNear, zFar);
	glUniformMatrix4fv(TextureProjection, 1, GL_TRUE, textureProjection);
}

void keyboard(unsigned char key, int x, int y) {
	switch (key) {
	case 033: // Escape Key
	case 'q': case 'Q':
		exit(EXIT_SUCCESS);
	default:
		break;
	}
}

int main(int argc, char **argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
	glutInitWindowSize(512, 512);
	glutCreateWindow("scene");

	// Iff you get a segmentation error at line 34, please uncomment the line below
	glewExperimental = GL_TRUE;
	glewInit();

	init();
	glutDisplayFunc(display);
	//initTexture();
	//textureDisplay();
	glutReshapeFunc(reshape);
	glutKeyboardFunc(keyboard);

	glutMainLoop();
	return 0;
}
