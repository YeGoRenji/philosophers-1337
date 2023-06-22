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
	if (this->number % 2 == 0)
		usleep(100);
	pthread_mutex_unlock(this->right_fork);
	pthread_mutex_unlock(this->left_fork);
	printf("Am philo %d, forks = {%x, %x}\n", this->number, ((unsigned int)this->left_fork & 0xFF), ((int)this->right_fork & 0xFF));
	pthread_mutex_lock(this->left_fork);
	pthread_mutex_lock(this->right_fork);
	return (NULL);
}

void	serve_forks(pthread_mutex_t **forks, int nb_philos)
{
	*forks = malloc(nb_philos * sizeof(pthread_mutex_t));
	while (nb_philos--)
		pthread_mutex_init(*forks + nb_philos, NULL);
}

void	serve_philos(t_philo **philos, pthread_mutex_t *forks,int nb_philos, t_info *info)
{
	int	i;

	*philos = malloc(nb_philos * sizeof(t_philo));
	i = 0;
	while (i < nb_philos)
	{
		(*philos)[i].number = i + 1;
		(*philos)[i].left_fork = forks + i;
		(*philos)[i].right_fork = forks + (i + 1) % nb_philos;
		(*philos)[i].info = info;
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
	serve_philos(&philos, forks, info.nb_of_philos, &info);
	start_sim(philos, info.nb_of_philos);
	while (info.nb_of_philos--)
		pthread_join(philos[info.nb_of_philos].thread, NULL);
	return (0);
}
