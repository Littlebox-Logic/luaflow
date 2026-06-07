#include <luaflow/ui.h>

int main(int argc, char *argv[])
{
	(void)(ui_init() || ui_mainloop());
	ui_close();
	return EXIT_SUCCESS;
}
