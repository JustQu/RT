/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   object_initiation.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmelessa <dmelessa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/13 15:35:10 by dwalda-r          #+#    #+#             */
/*   Updated: 2019/09/20 11:30:29 by dmelessa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

void		init_sphere(t_list *t, t_obj *p)
{
	t_color		dcolor;
	t_sphere	*sp;

	dcolor.color = 0x96d38c;
	p->type = sphere;
	sp = (t_sphere *)malloc(sizeof(t_sphere));
	p->data = sp;
	sp->radius = read_fparam(t->content, "radius", 0.2f);
	read_vec3_param(t->content, p->origin, "origin", (t_vec3){0.f, 0.0f, 3.0f});
	sp->radius2 = sp->radius * sp->radius;
	p->mat = read_material(dcolor);
}

void		init_plane(t_list *t, t_obj *p)
{
	t_color		dcolor;
	t_plane		*pl;

	dcolor.color = 0xc4def6;
	p->type = plane;
	pl = (t_plane *)malloc(sizeof(t_sphere));
	p->data = pl;
	read_vec3_param(t->content, pl->nv, "nv", (t_vec3){0.0f, -1.0f, 0.0f});
	vec3_normalize(pl->nv);
	read_vec3_param(t->content, p->origin, "origin", (t_vec3){0.f, -1.0f, 0.f});
	p->mat = read_material(dcolor);
}

void		init_cone(t_list *t, t_obj *p)
{
	t_color		dcolor;
	t_cone		*cn;

	dcolor.color = 0x213458;
	p->type = cone;
	cn = (t_cone *)malloc(sizeof(t_cone));
	p->data = cn;
	read_vec3_param(t->content, p->origin, "origin", (t_vec3){0.f, 0.0f, 4.0f});
	read_vec3_param(t->content, cn->dir, "direction", RTM_YUP);
	vec3_normalize(cn->dir);
	cn->angle = read_fparam(t->content, "angle", 0.5f);
	cn->k = tanf(cn->angle);
	cn->k2 = 1 + cn->k * cn->k;
	p->mat = read_material(dcolor);
}

void		init_cylinder(t_list *t, t_obj *p)
{
	t_color		dcolor;
	t_cylinder	*cl;

	dcolor.color = 0xffd464;
	p->type = cylinder;
	cl = (t_cylinder *)malloc(sizeof(t_cylinder));
	p->data = cl;
	read_vec3_param(t->content, p->origin, "origin", (t_vec3){0.f, 0.0f, 4.0f});
	read_vec3_param(t->content, cl->dir, "direction", RTM_YUP);
	vec3_normalize(cl->dir);
	cl->radius = read_fparam(t->content, "radius", 0.3f);
	p->mat = read_material(dcolor);
}
