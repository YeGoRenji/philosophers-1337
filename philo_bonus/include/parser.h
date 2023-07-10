/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylyoussf <ylyoussf@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/20 20:51:04 by ylyoussf          #+#    #+#             */
/*   Updated: 2023/07/10 15:51:35 by ylyoussf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include "structs.h"

int		ft_memcmp(const void *s1, const void *s2, size_t n);
char	*ft_itoa(int n);
char	*ft_strdup(const char *s1);
char	*ft_strjoin(char const *s1, char const *s2);
void	*ft_memcpy(void *dest, const void *src, size_t n);
size_t	ft_strlen(const char *s);
int		ft_atoi(const char *str);
int		ft_isdigit(int c);
bool	parse_args(int nb_args, char **args, t_info *info);

#endif
