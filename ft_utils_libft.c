/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils_libft.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enorie <enorie@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 17:11:16 by enorie            #+#    #+#             */
/*   Updated: 2024/04/10 14:40:50 by enorie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	ft_atoi(const char *nbr)
{
	int		i;
	long	r;
	int		s;

	i = 0;
	r = 0;
	s = 1;
	while (nbr[i] && !(nbr[i] > 47 && nbr[i] < 58))
		i++;
	if (!nbr[i])
		return (-1);
	while (nbr[i] && (nbr[i] > 47 && nbr[i] < 58) && r < 2147483647)
	{
		r = r * 10 + (nbr[i] - '0');
		i++;
	}	
	if (r > 2147483647)
		return (-1);
	return (r * s);
}

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	i;

	i = 0;
	if (n == 0)
		return (0);
	while (s1[i] && s2[i] && s1[i] == s2[i] && i < n - 1)
		i++;
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}

size_t	ft_strlen(const char *str)
{
	size_t	i;

	i = 0;
	if (!str)
		return (i);
	while (str[i])
		i++;
	return (i);
}

void	ft_usleep(long long time)
{
	long long	i;

	i = ft_get_time();
	while (ft_get_time() - i <= time)
		usleep(50);
}
