/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylyoussf <ylyoussf@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/30 16:25:38 by ylyoussf          #+#    #+#             */
/*   Updated: 2023/07/04 20:53:00 by ylyoussf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/structs.h"
#include "include/parser.h"
#include "include/debug.h"
#include "include/time_utils.h"
#include "include/philo_utils.h"

void	setup_philo(t_philo *philo, t_info *info, int number, sem_t *forks)
{
	philo->info = info;
	philo->number = number;
	philo->nb_eats = 0;
	philo->last_eat = -1;
	philo->forks = forks;
}

bool	check_if_stop(t_philo *philo)
{
	long long	time_not_eating;
	
	if(philo->last_eat == -1)
		return (false);
	time_not_eating = get_relative_time(philo->info->start) - philo->last_eat;
	return (time_not_eating > (long long)philo->info->time_to_die);
}

void	take_forks(t_philo *philo)
{
	sem_wait(philo->forks);
	print(philo, "has taken a fork");
	sem_wait(philo->forks);
	print(philo, "has taken a fork");
}

void	hand_forks(t_philo *philo)
{
	sem_post(philo->forks);
	sem_post(philo->forks);
}

void	eat(t_philo *philo)
{
	philo->last_eat = get_relative_time(philo->info->start);
	philo->nb_eats++;
}

void	die(t_philo *philo)
{
	print(philo, "died");
	exit(69);
}

void	philo_routine(t_info *info, int number, sem_t *forks)
{
	t_philo	philo;
	t_philo	*this;

	printf("Hello Am child %d\n", number);
	setup_philo(&philo, info, number, forks);
	this = &philo;
	if (this->info->nb_of_philos == 1)
	{
		this->last_eat = 0;
		print(this, "is thinking");
		print(this, "has taken a fork");
		milsleep(this->info->time_to_die);
		die(this);
	}
	while (true)
	{
		print(this, "is thinking");
		take_forks(this);
		print(this, "is eating");
		eat(this);
		milsleep(this->info->time_to_eat);
		hand_forks(this);
		print(this, "is sleeping");
		milsleep(this->info->time_to_sleep);
		if (check_if_stop(this))
			die(this);
	}
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

	printf("Hello From Parent !\n");

	i = 0;
	exit_status = 0;
	while (i++ < info->nb_of_philos)
	{
		waitpid(-1, &stat_loc, 0);
		exit_status = WEXITSTATUS(stat_loc);
		printf("exit_status %d\n", exit_status);
		if (exit_status == 69)
		{
			printf("fuck someone died..\n");
			kill(0, SIGKILL);
			break;
		}
	}
	printf("WTF! ");
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

int main(int argc, char **argv)
{
	t_info	info;
	sem_t	*forks;		
	pid_t	*pids;
	int		i;

	if (!check_nb_args(argc))
		return (-1);
	if (!parse_args(argc - 1, argv + 1, &info))
		return (-1);
	printf("Hello Philosophers\n"); //? Debug
	print_info(&info); //? Debug
	forks = init_semaphore(&info);
	pids = malloc(info.nb_of_philos * sizeof(int));
	i = 0;
	pids[i] = 0x69;
	info.start = get_current_ms();
	while (i < info.nb_of_philos)
	{
	 	pids[i] = fork();
		if (!pids[i])
			break ;
		i++;
	}
	if (!is_parent(pids, info.nb_of_philos))
		philo_routine(&info, i + 1, forks);
	else
		monitor_processes(&info);
	sem_unlink(FORKS);
	sem_close(forks);
	return (0);
}

