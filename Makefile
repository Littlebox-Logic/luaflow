CC		= gcc
INC		= -Iinclude
CFLAGS	= $(INC) -std=gnu23 -Wall -O2

ifeq ($(OS), Windows_NT)
	INC		+= -Iinclude/windows
	LIBS	= lib/windows/libglfw3.a -lgdi32 -lopengl32
	TARGET	= bin/luaflow.exe
	PLATFM	= Windows
else
	LIBS	= -lglfw -lGL
	TARGET	= bin/luaflow
	PLATFM	= Linux
endif

all:	infos $(TARGET)

infos:
	@printf "\033[;97mPlatform :\033[0m %s\n" $(PLATFM)
	@printf "\033[;97mTarget   :\033[0m %s\n" $(TARGET)
	@printf "\033[;97mCompiler :\033[0m %s\n" $(CC)

FILES	= main.c \
		  glad.c \
		  nkimpl.c \
		  ui.c \
		  ui_content.c \
		  widget.c \
		  graphics.c

SRCS	= $(FILES:%=src/%)
OBJS	= $(SRCS:src/%.c=obj/%.o)

$(TARGET):		$(OBJS)
	@mkdir -p bin
	@printf "\033[;92m[ Building  ]\033[0m %-20s-> %s\n" $< $@
	@$(CC) -lm -o $@ $^ $(LIBS)
	@printf "\033[;92m[ Generated ]\033[0m %s\n" $@

obj/%.o:		src/%.c
	@mkdir -p $(@D)
	@printf "\033[;92m[ Compiling ]\033[0m %-20s-> %s\n" $< $@
	@$(CC) -c $(CFLAGS) -o $@ $<

clean:
	@printf "\033[;92m[  Cleaned  ]\033[0m obj/*, bin/*\n"
	@rm -rf bin/*
	@rm -rf obj/*
