#pragma once
#include <GL/glew.h>
struct Position {
	GLfloat x;
	GLfloat y;
};
struct Color {
	GLubyte r;
	GLubyte g;
	GLubyte b;
	GLubyte a;
};
struct UV {
	float u, v;
};
struct Vertex {
	Position position;
	Color color;
	UV uv;
	void setColor(GLubyte r, GLubyte g, GLubyte b, GLubyte a) {
		color.r = r;
		color.g = g;
		color.b = b;
		color.a = a;
	}
	void setPosition(GLfloat x, GLfloat y) {
		position.x = x;
		position.y = y;
	}
	void SetUV(float u, float v) {
		uv.u = u;
		uv.v = v;
	}

};