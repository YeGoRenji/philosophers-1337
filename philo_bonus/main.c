/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylyoussf <ylyoussf@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/30 16:25:38 by ylyoussf          #+#    #+#             */
/*   Updated: 2023/07/03 21:55:52 by ylyoussf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/structs.h"
#include "include/parser.h"
#include "include/debug.h"
#include "include/time_utils.h"
#include "include/philo_utils.h"

void	do_something(t_info *info, sem_t *forks)
{
	// t_philo	this;

	printf("Child %d is waiting...\n", info->nb_of_philos);
	sem_wait(forks);
	printf("Child %d got a fork !\n", info->nb_of_philos);
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

int main(int argc, char **argv)
{
	t_info	info;
	sem_t	*forks;		
	pid_t	pid;
	
	// atexit(call_this);
	if (!check_nb_args(argc))
		return (-1);
	if (!parse_args(argc - 1, argv + 1, &info))
		return (-1);
	printf("Hello Philosophers\n"); //? Debug
	print_info(&info); //? Debug
	info.start = get_current_ms();
	forks = init_semaphore(&info);
	pid = 0x69;
	while (pid && info.nb_of_philos--)
		pid = fork();
	if (!pid)
	{
		do_something(&info, forks);
	}
	else
	{
		printf("Hello From Parent !\n");
		waitpid(pid, NULL, 0);
	}
	
	return (0);
}

