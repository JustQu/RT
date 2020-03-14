#include "rt.h"

static const t_camera	camera_default = {
	.origin = {
		.x = 0.0f,
		.y = 3.0f,
		.z = -2.0f,
		.w = 0.0f
	},
	.direction = {
		.x = 0.0f,
		.y = 0.0f,
		.z = 1.0f,
		.w = 0.0f
	},
	.ratio = (float)DEFAULT_WIDTH / (float)DEFAULT_HEIGHT,
	.inv_w = 1.0f / DEFAULT_WIDTH,
	.inv_h = 1.0f / DEFAULT_HEIGHT,
	.angle = 1.7320508757,
	.fov = 120
};

static const t_material	default_matte_material = {
	.type = matte,
	.color = {
		.value = 0x0000afff
	},
	.kd = 0.5f,
	.ka = 0.1f,
	.ks = 0.5f,
	.exp = 0.25f
};

static const t_obj default_sphere = {
	.type = sphere,
	.origin = {
		.x = 0.0f,
		.y = 0.0f,
		.z = 1.0f,
		.w = 0.0f},
	.r = 1.0f,
	.r2 = 1.0f,
	.material = {
		.type = phong,
		.color = {.value = 0x000000ff},
		.kd = 0.5f,
		.ka = 0.25f,
		.ks = 0.5,
		.exp = 10
	}};

static const t_obj default_plane = {
	.type = plane,
	.origin = {
		.x = 0.0f,
		.y = -1.0f,
		.z = 0.0f,
		.w = 0.0f},
	.direction = {.x = 0.0f, .y = -1.0f, .z = 0.0f, .w = 0.0f},
	.material = {
		.type = phong,
		.color = {.value = 0x00148869},
		.kd = 0.6f,
		.ka = 0.25f,
		.ks = 0.2f,
		.exp = 50.0f
	},
	.shadows = CL_TRUE
};

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
	.maxm = 0.0f, //max height of cylinder
	.material = {.type = phong, .color = {.value = 0x001002af}, .kd = 0.6f, .ka = 0.25f, .ks = 0.2, .exp = 5},
	.shadows = CL_TRUE
};

static const t_obj default_cone = {
	.type = cone,
	.origin = {
		.x = 0.0f,
		.y = 1.0f,
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
	.maxm = 0.0f,
	.minm = 0.0f,
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
	.material = {
		.type = phong,
		.color = {.value = 0x00bf8f0f},
		.kd = 0.6f,
		.ka = 0.25f,
		.ks = 0.2f,
		.exp = 50.0f
	},
	.shadows = CL_TRUE
};

static const t_triangle	default_triangle = {
	.vertex1 = {
		.x = -3.0f,
		.y = 1.0f,
		.z = 5.0f,
		.w = 0.0f
	},
	.vertex2 = {
		.x = -1.0f,
		.y = 1.0f,
		.z = 5.0f,
		.w = 0.0f
	},
	.vertex3 = {
		.x = -2.0f,
		.y = 3.0f,
		.z = 5.0f,
		.w = 0.0f
	},
	.vector1 = {
		.x = 2.0f,
		.y = 0.0f,
		.z = 0.0f,
		.w = 0.0f,
	},
	.vector2 = {
		.x = 1.0f,
		.y = 2.0f,
		.z = 0.0f,
		.w = 0.0f
	},
	.normal = {
		.x = 0.0f,
		.y = 0.0f,
		.z = -1.0f,
		.w = 0.0f
	},
	.material = {
		.color = 0x00af00af,
		.type = phong,
		.kd = 0.2,
		.ka = 0.25,
		.ks = 0.8,
		.exp = 10
	}
};

static const t_bbox	default_box = {
	.min ={
		.x = 0.0f,
		.y = 0.0f,
		.z = 1.0f,
		.w = 0.0f
	},
	.max = {
		.x = 1.0f,
		.y = 1.0f,
		.z = 2.0f,
		.w = 0.0f
	}
};

static const t_light	default_ambient_light = {
	.type = ambient,
	.origin = {
		.x = 0.0f,
		.y = 0.0f,
		.z = 0.0f,
		.w = 0.0f
	}
};

static const t_light	default_directional_light = {
	.type = directional,
	.origin = {
		.x = 0.0f,
		.y = 0.0f,
		.z = 0.0f,
		.w = 0.0f,
	},
	.direction = {
		.x = 0.0f,
		.y = -1.0f,
		.z = -1.0f,
		.w = 0.0f
	},
	.ls = 3.0f,
	.color = 0x00ffffff
};

static const t_light	default_point_light = {
	.type = point,
	.origin = {
		.x = 0.0f,
		.y = 3.0f,
		.z = 0.0f,
		.w = 0.0f
	},
	.ls = 3.0f,
	.color = 0x00ffffff
};

/**
** @TODO: reading scene from file or default scene
** @brief
** init scene
** @param scene
** @return ** int
*/
int read_data(t_scene *scene)
{
	scene->camera = camera_default;
	scene->nobjects = 10;
	scene->ntriangles = 1;
	scene->objects = (t_obj *)malloc(sizeof(t_obj) * (scene->nobjects + 9));
	scene->triangles = (t_triangle *)malloc(sizeof(t_triangle) * scene->ntriangles);
	scene->nlights = 3;
	scene->lights = (t_light *)malloc(sizeof(t_light) * (scene->nlights + 1));

	//default_scene
	scene->objects[0] = default_plane;

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
	scene->objects[4].origin.x = 5.0f;
	scene->objects[4].origin.y = 5.0f;
	scene->objects[4].origin.z = 7.0f;
	scene->objects[4].r = 2.0f;
	scene->objects[4].r2 = 4.0f;
	scene->objects[4].material.color.value = 0x003846b0;

	scene->objects[5] = default_cylinder;
	scene->objects[5].origin.x = 3.0f;
	scene->objects[5].origin.y = 3.0f;
	scene->objects[5].origin.z = 5.0f;
	scene->objects[5].direction.x = 1.0f;
	scene->objects[5].direction.y = 0.0f;
	scene->objects[5].direction.z = 0.0f;
	scene->objects[5].maxm = 0.0f;

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
		.ls = 0.1f,
		.color = {
			.value = 0x00ffffff
		}
	};
	scene->lights[0] = default_point_light;

	scene->lights[1] = default_directional_light;
	scene->lights[1].origin.x = INFINITY;
	scene->lights[1].origin.y = INFINITY;
	scene->lights[1].origin.z = INFINITY;

	scene->lights[2] = default_point_light;
	scene->lights[2].origin.x = -2.0f;
	scene->lights[2].origin.y = 1.0f;
	scene->lights[2].ls = 1.0f;
	//

	return (0);
}
