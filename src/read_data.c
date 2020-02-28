#include "rt.h"
#define CAMERA "camera"
#define ADD_FILE "add file"

void	print_vector(cl_float4 vec)
{
	printf("(%f, %f, %f)", vec.x, vec.y, vec.z);
}

void	init_func(t_scene *scene)
{
	scene->obj_name[0] = ft_strdup("cone");
	scene->obj_name[1] = ft_strdup("cylinder");
	scene->obj_name[2] = ft_strdup("paraboloid");
	scene->obj_name[3] = ft_strdup("plane");
	scene->obj_name[4] = ft_strdup("sphere");
	scene->obj_name[5] = ft_strdup("torus");
/**		don't forget change NUM_OF_TYPES	*/
	scene->nobjects = 0;
	scene->ntriangles = 0;
}

void	count(t_scene *scene, char	*file_name)
{
	char	*line;
	int		fd;
	int		gnl;
	int		i;

	i = -1;
	fd = fd_return(file_name);
	while ((gnl = get_next_line(fd, &line)) > 0)
	{
		while (++i < NUM_OF_TYPES)
			if (ft_strncmp(line, scene->obj_name[i], ft_strlen(scene->obj_name[i])) == 0)
				scene->nobjects += 1;
		if (ft_strncmp(line, TRIANGLE, ft_strlen(TRIANGLE)) == 0)
			scene->ntriangles += 1;
		i = -1;
		if (ft_strncmp(line, ADD_FILE, ft_strlen(ADD_FILE)) == 0)
		{
			file_name = find_file_name(line);
			count(scene, file_name);
			printf("add file \"%s\"\n", file_name); //delete later
			free(file_name);
		}
		free(line);
	}
	if (gnl == -1)
		unable_to_read_file(file_name);
	close(fd);
}

void	read_file(t_scene *scene, char *file_name)
{
	char	*line;
	int		fd;
	int		gnl;
	int		i;

	i = -1;
	fd = fd_return(file_name);
	while ((gnl = get_next_line(fd, &line)) > 0)
	{
		if (ft_strncmp(line, CAMERA, ft_strlen(CAMERA)) == 0)
			init_camera(line, scene);
		while (++i < NUM_OF_TYPES)
			if (ft_strncmp(line, scene->obj_name[i], ft_strlen(scene->obj_name[i])) == 0)
				init_object(line, scene, i);
		if (ft_strncmp(line, TRIANGLE, ft_strlen(TRIANGLE)) == 0)
			init_triangle(line, scene);
		i = -1;
		if (ft_strncmp(line, ADD_FILE, ft_strlen(ADD_FILE)) == 0)
		{
			file_name = find_file_name(line);
			read_file(scene, file_name);
			free(file_name);
		}
		free(line);
	}
	if (gnl == -1)
		unable_to_read_file(file_name);
	close(fd);
}

/**
** @TODO: reading scene from file or default scene
** @brief
** init scene
** @param scene, file
** @return ** void
*/
void	read_data(t_scene *scene, char *file_name)
{
	init_func(scene);
	count(scene, file_name);
	scene->objects = malloc(sizeof(t_obj) * scene->nobjects);
	scene->triangles = malloc(sizeof(t_obj) * scene->ntriangles);
	printf("obj = %d; tri = %d\n", scene->nobjects, scene->ntriangles);//delete later
	scene->nobjects = 0;
	scene->ntriangles = 0;
	read_file(scene, file_name);
	printf("cam: origin");
	print_vector(scene->camera.origin);
	printf(" direction");
	print_vector(scene->camera.direction);
	printf(" fov(%d)\n", scene->camera.fov);
	for (int n = 0; n < scene->nobjects; n++)
	{
		printf("type (%d): origin", scene->objects[n].type);
		print_vector(scene->objects[n].origin);
		printf(" direction");
		print_vector(scene->objects[n].direction);
		printf(" radius(%f)", scene->objects[n].r);
		printf(" color(%d)\n", scene->objects[n].material.color);
	}
}
