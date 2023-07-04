/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylyoussf <ylyoussf@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/30 01:29:54 by ylyoussf          #+#    #+#             */
/*   Updated: 2023/07/04 17:18:41 by ylyoussf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/philo_utils.h"

void	print(t_philo *philo, char *doing)
{
	// bool	stop;

	printf("%lld\t%d\t%s\n",
		get_relative_time(philo->info->start),
		philo->number,
		doing);
}

sem_t	*init_semaphore(t_info *info)
{
	sem_t	*sem;
	sem_unlink(FORKS);
	sem = sem_open(FORKS, O_CREAT, 0644, info->nb_of_philos);
	if (sem == SEM_FAILED)
		(printf("Error: sem_open failed\n"), exit(-1));
	return (sem);
}
