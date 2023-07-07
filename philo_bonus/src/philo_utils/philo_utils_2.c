/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils_2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylyoussf <ylyoussf@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/06 18:28:29 by ylyoussf          #+#    #+#             */
/*   Updated: 2023/07/07 20:52:59 by ylyoussf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/philo_utils.h"

void	clean(t_info *info)
{
	sem_close(info->forks);
	sem_close(info->print);
	sem_unlink(FORKS);
	sem_unlink(PRINT);
}

void	ft_reaper(t_philo *philo)
{

}
