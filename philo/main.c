/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylyoussf <ylyoussf@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/20 20:44:46 by ylyoussf          #+#    #+#             */
/*   Updated: 2023/07/06 16:25:29 by ylyoussf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/structs.h"
#include "include/parser.h"
#include "include/debug.h"
#include "include/time_utils.h"
#include "include/philo_utils.h"

void	wait_and_clean(t_philo *philos, pthread_mutex_t *forks, t_info *info)
{
	int	i;

	// printf("Main thread is joining !..\n");
	i = 0;
	while (i < info->nb_of_philos)
		pthread_join(philos[i++].thread, NULL);
	// printf("Main thread is destroying !..\n");
	i = 0;
	while (i < info->nb_of_philos)
	{
		pthread_mutex_destroy(&philos[i].death_mutex);
		pthread_mutex_destroy(&forks[i]);
		i++;
	}
	pthread_mutex_destroy(&info->stop_mutex);
	// printf("Main thread is Done :) !..\n");
}

bool	check_nb_args(int argc)
{
	if (argc != 5 && argc != 6)
	{
		printf("Usage: ./philo #philos T_die T_eat T_sleep [min_eats_top]\n");
		return (false);
	}
	return (true);
}

int	main(int argc, char **argv)
{
	t_info			info;
	t_philo			*philos;
	pthread_mutex_t	*forks;

	// atexit(call_this);
	if (!check_nb_args(argc))
		return (-1);
	if (!parse_args(argc - 1, argv + 1, &info))
		return (-1);
	printf("Hello Philosophers\n"); //? Debug
	print_info(&info); //? Debug
	if (!init_mutexes(&info))
		return (-1);
	if (!serve_forks(&forks, info.nb_of_philos))
		return (-1);
	if (!serve_philos(&philos, forks, &info))
		return (-1);
	if (!start_sim(philos, info.nb_of_philos))
		return (free(philos), free(forks), -1);
	monitor_threads(philos, &info);
	wait_and_clean(philos, forks, &info);
	return (free(philos), free(forks), 0);
}
