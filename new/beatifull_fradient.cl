__kernel void(__global int *c, const int a)
{
	const int work_item_id = get_global_id(0);
	int x = work_item_id % 1920;
	int y = work_item_id / 1920;
	int fx = (float)x  / (float)1920 * 255;
	int fy = (float)y / (float) 1080 * 255;
	int fz = 0;
	c[work_item_id] = fx << 16 | fy << 8 | fz;
}