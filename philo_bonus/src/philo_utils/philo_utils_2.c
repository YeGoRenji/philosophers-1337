/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils_2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylyoussf <ylyoussf@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/06 18:28:29 by ylyoussf          #+#    #+#             */
/*   Updated: 2023/07/08 20:49:48 by ylyoussf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/philo_utils.h"

void	clean(t_info *info, bool unlink)
{
	sem_close(info->forks);
	sem_close(info->print);
	sem_close(info->stop);
	if (!unlink)
		return ;
	sem_unlink(FORKS);
	sem_unlink(PRINT);
	sem_unlink(STOP);
}

void	*ft_reaper(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	while (true)
	{
		usleep(20);
		if (check_if_stop(philo))
			die(philo);
	}
	return (NULL);
}
