/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylyoussf <ylyoussf@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/20 20:44:46 by ylyoussf          #+#    #+#             */
/*   Updated: 2023/06/22 02:39:10 by ylyoussf         ###   ########.fr       */
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
void	routine_diali(void)
{
	// pthread_mutex_lock()
	while (1)
	{
		usleep(2000 * 1000);
		printf("Ana ah ana\n");
	}
}

int	serve_spoons(pthread_mutex_t **spoons, int nb_philos)
{
	*spoons = malloc(nb_philos * sizeof(pthread_mutex_t));
	while (nb_philos--)
		pthread_mutex_init(*spoons + nb_philos, NULL);
}

int	main(int argc, char **argv)
{
	t_info			info;
	pthread_t		a_thread;
	pthread_mutex_t	*spoons;

	if (argc != 5 && argc != 6)
	{
		printf("Usage: ./philo #philos T_die T_eat Tto_sleep [min_eats_top]\n");
		return (-1);
	}
	printf("Hello Philosophers\n");
	parse_args(argc - 1, argv + 1, &info);
	print_info(&info);
	serve_spoons(spoons, info.nb_of_philos);
	return (0);
}
