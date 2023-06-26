/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylyoussf <ylyoussf@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/24 17:41:20 by ylyoussf          #+#    #+#             */
/*   Updated: 2023/06/26 01:55:41 by ylyoussf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/time_utils.h"

long long	get_current_ms(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return (time.tv_sec * 1000 + time.tv_usec / 1000);
}

long long	get_timestamp(t_info *info)
{
	if (get_current_ms() - info->starting_ms < 0)
		printf("why %lld ?\n", get_current_ms() - info->starting_ms);
	return (get_current_ms() - info->starting_ms);
}

void	milsleep(long long time_in_ms)
{
	long long	start;

	start = get_current_ms();
	while (get_current_ms() - start < time_in_ms)
		usleep(100);
}
// void	milsleep(unsigned int miliseconds)
// {
// 	usleep(1000 * miliseconds);
// }
