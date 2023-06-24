/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time_utils.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylyoussf <ylyoussf@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/24 17:43:06 by ylyoussf          #+#    #+#             */
/*   Updated: 2023/06/24 19:04:20 by ylyoussf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TIME_UTILS_H
# define TIME_UTILS_H

# include "structs.h"

long long	get_current_ms(void);
long long	get_timestamp(t_info *info);
void		milsleep(long long miliseconds);
#endif
