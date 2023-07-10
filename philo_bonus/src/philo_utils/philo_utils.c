/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylyoussf <ylyoussf@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/30 01:29:54 by ylyoussf          #+#    #+#             */
/*   Updated: 2023/07/10 16:20:23 by ylyoussf         ###   ########.fr       */
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
		(printf("Error: sem_open(forks) failed\n"), exit(-1));
	info->print = sem_open(PRINT, O_CREAT, 0644, 1);
	if (info->print == SEM_FAILED)
		(printf("Error: sem_open(print) failed\n"), exit(-1));
}

bool	check_if_stop(t_philo *philo)
{
	long long	time_not_eating;
	t_time		last_eat;

	sem_wait(philo->stop);
	last_eat = philo->last_eat;
	sem_post(philo->stop);
	if (last_eat == -1)
		return (false);
	time_not_eating = get_relative_time(philo->info->start) - philo->last_eat;
	return (time_not_eating > (long long)philo->info->time_to_die);
}

t_philo	*setup_philo(t_philo *philo, t_info *info, int number)
{
	char *sem_name;
	char *number_str;

	philo->info = info;
	philo->number = number;
	philo->nb_eats = 0;
	philo->last_eat = -1;
	number_str = ft_itoa(number);
	sem_name = ft_strjoin("/stop", number_str);
	sem_unlink(sem_name);
	philo->stop = sem_open(sem_name, O_CREAT, 0644, 1);
	(free(sem_name), free(number_str));
	// TODO : Should I protecc ?
	// Check if memory is fully freed !
	if (philo->stop == SEM_FAILED)
		return (NULL);
	return (philo);
}

void	die(t_philo *philo)
{
	print(philo, "died", 1);
	exit(69);
}
