# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: aapricot <aapricot@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/02/10 14:33:34 by dmelessa          #+#    #+#              #
#    Updated: 2020/12/29 18:47:11 by aapricot         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = ./RT
CC = clang
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
		 -I/Users/dmelessa/rt2/Libs/SDL2_image.framework/Headers\
		 -I./Libs/SDL2\
		 -I./Libs/SDL2_ttf/include\
		 -g\
		 -Wall\
		 -Werror\
		 -Wextra\
		 -D CL_TARGET_OPENCL_VERSION=220
		#  --analyze\
		#  --analyzer-output html\
		 -Wall\
		 -Werror\
		 -Wextra
ifeq ($(SYSTEM), $(MACOS))

	LDLIBS = -lm\
			 -lft\
			 -framework SDL2\
			 -framework OpenCL\
			 -framework SDL2_image\
			 -framework SDL2_ttf


	# SDL		= -framework SDL2_image\
	# 		 -framework SDL2_ttf\


	# SDL		= -lSDL2_image\
	# 		 -lSDL2_ttf\
	# 		 -lSDL2_gfx

	LDFLAGS = -L$(LIBFTDIR)\
			  -F $(LIBSDIR)\
			  -rpath $(LIBSDIR)

else ifeq ($(SYSTEM), $(LINUX))

	LDLIBS = -lm\
			 -l SDL2\
			 -l OpenCL
			 -lSDL2_image -lSDL2_ttf -lSDL2_gfx

	LDFLAGS	= $(LIBFT)

endif


LIBSDIR = $(CURRENTDIR)/Libs

LIBFT = $(LIBFTDIR)/libft.a
LIBFTDIR = $(LIBSDIR)/libft
LIBFTINC = $(LIBFTDIR)
LIBFTHEAD = $(LIBFTINC)/libft.h $(LIBFTINC)/get_next_line.h

#MACOS
SDL2DIR = $(LIBSDIR)/SDL2.framework
SDL2INC = ./Libs

INCDIR = $(CURRENTDIR)/include
INCS = *.h
INCS := $(addprefix $(INCDIR)/, $(INCS))

SRCSDIR	= ./srcs/
SRCS =aabb.c				gui_tab_bar.c			pars_material.c\
args.c				gui_tab_bar_2.c			pars_obj.c\
bvh.c				gui_tab_utils.c			pars_option.c\
bvh_01.c			gui_tab_utils_2.c		pars_texture.c\
camera.c			gui_utils.c			parser.c\
catch_event.c			gui_utils_2.c			parser_functions.c\
catch_keydown.c			gui_utils_3.c			perlin.c\
cleanup_buffers.c		gui_utils_4.c			random.c\
color.c				image.c				resource_manager.c\
create_program.c		init.c				resource_manager_utils.c\
error_handling.c		init_buffer.c			resource_manager_utils01.c\
error_handling_01.c		init_parsed_scene.c		rt.c\
get_default.c			instance_manager.c		rt_error.c\
get_first_values.c		interface.c			rt_ocl.c\
get_key_value.c			light_manager.c			rt_options.c\
get_light_type.c		loading_screen.c		sampler.c\
get_obj_mat_types.c		logs.c				sampler_01.c\
get_second_values.c		logs_second.c			sampler_manager.c\
get_tex_cam_types.c		logs_third.c			sampler_utils.c\
get_tracer_type.c		main.c				swap.c\
gui.c				matrix.c			texture_manager.c\
gui_button.c			matrix_01.c			utils.c\
gui_get_data.c			matrix_02.c			validate_objects_1.c\
gui_get_data_2.c		matrix_03.c			validate_objects_2.c\
gui_get_data_3.c		matrix_manager.c		validate_objects_3.c\
gui_init.c			object_manager.c		vector.c\
gui_object_vision.c		pars_camera.c			vector_utils.c\
gui_render_text.c		pars_light.c			window.c\
gui_material_type.c


OBJSDIR = ./obj/
OBJS = $(addprefix $(OBJSDIR), $(SRCS:.c=.o))

all: $(LIBFT) $(NAME)

$(NAME): $(OBJS) $(INCS) $(LIBFTHEAD)
	@echo 'making executable'
	@$(CC) -o $@ $(OBJS) $(LDLIBS) $(SDL) $(LDFLAGS)
	@echo DONE!


$(LIBFT):
	@make -C $(LIBFTDIR)

$(OBJS): $(OBJSDIR)%.o: $(SRCSDIR)%.c | $(OBJSDIR)
	@$(CC) $(CFLAGS) -c $< -o $@

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
