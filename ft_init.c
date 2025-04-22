/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_init.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enorie <enorie@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 12:20:03 by enorie            #+#    #+#             */
/*   Updated: 2024/04/12 14:19:10 by enorie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

t_info	*ft_init3(char **argv)
{
	t_info	*info;

	info = malloc(sizeof(t_info));
	if (!info)
		return (NULL);
	info->n_philos = ft_atoi(argv[1]);
	info->t_d = ft_atoi(argv[2]);
	info->t_e = ft_atoi(argv[3]);
	info->t_s = ft_atoi(argv[4]);
	if (info->n_philos == -1 || info->t_d == -1
		|| info->t_e == -1 || info->t_s == -1)
		return (free(info), NULL);
	info->use_tte = 0;
	if (argv[5])
	{
		info->t_t_e = ft_atoi(argv[5]);
		info->use_tte = 1;
	}
	info->dead = 0;
	info->stop = 0;
	return (info);
}

t_info	*ft_init2(char **argv)
{
	t_info	*info;
	int		i;

	i = 0;
	info = ft_init3(argv);
	if (!info)
		return (NULL);
	info->fork = malloc(sizeof(pthread_mutex_t) * info->n_philos);
	if (!info->fork)
		return (free(info), NULL);
	while (i < info->n_philos)
	{
		if (pthread_mutex_init(&info->fork[i++], NULL))
			return (free(info->fork), free(info), NULL);
	}
	if (pthread_mutex_init(&info->w, NULL))
		return (free(info->fork), free(info), NULL);
	if (pthread_mutex_init(&info->start, NULL))
		return (free(info->fork), free(info), NULL);
	if (pthread_mutex_init(&info->death, NULL))
		return (free(info->fork), free(info), NULL);
	return (info);
}

int	ft_init(char **argv, t_info **n, t_philos **philos, t_arg **args)
{
	*n = ft_init2(argv);
	if (!*n)
		return (printf("Wrong arg"), 1);
	if ((*n)->n_philos < 1)
		return (free((*n)), printf("not enough philos"), 1);
	*philos = malloc(sizeof(t_philos) * (*n)->n_philos);
	if (!*philos)
		return (free(n), 1);
	*args = malloc(sizeof(t_arg) * (*n)->n_philos);
	if (!*args)
		return (free(n), free(philos), 1);
	return (0);
}

int	ft_c_d(t_arg *a)
{
	int	i;

	i = 0;
	pthread_mutex_lock(&a->info->death);
	if (a->info->dead)
		i = 1;
	pthread_mutex_unlock(&a->info->death);
	return (i);
}

int	ft_c_s(t_arg *a)
{
	int	i;

	i = 0;
	pthread_mutex_lock(&a->info->w);
	if (a->info->stop)
		i = 1;
	pthread_mutex_unlock(&a->info->w);
	return (i);
}
