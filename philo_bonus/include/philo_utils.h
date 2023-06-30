/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylyoussf <ylyoussf@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/29 19:13:09 by ylyoussf          #+#    #+#             */
/*   Updated: 2023/06/30 13:18:43 by ylyoussf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_UTILS_H
# define PHILO_UTILS_H

# include "structs.h"
# include "time_utils.h"
# include "philo_routine.h"

bool	start_sim(t_philo *philos, int nb_philos);
bool	serve_forks(pthread_mutex_t **forks, int nb_philos);
bool	serve_philos(t_philo **philos, pthread_mutex_t *forks, t_info *info);
bool	init_mutexes(t_info *info);
bool	check_min_eats(t_philo	*philo);
void	print(t_philo *philo, char *doing, bool ded);
void	stop(t_info *info, bool boolean);
void	monitor_threads(t_philo *philos, t_info *info);
#endif
