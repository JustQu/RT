@echo off

mkdir .\build
pushd .\build
cl /FC /Zi ..\main.c -I ../../include ^
					-I ../../Libs/libft/includes ^
					-I ../../Libs/SDL/include ^
					../../Libs/libft/libft.lib ^
					..\..\Libs\SDL\lib\win64\SDL2.lib ^
					"C:\Program Files\NVIDIA GPU Computing Toolkit\CUDA\v10.2\lib\x64\OpenCL.lib"

popd
