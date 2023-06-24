/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylyoussf <ylyoussf@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/21 17:15:56 by ylyoussf          #+#    #+#             */
/*   Updated: 2023/06/24 19:06:32 by ylyoussf         ###   ########.fr       */
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
	int			nb_of_philos;
	int			time_to_die;
	int			time_to_eat;
	int			time_to_sleep;
	int			min_eats;
	long long	starting_ms;
}				t_info;

typedef struct s_philo
{
	int				number;
	pthread_t		thread;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
	t_info			*info;
	long long		last_eat;
	long long		nb_eats;
	pthread_mutex_t	*print_mutex;
	pthread_mutex_t	*check_death;
}				t_philo;

#endif
