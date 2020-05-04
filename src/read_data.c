#include "rt.h"
#define CAMERA "camera"
#define ADD_FILE "add file"

static const t_camera default_camera = {
	.viewplane = {
		.pixel_size = 1.0f,
		.width = DEFAULT_WIDTH,
		.height = DEFAULT_HEIGHT},
	.type = perspective,
	.origin = {.x = 0.0f, .y = 2.0f, .z = -2.0f, .w = 0.0f},
	.direction = {.x = 0.0f, .y = 0.0f, .z = 1.0f, .w = 0.0f},
	.up = {.x = 0.0f, .y = 1.0f, .z = 0.0f, .w = 0.0f},
	.d = 1.0f,
	.zoom = 1.0f,
	.ratio = (float)DEFAULT_WIDTH / (float)DEFAULT_HEIGHT,
	.normalized = FALSE
};

static const t_camera default_thin_lens_camera = {
	.viewplane = {
		.pixel_size = 1.0f,
		.width = DEFAULT_WIDTH,
		.height = DEFAULT_HEIGHT,
	},
	.type = thin_lens,
	.origin = {.x = 0.0f, .y = 1.0f, .z = 0.0f, .w = 0.0f},
	.direction = {.x = 0.0f, .y = 0.0f, .z = 1.0f, .w = 0.0f},
	.up = {.x = 0.0f, .y = 1.0f, .z = 0.0f, .w = 0.0f},
	.d = DEFAULT_WIDTH / 2,
	.zoom = 1.0f,
	.ratio = (float)DEFAULT_WIDTH / DEFAULT_HEIGHT,
	.normalized = FALSE,

	.lens_radius = 0.5f,
	.f = 5.0f
};

static const t_camera deafult_fisheye_camera = {
	.viewplane = {
		.pixel_size = 1.0f,
		.width = DEFAULT_WIDTH,
		.height = DEFAULT_HEIGHT,
	},
	.type = fisheye,
	.origin = { .x = 0.0f, .y = 1.0f, .z = 0.0f, .w = 0.0f },
	.direction = { .x = 0.0f, .y = 0.0f, .z = 1.0f, .w = 0.0f },
	.up = {.x = 0.0f, .y = 1.0f, .z = 0.0f, .w = 0.0f},
	.d = DEFAULT_WIDTH / 1,
	.zoom = 1.0f,
	.ratio = (float)(DEFAULT_WIDTH) / DEFAULT_HEIGHT,
	.normalized = FALSE,

	.f = 360.0f
};

static const t_material default_matte_material = {
	.type = matte,
	.color = {
		.value = 0x0000afff},
	.kd = 0.5f,
	.ka = 0.1f,
	.ks = 0.5f,
	.exp = 0.25f};

static const t_obj default_sphere = {
	.type = sphere,
	.origin = {
		.x = 0.0f,
		.y = 0.0f,
		.z = 1.0f,
		.w = 0.0f},
	.r = 1.0f,
	.r2 = 1.0f,
	.material = {.type = phong, .color = {.value = 0x000000ff}, .kd = 0.5f, .ka = 0.25f, .ks = 0.5, .exp = 10},
	.shadows = CL_TRUE};

static const t_obj default_plane = {
	.type = plane,
	.origin = {
		.x = 0.0f,
		.y = -1.0f,
		.z = 0.0f,
		.w = 0.0f},
	.direction = {.x = 0.0f, .y = -1.0f, .z = 0.0f, .w = 0.0f},
	.material = {.type = phong, .color = {.value = 0x00aaaaaa}, .kd = 0.8f, .ka = 0.25f, .ks = 0.05f, .exp = 10.0f},
	.shadows = CL_TRUE};

