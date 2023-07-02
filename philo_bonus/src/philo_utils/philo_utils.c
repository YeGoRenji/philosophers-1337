/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylyoussf <ylyoussf@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/30 01:29:54 by ylyoussf          #+#    #+#             */
/*   Updated: 2023/07/02 17:29:22 by ylyoussf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/philo_utils.h"

sem_t	*init_semaphore(t_info *info)
{
	sem_t	*sem;
	if (sem_unlink("/forks"))
		exit(-1);
	sem = sem_open("/forks", O_CREAT, 0644, info->nb_of_philos);
	if (!sem)
		exit(-1);
	return (sem);
}
