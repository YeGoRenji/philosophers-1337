/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylyoussf <ylyoussf@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/30 16:25:38 by ylyoussf          #+#    #+#             */
/*   Updated: 2023/06/30 23:55:43 by ylyoussf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/structs.h"
#include "include/parser.h"
#include "include/debug.h"
#include "include/time_utils.h"
#include "include/philo_utils.h"

int main(int argc, char **argv)
{
	t_info			info;
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
	//nb = 5;
	while (info.nb_of_philos--)
	{
		pid = fork();
		if (!pid)
			break;
	}

	if (!pid)
		printf("Hello From Child %d!\n", info.nb_of_philos);
	else
		printf("Hello From Parent !\n");

	return (0);
}