static const t_obj default_cylinder = {
	.type = cylinder,
	.origin = {
		.x = 2.0f,
		.y = 3.0f,
		.z = 5.0f,
		.w = 0.0f},
	.direction = {.x = 0.0f, .y = 1.0f, .z = 0.0f, .w = 0.0f},
	.r = 1.0f,
	.r2 = 1.0f,
	.maxm = 5.0f, //max height of cylinder
	.material = {.type = phong, .color = {.value = 0x001002af}, .kd = 0.6f, .ka = 0.25f, .ks = 0.2, .exp = 5},
	.shadows = CL_TRUE};

static const t_obj default_cone = {
	.type = cone,
	.origin = {
		.x = 0.0f,
		.y = 2.0f,
		.z = 5.0f,
		.w = 0.0f,
	},
	.direction = {
		.x = 0.0f,
		.y = 1.0f,
		.z = 0.0f,
		.w = 0.0f,
	},
	.angle = 60.0f * M_PI / 180.0f, //radians
	.r = 0.57735026919,
	.r2 = 1.33333333333, //tan(angle / 2) + 1
	.maxm = 3.0f,
	.minm = -3.0f,
	.material = {.type = phong, .color = {.value = 0x00ffaf}, .kd = 0.6f, .ka = 0.25f, .ks = 0.2f, .exp = 50.0f},
	.shadows = CL_TRUE};

static const t_obj default_paraboloid = {
	.type = paraboloid,
	.origin = {
		.x = 2.0f,
		.y = 1.0f,
		.z = 5.0f,
		.w = 0.0f},
	.direction = {.x = 0.0f, .y = 1.0f, .z = 0.0f, .w = 0.0f},
	.r = 0.3f,
	.minm = 0.0f,
	.maxm = 2.0f,
	.material = {.type = phong, .color = {.value = 0x05f000f}, .kd = 0.6f, .ka = 0.25f, .ks = 0.2f, .exp = 50.0f},
	.shadows = CL_TRUE};

static const t_obj default_torus = {
	.type = torus,
	.origin = {
		.x = 0.0f,
		.y = 1.0f,
		.z = 1.0f,
		.w = 0.0f},
	.direction = {.x = 0.0f, .y = 0.7071067118f, .z = 0.7071067118f, .w = 0.0f},
	.r = 2.0f,
	.r2 = 0.4f,
	.material = {.type = phong, .color = {.value = 0x00bf8f0f}, .kd = 0.6f, .ka = 0.25f, .ks = 0.2f, .exp = 50.0f},
	.shadows = CL_TRUE};

static const t_triangle default_triangle = {
	.vertex1 = {
		.x = -3.0f,
		.y = 1.0f,
		.z = -5.0f,
		.w = 0.0f},
	.vertex2 = {.x = -1.0f, .y = 1.0f, .z = 5.0f, .w = 0.0f},
	.vertex3 = {.x = -2.0f, .y = 3.0f, .z = 5.0f, .w = 0.0f},
	.vector1 = {
		.x = 2.0f,
		.y = 0.0f,
		.z = 0.0f,
		.w = 0.0f,
	},
	.vector2 = {.x = 1.0f, .y = 2.0f, .z = 0.0f, .w = 0.0f},
	.normal = {.x = 0.0f, .y = 0.0f, .z = -1.0f, .w = 0.0f},
	.material = {.color = 0x00af00af, .type = phong, .kd = 0.2, .ka = 0.25, .ks = 0.8, .exp = 10
}};
static const t_bbox default_box = {
	.min = {
		.x = 0.0f,
		.y = 0.0f,
		.z = 1.0f,
		.w = 0.0f},
	.max = {.x = 1.0f, .y = 1.0f, .z = 2.0f, .w = 0.0f}};

static const t_light default_ambient_light = {
	.type = ambient,
	.origin = {
		.x = 0.0f,
		.y = 0.0f,
		.z = 0.0f,
		.w = 0.0f}};

static const t_light default_directional_light = {
	.type = directional,
	.origin = {
		.x = 0.0f,
		.y = 0.0f,
		.z = 0.0f,
		.w = 0.0f,
	},
	.direction = {.x = 0.0f, .y = -1.0f, .z = -1.0f, .w = 0.0f},
	.ls = 3.0f,
	.color = 0x00ffffff};

