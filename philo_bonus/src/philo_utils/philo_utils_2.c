/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils_2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylyoussf <ylyoussf@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/06 18:28:29 by ylyoussf          #+#    #+#             */
/*   Updated: 2023/07/10 16:11:13 by ylyoussf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/philo_utils.h"

void	clean(t_info *info, bool unlink)
{
	sem_close(info->forks);
	sem_close(info->print);
	if (!unlink)
		return ;
	sem_unlink(FORKS);
	sem_unlink(PRINT);
}

void	*ft_reaper(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	while (true)
	{
		if (check_if_stop(philo))
			die(philo);
	}
	return (NULL);
}
