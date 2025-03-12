/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_dir.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aakhrif <aakhrif@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 06:25:58 by aakhrif           #+#    #+#             */
/*   Updated: 2025/03/12 06:26:51 by aakhrif          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	ray_facing_north(double ray_angle)
{
	ray_angle = normalize_angle(ray_angle);
	return (ray_angle > PI && ray_angle < 1.5 * PI);
}

int	ray_facing_south(double ray_angle)
{
	ray_angle = normalize_angle(ray_angle);
	return (ray_angle > 0.5 * PI && ray_angle < PI);
}

int	ray_facing_east(double ray_angle)
{
	ray_angle = normalize_angle(ray_angle);
	return (ray_angle < 0.5 * PI || ray_angle > 1.5 * PI);
}

int	ray_facing_west(double ray_angle)
{
	ray_angle = normalize_angle(ray_angle);
	return (ray_angle > 0.5 * PI);
}