static const t_light default_point_light = {
	.type = point,
	.origin = {
		.x = 0.0f,
		.y = 2.0f,
		.z = 0.0f,
		.w = 0.0f},
	.ls = 3.0f,
	.color = 0x00ffffff};

void init_func(t_scene *scene)
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

void	read_file(t_scene *scene, char *scene_file)
{
	char	*line;
	int		fd;
	int		gnl;
	int		i;

	i = -1;
	fd = fd_return(scene_file);
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
			scene_file = find_file_name(line);
			read_file(scene, scene_file);
			free(scene_file);
		}
		free(line);
	}
	if (gnl == -1)
		unable_to_read_file(scene_file);
	close(fd);
}

void	init_default_scene(t_scene *scene, t_sampler_manager *sampler_manager)
{
	// scene->camera = default_camera;

	scene->camera = default_thin_lens_camera;
	scene->camera.sampler_id = new_sampler(sampler_manager, rand_jitter, NUM_SAMPLES, DISK_SAMPLES);

	compute_uvw(&scene->camera);

	scene->nobjects = 9;
	scene->ntriangles = 1;
	scene->objects = (t_obj *)malloc(sizeof(t_obj) * (scene->nobjects + 10));
	scene->triangles = (t_triangle *)malloc(sizeof(t_triangle) * (scene->ntriangles + 10));
	scene->nlights = 2;
	scene->lights = (t_light *)malloc(sizeof(t_light) * (scene->nlights + 10));

	//default_scene
#if 1
	scene->objects[0] = default_plane;

	scene->objects[0] = default_sphere;
	scene->objects[0].origin.x = 0.0f;
	scene->objects[0].origin.y = 0.0f;
	scene->objects[0].origin.z = 0.0f;
	scene->objects[0].r = 0.1f;
	scene->objects[0].r2 = 0.01f;
	scene->objects[0].material.color.value = 0x0000ff00;

	// scene->objects[1] = default_sphere;
	// scene->objects[1].origin.x = 10.0f;
	// scene->objects[1].origin.y = 10.0f;
	// scene->objects[1].origin.z = 0.0f;
	// scene->objects[1].r = 10.0f;
	// scene->objects[1].r2 = 100.0f;
	// scene->objects[1].material.color.value = 0x003846b0;

	scene->objects[1] = default_plane;
	scene->objects[1].origin.x = 0.0f;
	scene->objects[1].origin.y = 0.0f;
	scene->objects[1].origin.z = 10.0f;
	scene->objects[1].origin.w = 0.0f;
	scene->objects[1].direction.x = 0.0f;
	scene->objects[1].direction.y = 0.0f;
	scene->objects[1].direction.z = 1.0f;
	scene->objects[1].direction.w = 0.0f;
	scene->objects[1].material.color.value = 0x00fa00af;

	scene->objects[2] = default_plane;
	scene->objects[2].origin.x = 3.0f;
	scene->objects[2].origin.y = 0.0f;
	scene->objects[2].origin.z = 0.0f;
	scene->objects[2].origin.w = 0.0f;
	scene->objects[2].direction.x = -0.86602540378f;
	scene->objects[2].direction.y = 0.0f;
	scene->objects[2].direction.z = 0.5f;
	scene->objects[2].direction.w = 0.0f;
	scene->objects[2].material.color.value = 0x0000afaf;

	scene->objects[3] = default_plane;
	scene->objects[3].origin.x = -3.0f;
	scene->objects[3].origin.y = 0.0f;
	scene->objects[3].origin.z = 0.0f;
	scene->objects[3].origin.w = 0.0f;
	scene->objects[3].direction.x = 0.86602540378f;
	scene->objects[3].direction.y = 0.0f;
	scene->objects[3].direction.z = 0.5f;
	scene->objects[3].direction.w = 0.0f;
	scene->objects[3].material.color.value = 0x00af0f00;

	scene->objects[4] = default_sphere;
	scene->objects[4].origin.x = 2.0f;
	scene->objects[4].origin.y = 4.0f;
	scene->objects[4].origin.z = 0.0f;
	scene->objects[4].r = 1.0f;
	scene->objects[4].r2 = 1.0f;
	scene->objects[4].material.color.value = 0x003846b0;

	scene->objects[5] = default_cylinder;
	scene->objects[5].origin.x = 3.0f;
	scene->objects[5].origin.y = 3.0f;
	scene->objects[5].origin.z = 5.0f;
	scene->objects[5].direction.x = 1.0f;
	scene->objects[5].direction.y = 0.0f;
	scene->objects[5].direction.z = 0.0f;
	scene->objects[5].maxm = 5.0f;

	scene->objects[6] = default_cone;
	scene->objects[6].material.color.value = 0x00ffafff;

	scene->objects[7] = default_paraboloid;

	scene->objects[8] = default_torus;
	scene->objects[8].origin.x = 0.0f;
	scene->objects[8].origin.y = 0.0f;
	scene->objects[8].origin.z = 4.0f;
	scene->objects[8].direction.x = 0.0f;
	scene->objects[8].direction.y = 0.0;
	scene->objects[8].direction.z = 1;
	scene->objects[8].r = 1.5f;
	scene->objects[8].r2 = 0.3f;
	scene->objects[8].bounding_box.max.x =
		scene->objects[8].origin.x + scene->objects[8].r + scene->objects[8].r2;
	scene->objects[8].bounding_box.max.y =
		scene->objects[8].origin.y + scene->objects[8].r + scene->objects[8].r2;
	scene->objects[8].bounding_box.max.z =
		scene->objects[8].origin.z + scene->objects[8].r + scene->objects[8].r2;
	scene->objects[8].bounding_box.min.x =
		scene->objects[8].origin.x - scene->objects[8].r - scene->objects[8].r2;
	scene->objects[8].bounding_box.min.y =
		scene->objects[8].origin.y - scene->objects[8].r - scene->objects[8].r2;
	scene->objects[8].bounding_box.min.z =
		scene->objects[8].origin.z - scene->objects[8].r - scene->objects[8].r2;

	scene->objects[9] = default_torus;
	scene->objects[9].origin.x = -2.0f;
	scene->objects[9].origin.y = 5.0f;
	scene->objects[9].origin.z = 4.0f;
	scene->objects[9].direction.x = 0.86602540378f;
	scene->objects[9].direction.y = -0.5;
	scene->objects[9].direction.z = 0;
	scene->objects[9].r = 1.5f;
	scene->objects[9].r2 = 0.3f;
	scene->objects[9].bounding_box.max.x =
		scene->objects[9].origin.x + scene->objects[9].r + scene->objects[9].r2;
	scene->objects[9].bounding_box.max.y =
		scene->objects[9].origin.y + scene->objects[9].r + scene->objects[9].r2;
	scene->objects[9].bounding_box.max.z =
		scene->objects[9].origin.z + scene->objects[9].r + scene->objects[9].r2;
	scene->objects[9].bounding_box.min.x =
		scene->objects[9].origin.x - scene->objects[9].r - scene->objects[9].r2;
	scene->objects[9].bounding_box.min.y =
		scene->objects[9].origin.y - scene->objects[9].r - scene->objects[9].r2;
	scene->objects[9].bounding_box.min.z =
		scene->objects[9].origin.z - scene->objects[9].r - scene->objects[9].r2;

	scene->triangles[0] = default_triangle;

	scene->ambient_light = (t_light){
		.type = ambient,
		.ls = 0.0f,
		.color = {
			.value = 0x00ffffff}};
	scene->lights[0] = default_point_light;

	scene->lights[1] = default_directional_light;
	scene->lights[1].ls = 0.0f;
	scene->lights[1].origin.x = INFINITY;
	scene->lights[1].origin.y = INFINITY;
	scene->lights[1].origin.z = INFINITY;

	scene->lights[2] = default_point_light;
	scene->lights[2].origin.x = -2.0f;
	scene->lights[2].origin.y = 5.0f;
	scene->lights[2].ls = 1.0f;
	//

#else
	scene->camera.viewplane.pixel_size = 0.05;
	scene->camera.d = 40;
	scene->camera.f = 50;
	scene->camera.lens_radius = 5.0f;

	scene->objects[0] = default_plane;
	scene->objects[0].origin.x = 0.0f;
	scene->objects[0].origin.y = 0.0f;
	scene->objects[0].origin.z = 0.0f;
	scene->objects[0].direction.x = 0.0f;
	scene->objects[0].direction.y = 0.0f;
	scene->objects[0].direction.z = 1.0f;
	// scene->objects[0].direction.y = 0.999f;
	// scene->objects[0].direction.z = sqrtf(1.0f - 0.999f * 0.999f);
	scene->objects[0].material.color.value = 0x0000ff00;
	scene->objects[0].material.ks = 0.00;
	scene->objects[0].material.ka = 0.00;
	scene->objects[0].material.exp = 10000;

	scene->objects[1] = default_sphere;
	scene->objects[1].origin.x = 0.0f;
	scene->objects[1].origin.y = -10.0f;
	scene->objects[1].origin.z = 50.0f;
	scene->objects[1].r = 10;
	scene->objects[1].r2 = 100;

	scene->objects[2] = default_cylinder;
	scene->objects[2].origin.x = 40.0f;
	scene->objects[2].origin.y = -10.0f;
	scene->objects[2].origin.z = 70.0f;
	scene->objects[2].maxm = 15.0f;
	scene->objects[2].r = 10.0f;
	scene->objects[2].r2 = 100.0f;
	scene->objects[2].material.color.value = 0x0026E600;

	scene->objects[3] = default_plane;
	scene->objects[3].origin.y = -100;
	scene->objects[3].direction.y = 0.99f;
	scene->objects[3].direction.z = -sqrtf(1.0f - 0.99f * 0.99f);

	scene->objects[4] = default_sphere;
	scene->objects[4].r = 10;
	scene->objects[4].r2 = 100;
	scene->objects[4].origin.x = -25.0f;
	scene->objects[4].origin.y = -10.0f;
	scene->objects[4].origin.z = 40.0f;
	scene->objects[4].material.color.value = 0x00B00B69;

	scene->nobjects = 5;

	scene->lights[0] = default_point_light;
	scene->lights[0].direction.x = -1.0f;
	scene->lights[0].direction.y = 1.0f;
	scene->lights[0].direction.z = 0.0f;
	scene->lights[0].origin.x = 0.0f;
	scene->lights[0].origin.y = 500.0f;
	scene->lights[0].origin.z = 50.0f;
	scene->lights[0].ls = 2.0f;

	scene->lights[1] = default_point_light;
	scene->lights[1].origin = default_camera.origin;
	scene->lights[1].origin.z = 50.0f;
	scene->lights[1].origin.y = -20.0f;
	scene->lights[1].origin.x = 40.0f;
	scene->lights[1].ls = 0.5f;

	scene->nlights = 2;

	scene->triangles[0] = default_triangle;

	scene->ambient_light = (t_light){
		.type = ambient,
		.ls = 0.3f,
		.color = {
			.value = 0x00ffffff}};

#endif
	return (0);
}

/**
**
** @brief
** reading scene from file or default scene
** @param scene, file
** @return ** void
*/
void	read_data(t_scene *scene, t_sampler_manager *sampler_manager, char *scene_file)
{
	if (scene_file != NULL)
	{
		init_func(scene);
		count(scene, scene_file);
		scene->objects = malloc(sizeof(t_obj) * scene->nobjects);
		scene->triangles = malloc(sizeof(t_obj) * scene->ntriangles);
		scene->nobjects = 0;
		scene->ntriangles = 0;
		read_file(scene, scene_file);
	}
	else
		init_default_scene(scene, sampler_manager);
}
