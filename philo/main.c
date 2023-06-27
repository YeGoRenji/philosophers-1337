/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylyoussf <ylyoussf@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/20 20:44:46 by ylyoussf          #+#    #+#             */
/*   Updated: 2023/06/27 21:43:35 by ylyoussf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/structs.h"
#include "include/parser.h"
#include "include/debug.h"
#include "include/time_utils.h"

bool	check_if_dead(t_philo *philo)
{
	long long	time_not_eating;

	time_not_eating = get_relative_time(philo->info) - philo->last_eat;
	// fprintf(stderr, "time not eating : %u\n", time_not_eating);
	return (time_not_eating > (long long)philo->info->time_to_die);
}

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
	pthread_mutex_lock(&philo->info->print_mutex);
	printf("%lld %d %s\n",
		get_relative_time(philo->info),
		philo->number,
		doing
	);
	pthread_mutex_unlock(&philo->info->print_mutex);
}

void	take_forks(t_philo *philo, bool right_first)
{
	if (right_first)
	{
		pthread_mutex_lock(philo->right_fork);
		print(philo, "has taken a fork", 0); //! Remove Right
		pthread_mutex_lock(philo->left_fork);
		print(philo, "has taken a fork", 0); //! Remove left
	}
	else
	{
		pthread_mutex_lock(philo->left_fork);
		print(philo, "has taken a fork", 0); //! Remove left
		pthread_mutex_lock(philo->right_fork);
		print(philo, "has taken a fork", 0); //! Remove Right
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

bool	check_if_stop(t_info *info)
{
	bool	stop;

	pthread_mutex_lock(&info->stop_mutex);
	stop = info->stop;
	pthread_mutex_unlock(&info->stop_mutex);
	return (stop);
}

void	*philo_routine(void *arg)
{
	t_philo	*this;

	this = (t_philo *)arg;
	// while (true)
	while (!check_if_dead(this))
	{
		print(this, "is thinking", 0);
		take_forks(this, this->number % 2);
		print(this, "is eating", 0);

		pthread_mutex_lock(&this->death_mutex);
		this->last_eat = get_relative_time(this->info);
		this->nb_eats++;
		pthread_mutex_unlock(&this->death_mutex);

		milsleep(this->info->time_to_eat);
		hand_forks(this, this->number % 2);

		print(this, "is sleeping", 0);
		milsleep(this->info->time_to_sleep);
	}
	return (NULL);
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
		// (*philos)[i].death_mutex = malloc(sizeof(pthread_mutex_t));
		// if (!(*philos)[i].death_mutex)
		// 	return (false);
		if (pthread_mutex_init(&(*philos)[i].death_mutex, NULL))
			return (false);
		i++;
	}
	return (true);
}

int	start_sim(t_philo *philos, int nb_philos)
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

int	check_nb_args(int argc)
{
	if (argc != 5 && argc != 6)
	{
		printf("Usage: ./philo #philos T_die T_eat T_sleep [min_eats_top]\n");
		return (false);
	}
	return (true);
}

void	call_this()
{
	system("leaks philo");
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
	// pthread_mutex_t	*stop_mutex;
	// pthread_mutex_t	*print_mutex;

	// stop_mutex = malloc(sizeof(pthread_mutex_t));
	// if (!stop_mutex)
	// 	return (false);
	// print_mutex = malloc(sizeof(pthread_mutex_t));
	// if (!print_mutex)
	// 	return (false);
	// if (pthread_mutex_init(stop_mutex, NULL))
	// 	return (false);
	// if (pthread_mutex_init(print_mutex, NULL))
	// 	return (false);
	// info->stop_mutex = stop_mutex;
	// info->print_mutex = print_mutex;

	if (pthread_mutex_init(&info->stop_mutex, NULL))
		return (false);
	if (pthread_mutex_init(&info->print_mutex, NULL))
		return (false);
	return (true);
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
	if (!init_mutexes(&info))
		return (-1);
	if (!serve_forks(&forks, info.nb_of_philos))
		return (-1);
	if (!serve_philos(&philos, forks, &info))
		return (-1);
	if (!start_sim(philos, info.nb_of_philos))
		return (free(philos), -1);
	i = 0;
	int	philos_satisfied = 0;
	while (true)
	{
		usleep(10);
		pthread_mutex_lock(&philos[i].death_mutex);
		if (check_if_dead(&philos[i]))
		{
			(stop(&info, true));
			pthread_mutex_unlock(&philos[i].death_mutex);
			print(&philos[i], "died", 1);
			break;
		}
		philos_satisfied += (info.min_eats > 0) && check_min_eats(&philos[i]);
		pthread_mutex_unlock(&philos[i].death_mutex);
		if (philos_satisfied >= info.nb_of_philos)
		{
			(stop(&info, true));
			break;
		}
		i = (i + 1) % info.nb_of_philos;
		philos_satisfied = (i != 0) * philos_satisfied;
	}
	// pthread_mutex_unlock(&info.print_mutex);
	// pthread_mutex_destroy(&info.print_mutex);
	while (info.nb_of_philos--)
	{
		pthread_join(philos[info.nb_of_philos].thread, NULL);
	}
	//! TODO: Print After Join Cause Weird af lol
	// fflush(stdout);
	// puts("WTFFFF !");
	// exit(0);
}
