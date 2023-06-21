/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylyoussf <ylyoussf@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/20 20:51:17 by ylyoussf          #+#    #+#             */
/*   Updated: 2023/06/21 02:15:44 by ylyoussf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/parser.h"

int	parse_args(int nb_args, char **args, t_info *info)
{
	info->nb_of_philos = ft_atoi(args[1]);
	info->time_to_die = ft_atoi(args[2]);
	info->time_to_eat = ft_atoi(args[3]);
	info->time_to_sleep = ft_atoi(args[4]);
	if (nb_args == 5)
		info->time_min_eat = ft_atoi(args[5]);
	else
		info->time_min_eat = -1;
	return (0);
}
