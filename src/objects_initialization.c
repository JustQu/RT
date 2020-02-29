#include "rt.h"

void	init_camera(char *line, t_scene *scene)
{
	t_camera	*cam;
	int			first;
	int			last;

	cam = &scene->camera;

	find_parentheses(line, "origin", &first, &last);
	cam->origin = get_vector(&first, &last, line);

	find_parentheses(line, "direction", &first, &last);
	cam->direction = get_vector(&first, &last, line);

	find_parentheses(line, "fov", &first, &last);
	cam->fov = get_number(&first, &last, line);
}

void	init_object(char *line, t_scene *scene, int type)
{
	t_obj	*obj;
	int			first;
	int			last;

	obj = &scene->objects[scene->nobjects];
	obj->type = type;

	find_parentheses(line, "origin", &first, &last);
	obj->origin = get_vector(&first, &last, line);

	if (find_parentheses(line, "direction", &first, &last))
		obj->direction = get_vector(&first, &last, line);

	if (find_parentheses(line, "radius", &first, &last))
		obj->r = get_number(&first, &last, line);

	if (find_parentheses(line, "angle", &first, &last))
		obj->angle = get_number(&first, &last, line);

	if (find_parentheses(line, "radius2", &first, &last))
		obj->r2 = get_number(&first, &last, line);
	else
		obj->r2 = obj->r * obj->r;

	if (find_parentheses(line, "color", &first, &last))
		obj->material.color = get_vector(&first, &last, line);

	if (find_parentheses(line, "emission", &first, &last))
		obj->material.emission = get_vector(&first, &last, line);

	if (find_parentheses(line, "minm", &first, &last))
		obj->minm = get_number(&first, &last, line);

	if (find_parentheses(line, "maxm", &first, &last))
		obj->maxm = get_number(&first, &last, line);

	scene->nobjects += 1;
}

void	init_triangle(char *line, t_scene *scene)
{
	t_triangle	*obj;
	int			first;
	int			last;

	obj = &scene->triangles[scene->ntriangles];

	find_parentheses(line, "vertex1", &first, &last);
	obj->vertex1 = get_vector(&first, &last, line);

	find_parentheses(line, "vertex2", &first, &last);
	obj->vertex2 = get_vector(&first, &last, line);

	find_parentheses(line, "vertex3", &first, &last);
	obj->vertex3 = get_vector(&first, &last, line);

	if (find_parentheses(line, "color", &first, &last))
		obj->material.color = get_vector(&first, &last, line);

	if (find_parentheses(line, "emission", &first, &last))
		obj->material.emission = get_vector(&first, &last, line);

	/** difine vector1, vector2, normal */

	scene->ntriangles += 1;
}
