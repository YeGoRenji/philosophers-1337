/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main-manda.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylyoussf <ylyoussf@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/20 20:44:46 by ylyoussf          #+#    #+#             */
/*   Updated: 2023/06/30 15:55:45 by ylyoussf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/structs.h"
#include "include/parser.h"
#include "include/debug.h"
#include "include/time_utils.h"
#include "include/philo_utils.h"

void	call_this(void)
{
	system("leaks philo");
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
	info.start = get_current_ms();
	if (!init_mutexes(&info))
		return (-1);
	if (!serve_forks(&forks, info.nb_of_philos))
		return (-1);
	if (!serve_philos(&philos, forks, &info))
		return (-1);
	if (!start_sim(philos, info.nb_of_philos))
		return (free(philos), free(forks), -1);
	monitor_threads(philos, &info);
	return (0);
}
