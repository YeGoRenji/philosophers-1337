/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylyoussf <ylyoussf@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/20 20:44:46 by ylyoussf          #+#    #+#             */
/*   Updated: 2023/06/26 01:36:03 by ylyoussf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/structs.h"
#include "include/parser.h"
#include "include/debug.h"
#include "include/time_utils.h"
#include <stdbool.h>


int	check_if_dead(t_philo *philo)
{
	long long	time_not_eating;

	time_not_eating = get_timestamp(philo->info) - philo->last_eat;
	// fprintf(stderr, "time not eating : %u\n", time_not_eating);
	return (time_not_eating > (long long)philo->info->time_to_die);
}

void	print(t_philo *philo, char *doing, int ded)
{
	pthread_mutex_lock(philo->print_mutex);
	printf("%lld %d %s\n",
		get_timestamp(philo->info),
		philo->number,
		doing
	);
	if (!ded)
		pthread_mutex_unlock(philo->print_mutex);
}

void	take_forks(t_philo *philo, bool right_first)
{
	if (right_first)
	{
		pthread_mutex_lock(philo->right_fork);
		print(philo, "has taken right fork", 0); //! Remove Right
		pthread_mutex_lock(philo->left_fork);
		print(philo, "has taken left fork", 0); //! Remove left
	}
	else
	{
		pthread_mutex_lock(philo->left_fork);
		print(philo, "has taken left fork", 0); //! Remove left
		pthread_mutex_lock(philo->right_fork);
		print(philo, "has taken right fork", 0); //! Remove Right
	}

}

void	hand_forks(t_philo *philo, bool right_first)
{
	if (right_first)
	{
		pthread_mutex_unlock(philo->left_fork);
		pthread_mutex_unlock(philo->right_fork);
	}
	else
	{
		pthread_mutex_unlock(philo->right_fork);
		pthread_mutex_unlock(philo->left_fork);
	}
}

void	*philo_routine(void *arg)
{
	t_philo	*this;
	int	*return_val;

	this = (t_philo *)arg;
	// if (this->number % 2 == 0)
	// 	usleep(1000 * this->info->time_to_eat / 2);
	return_val = malloc(sizeof(int));
	*return_val = 0;
	while (1)
	{
		print(this, "is thinking", 0);
		take_forks(this, this->number % 2);
		print(this, "is eating", 0);

		pthread_mutex_lock(this->check_death);
		this->last_eat = get_timestamp(this->info);
		this->nb_eats++;
		pthread_mutex_unlock(this->check_death);

		milsleep(this->info->time_to_eat);
		hand_forks(this, this->number % 2);

		print(this, "is sleeping", 0);
		milsleep(this->info->time_to_sleep);
	}
	return (return_val);
}

int	serve_forks(pthread_mutex_t **forks, int nb_philos)
{
	*forks = malloc(nb_philos * sizeof(pthread_mutex_t));
	while (nb_philos--)
		if (pthread_mutex_init(*forks + nb_philos, NULL))
			return (0);
	return (1);
}

int	serve_philos(t_philo **philos, pthread_mutex_t *forks,int nb_philos, t_info *info)
{
	int				i;
	pthread_mutex_t	*print_mutex;

	print_mutex = malloc(sizeof(pthread_mutex_t));
	if (pthread_mutex_init(print_mutex, NULL))
		return (0);
	*philos = malloc(nb_philos * sizeof(t_philo));
	if (!philos)
		return (0);
	i = 0;
	while (i < nb_philos)
	{
		(*philos)[i].number = i + 1;
		(*philos)[i].left_fork = forks + i;
		(*philos)[i].right_fork = forks + (i + 1) % nb_philos;
		(*philos)[i].info = info;
		(*philos)[i].last_eat = 0;
		(*philos)[i].nb_eats = 0;
		(*philos)[i].print_mutex = print_mutex;
		//! Protecc
		(*philos)[i].check_death = malloc(sizeof(pthread_mutex_t));
		pthread_mutex_init((*philos)[i].check_death, NULL);
		i++;
	}
	return (1);
}

int	start_sim(t_philo *philos, int nb_philos)
{
	while (nb_philos--)
	{
		if (pthread_create(&philos[nb_philos].thread, NULL,
			&philo_routine, &philos[nb_philos]))
			return (0);
		if (pthread_detach(philos[nb_philos].thread))
			return (0);
	}
	return (1);
}

int	check_nb_args(int argc)
{
	if (argc != 5 && argc != 6)
	{
		printf("Usage: ./philo #philos T_die T_eat T_sleep [min_eats_top]\n");
		return (0);
	}
	return (1);
}

void	call_this()
{
	system("leaks philo");
}

int	check_min_eats(t_philo	*philo)
{
	return (philo->nb_eats >= philo->info->min_eats);
}

int	main(int argc, char **argv)
{
	t_info			info;
	t_philo			*philos;
	pthread_mutex_t	*forks;
	int				i;

	// atexit(call_this);

	if (!check_nb_args(argc))
		return (-1);
	if (!parse_args(argc - 1, argv + 1, &info))
		return (-1);
	printf("Hello Philosophers\n"); //? Debug
	print_info(&info); //? Debug
	info.starting_ms = get_current_ms();
	if (!serve_forks(&forks, info.nb_of_philos))
		return (-1);
	if (!serve_philos(&philos, forks, info.nb_of_philos, &info))
		return (-1);
	if (!start_sim(philos, info.nb_of_philos))
		return (free(philos), -1);
	i = 0;
	int	philos_satisfied = 0;
	while (1)
	{
		usleep(10);
		pthread_mutex_lock(philos[i].check_death);
		if (check_if_dead(&philos[i]))
			return (print(&philos[i], "died", 1), 0);
		philos_satisfied += (info.min_eats != -1) && check_min_eats(&philos[i]);
		pthread_mutex_unlock(philos[i].check_death);
		if (philos_satisfied >= info.nb_of_philos)
			return (0);
		i = (i + 1) % info.nb_of_philos;
		philos_satisfied = (i != 0) * philos_satisfied;
	}
}
