/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylyoussf <ylyoussf@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/29 19:14:29 by ylyoussf          #+#    #+#             */
/*   Updated: 2023/06/30 01:22:31 by ylyoussf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/philo_utils.h"

bool	check_if_dead(t_philo *philo)
{
	long long	time_not_eating;

	time_not_eating = get_relative_time(philo->info->start) - philo->last_eat;
	return (time_not_eating > (long long)philo->info->time_to_die);
}

bool	serve_forks(pthread_mutex_t **forks, int nb_philos)
{
	*forks = malloc(nb_philos * sizeof(pthread_mutex_t));
	while (nb_philos--)
		if (pthread_mutex_init(*forks + nb_philos, NULL))
			return (false);
	return (true);
}

bool	serve_philos(t_philo **philos, pthread_mutex_t *forks, t_info *info)
{
	int				i;

	*philos = malloc(info->nb_of_philos * sizeof(t_philo));
	if (!philos)
		return (false);
	i = 0;
	while (i < info->nb_of_philos)
	{
		(*philos)[i].number = i + 1;
		(*philos)[i].left_fork = forks + i;
		(*philos)[i].right_fork = forks + (i + 1) % info->nb_of_philos;
		(*philos)[i].info = info;
		(*philos)[i].last_eat = 0;
		(*philos)[i].nb_eats = 0;
		if (pthread_mutex_init(&(*philos)[i].death_mutex, NULL))
			return (false);
		i++;
	}
	return (true);
}

bool	start_sim(t_philo *philos, int nb_philos)
{
	while (nb_philos--)
	{
		if (pthread_create(&philos[nb_philos].thread, NULL,
				&philo_routine, &philos[nb_philos]))
			return (false);
		if (pthread_detach(philos[nb_philos].thread))
			return (false);
	}
	return (true);
}

void	monitor_threads(t_philo *philos, t_info *info)
{
	int	philos_satisfied;
	int	i;

	philos_satisfied = 0;
	i = 0;
	while (true)
	{
		pthread_mutex_lock(&philos[i].death_mutex);
		if (check_if_dead(&philos[i]))
		{
			stop(info, true);
			print(&philos[i], "died", 1);
			pthread_mutex_unlock(&philos[i].death_mutex);
			break ;
		}
		philos_satisfied += (info->min_eats > 0 && check_min_eats(&philos[i]));
		pthread_mutex_unlock(&philos[i].death_mutex);
		if (philos_satisfied >= info->nb_of_philos)
		{
			stop(info, true);
			break ;
		}
		i = (i + 1) % info->nb_of_philos;
		philos_satisfied = (i != 0) * philos_satisfied;
	}
}
