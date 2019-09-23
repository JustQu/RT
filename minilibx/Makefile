# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: dmelessa <dmelessa@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/09/20 12:23:32 by dmelessa          #+#    #+#              #
#    Updated: 2019/09/20 12:25:01 by dmelessa         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

UNAME_S := $(shell uname -s)
NAME := libmlx.a
MINILIBX_DIR :=
ifeq ($(UNAME_S), Linux)
	MINILIBX_DIR := ./X11
endif
ifeq ($(UNAME_S), Darwin)
	MINILIBX_DIR := ./minilibx_macos
endif

.PHONY: all
all : $(NAME)

$(NAME):
	@echo creating $(NAME)
	@make -C $(MINILIBX_DIR) all
	@cp $(MINILIBX_DIR)/$(NAME) ./

.PHONY: clean
clean:
	@make -C $(MINILIBX_DIR) clean

.PHONY: fclean
fclean: clean
	-@rm -f $(NAME)

.PHONY: re
re: fclean all
