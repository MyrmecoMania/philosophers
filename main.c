/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enorie <enorie@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/28 14:39:13 by enorie            #+#    #+#             */
/*   Updated: 2024/04/17 13:17:33 by enorie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	ft_write(char *str, t_arg *a)
{
	long long	time;

	pthread_mutex_lock(&a->info->w);
	if (ft_strncmp(str, "is dead", ft_strlen(str)))
	{
		if (ft_c_d(a))
		{
			pthread_mutex_unlock(&a->info->w);
			return ;
		}
	}
	time = ft_get_time();
	printf("%lld %d %s\n", (time - a->start), a->i + 1, str);
	if (!ft_strncmp(str, "is eating", ft_strlen(str)))
	{
		a->p[a->i].t_e += 1;
		if (a->info->use_tte && a->p[a->i].t_e == a->info->t_t_e)
			a->info->stop = 1;
		a->p[a->i].l_m = time;
	}
	pthread_mutex_unlock(&a->info->w);
	if (!ft_strncmp(str, "is eating", ft_strlen(str)))
		ft_usleep(a->info->t_e);
	else if (!ft_strncmp(str, "is sleeping", ft_strlen(str)))
		ft_usleep(a->info->t_s);
}

void	*check_death(void *arg)
{
	t_arg		*a;
	int			i;

	a = (t_arg *)arg;
	while (!ft_c_s(a))
	{
		usleep(5000);
		pthread_mutex_lock(&a->info->w);
		pthread_mutex_lock(&a->info->death);
		i = -1;
		while (++i < a->info->n_philos)
		{
			if ((ft_get_time() - a->p[i].l_m) >= a->info->t_d)
			{
				printf("%lld %d %s\n",
					(ft_get_time() - a->start), i + 1, "is dead");
				a->info->dead = 1;
				pthread_mutex_unlock(&a->info->death);
				return (pthread_mutex_unlock(&a->info->w), NULL);
			}
		}	
		pthread_mutex_unlock(&a->info->w);
		pthread_mutex_unlock(&a->info->death);
	}
	return (NULL);
}

int	main(int argc, char **argv)
{
	t_info			*n;
	t_philos		*philos;
	t_arg			*args;
	pthread_t		death;
	int				i;

	n = NULL;
	philos = NULL;
	args = NULL;
	if (argc < 5 || argc > 6)
		return (printf(ARG_ERROR), 1);
	if (ft_init(argv, &n, &philos, &args))
		return (1);
	pthread_mutex_lock(&n->start);
	ft_create_philo(argv, philos, args, n);
	pthread_mutex_unlock(&(n->start));
	if (n->n_philos > 1)
		pthread_create(&death, NULL, &check_death, args);
	i = 0;
	while (i < n->n_philos)
		pthread_join(philos[i++].thread, NULL);
	if (n->n_philos > 1)
		pthread_join(death, NULL);
	return (pthread_mutex_lock(&n->w), pthread_mutex_unlock(&n->w),
		free(philos), free(args), free(n->fork), free(n), 0);
}
