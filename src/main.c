#include <luaflow/ui.h>

int main(int argc, char *argv[])
{
	ui_init();
	ui_mainloop();
	ui_close();
	return EXIT_SUCCESS;
}
