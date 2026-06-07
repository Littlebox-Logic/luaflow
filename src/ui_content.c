#include <luaflow/ui_content.h>
#include <luaflow/ui.h>

int ui_content(struct nk_context *ctx)
{
	nk_layout_row_static(ctx, 90, 1000, 1);
	nk_label(ctx, "1234123412341234", NK_TEXT_CENTERED);
	return EXIT_SUCCESS;
}