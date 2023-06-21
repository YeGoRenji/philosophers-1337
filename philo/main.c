/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylyoussf <ylyoussf@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/20 20:44:46 by ylyoussf          #+#    #+#             */
/*   Updated: 2023/06/21 20:54:08 by ylyoussf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/structs.h"
#include "include/parser.h"
#include "include/debug.h"

void	*routine_dialo(void *arg)
{
	(void)arg;
	while (1)
	{
		usleep(1000 * 1000);
		printf("Ana dak khona\n");
	}
}
void	routine_diali()
{
	while (1)
	{
		usleep(2000 * 1000);
		printf("Ana ah ana\n");
	}
}

int	main(int argc, char **argv)
{
	t_info		info;
	pthread_t	a_thread;

	if (argc != 5 && argc != 6)
	{
		printf("Usage: ./philo #philos T_die T_eat Tto_sleep [min_eats_top]\n");
		return (-1);
	}
	printf("Hello Philosophers\n");
	pthread_create(&a_thread, NULL, routine_dialo, NULL);
	routine_diali();
	parse_args(argc - 1, argv + 1, &info);
	print_info(&info);
	return (0);
}
