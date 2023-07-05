/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylyoussf <ylyoussf@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/30 16:25:38 by ylyoussf          #+#    #+#             */
/*   Updated: 2023/07/05 21:33:01 by ylyoussf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/structs.h"
#include "include/parser.h"
#include "include/debug.h"
#include "include/time_utils.h"
#include "include/philo_utils.h"
#include <stdlib.h>

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


void	clean(t_info *info)
{
	sem_close(info->forks);
	sem_close(info->print);
	sem_unlink(FORKS);
	sem_unlink(PRINT);
}

void	philo_routine(t_info *info, int number)
{
	t_philo	philo;
	t_philo	*this;

	// printf("Hello Am child %d\n", number);
	// TODO : Should I Fix Deadlock ?
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
	exit(0);
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


void	monitor_processes(t_info *info)
{
	int 	stat_loc;
	int		exit_status;
	int		i;
	// pid_t	current;

	// printf("Hello From Parent !\n");

	i = 0;
	exit_status = 0;
	while (i++ < info->nb_of_philos)
	{
		waitpid(-1, &stat_loc, 0);
		exit_status = WEXITSTATUS(stat_loc);
		// printf("exit_status %d\n", exit_status);
		if (exit_status == 69)
		{
			printf("Someone Died !\n");
			clean(info);
			kill(0, SIGINT);
			break ;
		}
	}
	clean(info);
}

bool	is_parent(pid_t *pids, int size)
{
	while (size--)
	{
		if (pids[size] == 0)
			return (false);
	}
	return (true);
}

int	serve_philos(pid_t *pid, t_info *info)
{
	int	i;

	i = 0;
	*pid = 0x69;
	while (*pid && i++ < info->nb_of_philos)
	 	*pid = fork();
	return (i);
}

int main(int argc, char **argv)
{
	t_info	info;
	pid_t	pid;
	int		i;

	if (!check_nb_args(argc))
		return (-1);
	if (!parse_args(argc - 1, argv + 1, &info))
		return (-1);
	// printf("Hello Philosophers\n"); //? Debug
	print_info(&info); //? Debug
	init_semaphores(&info);
	info.start = get_current_ms();
	i = serve_philos(&pid, &info);
	if (!pid)
		philo_routine(&info, i);
	else
		monitor_processes(&info);
	return (0);
}
