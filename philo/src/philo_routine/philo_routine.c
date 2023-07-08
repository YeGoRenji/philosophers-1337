/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_routine.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylyoussf <ylyoussf@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/29 18:50:57 by ylyoussf          #+#    #+#             */
/*   Updated: 2023/07/08 23:43:48 by ylyoussf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/philo_routine.h"

void	take_forks(t_philo *philo, bool right_first)
{
	pthread_mutex_t	*forks[2];

	forks[0] = philo->left_fork;
	forks[1] = philo->right_fork;
	pthread_mutex_lock(forks[right_first]);
	print(philo, "has taken a fork", 0);
	pthread_mutex_lock(forks[!right_first]);
	print(philo, "has taken a fork", 0);
}

void	hand_forks(t_philo *philo, bool right_first)
{
	pthread_mutex_t	*forks[2];

	forks[0] = philo->left_fork;
	forks[1] = philo->right_fork;
	pthread_mutex_unlock(forks[right_first]);
	pthread_mutex_unlock(forks[!right_first]);
}

void	eat(t_philo *philo)
{
	pthread_mutex_lock(&philo->death_mutex);
	philo->last_eat = get_relative_time(philo->info->start);
	philo->nb_eats++;
	pthread_mutex_unlock(&philo->death_mutex);
}

void	*handle_one_philo(t_philo *this)
{
	pthread_mutex_lock(&this->death_mutex);
	this->last_eat = 0;
	pthread_mutex_unlock(&this->death_mutex);
	print(this, "is thinking", 0);
	print(this, "has taken a fork", 0);
	milsleep(this->info->time_to_die);
	return (NULL);
}

void	*philo_routine(void *arg)
{
	t_philo	*this;

	this = (t_philo *)arg;
	if (this->info->nb_of_philos == 1)
		return (handle_one_philo(this));
	while (true)
	{
		print(this, "is thinking", 0);
		take_forks(this, this->number % 2);
		print(this, "is eating", 0);
		eat(this);
		milsleep(this->info->time_to_eat);
		hand_forks(this, this->number % 2);
		print(this, "is sleeping", 0);
		milsleep(this->info->time_to_sleep);
		if (check_if_stop(this->info))
			break ;
	}
	return (NULL);
}
