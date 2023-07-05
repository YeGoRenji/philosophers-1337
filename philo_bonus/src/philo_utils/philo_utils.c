/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylyoussf <ylyoussf@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/30 01:29:54 by ylyoussf          #+#    #+#             */
/*   Updated: 2023/07/05 01:50:12 by ylyoussf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/philo_utils.h"

void	print(t_philo *philo, char *doing)
{
	// bool	stop;

	printf("%lld\t%d\t%s\n",
		get_relative_time(philo->info->start),
		philo->number,
		doing);
}

sem_t	*init_semaphore(t_info *info)
{
	sem_t	*sem;
	sem_unlink(FORKS);
	sem = sem_open(FORKS, O_CREAT, 0644, info->nb_of_philos);
	if (sem == SEM_FAILED)
		(printf("Error: sem_open failed\n"), exit(-1));
	return (sem);
}

bool	check_if_stop(t_philo *philo)
{
	long long	time_not_eating;
	
	if(philo->last_eat == -1)
		return (false);
	time_not_eating = get_relative_time(philo->info->start) - philo->last_eat;
	return (time_not_eating > (long long)philo->info->time_to_die);
	// TODO : CHECK min_eats
}

void	die(t_philo *philo)
{
	print(philo, "died");
	exit(69);
}

void	milsleep_check(t_philo *philo, t_time time_in_ms)
{
	t_time	start;

	start = get_current_ms();
	while (get_current_ms() - start < time_in_ms)
	{
		usleep(100);
		if (check_if_stop(philo))
		{
			die(philo);
			exit(69);
		}
	}
}
