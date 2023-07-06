/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_routine.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylyoussf <ylyoussf@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/06 18:26:34 by ylyoussf          #+#    #+#             */
/*   Updated: 2023/07/06 20:39:03 by ylyoussf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/philo_routine.h"

t_philo	*setup_philo(t_philo *philo, t_info *info, int number)
{
	philo->info = info;
	philo->number = number;
	philo->nb_eats = 0;
	philo->last_eat = -1;
	return (philo);
}

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
			(hand_forks(philo), exit(0));
}

void	philo_routine(t_info *info, int number)
{
	t_philo	philo;
	t_philo	*this;

	// TODO : Should I Fix Deadlock ?
	if (number % 2 == 0)
		usleep(200);
	this = setup_philo(&philo, info, number);
	if (this->info->nb_of_philos == 1)
	{
		this->last_eat = 0;
		print(this, "is thinking", 0);
		print(this, "has taken a fork", 0);
		milsleep_check(this, this->info->time_to_die);
		die(this);
	}
	while (true)
	{
		print(this, "is thinking", 0);
		take_forks(this);
		print(this, "is eating", 0);
		eat(this);
		milsleep_check(this, this->info->time_to_eat);
		hand_forks(this);
		print(this, "is sleeping", 0);
		milsleep_check(this, this->info->time_to_sleep);
	}
	clean(info);
}
