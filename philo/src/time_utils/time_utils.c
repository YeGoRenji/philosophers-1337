/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylyoussf <ylyoussf@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/24 17:41:20 by ylyoussf          #+#    #+#             */
/*   Updated: 2023/07/08 01:45:42 by ylyoussf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/time_utils.h"

t_time	get_current_ms(void)
{
	struct timeval	time;
	t_time			t;

	gettimeofday(&time, NULL);
	t = time.tv_sec * 1000 + time.tv_usec / 1000;
	return (t);
}

t_time	get_relative_time(t_time relative_to)
{
	t_time	relative_time;

	relative_time = get_current_ms() - relative_to;
	return (relative_time);
}

void	milsleep(t_time time_in_ms)
{
	t_time	start;

	start = get_current_ms();
	while (get_relative_time(start) < time_in_ms)
		usleep(100);
}
