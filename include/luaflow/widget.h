#pragma once

#include <stddef.h>

typedef struct
{
	void	(*call)(void);
	void	*comp;
	bool	enable;
}	*Button, _Button;

typedef struct
{
	int		x;
	int		y;
	size_t	font_size;
	size_t	textlen;
	char	text[];
}	*Label, _Label;

int frame(void);
int button(void);
