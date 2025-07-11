/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   controls.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psantos- <psantos-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/09 01:16:54 by psantos-          #+#    #+#             */
/*   Updated: 2025/07/10 01:28:53 by psantos-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void	ft_free_map(t_map *map)
{
	int	y;
	int	x;

	if (map && map->array)
	{
		y = 0;
		while (y < map->height)
		{
			if (map->array[y])
			{
				x = 0;
				while (x < map->width)
				{
					if (map->array[y][x])
						free(map->array[y][x]);
					x++;
				}
				free(map->array[y]);
			}
			y++;
		}
		free(map->array);
	}
	if (map)
		free(map);
}

void	ft_return_error(t_fdf **env)
{
	if (env && *env)
	{
		if ((*env)->img)
			mlx_destroy_image((*env)->mlx, (*env)->img);
		if ((*env)->win)
			mlx_destroy_window((*env)->mlx, (*env)->win);
		if ((*env)->map)
			ft_free_map((*env)->map);
		destroy_display((*env)->mlx);
		free((*env)->mlx);
		free(*env);
	}
	exit(1);
}

int	ft_close_win(void *params)
{
	t_fdf	*env;

	env = (t_fdf *)params;
	ft_return_error(&env);
	return (0);
}

int	ft_key_press(int keycode, void *params)
{
	t_fdf	*env;

	env = (t_fdf *)params;
	if (keycode == ESCAPE)
		ft_close_win(env);
	return (0);
}

void	ft_hook_controls(t_fdf *env)
{
	mlx_key_hook(env->win, ft_key_press, env);
	mlx_hook(env->win, 17, 0, ft_close_win, env);
}
