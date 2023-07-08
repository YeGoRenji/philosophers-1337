/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_routine.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylyoussf <ylyoussf@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/06 18:26:34 by ylyoussf          #+#    #+#             */
/*   Updated: 2023/07/08 01:41:09 by ylyoussf         ###   ########.fr       */
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
	philo->last_eat = get_relative_time(philo->info->start);
	philo->nb_eats++;
	if (philo->info->min_eats != -1)
		if (philo->nb_eats >= philo->info->min_eats)
			(hand_forks(philo), clean(philo->info), exit(0));
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
		usleep(200);
	this = setup_philo(&philo, info, number);
	if (pthread_create(&reaper, NULL, ft_reaper, &philo))
		clean(this->info);
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
