/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils_2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylyoussf <ylyoussf@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/30 01:29:54 by ylyoussf          #+#    #+#             */
/*   Updated: 2023/07/03 11:27:39 by ylyoussf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/philo_utils.h"

void	print(t_philo *philo, char *doing, bool ded)
{
	bool	stop;

	stop = false;
	if (!ded)
	{
		pthread_mutex_lock(&philo->info->stop_mutex);
		if (philo->info->stop)
			stop = true;
		pthread_mutex_unlock(&philo->info->stop_mutex);
		if (stop)
			return ;
	}
	printf("%lld %d %s\n",
		get_relative_time(philo->info->start),
		philo->number,
		doing);
}

bool	check_min_eats(t_philo	*philo)
{
	return (philo->nb_eats >= philo->info->min_eats);
}

void	stop(t_info *info, bool boolean)
{
	pthread_mutex_lock(&info->stop_mutex);
	info->stop = boolean;
	pthread_mutex_unlock(&info->stop_mutex);
}

bool	init_mutexes(t_info *info)
{
	if (pthread_mutex_init(&info->stop_mutex, NULL))
		return (false);
	return (true);
}
