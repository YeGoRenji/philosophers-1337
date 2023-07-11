/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylyoussf <ylyoussf@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/30 16:25:38 by ylyoussf          #+#    #+#             */
/*   Updated: 2023/07/11 10:15:48 by ylyoussf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/structs.h"
#include "include/parser.h"
#include "include/debug.h"
#include "include/time_utils.h"
#include "include/philo_utils.h"
#include "include/philo_routine.h"

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
	int	stat_loc;
	int	exit_status;
	int	i;

	i = 0;
	exit_status = 0;
	while (i++ < info->nb_of_philos)
	{
		waitpid(-1, &stat_loc, 0);
		exit_status = WEXITSTATUS(stat_loc);
		if (exit_status)
			(clean(info, 1), kill(0, SIGINT));
	}
	clean(info, 1);
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

int	main(int argc, char **argv)
{
	t_info	info;
	pid_t	pid;
	int		i;

	if (!check_nb_args(argc))
		return (-1);
	if (!parse_args(argc - 1, argv + 1, &info))
		return (-1);
	init_semaphores(&info);
	info.start = get_current_ms();
	i = serve_philos(&pid, &info);
	if (!pid)
		philo_routine(&info, i);
	else
		monitor_processes(&info);
	return (0);
}
