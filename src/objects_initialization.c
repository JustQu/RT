#include "rt.h"

void	init_camera(char *line, t_scene *scene)
{
	t_camera	*cam;
	int			first;
	int			last;

	cam = &scene->camera;

	find_parentheses(line, "origin", &first, &last);
	cam->origin = get_vector(&first, &last, line);

	find_parentheses(line, "orientation", &first, &last);
	cam->direction = get_vector(&first, &last, line);

	find_parentheses(line, "fov", &first, &last);
	cam->fov = get_number(&first, &last, line);
}

void	init_object(char *line, t_scene *scene, int type)
{
	t_obj	obj;

	obj = scene->objects[scene->nobjects];
	scene->objects += 1;
}

void	init_triangle(char *line, t_scene *scene)
{
	t_triangle	obj;

	obj = scene->triangles[scene->ntriangles];
	scene->ntriangles += 1;
}
