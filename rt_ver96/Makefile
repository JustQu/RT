
NAME = RT_OpenCL
COMP = gcc

#SYSTEM:
SYSTEM = $(shell uname)
MACOS = Darwin
LINYX = Linux

#FLAGS: for mac now
WWW = 
#WWW = -Wall -Wextra -Werror
ifeq ($(SYSTEM), $(MACOS))
	FLAGS = -framework SDL2 -F ./frameworks/ -rpath ./frameworks/ -framework OpenCL
else ifeq ($(SYSTEM), $(LINYX))
	FLAGS = -l SDL2 -lm -l OpenCL
endif


#DIR:
LIBFT_DIR = ./libft/
SDL2_DIR = ./frameworks/SDL2.framework/
SDL2_INC = $(SDL2_DIR)Headers
C_DIR = ./source/
INC = ./includes/
O_DIR = ./obj/

#HEAD:
HEADERS = $(INC)rt.h $(INC)sizes.h

#LIB:
LIBFT_A = $(LIBFT_DIR)libft.a

#FILES:
C_FLS =	main.c init_scene.c read_vec.c open_cl.c ft_clerror.c create_program.c
O_FLS = $(C_FLS:%.c=%.o)

SOURSES = $(addprefix $(C_DIR), $(C_FLS))
OBJECTS = $(addprefix $(O_DIR), $(O_FLS))
INCLUDES = -I $(INC) -I $(LIBFT_DIR) -I $(SDL2_INC)
LIBS = $(LIBFT_A)

all: $(NAME)

$(NAME): $(LIBFT_A) $(O_DIR) $(OBJECTS) $(HEADERS)
	$(COMP) -o $(NAME) $(OBJECTS) $(INCLUDES) $(LIBS) $(FLAGS)

$(O_DIR)%.o: $(C_DIR)%.c $(HEADERS)
	$(COMP) $(WWW) -c $(INCLUDES) $< -o $@

$(LIBFT_A):
	make -C $(LIBFT_DIR)

$(O_DIR):
	mkdir -p $(O_DIR)

clean:
	rm -rf $(O_DIR)
	make -C $(LIBFT_DIR)/ fclean

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
