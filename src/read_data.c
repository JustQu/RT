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

cl_float3	get_color(float a, float b, float c)
{
	cl_float3	clr3;

	clr3.x = a;
	clr3.y = b;
	clr3.z = c;
	return clr3;
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
<<<<<<< HEAD
	scene->camera = camera_default;
	scene->nobjects = 7;
	scene->ntriangles = 1;
	scene->objects = (t_obj *)malloc(sizeof(t_obj) * scene->nobjects);
	scene->triangles = (t_triangle *)malloc(sizeof(t_triangle) * scene->ntriangles);
//	scene->boxes = (t_box *)malloc(sizeof(t_box));

	//default_scene
	scene->objects[0] = default_plane;
	scene->objects[0].material.emission = get_color(1, 1, 1);

	scene->objects[1] = default_plane;
	scene->objects[1].origin.x = 0.0f;
	scene->objects[1].origin.y = 0.0f;
	scene->objects[1].origin.z = 10.0f;
	scene->objects[1].origin.w = 0.0f;
	scene->objects[1].direction.x = 0.0f;
	scene->objects[1].direction.y = 0.0f;
	scene->objects[1].direction.z = 1.0f;
	scene->objects[1].direction.w = 0.0f;
	scene->objects[1].material.color = get_color(1, 0, 0);

	scene->objects[2] = default_plane;
	scene->objects[2].origin.x = 3.0f;
	scene->objects[2].origin.y = 0.0f;
	scene->objects[2].origin.z = 0.0f;
	scene->objects[2].origin.w = 0.0f;
	scene->objects[2].direction.x = -0.86602540378f;
	scene->objects[2].direction.y = 0.0f;
	scene->objects[2].direction.z = 0.5f;
	scene->objects[2].direction.w = 0.0f;
	scene->objects[2].material.color = get_color(0, 1, 0);

	scene->objects[3] = default_plane;
	scene->objects[3].origin.x = -3.0f;
	scene->objects[3].origin.y = 0.0f;
	scene->objects[3].origin.z = 0.0f;
	scene->objects[3].origin.w = 0.0f;
	scene->objects[3].direction.x = 0.86602540378f;
	scene->objects[3].direction.y = 0.0f;
	scene->objects[3].direction.z = 0.5f;
	scene->objects[3].direction.w = 0.0f;
	scene->objects[3].material.color = get_color(0, 0, 1);

	scene->objects[4] = default_sphere;
	scene->objects[4].origin.x = 5.0f;
	scene->objects[4].origin.y = 5.0f;
	scene->objects[4].origin.z = 7.0f;
	scene->objects[4].r = 2.0f;
	scene->objects[4].r2 = 4.0f;
	scene->objects[4].material.color = get_color(1,0,1);

	scene->objects[5] = default_sphere;
	scene->objects[5].origin.x = 5.0f;
	scene->objects[5].origin.y = 8.0f;
	scene->objects[5].origin.z = 5.0f;
	scene->objects[5].r = 2.0f;
	scene->objects[5].r2 = 4.0f;
	scene->objects[5].material.color = get_color(1,1,0);

	scene->objects[6] = default_plane;
	scene->objects[6].origin.y = 10.0f;
	scene->objects[6].material.emission = get_color(1, 1, 1);

	/*

	scene->objects[5] = default_cylinder;
	scene->objects[5].origin.x = -1.0f;
	scene->objects[5].origin.y = 5.0f;
	scene->objects[5].origin.z = 7.0f;
	scene->objects[5].direction.x = 1.0f;
	scene->objects[5].direction.y = 0.0f;
	scene->objects[5].direction.z = 0.0f;
	scene->objects[5].maxm = 5.0f;

	scene->objects[6] = default_cone;
	scene->objects[6].material.color = 0x00d4ca19;

	scene->objects[7] = default_paraboloid;

	scene->objects[8] = default_torus;
	scene->objects[8].origin.x = -3.0f;
	scene->objects[8].origin.y = 4.0f;
	scene->objects[8].origin.z = 4.0f;
	scene->objects[8].direction.x = 0.0f;
	scene->objects[8].direction.y = 0.5;
	scene->objects[8].direction.z = 0.86602540378;
	scene->objects[8].r = 1.5f;
	scene->objects[8].r2 = 0.3f;

	scene->objects[9] = default_torus;
	scene->objects[9].origin.x = -2.0f;
	scene->objects[9].origin.y = 5.0f;
	scene->objects[9].origin.z = 4.0f;
	scene->objects[9].direction.x = 0.86602540378f;
	scene->objects[9].direction.y = -0.5;
	scene->objects[9].direction.z = 0;
	scene->objects[9].r = 1.5f;
	scene->objects[9].r2 = 0.3f;
	*/

	return (0);
=======
	init_func(scene);
	count(scene, file_name);
	scene->objects = malloc(sizeof(t_obj) * scene->nobjects);
	scene->triangles = malloc(sizeof(t_obj) * scene->ntriangles);
	printf("obj = %d; tri = %d\n", scene->nobjects, scene->ntriangles);//delete later
	scene->nobjects = 0;
	scene->ntriangles = 0;
	read_file(scene, file_name);
	/* delete all of next */
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
>>>>>>> master
}
