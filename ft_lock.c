/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lock.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enorie <enorie@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 15:09:59 by enorie            #+#    #+#             */
/*   Updated: 2024/04/17 15:16:29 by enorie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	ft_lock_mine(t_arg *a)
{
	pthread_mutex_lock(&a->info->fork[a->i]);
	ft_write("has taken a fork", a);
	if (a->i == (a->n - 1))
		pthread_mutex_lock(&a->info->fork[0]);
	else
		pthread_mutex_lock(&(a->info->fork[a->i + 1]));
	ft_write("has taken a fork", a);
	ft_write("is eating", a);
	pthread_mutex_unlock(&a->info->fork[a->i]);
	if (a->i == (a->n - 1))
		pthread_mutex_unlock(&a->info->fork[0]);
	else
		pthread_mutex_unlock(&(a->info->fork[a->i + 1]));
	ft_write("is sleeping", a);
	ft_write("is thinking", a);
}

void	ft_lock_other(t_arg *a)
{
	if (a->i == (a->n - 1))
		pthread_mutex_lock(&a->info->fork[0]);
	else
		pthread_mutex_lock(&(a->info->fork[a->i + 1]));
	ft_write("has taken a fork", a);
	pthread_mutex_lock(&a->info->fork[a->i]);
	ft_write("has taken a fork", a);
	ft_write("is eating", a);
	if (a->i == (a->n - 1))
		pthread_mutex_unlock(&a->info->fork[0]);
	else
		pthread_mutex_unlock(&(a->info->fork[a->i + 1]));
	pthread_mutex_unlock(&a->info->fork[a->i]);
	ft_write("is sleeping", a);
	ft_write("is thinking", a);
}
