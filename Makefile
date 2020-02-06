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
		 -I$(SDL2INC)

LDLIBS = -lm\
		 -lft\
		 -lrtmath\
		 -framework SDL2\
		 -framework OpenCL

LDFLAGS	=	-L$(LIBFTDIR)\
			-L$(RTMATHDIR)\
			-F ./frameworks\
			-rpath ./frameworks

LIBFT = libft.a
LIBFTDIR = ./libft
LIBFTINC = $(LIBFTDIR)/includes

RTMATH = librtmath.a
RTMATHDIR = ./rtmath
RTMATHINC = $(RTMATHDIR)/includes

SDL2 = libS
SDL2DIR = ./frameworks/SDL2.framework
SDL2INC = $(SDL2DIR)/Headers

INCDIR = ./includes/
INCS = rt.h
INCS := $(addprefix $(INCDIR), $(INCS))

SRCSDIR = ./src/
SRCS = main.c reader.c camera_movement.c\
		ft_itoaf.c list_funcs.c object_initiation.c other_initiation.c\
		param_reading.c utils.c read_kernel.c

OBJSDIR	=	./objs/
OBJS	=	$(addprefix $(OBJSDIR), $(SRCS:.c=.o))

NAME = ./RT

.PHONY: all
all: $(LIBFT) $(RTMATH) $(NAME)

$(NAME): $(OBJS) 
	@echo 'making executable'
	$(CC) $(LDLIBS) $(LDFLAGS) -o $@ $(OBJS) -framework OpenCL
	@echo DONE!

$(LIBFT):
	@make -C $(LIBFTDIR)

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

.PHONY: fclean
fclean: clean
	@echo deliting executable file
	@$(RM) $(NAME)
	@make -C $(LIBFTDIR) fclean
	@make -C $(RTMATHDIR) fclean


.PHONY: re
re:	fclean all
