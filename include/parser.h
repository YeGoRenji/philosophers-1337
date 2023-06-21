/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylyoussf <ylyoussf@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/20 20:51:04 by ylyoussf          #+#    #+#             */
/*   Updated: 2023/06/21 02:19:37 by ylyoussf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include <stdio.h>
# include <stdint.h>

typedef struct s_info
{
	int	nb_of_philos;
	int	time_to_eat;
	int	time_to_die;
	int	time_to_sleep;
	int	time_min_eat;
}				t_info;


int	ft_atoi(const char *str);
int	parse_args(int nb_args, char **args, t_info *info);

#endif
