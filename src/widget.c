#include <luaflow/widget.h>
#include <luaflow/graphics.h>

#include <stdlib.h>

Button *buttons = nullptr;

int button(void)
{
	return EXIT_SUCCESS;
}

int frame(void)
{
	draw_line(150, 20, 150, 780, 2.0f, 0.6f, 0.6f, 0.6f, 1.0f);
	draw_line(150, 100, 1180, 100, 2.0f, 0.6f, 0.6f, 0.6f, 1.0f);
	return EXIT_SUCCESS;
}
