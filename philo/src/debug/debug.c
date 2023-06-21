/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylyoussf <ylyoussf@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/21 17:15:22 by ylyoussf          #+#    #+#             */
/*   Updated: 2023/06/21 17:32:42 by ylyoussf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/debug.h"

void	print_info(t_info *info)
{
	printf("*********************************\n");
	printf("#Philos : %d\n", info->nb_of_philos);
	printf("Time to die : %dms\n", info->time_to_die);
	printf("Time to eat : %dms\n", info->time_to_eat);
	printf("Time to sleep : %dms\n", info->time_to_sleep);
	if (info->min_eats != -1)
		printf("Min Time to eat : %dms\n", info->min_eats);
	printf("*********************************\n");
}
