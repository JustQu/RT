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

	cam->angle = tan((cam->fov * PI) / 360);
	cam->ratio = (float)DEFAULT_WIDTH / DEFAULT_HEIGHT;
}

void	InitObjToZero(t_obj	*obj)
{
	obj->material.emission.x = 0;
	obj->material.emission.y = 0;
	obj->material.emission.z = 0;
	obj->material.color.x = 0;
	obj->material.color.y = 0;
	obj->material.color.z = 0;
	obj->r = 0;
	obj->r2 = 0;
	obj->angle = 0;
	obj->maxm = 0;
	obj->minm = 0;
}

void	init_object(char *line, t_scene *scene, int type)
{
	t_obj	*obj;
	int			first;
	int			last;

	obj = &scene->objects[scene->nobjects];

	InitObjToZero(obj);

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
	else if (obj->type == 0) /* cone */
		obj->r2 = obj->r * obj->r + 1;
	else
		obj->r2 = obj->r * obj->r;

	if (find_parentheses(line, "minm", &first, &last))
		obj->minm = get_number(&first, &last, line);

	if (find_parentheses(line, "maxm", &first, &last))
		obj->maxm = get_number(&first, &last, line);

	if (find_parentheses(line, "color", &first, &last))
		obj->material.color = get_vector(&first, &last, line);

	if (find_parentheses(line, "emission", &first, &last))
		obj->material.emission = get_vector(&first, &last, line);

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

	/** difine vector1, vector2 */
	obj->vector1.x = obj->vertex2.x - obj->vertex1.x;
	obj->vector1.y = obj->vertex2.y - obj->vertex1.y;
	obj->vector1.z = obj->vertex2.z - obj->vertex1.z;

	obj->vector2.x = obj->vertex3.x - obj->vertex1.x;
	obj->vector2.y = obj->vertex3.y - obj->vertex1.y;
	obj->vector2.z = obj->vertex3.z - obj->vertex1.z;

	scene->ntriangles += 1;
}
