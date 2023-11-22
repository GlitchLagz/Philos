/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_state_n_time.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpawson < tpawson@student.42adel.org.au    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/29 13:16:47 by tpawson           #+#    #+#             */
/*   Updated: 2023/11/22 04:21:03 by tpawson          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

u_int64_t	get_time(void)
{
	struct timeval	time;

	if (gettimeofday(&time, NULL))
		return (0);
	return ((time.tv_sec * (u_int64_t)1000) + (time.tv_usec / 1000));
}

void	announce(char *s, t_philo *philo)
{
	u_int64_t	time;

	pthread_mutex_lock(&philo->info->write);
	time = get_time() - philo->info->start_t;
	if (philo->info->dead == 0 && ft_strcmp(s, "died") == 0)
	{
		printf("%llu %d \033[1;31m%s\n", time, philo->philo_nb, s);
		philo->info->dead = 1;
	}
	if (philo->info->dead == 0)
		printf("%llu %d %s\n", time, philo->philo_nb, s);
	pthread_mutex_unlock(&philo->info->write);
}

void	drop_forks(t_philo *philo)
{
	pthread_mutex_unlock(philo->right);
	pthread_mutex_unlock(philo->left);
	announce("is sleeping", philo);
	usleep_helper(philo->info->tts);
}

void	take_forks(t_philo *philo)
{
	pthread_mutex_lock(philo->right);
	announce("has taken a fork", philo);
	pthread_mutex_lock(philo->left);
	announce("has taken a fork", philo);
}

void	eat_cycle(t_philo *philo)
{
	take_forks(philo);
	pthread_mutex_lock(&philo->lock);
	philo->e_bool = 1;
	philo->t_until_d = get_time() + philo->info->ttd;
	announce("is eating", philo);
	philo->times_eaten++;
	usleep_helper(philo->info->tte);
	philo->e_bool = 0;
	pthread_mutex_unlock(&philo->lock);
	drop_forks(philo);
}
