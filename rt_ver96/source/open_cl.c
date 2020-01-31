#include "../includes/rt.h"

void    open_cl(Uint32 *img, t_cam cam, t_obj *obj, unsigned int num)
{
    cl_platform_id platform_id = NULL;
    cl_device_id device_id = NULL;   
    cl_uint err_num_devices;
    cl_uint err_num_platforms;
    cl_int err = clGetPlatformIDs(1, &platform_id, &err_num_platforms);
    err = clGetDeviceIDs( platform_id, CL_DEVICE_TYPE_DEFAULT, 1, &device_id, &err_num_devices);

    cl_context context = clCreateContext( NULL, 1, &device_id, NULL, NULL, &err);
    cl_command_queue command_queue = clCreateCommandQueue(context, device_id, 0, &err);
    cl_mem img_cl = clCreateBuffer(context, CL_MEM_WRITE_ONLY, WIN_SIZE * sizeof(int), NULL, &err);
    cl_mem obj_cl = clCreateBuffer(context, CL_MEM_READ_ONLY, num * sizeof(t_obj), NULL, &err);
    err = clEnqueueWriteBuffer(command_queue, obj_cl, CL_TRUE, 0,
        num * sizeof(t_obj), obj, 0, NULL, NULL);
    ft_clerror(err);
    cl_program program = create_program(context);

    err = clBuildProgram(program, 1, &device_id, "-I ./includes", NULL, NULL);
        size_t len = 0;
	err = CL_SUCCESS;
	err = clGetProgramBuildInfo(program, device_id, CL_PROGRAM_BUILD_LOG, 0, NULL, &len);
	char *buffer = calloc(len, sizeof(char));
	err = clGetProgramBuildInfo(program, device_id, CL_PROGRAM_BUILD_LOG, len, buffer, NULL);
	printf("%s",buffer);

    cl_kernel kernel = clCreateKernel(program, "kernel_main", &err);
    err = clSetKernelArg(kernel, 0, sizeof(cl_mem), (void *)&img_cl);
    ft_clerror(err);
    err = clSetKernelArg(kernel, 1, sizeof(t_cam), (void *)&cam);
    ft_clerror(err);
    err = clSetKernelArg(kernel, 2, sizeof(cl_mem), (void *)&obj_cl);
    ft_clerror(err);
    err = clSetKernelArg(kernel, 3, sizeof(unsigned int), (void *)&num);
    ft_clerror(err);
 
    size_t global_item_size = WIN_SIZE; // Process the entire lists
    size_t local_item_size = DIVIDE_SIZE; // Divide work items into groups of 64
    err = clEnqueueNDRangeKernel(command_queue, kernel, 1, NULL, 
        &global_item_size, &local_item_size, 0, NULL, NULL);
    ft_clerror(err);

    err = clEnqueueReadBuffer(command_queue, img_cl, CL_TRUE, 0, WIN_SIZE * sizeof(int), img, 0, NULL, NULL);
    ft_clerror(err);

    err = clFlush(command_queue);
    err = clFinish(command_queue);
    err = clReleaseKernel(kernel);
    err = clReleaseProgram(program);
    err = clReleaseMemObject(img_cl);
    err = clReleaseMemObject(obj_cl);
    err = clReleaseCommandQueue(command_queue);
    err = clReleaseContext(context);
}
