/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hello.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dwalda-r <dwalda-r@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/13 09:55:21 by dwalda-r          #+#    #+#             */
/*   Updated: 2020/01/15 15:53:52 by dwalda-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <OpenCL/opencl.h>
#include "../libft/includes/libft.h"
#define DATA_SIZE (1024)
#define MAX_SOURCE_SIZE (0x100000)
size_t read_kernel(char *file_name, char **str);

int main(void) {
	int i = 0;
	const int LIST_SIZE = 1024;
	int *A = (int *)malloc((LIST_SIZE) * sizeof(int));
	int *B = (int *)malloc((LIST_SIZE)* sizeof(int));
	while(i < LIST_SIZE)
	{
		A[i] = i;
		B[i] = LIST_SIZE - i;
		i++;
	}
	char *source_str;
	size_t source_size = read_kernel("vector_add_kernel.cl", &source_str);
	// FILE *fp;
    // char *source_str;
    // size_t source_size;
 
    // fp = fopen("vector_add_kernel.cl", "r");
    // if (!fp) {
    //     fprintf(stderr, "Failed to load kernel.\n");
    //     exit(1);
    // }
    // source_str = (char*)malloc(MAX_SOURCE_SIZE);
    // source_size = fread( source_str, 1, MAX_SOURCE_SIZE, fp);
    // fclose( fp );
	// printf("%d", ft_strcmp(ss, source_str));
	cl_platform_id pl_id = NULL;
	cl_device_id de_id = NULL;
	cl_uint ret_num_devices;
	cl_uint ret_num_platforms;
	cl_int ret = clGetPlatformIDs(1, &pl_id, &ret_num_platforms);
	ret = clGetDeviceIDs(pl_id, CL_DEVICE_TYPE_GPU, 1, &de_id, &ret_num_devices);

	//создание контекста 
	cl_context context = clCreateContext(NULL, 1, &de_id, NULL, NULL, &ret);
	//создание очереди команд
	cl_command_queue command_queue = clCreateCommandQueue(context, de_id, 0, &ret);
	//выделение памяти для переменных
	cl_mem a_mem_obj = clCreateBuffer(context, CL_MEM_READ_ONLY, LIST_SIZE * sizeof(int), NULL, &ret);
	cl_mem b_mem_obj = clCreateBuffer(context, CL_MEM_READ_ONLY, LIST_SIZE * sizeof(int), NULL, &ret);
	cl_mem c_mem_obj = clCreateBuffer(context, CL_MEM_WRITE_ONLY, LIST_SIZE * sizeof(int), NULL, &ret);
	//копирование переменных в буферы
	ret = clEnqueueWriteBuffer(command_queue, a_mem_obj, CL_TRUE, 0, LIST_SIZE * sizeof(int), A, 0, NULL, NULL);
	ret = clEnqueueWriteBuffer(command_queue, b_mem_obj, CL_TRUE, 0, LIST_SIZE * sizeof(int), B, 0, NULL, NULL);
	//создание программы из кернел исходника
	cl_program program = clCreateProgramWithSource(context, 1, (const char **)&source_str, (const size_t *)&source_size, &ret);
	
	ret = clBuildProgram(program, 1, &de_id, NULL, NULL, NULL);

	cl_kernel kernel = clCreateKernel(program, "vector_add", &ret);
	
	ret = clSetKernelArg(kernel, 0, sizeof(cl_mem), (void *)&a_mem_obj);
	ret = clSetKernelArg(kernel, 1, sizeof(cl_mem), (void *)&b_mem_obj);
	ret = clSetKernelArg(kernel, 2, sizeof(cl_mem), (void *)&c_mem_obj);

	size_t global_item_size = LIST_SIZE;
	size_t local_item_size = 64;
	ret = clEnqueueNDRangeKernel(command_queue, kernel, 1, NULL, &global_item_size, &local_item_size, 0, NULL, NULL);

	int *C = (int *)malloc(sizeof(int) * LIST_SIZE);
	ret = clEnqueueReadBuffer(command_queue, c_mem_obj, CL_TRUE, 0, LIST_SIZE * sizeof(int), C, 0, NULL, NULL);

	i = 0;
	while (i < LIST_SIZE)
	{
			printf("%d + %d = %d\n", A[i], B[i], C[i]);
		i++;
	}

	ret = clFlush(command_queue);
	ret = clFinish(command_queue);
	ret = clReleaseKernel(kernel);
	ret = clReleaseProgram(program);
	ret = clReleaseMemObject(a_mem_obj);
	ret = clReleaseMemObject(b_mem_obj);
	ret = clReleaseMemObject(c_mem_obj);
	ret = clReleaseCommandQueue(command_queue);
	ret = clReleaseContext(context);
	free(A);
	free(B);
	free(C);
	return 0;
}