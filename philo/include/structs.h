/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylyoussf <ylyoussf@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/21 17:15:56 by ylyoussf          #+#    #+#             */
/*   Updated: 2023/07/09 18:15:46 by ylyoussf         ###   ########.fr       */
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
# include <stdbool.h>

typedef long long	t_time;

typedef struct s_death_state
{
	bool			is_death;
	int				philo_number;
	t_time			when;
}				t_death_state;

typedef struct s_info
{
	int				nb_of_philos;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				min_eats;
	t_time			start;
	pthread_mutex_t	stop_mutex;
	bool			stop;
	t_death_state	death_state;
}				t_info;

typedef struct s_philo
{
	int				number;
	pthread_t		thread;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
	t_info			*info;
	t_time			last_eat;
	long			nb_eats;
	pthread_mutex_t	death_mutex;
}				t_philo;

#endif
