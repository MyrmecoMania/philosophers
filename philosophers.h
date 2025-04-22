/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enorie <enorie@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/17 12:26:03 by enorie            #+#    #+#             */
/*   Updated: 2024/04/17 15:16:12 by enorie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <stdio.h>
# include <pthread.h>
# include <unistd.h>
# include <stdlib.h>
# include <sys/time.h>

# define ARG_ERROR "./philosophers number_of_philosophers time_to_die \
time_to_eat time_to_sleep [number_of_times_each_philosopher_must_eat]"

typedef struct s_info
{
	int				n_philos;
	int				t_d;
	int				t_e;
	int				t_s;
	int				t_t_e;
	int				use_tte;
	int				dead;
	int				stop;
	pthread_mutex_t	death;
	pthread_mutex_t	w;
	pthread_mutex_t	start;
	pthread_mutex_t	*fork;
}				t_info;

typedef struct s_philos
{
	t_info			*info;
	pthread_t		thread;
	int				index;
	long long		l_m;
	int				t_e;
}				t_philos;

typedef struct s_arg
{
	t_philos	*p;
	t_info		*info;
	int			i;
	int			n;
	long long	start;
}				t_arg;

int			ft_atoi(const char *nbr);
int			ft_strncmp(const char *s1, const char *s2, size_t n);
size_t		ft_strlen(const char *str);
long long	ft_get_time(void);
int			ft_rolling(t_arg *a);
void		ft_create_philo(char **argv, t_philos *philos, t_arg *args,
				t_info *info);
void		*check_death(void *arg);
void		ft_write(char *str, t_arg *a);
void		ft_usleep(long long time);
int			ft_init(char **argv, t_info **n, t_philos **philos, t_arg **args);
int			ft_c_d(t_arg *a);
int			ft_c_s(t_arg *a);
void		ft_death(pthread_t *death, t_arg *args);
void		ft_lock_mine(t_arg *a);
void		ft_lock_other(t_arg *a);

#endif
