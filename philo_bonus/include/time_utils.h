/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time_utils.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylyoussf <ylyoussf@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/24 17:43:06 by ylyoussf          #+#    #+#             */
/*   Updated: 2023/07/08 01:11:52 by ylyoussf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TIME_UTILS_H
# define TIME_UTILS_H

# include "structs.h"

t_time		get_current_ms(void);
t_time		get_relative_time(t_time relative_to);
void		milsleep(t_time time_in_ms);
#endif
