/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enorie <enorie@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/02 17:19:10 by enorie            #+#    #+#             */
/*   Updated: 2024/04/17 15:16:17 by enorie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

long long	ft_get_time(void)
{
	long long		r;
	struct timeval	time;

	gettimeofday(&time, NULL);
	r = time.tv_sec * 1000;
	r += time.tv_usec / 1000;
	return (r);
}

int	ft_rolling(t_arg *a)
{
	pthread_mutex_lock(&a->p[a->i].info->death);
	if (a->info->dead)
	{
		pthread_mutex_unlock(&a->p[a->i].info->death);
		return (0);
	}
	pthread_mutex_unlock(&a->p[a->i].info->death);
	if (a->info->use_tte && a->info->t_t_e == a->p[a->i].t_e)
		return (0);
	return (1);
}

void	ft_routine(t_arg *a)
{
	if (a->i % 2 == 0)
		ft_lock_mine(a);
	else
		ft_lock_other(a);
	if (a->n % 2 != 0)
		ft_usleep(a->info->t_e);
}

void	*ft_philo(void *arg)
{
	t_arg		*a;

	a = (t_arg *)arg;
	if (a->n == 1)
	{
		ft_write("has taken a fork", a);
		ft_usleep((a->p[a->i].info->t_d));
		ft_write("is dead", a);
		return (NULL);
	}
	pthread_mutex_lock(&a->info->start);
	pthread_mutex_unlock(&a->info->start);
	if (a->n % 2 == 0 && a->i % 2 == 0)
		ft_usleep(a->info->t_e * 0.5);
	while (ft_rolling(a))
		ft_routine(a);
	return (NULL);
}

void	ft_create_philo(char **argv, t_philos *philos,
	t_arg *args, t_info *info)
{
	int			i;
	long long	time;

	i = -1;
	time = ft_get_time();
	while (++i < info->n_philos)
	{
		philos[i].index = i;
		philos[i].info = info;
		philos[i].l_m = time;
		if (argv[5])
			philos[i].t_e = 0;
		args[i].start = time;
		args[i].p = philos;
		args[i].i = i;
		args[i].n = info->n_philos;
		args[i].info = info;
		pthread_create(&(philos[i].thread), NULL, &ft_philo, &args[i]);
	}
}
