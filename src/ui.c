#include <luaflow/ui.h>
#include <luaflow/widget.h>
#include <luaflow/graphics.h>
#include <luaflow/nkimpl.h>
#include <luaflow/ui_content.h>

#include <glad/glad.h>
#include <nuklear/nuklear.h>
#include <nuklear/nuklear_glfw_gl3.h>

#include <stdio.h>

#define WIN_WIDTH	1200
#define WIN_HEIGHT	800

GLFWwindow	*window;
struct		nk_context		*ctx			= nullptr;
struct		nk_font_atlas	*atlas			= nullptr;
struct		nk_glfw			glfw_backend	= {0};
float		ui_scale_x;
float		ui_scale_y;

/* 初始化 UI */
int ui_init(void)
{
	int fb_width, fb_height;

	if (!glfwInit())
	{
		fprintf(stderr, "Failed to initialize GLFW.\n");
		return EXIT_FAILURE;
	}

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_SCALE_TO_MONITOR, GLFW_TRUE);
	glfwWindowHint(GLFW_SAMPLES, 4);
	if (!(window = glfwCreateWindow(WIN_WIDTH, WIN_HEIGHT, "Luaflow Editor", nullptr, nullptr)))
	{
		glfwTerminate();
		return EXIT_FAILURE;
	}

	glfwMakeContextCurrent(window);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		printf("Failed to initialize GLAD\n");
		return EXIT_FAILURE;
	}

	/*glEnable(GL_MULTISAMPLE);*/
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glfwGetFramebufferSize(window, &fb_width, &fb_height);

	ui_scale_x = (float)fb_width  / WIN_WIDTH;
	ui_scale_y = (float)fb_height / WIN_HEIGHT;

	if (!(ctx = nk_glfw3_init(&glfw_backend, window, NK_GLFW3_INSTALL_CALLBACKS)))
	{
		glfwDestroyWindow(window);
		glfwTerminate();
		return EXIT_FAILURE;
	}
	ctx -> style.window.border		= 2.0f;
	// ctx -> style.window.rounding	= 4.0f;

	nk_glfw3_font_stash_begin(&glfw_backend, &atlas);
	struct nk_font_config font_cfg = nk_font_config(20);
	font_cfg.range = nk_font_chinese_glyph_ranges();
	struct nk_font *font;
	if (!(font = nk_font_atlas_add_from_file(atlas, "fonts/SourceHanMono-Regular.otf", 20, &font_cfg))
		&& !(font = nk_font_atlas_add_from_file(atlas, "../fonts/SourceHanMono-Regular.otf", 20, &font_cfg)))
	{
		printf("FONT ERROR\n");
		return EXIT_FAILURE;
	}
	// struct nk_font *default_font = nk_font_atlas_add_default(atlas, 14.0f, NULL);
	nk_glfw3_font_stash_end(&glfw_backend);
	nk_style_set_font(ctx, &font -> handle);

	return EXIT_SUCCESS;
}

/* 主事件循环 */
int ui_mainloop(void)
{
	while (!glfwWindowShouldClose(window))
	{
		glfwPollEvents();
		nk_glfw3_new_frame(&glfw_backend);

		ctx -> style.window.background = nk_rgba(255, 255, 255, 255);
		if (nk_begin(ctx, "main", nk_rect(0, 0, 1200, 800), NK_WINDOW_NO_SCROLLBAR))	ui_content(ctx);
		nk_end(ctx);

		glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
		nk_glfw3_render(&glfw_backend, NK_ANTI_ALIASING_ON, 512, 512);
		glfwSwapBuffers(window);

		if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)	// Esc 键退出
			glfwSetWindowShouldClose(window, true);
	}

	return EXIT_SUCCESS;
}

/* 关闭 UI */
void ui_close(void)
{
	nk_glfw3_shutdown(&glfw_backend);
	glfwDestroyWindow(window);
	glfwTerminate();
}
