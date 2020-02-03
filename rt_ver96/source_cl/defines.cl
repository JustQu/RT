# define WIN_W 1024
# define WIN_H 720
# define WIN_SIZE WIN_H * WIN_W

# define REFLECTIONS 4

# define CONE		0
# define CYLINDER	1
# define CIRCLE		2
# define PLANE		3
# define SPHERE		4
# define LIGHT		5

typedef struct	s_cam
{
	float3		pnt;
	float3		dir;
}				t_cam;

typedef	struct	s_obj
{
	int			type;
	float3		pnt;
	float3		dir;
	float		r;
	int			clr;
	float		dif;
	float		ref;
}				t_obj;

t_obj			closest_figure(t_cam ray, __global const t_obj *obj, const int n);
