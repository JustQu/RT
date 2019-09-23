# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: dmelessa <dmelessa@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/09/20 12:23:13 by dmelessa          #+#    #+#              #
#    Updated: 2019/09/20 12:23:14 by dmelessa         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

#compiler
CC	=	gcc

#rm utils with flags
RM	=	rm -f

#compiler flags
CFLAGS	=	-I$(INCSDIR)\
			-Wall\
			-Werror\
			-Wextra\
			-std=c99\
			-pedantic\
			-O3

#linker flags
LDFLAGS	= 

#--------------------------------------------------------------------------------
#source fiiles and their directory
#--------------------------------------------------------------------------------
SRCS	=	mat3_init.c mat3_inv.c mat3_mul.c mat3_transpose.c\
			mat4_copy.c mat4_init.c mat4_inv.c mat4_mul.c mat4_trace.c\
			mat4_transpose.c\
			vec3_distance.c vec3_init.c vec3_mul.c vec3_normalize.c\
			vec3_rotate.c vec3_sub.c vec3_wrap.c\
			vec4_init.c vec4_mul.c vec4_normalize.c vec4_sub.c vec4_sum.c\
			vec3_sum.c\
			utils1.c utils2.c
SRCSDIR	=	./

#--------------------------------------------------------------------------------
#includes fiiles and their directory
#--------------------------------------------------------------------------------
INCSDIR	=	./includes/
INCS	=	rtmath.h mat3.h mat4.h rt_types.h utils.h vec3.h vec4.h
INCS	:=	$(addprefix $(INCSDIR), $(INCS))

#--------------------------------------------------------------------------------
#object fiiles and their directory
#--------------------------------------------------------------------------------
OBJSDIR	=	./objs/
OBJS	=	$(addprefix $(OBJSDIR), $(SRCS:.c=.o))

#--------------------------------------------------------------------------------
#name of executable
#--------------------------------------------------------------------------------
NAME	=	librtmath.a

.PHONY: all
all: $(NAME)

$(NAME): $(OBJS)
	@ar rc $(NAME) $^
	@echo '$(NAME) created'

$(OBJS): $(OBJSDIR)%.o: $(SRCSDIR)%.c | $(OBJSDIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJS): $(INCS)

$(OBJSDIR):
	mkdir $@

.PHONY: clean
clean:
	-@$(RM) $(OBJS)

.PHONY: fclean
fclean: clean
	-@$(RM) $(NAME)

.PHONY: re
re: fclean all