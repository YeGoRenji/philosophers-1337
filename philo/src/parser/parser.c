/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylyoussf <ylyoussf@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/20 20:51:17 by ylyoussf          #+#    #+#             */
/*   Updated: 2023/06/27 18:26:30 by ylyoussf         ###   ########.fr       */
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

void	print_error(void)
{
	write(2, "Error: Invalid Arg\n", 19);
}

int	parse_args(int nb_args, char **args, t_info *info)
{
	int	*struc_members;
	int	i;

	if (!check_args(nb_args, args))
		return (print_error(), 0);
	struc_members = (int *)info;
	i = 0;
	while (i < nb_args)
	{
		struc_members[i] = ft_atoi(args[i]);
		if (struc_members[i] == 0)
			return (print_error(), 0);
		i++;
	}
	if (nb_args != 5)
		info->min_eats = -1;
	info->stop = false;
	return (1);
}
