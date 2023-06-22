/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylyoussf <ylyoussf@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/21 17:15:56 by ylyoussf          #+#    #+#             */
/*   Updated: 2023/06/22 12:52:36 by ylyoussf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTS_H
# define STRUCTS_H

# include <stdio.h>
# include <stdlib.h>
# include <stdint.h>
# include <sys/time.h>
# include <unistd.h>
# include <pthread.h>

typedef struct s_info
{
	int	nb_of_philos;
	int	time_to_die;
	int	time_to_eat;
	int	time_to_sleep;
	int	min_eats;
}				t_info;

typedef struct philo
{
	int				number;
	pthread_t		thread;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
}				t_philo;

#endif
