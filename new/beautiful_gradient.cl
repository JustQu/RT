__kernel void render(__global int *c, int offset)
{
	const int work_item_id = get_global_id(0);
	int x = work_item_id % 800;
	int y = work_item_id / 800;
	int fx = (float)x / 800 * 255;
	int fy = (float)y / 640 * 255;
	int fz = 0;
	c[work_item_id] = fx << 16 | fy << 8 | fz;
}

__kernel void render2(__global int *c)
{
	const int work_item_id = get_global_id(0);
	int x = work_item_id % 800;
	int y = work_item_id / 800;
	int fx = (float)x / (float)800 * 255;
	int fy = (float)y / (float)640 * 255;
	int fz = 32;
	c[work_item_id] = (fx << 16) | (fy << 8) | fz;
}
