/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylyoussf <ylyoussf@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/20 20:51:17 by ylyoussf          #+#    #+#             */
/*   Updated: 2023/06/22 12:49:41 by ylyoussf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/parser.h"

int	is_valid(char *arg)
{
	while (*arg == ' ')
		arg++;
	if (*arg == '-')
		return (0);
	else if (*arg == '+')
		arg++;
	if (!ft_isdigit(*arg))
		return (0);
	return (1);
}

int	check_args(int nb_args, char **args)
{
	while (nb_args--)
		if (!is_valid(args[nb_args]))
			return (0);
	return (1);
}

int	parse_args(int nb_args, char **args, t_info *info)
{
	if (!check_args(nb_args, args))
		(write(2, "Error: Invalid Arg\n", 19), exit(-1));
	info->nb_of_philos = ft_atoi(args[0]);
	info->time_to_die = ft_atoi(args[1]);
	info->time_to_eat = ft_atoi(args[2]);
	info->time_to_sleep = ft_atoi(args[3]);
	if (nb_args == 5)
		info->min_eats = ft_atoi(args[4]);
	else
		info->min_eats = -1;
	return (1);
}
