# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: dmelessa <dmelessa@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/02/10 14:33:34 by dmelessa          #+#    #+#              #
#    Updated: 2020/02/16 19:19:53 by dmelessa         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = ./RT
CC = gcc
RM = rm -f
CURRENTDIR = .

#UNAME_S = $(shell uname -s)

#SYSTEM:
SYSTEM = $(shell uname)
MACOS = Darwin
LINUX = Linux

CFLAGS = -I$(INCDIR)\
		 -I$(LIBFTINC)\
		 -I$(SDL2INC)\
#		 -Wall\
		 -Werror\
		 -Wextra
ifeq ($(SYSTEM), $(MACOS))
	LDLIBS = -lm\
			 -lft\
			 -framework SDL2\
			 -framework OpenCL

	LDFLAGS = -L$(LIBFTDIR)\
			  -F $(LIBSDIR)\
			  -rpath $(LIBSDIR)
else ifeq ($(SYSTEM), $(LINUX))
	LDLIBS = -lm\
			 -l SDL2\
			 -l OpenCL

	LDFLAGS	= $(LIBFT)
endif


LIBSDIR = $(CURRENTDIR)/Libs

LIBFT = $(LIBFTDIR)/libft.a
LIBFTDIR = $(LIBSDIR)/libft
LIBFTINC = $(LIBFTDIR)/includes

#MACOS
SDL2DIR = $(LIBSDIR)/SDL2.framework
SDL2INC = $(SDL2DIR)/Headers

INCDIR = $(CURRENTDIR)/include/
INCS = rt.h world.h
INCS := $(addprefix $(INCDIR), $(INCS))

SRCSDIR	= ./src/
SRCS =	main.c init.c init_window.c catch_event.c\
		read_data.c create_program.c error_handling.c

OBJSDIR = ./obj/
OBJS = $(addprefix $(OBJSDIR), $(SRCS:.c=.o))

all: $(LIBFT) $(NAME)

$(NAME): $(OBJS) $(INCS)
	@echo 'making executable'
	$(CC) -o $@ $(OBJS) $(LDLIBS) $(LDFLAGS)
	@echo DONE!


$(LIBFT):
	@make -C $(LIBFTDIR)

$(OBJS): $(OBJSDIR)%.o: $(SRCSDIR)%.c | $(OBJSDIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJS): $(INCS)

$(OBJSDIR):
	mkdir $@

clean:
	@echo deliting object files
	@$(RM) $(OBJS)
	@make -C $(LIBFTDIR) clean

fclean: clean
	@echo deliting executable file
	@$(RM) $(NAME)
	@make -C $(LIBFTDIR) fclean

.PHONY: all clean fclean re
re:	fclean all
