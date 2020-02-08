# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: dmelessa <dmelessa@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/09/20 11:48:45 by dmelessa          #+#    #+#              #
#    Updated: 2019/09/20 12:22:51 by dmelessa         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

#compiler
CC	=	gcc

#rm utils with flags
RM	=	rm -f

#compiler flags
CFLAGS	=	-I$(INCSDIR)\
#			-Wall\
			-Werror\
			-Wextra
			-std=c99\
			-pedantic\
			-O3

#linker flags
LDFLAGS	= 

#-------------------------------------------------------------------------------
#source fiiles and their directory
#-------------------------------------------------------------------------------
SRCS	=	$(addprefix ft_,\
			memset.c bzero.c memcpy.c memccpy.c memmove.c memchr.c memcmp.c\
			strlen.c strnlen.c strdup.c strcpy.c strncpy.c strcat.c strncat.c\
			strlcat.c strchr.c strrchr.c strstr.c strnstr.c strcmp.c strncmp.c\
			atoi.c isalpha.c isdigit.c isalnum.c isascii.c isprint.c toupper.c\
			tolower.c islower.c isupper.c memalloc.c memdel.c strnew.c strdel.c\
			strclr.c striter.c striteri.c strmap.c strmapi.c strequ.c strnequ.c\
			strsub.c strjoin.c strtrim.c strsplit.c itoa.c putchar.c putstr.c\
			putendl.c putnbr.c putchar_fd.c putstr_fd.c putendl_fd.c\
			putnbr_fd.c lstnew.c lstdelone.c lstdel.c lstadd.c lstiter.c\
			lstmap.c isspace.c strndup.c wc.c strtol.c swap.c isbase.c)\
			get_next_line.c
SRCSDIR	=	./

#-------------------------------------------------------------------------------
#includes fiiles and their directory
#-------------------------------------------------------------------------------
INCSDIR	=	./includes/
INCS	=	libft.h
INCS	:=	$(addprefix $(INCSDIR), $(INCS))

#-------------------------------------------------------------------------------
#object fiiles and their directory
#-------------------------------------------------------------------------------
OBJSDIR	=	./objs/
OBJS	=	$(addprefix $(OBJSDIR), $(SRCS:.c=.o))

#-------------------------------------------------------------------------------
#name of executable
#-------------------------------------------------------------------------------
NAME	=	libft.a

all: $(NAME)

$(NAME): $(OBJS)
	@ar rc $(NAME) $^
	@echo '$(NAME) created'

$(OBJS): $(OBJSDIR)%.o: $(SRCSDIR)%.c | $(OBJSDIR)
	@$(CC) $(CFLAGS) -c $< -o $@

$(OBJS): $(INCS)

$(OBJSDIR):
	-@mkdir $@

clean:
	-@echo 'deliting $(NAME) object files'
	-@$(RM) $(OBJS)

fclean: clean
	-@echo 'deliting $(NAME)'
	-@$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re