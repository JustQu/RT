/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gui.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alex <alex@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/18 17:10:47 by alex              #+#    #+#             */
/*   Updated: 2020/12/29 16:01:04 by alex             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GUI_H
# define GUI_H

# ifndef __DARWIN__
#  include <SDL2/SDL_render.h>
#  include <SDL2/SDL_image.h>
#  include <SDL2/SDL_ttf.h>
# else
#  include <SDL_render.h>
#  include <SDL_image.h>
#  include <SDL_ttf.h>
# endif

# include "instance_manager.h"
# include "window.h"
# include "image.h"
# include "rt_options.h"

# define WIDTH_MENU DEFAULT_WIDTH / 4
# define WIDTH_OFFSET DEFAULT_WIDTH - DEFAULT_WIDTH / 4
# define MARGIN 5
# define MARGIN_Y 7
# define FONT_TITLE_SIZE 20
# define FONT_SUBTITLE_SIZE 15
# define FONT_TEXT 12
# define COLOR_STEP 100
# define HEIGHT_BUTTON 30
# define SPACER		150

typedef struct s_rt		t_rt;
typedef struct s_vector	t_vector;

int						g_show_gui;
int						g_camera_tab_pressed;
int						g_objects_tab_pressed;
int						g_options_tab_pressed;
int						g_save_image;
int						g_font_size;

typedef struct			s_all_rect
{
	SDL_Rect			background;
	SDL_Rect			title_button;
	SDL_Rect			tab_camera_button;
	SDL_Rect			tab_objects_button;
	SDL_Rect			tab_textures_button;
	SDL_Rect			tab_options_button;
	SDL_Rect			first_button;
	SDL_Rect			second_button;
	SDL_Rect			third_button;
	SDL_Rect			fourth_button;
	SDL_Rect			fifth_button;
	SDL_Rect			sixth_button;
	SDL_Rect			seven_button;
	SDL_Rect			eight_button;
	SDL_Rect			nine_button;
	SDL_Rect			ten_button;
	SDL_Rect			eleven_button;
	SDL_Rect			twelve_button;
	SDL_Rect			thirteen_button;
	SDL_Rect			save_img_button;
}						t_all_rect;

typedef struct			s_colors
{
	SDL_Color			background_color;
	SDL_Color			border_color;
	SDL_Color			inside_color;
	SDL_Color			text_color;
}						t_colors;

/*
** 288 bytes
*/

typedef struct			s_gui
{
	t_colors			colors;
	t_all_rect			all_rect;

	t_instance_info		current_instance;
	t_light				current_light;
	t_camera			camera;
	t_rt_options		options;
}						t_gui;

void					init_colors(t_colors *color);
void					init_rect(t_all_rect *rect, t_window *win);
void					gui(t_window *win, t_gui *const gui);
void					render_texture(SDL_Texture *tex, SDL_Renderer *ren,
								int x, int y);
SDL_Texture				*load_texture(char *str, SDL_Renderer *renderer);
void					render_rect(SDL_Texture *texture,
					SDL_Renderer *renderer, SDL_Rect *rect);
void					draw_fill_rect(t_window *win, SDL_Rect *background,
					SDL_Color *color);
SDL_Texture				*render_text(char *message, char *font_file,
							SDL_Color color, SDL_Renderer *renderer);
void					draw_button(t_window *win,
					SDL_Rect *rect, char **str, t_colors *color);
void					draw_button_xyz(t_window *win, SDL_Rect *rect,
					char **str_xyz, t_colors *color);
void					draw_checkbox(t_rt *rt, SDL_Rect *rect, char *str,
								t_colors *color);
void					draw_button_choise(t_window *win, SDL_Rect *rect,
					char **str_xyz, t_colors *color);
void					draw_is_pressed_button(t_window *win, SDL_Rect *rect,
					char *str, t_colors *color);
void					gui_tab_bar(t_window *win, t_gui *gui);
void					draw_title_ray_tracing(t_window *win, SDL_Color *color);
void					draw_button_rgb(t_window *win, SDL_Rect *rect,
					char **str_xyz, t_colors *color);
void					render_tab_bar(t_window *win, SDL_Color *color,
					SDL_Rect *rect, char *str);
SDL_Rect				init_rect_size(int x, int y, int w, int h);
SDL_Color				init_color(int r, int g, int b, int a);
void					save_image_func(t_window *win, t_image *image);
SDL_Texture				*create_tab_subtitles(t_window *win, char *str,
					SDL_Color *color);
char					*itoa_float(float num);
void					draw_button_rect_xyz(t_window *win, SDL_Rect *rect,
					char *str, t_colors *color);
void					get_material_data(int ptr, char *string,
					char *str[4]);
void					get_camera_type_data(int ptr, char *string,
					char *str[4]);
void					get_str_data(char *str1, char *string, char *str[4]);
void					get_float_data(float ptr, char *string, char *str[4]);
void					get_float4_data(cl_float4 ptr,
						char *string, char *str[4]);
void					get_shape_data(int ptr, char *string, char *str[4]);
void					get_texture_data(int ptr, char *string, char *str[4]);
void					get_rt_type_data(int ptr, char *string, char **str);
void					gui_cone_vision(t_window *win,
					t_gui *gui);
void					gui_cylinder_vision(t_window *win,
					t_gui *gui);
void					gui_torus_vision(t_window *win,
					t_gui *gui);
void					gui_box_vision(t_window *win,
					t_gui *gui);
void					gui_disk_vision(t_window *win,
					t_gui *gui);
void					gui_rectangle_vision(t_window *win,
					t_gui *gui);
void					get_intensive_data(int ptr, char *string,
					char *str[4]);
void					gui_triangle_vision(t_window *win, t_gui *gui);
void					get_void_data(char *string, char *str[4]);
void					get_ambient_il_data(int ptr,
					char *string, char *str[4]);
void					get_true_data(int ptr,
					char *string, char *str[4]);
void					get_illumin_data(int ptr,
					char *string, char **str);
int						catch_keydown_2(t_rt *rt, t_window *win,
					SDL_Event event);
void					gui_init_title(t_window *win,
					t_all_rect *all_rect, t_colors *color);
void					draw_save_image_text(t_window *win);
void					draw_for_button(t_window *win,
					SDL_Rect *rect, t_colors *color);
void					draw_line(t_window *win, t_colors *color,
					SDL_Rect rect, SDL_Rect rect_2);
void					option_tab_cont(t_window *win,
					t_gui *gui);
void					draw_color_button(t_window *win, t_colors *color,
					t_color fill_color, SDL_Rect *rect);
void					light_tab(t_window *win,
					t_gui *gui);
void					minimum_rect_size(int w, int h,
					SDL_Rect *rect, SDL_Rect *ptr);
void					get_color_data(t_color color,
					char *string, char **str);
void					type_ambien_il(t_window *win,
					t_gui *gui);
void					free_str(char *str[4]);
void					draw_text(t_window *win, SDL_Rect *rect,
					char *str, t_colors *color);
void					get_texture_data_2(int ptr, char **str);
void					is_type_lights(t_window *win,
					t_gui *gui);
void					objects_tab_cont(t_window *win,
						t_gui *gui);
void					utils_call_option_tab(t_window *win,
							t_gui *gui, char **str);
void					util_call_object_tab(t_window *win,
							t_gui *gui, char **str);
void					util_call_camera_tab(t_window *win,
							t_gui *gui, char **str);
void					utils_call_objects_tab_cont(t_window *win,
													t_gui *gui, char **str);

void					init_gui(t_gui *const gui, t_window win);
void					gui_material_type(t_window *win,
											t_gui *gui);

#endif
