/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_routine.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylyoussf <ylyoussf@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/06 18:26:34 by ylyoussf          #+#    #+#             */
/*   Updated: 2023/07/11 11:14:26 by ylyoussf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/philo_routine.h"

void	take_forks(t_philo *philo)
{
	sem_wait(philo->info->forks);
	print(philo, "has taken a fork", 0);
	sem_wait(philo->info->forks);
	print(philo, "has taken a fork", 0);
}

void	hand_forks(t_philo *philo)
{
	sem_post(philo->info->forks);
	sem_post(philo->info->forks);
}

void	eat(t_philo *philo)
{
	sem_wait(philo->stop);
	philo->last_eat = get_relative_time(philo->info->start);
	philo->nb_eats++;
	if (philo->info->min_eats != -1)
	{
		if (philo->nb_eats >= philo->info->min_eats)
		{
			hand_forks(philo);
			sem_post(philo->stop);
			clean_philo(philo);
			exit(0);
		}
	}
	sem_post(philo->stop);
}

void	handle_one_philo(t_philo *this)
{
	this->last_eat = 0;
	print(this, "is thinking", 0);
	print(this, "has taken a fork", 0);
	milsleep(this->info->time_to_die);
	die(this);
}

void	philo_routine(t_info *info, int number)
{
	t_philo		philo;
	t_philo		*this;
	pthread_t	reaper;

	if (number % 2 == 0)
		usleep(100);
	this = setup_philo(&philo, info, number);
	if (pthread_create(&reaper, NULL, ft_reaper, &philo))
		(clean_philo(this), exit(-1));
	if (pthread_detach(reaper))
		(clean_philo(this), exit(-1));
	if (this->info->nb_of_philos == 1)
		handle_one_philo(this);
	while (true)
	{
		print(this, "is thinking", 0);
		take_forks(this);
		print(this, "is eating", 0);
		eat(this);
		milsleep(this->info->time_to_eat);
		hand_forks(this);
		print(this, "is sleeping", 0);
		milsleep(this->info->time_to_sleep);
	}
}
