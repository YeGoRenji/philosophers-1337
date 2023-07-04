/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylyoussf <ylyoussf@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/21 17:15:56 by ylyoussf          #+#    #+#             */
/*   Updated: 2023/07/04 19:21:15 by ylyoussf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTS_H
# define STRUCTS_H

# include <stdio.h>
# include <stdlib.h>
# include <stdint.h>
# include <sys/time.h>
# include <unistd.h>
# include <semaphore.h>
# include <fcntl.h>
# include <stdbool.h>
# include <signal.h>
# define FORKS "/forks"

typedef long long	t_time;
typedef struct s_info
{
	int				nb_of_philos;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				min_eats;
	t_time			start;
	bool			stop;
}				t_info;

typedef struct s_philo
{
	int				number;
	t_info			*info;
	t_time			last_eat;
	long			nb_eats;
	sem_t			*forks;
}				t_philo;

#endif
