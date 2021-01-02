# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: user <user@student.42.fr>                  +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/06/29 17:22:43 by user              #+#    #+#              #
#    Updated: 2020/06/29 17:22:46 by user             ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME 			:= libft.a
FLAGS 			:= -g
CC 				:= gcc
REMOVE 			:= /bin/rm -rf
DIR_INCLUDE 	:= ./include
H_LIBFT			:= libft.h
HEADERS			:= $(H_LIBFT)
DIR_BIN 		:= bin/
DIR_LIBFT		:= .


SRC = ft_strlen.c ft_strcmp.c ft_strcpy.c ft_strdup.c ft_strncpy.c ft_atoi.c \
ft_bzero.c ft_strcat.c ft_strncat.c ft_strlcat.c ft_strchr.c ft_strrchr.c \
ft_strncmp.c ft_isalpha.c ft_isdigit.c ft_isalnum.c ft_isascii.c \
ft_isprint.c ft_toupper.c ft_tolower.c ft_memset.c \
ft_memcpy.c ft_memccpy.c ft_memmove.c ft_memchr.c \
ft_memalloc.c ft_memdel.c ft_strnew.c ft_strdel.c ft_strclr.c ft_striter.c \
ft_strstr.c ft_strnstr.c ft_striteri.c ft_strmap.c ft_strmapi.c ft_strequ.c \
ft_strnequ.c ft_strsub.c ft_strjoin.c ft_putchar.c ft_putstr.c ft_putendl.c \
ft_putnbr.c ft_putchar_fd.c ft_putstr_fd.c ft_putendl_fd.c ft_putnbr_fd.c \
ft_strtrim.c ft_itoa.c ft_strsplit.c ft_lstnew.c ft_lstdelone.c ft_lstdel.c \
ft_lstadd.c ft_lstiter.c ft_lstmap.c ft_strrev.c ft_range.c ft_swap.c \
ft_printbits.c ft_space.c get_next_line.c ft_strsplit_2.c

SRCS 			:= $(SRC)

DIRS_SRC		:= $(DIR_LIBFT)

OBJS			:= $(SRCS:.c=.o)
OBJS_BIN		:= $(addprefix $(DIR_BIN), $(OBJS))

vpath %.c $(DIRS_SRC)
vpath %.h $(DIR_INCLUDE)
vpath %.o $(DIR_BIN)

all: $(NAME)

$(NAME): $(OBJS)
	ar crus $@ $(OBJS_BIN)

$(OBJS):%.o: %.c $(HEADERS) | $(DIR_BIN)
	$(CC) $(FLAGS) -c $< -o $(DIR_BIN)$@ $(addprefix -I, $(DIR_INCLUDE)) -pipe

$(DIR_BIN):
	mkdir -p $@

clean:
	$(REMOVE) $(OBJS)
	$(REMOVE) $(DIR_BIN)

fclean: clean
	$(REMOVE) $(NAME)

re: fclean all

.PHONY:	clean fclean re
.SILENT: all $(NAME) $(OBJS) $(DIR_BIN) clean fclean re
