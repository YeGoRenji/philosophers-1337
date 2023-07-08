/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylyoussf <ylyoussf@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/29 19:13:09 by ylyoussf          #+#    #+#             */
/*   Updated: 2023/07/08 16:30:18 by ylyoussf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_UTILS_H
# define PHILO_UTILS_H

# include "time_utils.h"

void	init_semaphores(t_info *info);
void	print(t_philo *philo, char *doing, bool lock);
void	die(t_philo *philo);
void	clean(t_info *info, bool unlink);
void	*ft_reaper(void *arg);
t_philo	*setup_philo(t_philo *philo, t_info *info, int number);
bool	check_if_stop(t_philo *philo);
#endif
