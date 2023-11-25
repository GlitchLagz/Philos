/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_state_n_time.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpawson < tpawson@student.42adel.org.au    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/29 13:16:47 by tpawson           #+#    #+#             */
/*   Updated: 2023/11/24 16:20:48 by tpawson          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void	announce(char *s, t_philo *philo)
{
	u_int64_t				time;
	static pthread_mutex_t	lock = PTHREAD_MUTEX_INITIALIZER;

	pthread_mutex_lock(&lock);
	time = get_time() - philo->info->start_t;
	if (philo->info->dead == 0 && ft_strcmp(s, "died") == 0)
	{
		printf("%llu %d \033[1;31m%s\n", time, philo->philo_nb, s);
		philo->info->dead = 1;
	}
	if (philo->info->dead == 0)
		printf("%llu %d %s\n", time, philo->philo_nb, s);
	pthread_mutex_unlock(&lock);
}

void	drop_forks(t_philo *philo)
{
	pthread_mutex_unlock(&(*philo->right));
	pthread_mutex_unlock(&philo->left);
	philo->first = 0;
	philo->did_left = 0;
	philo->did_right = 0;
	philo->l_locked = 0;
	*philo->r_locked = 0;
}

void	take_forks(t_philo *philo)
{
	static pthread_mutex_t	lock = PTHREAD_MUTEX_INITIALIZER;

	pthread_mutex_lock(&lock);
	if (((philo->did_left == 1 && (*philo->r_locked) == 0) && philo
			->info->fin == 0) || (*philo->r_locked == 0
			&& philo->info->fin == 0))
	{
		*philo->r_locked = 1;
		philo->did_right = 1;
		pthread_mutex_lock(&(*philo->right));
		announce("has taken a fork", philo);
	}
	else if (philo->did_right == 1 && philo->l_locked == 0
		&& philo->info->fin == 0)
	{
		philo->l_locked = 1;
		philo->did_left = 1;
		pthread_mutex_lock(&philo->left);
		announce("has taken a fork", philo);
	}
	pthread_mutex_unlock(&lock);
}

void	eaten_c(t_philo *philo)
{
	static pthread_mutex_t	lock = PTHREAD_MUTEX_INITIALIZER;

	pthread_mutex_lock(&lock);
	philo->info->eaten += 1;
	philo->times_eaten += 1;
	pthread_mutex_unlock(&lock);
}

void	eat_cycle(t_philo *philo)
{
	announce("is eating", philo);
	if (!philo->first)
		philo->last_ate = get_time();
	usleep_helper(philo->info->tte);
	drop_forks(philo);
	eaten_c(philo);
	announce("is sleeping", philo);
	usleep_helper(philo->info->tts);
}
