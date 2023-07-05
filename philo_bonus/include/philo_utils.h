/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylyoussf <ylyoussf@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/29 19:13:09 by ylyoussf          #+#    #+#             */
/*   Updated: 2023/07/05 20:59:59 by ylyoussf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_UTILS_H
# define PHILO_UTILS_H

# include "structs.h"
# include "time_utils.h"
# include <sys/wait.h>

void	init_semaphores(t_info *info);
void	print(t_philo *philo, char *doing, bool lock);
void	milsleep_check(t_philo *philo, t_time time_in_ms);
void	die(t_philo *philo);
#endif
