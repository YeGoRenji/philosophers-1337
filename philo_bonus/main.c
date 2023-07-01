/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylyoussf <ylyoussf@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/30 16:25:38 by ylyoussf          #+#    #+#             */
/*   Updated: 2023/07/01 18:23:08 by ylyoussf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/structs.h"
#include "include/parser.h"
#include "include/debug.h"
#include "include/time_utils.h"
#include "include/philo_utils.h"
#include <semaphore.h>

int main(int argc, char **argv)
{
	t_info	info;
	sem_t	*forks;		
	// t_philo			*philos;
	// pthread_mutex_t	*forks;


	// atexit(call_this);
	if (!check_nb_args(argc))
		return (-1);
	if (!parse_args(argc - 1, argv + 1, &info))
		return (-1);
	printf("Hello Philosophers\n"); //? Debug
	print_info(&info); //? Debug
	int pid;
	info.start = get_current_ms();
	// sem_init(&forks, true, info.nb_of_philos);
	forks = sem_open("/forks", O_RDWR, 0600, info.nb_of_philos);
	// if (!init_mutexes(&info))
	// 	return (-1);
	//nb = 5;
	if (!forks)
		(printf("Error: Can't open semaphore\n"), exit(-1));
	while (info.nb_of_philos--)
	{
		pid = fork();
		if (!pid)
			break;
	}
	if (!pid)
	{
		sem_wait(forks);
		printf("Child %d got a fork !\n", info.nb_of_philos);
	}
	else
	{
		printf("Hello From Parent !\n");
	}
	
	return (0);
}

