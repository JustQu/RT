#include "../includes/rt.h"

void	quit(char *s)
{
	printf("%s: %s\n", s, SDL_GetError());
	SDL_Quit();
	exit(1);
}

void	print_usage(void)
{
	ft_putendl("Usage ./rt [name_of_scene]");
	exit(0);
}

int		fd_return(char *name)
{
	int		fd;

	if ((fd = open(name, O_RDONLY)) < 0)
	{
		ft_putendl("unable to open file");
		exit(1);
	}
	return (fd);
}

void rtCycle(t_rt *rt)
{
	SDL_Event	e;
	t_bool		quit;

	quit = FALSE;
	rt->sdl->tex = SDL_CreateTexture(rt->sdl->ren, SDL_PIXELFORMAT_ARGB8888, SDL_TEXTUREACCESS_STREAMING, WIN_W, WIN_H);
	SDL_UpdateTexture(rt->sdl->tex, NULL, rt->img, sizeof(Uint32) * WIN_W);
	SDL_RenderClear(rt->sdl->ren);
	SDL_RenderCopy(rt->sdl->ren, rt->sdl->tex, NULL, NULL);
	SDL_RenderPresent(rt->sdl->ren);
	while (!quit)
	{
		while(SDL_PollEvent(&e))
		{
			if (e.type == SDL_QUIT)
				quit = 1;
		}
		SDL_Delay(1000);
	}
}

void	init_sdl(t_rt *rt)
{
	t_sdl			*sdl;
	Uint32			ren_flags;

	sdl = (t_sdl*)malloc(sizeof(t_sdl));
	ren_flags = SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC;
	if (SDL_Init(SDL_INIT_VIDEO) != 0)
		quit("SDL_Init Error");
	if (!(sdl->win =SDL_CreateWindow("I am trying :)", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WIN_W, WIN_H, SDL_WINDOW_SHOWN)))
		quit("SDL_CreateWindow Error");
	if (!(sdl->ren = SDL_CreateRenderer(sdl->win, -1, ren_flags)))
	{
		SDL_DestroyWindow(sdl->win);
		quit("SDL_CreateRenderer Error");
	}
	rt->sdl = sdl;
}

int		main(int ac, char *av[])
{
	t_rt	*rt;

	if (ac != 2)
		print_usage();
	if (!(rt = (t_rt*)malloc(sizeof(t_rt))))
		exit(1);
	rt->img = (Uint32*)malloc(sizeof(Uint32) * WIN_SIZE);
	rt->name = av[1];
	init_scene(rt);
	open_cl(rt->img, rt->cam, rt->obj, rt->num_obj);
	init_sdl(rt);
	rtCycle(rt);
	SDL_DestroyTexture(rt->sdl->tex);
	SDL_DestroyRenderer(rt->sdl->ren);
	SDL_DestroyWindow(rt->sdl->win);
	SDL_Quit();
	return (0);
}
