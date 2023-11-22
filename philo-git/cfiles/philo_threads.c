/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_threads.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpawson < tpawson@student.42adel.org.au    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/04 21:39:08 by tpawson           #+#    #+#             */
/*   Updated: 2023/11/22 05:17:44 by tpawson          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

// Joining the threads allows for waiting
// for another thread to finish exeing
// before it starts exeing

void	*supervisor(void *ptr)
{
	t_philo	*philo;

	philo = (t_philo *) ptr;
	while (philo->info->dead == 0)
	{
		pthread_mutex_lock(&philo->lock);
		if (get_time() >= philo->t_until_d && philo->e_bool == 0)
			announce("died", philo);
		if (philo->times_eaten == philo->info->tte_nb)
		{
			pthread_mutex_lock(&philo->info->lock);
			philo->info->finished++;
			philo->times_eaten++;
			pthread_mutex_unlock(&philo->info->lock);
		}
		pthread_mutex_unlock(&philo->lock);
	}
	return ((void *)0);
}

void	*routine(void *ptr)
{
	t_philo	*philo;

	philo = (t_philo *) ptr;
	philo->t_until_d = get_time() + philo->info->ttd;
	if (pthread_create(&philo->thread, NULL, &supervisor, (void *)philo))
		return ((void *)1);
	while (philo->info->dead == 0)
	{
		eat_cycle(philo);
		announce("is thinking", philo);
	}
	if (pthread_join(philo->thread, NULL))
		return ((void *)1);
	return ((void *)0);
}

void	*tte_nb_route(void *ptr)
{
	t_philo	*philo;

	philo = (t_philo *) ptr;
	pthread_mutex_lock(&philo->info->write);
	printf("data val: %d", philo->info->dead);
	pthread_mutex_unlock(&philo->info->write);
	while (philo->info->dead == 0)
	{
		pthread_mutex_lock(&philo->lock);
		if (philo->info->finished >= philo->info->total_philos)
			philo->info->dead = 1;
		pthread_mutex_unlock(&philo->lock);
	}
	return ((void *)0);
}

int	thread_init(t_info *pro_info)
{
	pthread_t	thread_0;
	int			i;

	i = -1;
	pro_info->start_t = get_time();
	if (pro_info->tte_nb >= 1)
		if (pthread_create(&thread_0, NULL, &tte_nb_route, &pro_info->philo[0]))
			return (1);
	while (++i < pro_info->total_philos)
	{
		if (pthread_create(&pro_info->thread_id[i],
				NULL, &routine, &pro_info->philo[i]))
			return (1);
		usleep_helper(1);
	}
	i = -1;
	while (i++ < pro_info->total_philos)
		if (pthread_join(pro_info->thread_id[i], NULL))
			return (1);
	return (0);
}
