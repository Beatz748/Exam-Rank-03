#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

char	*image;
int		width, height;
float	x, y, w, h;
char	pixel, backside, rectangle;

int		ft_hit(float i, float j)
{
	if (i < x || i > x + w || j < y || j > y + h)
		return (0);
	if (i - x < 1 || x + w - i < 1 || j - y < 1 || y + h - j < 1)
		return (2);
	return (1);
}

void	ft_correct()
{
	int	i;
	int	j;
	int	hit;

	i = -1;
	while (++i < width)
	{
		j = -1;
		while (++j < height)
		{
			hit = ft_hit((float)i, (float)j);
			if (hit == 2 || (hit == 1 && rectangle == 'R'))
				image[i + j * width] = pixel;
		}
	}
}

int		ft_parser(FILE *file)
{
	int	ret, i;

	i = 0;
	if (fscanf(file, "%d %d %c\n", &width, &height, &backside) != 3)
		return (1);
	if (width > 300 || width < 1 || height > 300 || height < 1)
		return (1);
	image = malloc(width * height);
	if (image == NULL)
		return (1);
	while (i < height * width)
		image[i++] = backside;
	while ((ret = fscanf(file, "%c %f %f %f %f %c\n", &rectangle, &x, &y, &w, &h, &pixel)) == 6)
	{
		if (w <= 0 || h <= 0 || (rectangle != 'r' && rectangle != 'R'))
			return (1);
		ft_correct();
	}
	if (ret != -1)
		return (1);
	return (0);
}

void	ft_drawing()
{
	int	i;

	i = -1;
	while(++i < height)
	{
		write(1, image + i * width, width);
		write(1, "\n", 1);
	}
}

int		main(int ac, char **av)
{
	FILE *file;

	if (ac != 2)
	{
		write(1, "Error: argumentn", 16);
		return (1);
	}
	if (!(file = fopen(av[1], "r")) || ft_parser(file))
	{
		write(1, "Error: Operation file corrupted\n", 32);
		return (1);
	}
	ft_drawing();
	free(image);
	fclose(file);
	return (0);
}
