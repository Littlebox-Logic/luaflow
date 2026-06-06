#include <luaflow/graphics.h>
#include <luaflow/ui.h>

#include <GLFW/glfw3.h>

void draw_rect(int x, int y, int w, int h, float r, float g, float b, float a, bool fill)
{
	x *= ui_scale_x;
	y *= ui_scale_y;
	w *= ui_scale_x;
	h *= ui_scale_y;
	glPolygonMode(GL_FRONT_AND_BACK, fill ? GL_FILL : GL_LINE);
	glColor4f(r, g, b, a);
	glBegin(GL_QUADS);
	glVertex2i(x, y);
	glVertex2i(x + w, y);
	glVertex2i(x + w, y + h);
	glVertex2i(x, y + h);
	glEnd();
}

void draw_line(int x_1, int y_1, int x_2, int y_2, float width, float r, float g, float b, float a)
{
	x_1 *= ui_scale_x;
	x_2 *= ui_scale_x;
	y_1 *= ui_scale_y;
	y_2 *= ui_scale_y;
	glLineWidth(width);
	glColor4f(r, g, b, a);
	glBegin(GL_LINES);
	glVertex2i(x_1, y_1);
	glVertex2i(x_2, y_2);
	glEnd();
	glLineWidth(1.0f);
}
