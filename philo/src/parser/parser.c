/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylyoussf <ylyoussf@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/20 20:51:17 by ylyoussf          #+#    #+#             */
/*   Updated: 2023/07/03 21:42:12 by ylyoussf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/parser.h"


int	handle_int(char *str_number, int len)
{
	char	*max_min_str;

	max_min_str = "2147483647";
	if (*str_number == '-' || *str_number == '+')
		if (*str_number++ == '-')
			max_min_str = "2147483648";
	if (len > 10 || ft_memcmp(str_number, max_min_str, len) > 0)
		return (0);
	return (1);
}

bool	is_valid(char *arg)
{
	int		len;
	char	*tmp;
	int		still_zero;

	len = 0;
	tmp = arg;
	still_zero = 1;
	while (*arg == ' ')
		arg++;
	if (*arg == '-')
		return (false);
	else if (*arg == '+')
		arg++;
	while (*arg)
	{
		if (!ft_isdigit(*arg++))
			return (false);
		if (*arg != '0')
			still_zero = 0;
		len += !still_zero;
	}
	if (len >= 10)
		return (handle_int(tmp, len));
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
