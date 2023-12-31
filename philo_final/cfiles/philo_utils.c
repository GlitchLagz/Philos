/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpawson < tpawson@student.42adel.org.au    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/18 15:04:04 by tpawson           #+#    #+#             */
/*   Updated: 2023/11/24 11:50:37 by tpawson          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"
// useconds_t = unsiged int, is in microseconds

int	ft_atoi(char *s)
{
	int	i;
	int	pon;
	int	res;

	pon = 1;
	res = 0;
	i = 0;
	while (s[i] == ' ' || s[i] == '\t' || s[i] == '\r'
		|| s[i] == '\v' || s[i] == '\f' || s[i] == '\n')
		i++;
	if (s[i] == '+' || s[i] == '-')
	{
		if (s[i] == '-')
			pon = -1;
		i++;
	}
	while (s[i] >= '0' && s[i] <= '9')
	{
		res = (res * 10) + (s[i] - 48);
		i++;
	}
	return (res * pon);
}

long long	ft_atoll(char *s)
{
	int			i;
	int			pon;
	long long	res;

	pon = 1;
	res = 0;
	i = 0;
	while (s[i] == ' ' || s[i] == '\t' || s[i] == '\r'
		|| s[i] == '\v' || s[i] == '\f' || s[i] == '\n')
		i++;
	if (s[i] == '+' || s[i] == '-')
	{
		if (s[i] == '-')
			pon = -1;
		i++;
	}
	while (s[i] >= '0' && s[i] <= '9')
	{
		res = (res * 10) + (s[i] - 48);
		i++;
	}
	return (res * pon);
}

int	ft_strcmp(char *s1, char *s2)
{
	int	i;

	i = 0;
	while (s1[i] == s2[i] && s1[i] && s2[i])
		i++;
	return (s1[i] - s2[i]);
}

u_int64_t	get_time(void)
{
	struct timeval	time;

	if (gettimeofday(&time, NULL))
		return (0);
	return ((time.tv_sec * (u_int64_t)1000) + (time.tv_usec / 1000));
}

void	usleep_helper(useconds_t time)
{
	u_int64_t	start;

	start = get_time();
	while ((get_time() - start) < time)
		usleep(time / 10);
}
