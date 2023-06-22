/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylyoussf <ylyoussf@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/20 20:44:46 by ylyoussf          #+#    #+#             */
/*   Updated: 2023/06/22 11:53:26y ylyoussf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/structs.h"
#include "include/parser.h"
#include "include/debug.h"

void	*philo_routine(void *arg)
{
	t_philo	*this;

	this = (t_philo *)arg;
	pthread_mutex_unlock(this->right_fork);
	pthread_mutex_unlock(this->left_fork);
	usleep(1000);
	printf("Am philo %d, forks = {%p, %p}\n", this->number, this->left_fork, this->right_fork);
	pthread_mutex_lock(this->left_fork);
	pthread_mutex_lock(this->right_fork);
	exit(0);
}

void	serve_forks(pthread_mutex_t **forks, int nb_philos)
{
	*forks = malloc(nb_philos * sizeof(pthread_mutex_t));
	while (nb_philos--)
		pthread_mutex_init(*forks + nb_philos, NULL);
}

void	serve_philos(t_philo **philos, pthread_mutex_t *forks,int nb_philos)
{
	int	i;

	*philos = malloc(nb_philos * sizeof(t_philo));
	i = 0;
	while (i < nb_philos)
	{
		(*philos)[i].number = i + 1;
		// (*philos)[i].thread = PTHREAD_CREATE_JOINABLE;
		(*philos)[i].left_fork = forks + i;
		(*philos)[i].right_fork = forks + (i + 1) % nb_philos;
		i++;
	}
}

void	start_sim(t_philo *philos, int nb_philos)
{
	while (nb_philos--)
		pthread_create(&philos[nb_philos].thread, NULL,
			philo_routine, &philos[nb_philos]);
}

int	main(int argc, char **argv)
{
	t_info			info;
	t_philo			*philos;
	pthread_mutex_t	*forks;

	if (argc != 5 && argc != 6)
	{
		printf("Usage: ./philo #philos T_die T_eat T_sleep [min_eats_top]\n");
		return (-1);
	}
	printf("Hello Philosophers\n");
	parse_args(argc - 1, argv + 1, &info);
	print_info(&info);
	serve_forks(&forks, info.nb_of_philos);
	serve_philos(&philos, forks, info.nb_of_philos);
	start_sim(philos, info.nb_of_philos);
	// while (info.nb_of_philos--)
	// 	pthread_join(philos[info.nb_of_philos].thread, NULL);
	pthread_join(philos[0].thread, NULL);
	return (0);
}
