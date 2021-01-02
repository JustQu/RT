/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bvh.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmelessa <cool.3meu@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/05 19:29:26 by dmelessa          #+#    #+#             */
/*   Updated: 2020/12/20 23:13:14 by dmelessa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#define NO_INSTANCE 0xffffffff

#include <math.h>
#include <stdlib.h>

#include "bvh.h"
#include "bvh_01.h"
#include "scene.h"
#include "utils.h"
#include "rt_error.h"

void	sort_nodes(t_bvh_node *nodes, int size,
					int (*cmp)(t_bvh_node, t_bvh_node))
{
	int			l;
	int			r;
	t_bvh_node	node;
	t_bvh_node	tmp;

	if ((r = size - 1) == 0)
		return ;
	l = 0;
	node = nodes[(size + 1) / 2];
	while (l < r)
	{
		while (cmp(nodes[l], node))
			l++;
		while (cmp(node, nodes[r]))
			r--;
		if (l < r)
		{
			tmp = nodes[l];
			nodes[l++] = nodes[r];
			nodes[r--] = tmp;
		}
	}
	sort_nodes(nodes, (size + 1) / 2, cmp);
	sort_nodes(nodes + (size + 1) / 2, size / 2, cmp);
}

t_bbox	compute_bvh_node_aabb(t_bvh_node *nodes, int size)
{
	t_bbox	node_aabb;
	t_bbox	object_aabb;
	int		i;

	node_aabb.max = (cl_float4){ .x = -INFINITY, .y = -INFINITY,
								.z = -INFINITY, .w = -INFINITY };
	node_aabb.min = (cl_float4){ .x = INFINITY, .y = INFINITY,
								.z = INFINITY, .w = INFINITY };
	i = -1;
	while (++i < size)
	{
		object_aabb = nodes[i].aabb;
		node_aabb.max.x = float_max(object_aabb.max.x, node_aabb.max.x);
		node_aabb.max.y = float_max(object_aabb.max.y, node_aabb.max.y);
		node_aabb.max.z = float_max(object_aabb.max.z, node_aabb.max.z);
		node_aabb.min.x = float_min(object_aabb.min.x, node_aabb.min.x);
		node_aabb.min.y = float_min(object_aabb.min.y, node_aabb.min.y);
		node_aabb.min.z = float_min(object_aabb.min.z, node_aabb.min.z);
	}
	return (node_aabb);
}

/*
** @brief split node and objects inside
** The simplest approach. Select the longest axis
** and sort objects along this direction.
** @param node
** @param nodes
** @param size
** @return ** int
*/

int		split_bvh_node(t_bvh_node node, t_bvh_node *nodes, int size)
{
	int		split_index;
	float	length;
	int		longest_axis;

	split_index = (size + 1) / 2;
	longest_axis = 0;
	length = node.aabb.max.x - node.aabb.min.x;
	if (node.aabb.max.y - node.aabb.min.y > length)
	{
		length = node.aabb.max.y - node.aabb.min.y;
		longest_axis = 1;
	}
	if (node.aabb.max.z - node.aabb.min.z > length)
	{
		length = node.aabb.max.z - node.aabb.min.z;
		longest_axis = 2;
	}
	if (longest_axis == 0)
		sort_nodes(nodes, size, cmp_x);
	else if (longest_axis == 1)
		sort_nodes(nodes, size, cmp_y);
	else
		sort_nodes(nodes, size, cmp_z);
	return (split_index);
}

/*
** Recursive top-down building of bvh struct
*/

int		build_internal_node(t_bvh bvh, int *cur, t_bvh tmp_n, int size)
{
	int			id;
	int			nid;
	int			split;

	id = (*cur)++;
	if (size == 1)
	{
		bvh[id] = tmp_n[0];
		return (id);
	}
	bvh[id] = (t_bvh_node){.aabb = compute_bvh_node_aabb(tmp_n, size),
				.next = -1, .instance_id = -1};
	split = split_bvh_node(bvh[id], tmp_n, size);
	nid = build_internal_node(bvh, cur, tmp_n, split);
	bvh[nid].next = build_internal_node(bvh, cur, tmp_n + split, size - split);
	nid = id + 1;
	while (TRUE)
	{
		if ((nid = bvh[nid + 1].next) == -1)
			break ;
		bvh[nid].next = bvh[id + 1].next;
		if (bvh[nid].instance_id != -1)
			break ;
	}
	return (id);
}

/*
** malloc 2 times more nodes of bvh tree
*/

t_bvh	build_bvh(t_scene *scene)
{
	t_bvh				bvh;
	t_bvh				temp_nodes;
	t_instance_manager	instance_mngr;
	int					id;

	instance_mngr = scene->instance_mngr;
	bvh = ft_memalloc(instance_mngr.ninstances * 2 * sizeof(t_bvh_node));
	rt_is_dead(system_err, system_malloc_error, !bvh, "bvh.c 1");
	temp_nodes = ft_memalloc(instance_mngr.ninstances * sizeof(t_bvh_node));
	rt_is_dead(system_err, system_malloc_error, !temp_nodes, "bvh.c 2");
	id = -1;
	while (++id < instance_mngr.ninstances)
		temp_nodes[id] = (t_bvh_node){.instance_id = id,
			.aabb = instance_mngr.extra[id].aabb, .center = (cl_float3){{
				0.5f * (instance_mngr.extra[id].aabb.min.x +
					instance_mngr.extra[id].aabb.max.x),
				0.5f * (instance_mngr.extra[id].aabb.min.y +
					instance_mngr.extra[id].aabb.max.y),
				0.5f * (instance_mngr.extra[id].aabb.min.z +
					instance_mngr.extra[id].aabb.max.z)}}, .next = -1};
	id = 0;
	build_internal_node(bvh, &id, temp_nodes, instance_mngr.ninstances);
	free(temp_nodes);
	return (scene->bvh = bvh);
}
