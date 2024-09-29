/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bel-oirg <bel-oirg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/21 00:23:53 by bel-oirg          #+#    #+#             */
/*   Updated: 2024/09/29 09:50:11 by bel-oirg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub_bonus.h"

static void	error(void)
{
	puts(mlx_strerror(mlx_errno));
	exit(EXIT_FAILURE);
}

void	sprited(t_mlx *raw)
{
	char	*c_frame;
	char	*weapon;
	char	*full_path;
	int		frame;

	frame = -1;
	while (++frame < SP_FRAMES)
	{
		c_frame = ft_itoa(frame);
		weapon = ft_strjoin("./sprite_png/", c_frame);
		full_path = ft_strjoin(weapon, ".png");
		raw->sprite->txt[frame] = mlx_load_png(full_path);
		if (!raw->sprite->txt[frame])
			error();
	}
	raw->sprite->frame = 0;
	raw->sprite->is_sp = 0;
}

uint32_t	get_col(mlx_texture_t *texture, int x, int y)
{
	int		pixel_index;
	uint8_t	alpha;
	uint8_t	red;
	uint8_t	green;
	uint8_t	blue;

	pixel_index = (y * texture->width + x) * 4;
	alpha = texture->pixels[pixel_index + 0];
	red = texture->pixels[pixel_index + 1];
	green = texture->pixels[pixel_index + 2];
	blue = texture->pixels[pixel_index + 3];
	return ((alpha << 24) | (red << 16) | (green << 8) | blue);
}

void	frame_spirit(t_mlx *raw, int is_static)
{
	int				x;
	int				y;
	mlx_texture_t	*texture;
	int				frame;
	uint32_t		color;

	y = -1;
	frame = 0;
	if (!is_static)
		frame = raw->sprite->frame;
	texture = raw->sprite->txt[frame];
	while (++y < (int)texture->height)
	{
		x = -1;
		while (++x < (int)texture->width)
		{
			color = get_col(texture, x, y);
			if (color && color != 0xFFFFFF00)
				my_mlx_pixel_put(raw, (S_W - texture->width) / 2 + x, S_H
					- texture->height + y, get_col(texture, x, y));
		}
	}
}

void	render_sp(t_mlx *raw)
{
	if (!raw->sprite->is_sp)
		return (frame_spirit(raw, 1));
	if (raw->sprite->frame < SP_FRAMES)
	{
		frame_spirit(raw, 0);
		raw->sprite->frame++;
	}
	else
	{
		raw->sprite->is_sp = 0;
		raw->sprite->frame = 0;
	}
}
