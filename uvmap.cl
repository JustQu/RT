__kernel void render_kernel(__global float3 *output)
{
 const int work_item_id = get_global_id(0); 
 int x = work_item_id % 1920;
 int y = work_item_id / 1920;
 int fx = (float)x / (float)1920 * 255;
 int fy = (float)y / (float)1080 * 255;
 output[work_item_id] = (float3)(fx, fy, 0); 
}
