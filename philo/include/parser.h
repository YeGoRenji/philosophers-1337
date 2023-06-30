/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylyoussf <ylyoussf@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/20 20:51:04 by ylyoussf          #+#    #+#             */
/*   Updated: 2023/06/29 19:00:50 by ylyoussf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include "structs.h"

int		ft_atoi(const char *str);
int		ft_isdigit(int c);
bool	parse_args(int nb_args, char **args, t_info *info);
bool	check_nb_args(int argc);

#endif
