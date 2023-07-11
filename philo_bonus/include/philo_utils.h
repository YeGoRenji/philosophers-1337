/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylyoussf <ylyoussf@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/29 19:13:09 by ylyoussf          #+#    #+#             */
/*   Updated: 2023/07/11 11:11:01 by ylyoussf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_UTILS_H
# define PHILO_UTILS_H

# include "time_utils.h"
# include "parser.h"

void	init_semaphores(t_info *info);
void	print(t_philo *philo, char *doing, bool lock);
void	die(t_philo *philo);
void	clean(t_info *info, bool unlink);
void	clean_philo(t_philo *philo);
void	*ft_reaper(void *arg);
t_philo	*setup_philo(t_philo *philo, t_info *info, int number);
bool	check_if_stop(t_philo *philo);
#endif
