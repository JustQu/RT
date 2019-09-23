# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: dmelessa <dmelessa@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/09/20 12:27:08 by dmelessa          #+#    #+#              #
#    Updated: 2019/09/20 12:27:08 by dmelessa         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = gcc

RM = rm -f

UNAME_S := $(shell uname -s)

CFLAGS = -O3\
		 -I.\
		 -I$(INCDIR)\
		 -I$(LIBFTINC)\
		 -I$(RTMATHINC)\
		 -I$(MLXINC)\
		 -Wall\
		 -Werror\
		 -Wextra

LDLIBS = -lm\
		-lft\
		-lmlx\
		-lrtmath

ifeq ($(UNAME_S),Linux)
	LDLIBS += -L/usr/X11/lib -lXext -lX11
endif
ifeq ($(UNAME_S), Darwin)
	LDLIBS += -framework OpenGL -framework AppKit
endif

LDFLAGS	=	-L$(LIBFTDIR)\
			-L$(RTMATHDIR)\
			-L$(MLXDIR)

LIBFT = libft.a
LIBFTDIR = ./libft/
LIBFTINC = $(LIBFTDIR)/includes

MLXDIR = ./minilibx/
MLXINC = ./minilibx/include

RTMATH = librtmath.a
RTMATHDIR = ./rtmath/
RTMATHINC = $(RTMATHDIR)/includes

INCDIR = ./includes/
INCS = rtv1.h
INCS := $(addprefix $(INCDIR), $(INCS))

SRCSDIR = ./src/
SRCS = main.c draw.c control.c sphere.c reader.c saver.c camera_movement.c\
		convert_to_16.c ft_itoaf.c list_funcs.c object_initiation.c\
		other_initiation.c other_out.c out_objects.c out_params.c\
		param_reading.c utils.c cone.c cylinder.c normals.c\
		plane.c intersection.c rays.c

OBJSDIR	=	./objs/
OBJS	=	$(addprefix $(OBJSDIR), $(SRCS:.c=.o))

NAME = ./RTv1

.PHONY: all
all: $(LIBFT) $(RTMATH) $(NAME)

$(NAME): $(OBJS) 
	@echo 'making executable'
	$(CC) $(LDLIBS) $(LDFLAGS) -o $@ $(OBJS) 
	@echo DONE!

$(LIBFT):
	@make -C $(LIBFTDIR)
	@make -C $(MLXDIR)

$(RTMATH):
	@make -C $(RTMATHDIR)

$(OBJS): $(OBJSDIR)%.o: $(SRCSDIR)%.c | $(OBJSDIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJS): $(INCS)

$(OBJSDIR):
	mkdir $@

.PHONY: clean
clean:
	@echo deliting object files
	@$(RM) $(OBJS)
	@make -C $(LIBFTDIR) clean
	@make -C $(RTMATHDIR) clean
	@make -C $(MLXDIR) clean

.PHONY: fclean
fclean: clean
	@echo deliting executable file
	@$(RM) $(NAME)
	@make -C $(LIBFTDIR) fclean
	@make -C $(RTMATHDIR) fclean
	@make -C $(MLXDIR) fclean

.PHONY: re
re:	fclean all
