rem ===================build rt on windows using nvidia opencl lib===============
@echo off

mkdir .\build
pushd .\build
cl  /wd4204 /wd4996 /wd4706 /W4 /WX -FC -Zi /D CL_TARGET_OPENCL_VERSION=220^
					..\srcs\main.c ..\srcs\*.c ^
					-I ../include ^
					-I ../Libs/libft/includes ^
					-I ../Libs ^
					-I ../Libs/libft ^
					-I ../Libs/SDL2 ^
					-I ../Libs/SDL2_image/include ^
					-I ../Libs/SDL2_ttf/include ^
					-I ../Libs/SDL2_gfx ^
					/link /SUBSYSTEM:CONSOLE ^
					../Libs/libft/libft.lib ^
					../Libs\SDL2\lib\win64\SDL2main.lib ^
					../Libs\SDL2\lib\win64\SDL2.lib^ ../Libs\SDL2_image\lib\x64\SDL2_image.lib^
					../Libs\SDL2_ttf\lib\x64\SDL2_ttf.lib^
					"C:\Program Files\NVIDIA GPU Computing Toolkit\CUDA\v10.2\lib\x64\OpenCL.lib"^
					"Shell32.lib"
rem /link /SUBSYSTEM:CONSOLE ^ ..\srcs\*.c
rem /MDd /W4 /D_CRTDBG_MAP_ALLOC /EHsc /wd4204 /wd4996 /wd4706 /W4 /WX -
popd
