/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_routine.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylyoussf <ylyoussf@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/06 18:26:00 by ylyoussf          #+#    #+#             */
/*   Updated: 2023/07/08 16:29:08 by ylyoussf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_ROUTINE_H
# define PHILO_ROUTINE_H

# include "structs.h"
# include "time_utils.h"
# include "philo_utils.h"

void	take_forks(t_philo *philo);
void	hand_forks(t_philo *philo);
void	eat(t_philo *philo);
void	philo_routine(t_info *info, int number);

#endif
