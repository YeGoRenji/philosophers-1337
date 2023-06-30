/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylyoussf <ylyoussf@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/20 20:51:17 by ylyoussf          #+#    #+#             */
/*   Updated: 2023/06/29 19:01:14 by ylyoussf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/parser.h"

bool	check_nb_args(int argc)
{
	if (argc != 5 && argc != 6)
	{
		printf("Usage: ./philo #philos T_die T_eat T_sleep [min_eats_top]\n");
		return (false);
	}
	return (true);
}

bool	is_valid(char *arg)
{
	while (*arg == ' ')
		arg++;
	if (*arg == '-')
		return (false);
	else if (*arg == '+')
		arg++;
	if (!ft_isdigit(*arg))
		return (false);
	return (true);
}

bool	check_args(int nb_args, char **args)
{
	while (nb_args--)
		if (!is_valid(args[nb_args]))
			return (false);
	return (true);
}

void	print_error(void)
{
	write(2, "Error: Invalid Arg\n", 19);
}

bool	parse_args(int nb_args, char **args, t_info *info)
{
	int	*struc_members;
	int	i;

	if (!check_args(nb_args, args))
		return (print_error(), false);
	struc_members = (int *)info;
	i = 0;
	while (i < nb_args)
	{
		struc_members[i] = ft_atoi(args[i]);
		if (struc_members[i] == 0)
			return (print_error(), false);
		i++;
	}
	if (nb_args != 5)
		info->min_eats = -1;
	info->stop = false;
	return (true);
}
