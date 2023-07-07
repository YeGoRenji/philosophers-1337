/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylyoussf <ylyoussf@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/30 01:29:54 by ylyoussf          #+#    #+#             */
/*   Updated: 2023/07/07 18:18:03 by ylyoussf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/philo_utils.h"

void	print(t_philo *philo, char *doing, bool lock)
{
	sem_wait(philo->info->print);
	printf("%lld\t%d\t%s\n",
		get_relative_time(philo->info->start),
		philo->number,
		doing);
	if (!lock)
		sem_post(philo->info->print);
}

void	init_semaphores(t_info *info)
{
	sem_unlink(FORKS);
	sem_unlink(PRINT);
	info->forks = sem_open(FORKS, O_CREAT, 0644, info->nb_of_philos);
	if (info->forks == SEM_FAILED)
		(printf("Error: sem_open failed\n"), exit(-1));
	info->print = sem_open(PRINT, O_CREAT, 0644, 1);
	if (info->print == SEM_FAILED)
		(printf("Error: sem_open failed\n"), exit(-1));
}

bool	check_if_stop(t_philo *philo)
{
	long long	time_not_eating;

	if (philo->last_eat == -1)
		return (false);
	time_not_eating = get_relative_time(philo->info->start) - philo->last_eat;
	return (time_not_eating > (long long)philo->info->time_to_die);
}

void	die(t_philo *philo)
{
	print(philo, "died", 1);
	exit(69);
}

void	milsleep_check(t_philo *philo, t_time time_in_ms)
{
	t_time	start;

	start = get_current_ms();
	while (get_current_ms() - start < time_in_ms)
	{
		usleep(100);
		// TODO : Remove this and actually check with threads !
		if (check_if_stop(philo))
			die(philo);
	}
}
