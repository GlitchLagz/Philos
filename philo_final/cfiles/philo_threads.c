/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_threads.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpawson < tpawson@student.42adel.org.au    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/04 21:39:08 by tpawson           #+#    #+#             */
/*   Updated: 2023/11/24 15:05:31 by tpawson          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

// Joining the threads allows for waiting
// for another thread to finish exeing
// before it starts exeing

void	*monitor(void *ptr)
{
	t_both	*both;
	int		tt_e;

	both = (t_both *)ptr;
	tt_e = both->pro_info->tte_nb * both->pro_info->total_philos;
	while (1)
	{
		if (both->pro_info->eaten >= tt_e)
		{
			both->pro_info->fin = 1;
			return (NULL);
		}
		else if (both->pro_info->dead == 1)
			return (NULL);
	}
}

void	*supervisor(void *ptr)
{
	t_both		*both;
	int			i;
	u_int64_t	thyme;

	both = (t_both *) ptr;
	while (1)
	{
		i = -1;
		while (++i < both->pro_info->total_philos)
		{
			thyme = get_time() - both->philo[i].last_ate;
			if (thyme > both->pro_info->ttd)
			{
				announce("died", both->philo);
				both->pro_info->dead = 1;
				return (NULL);
			}
			else if (both->pro_info->fin)
				return (NULL);
		}
	}
}

void	*routine(void *ptr)
{
	t_philo *const	philo = (t_philo *)ptr;

	if (philo->first == 1)
	{
		pthread_mutex_lock(&philo->left);
		pthread_mutex_lock(&(*philo->right));
		announce("has taken a fork", philo);
		announce("has taken a fork", philo);
		eat_cycle(philo);
	}
	while (1)
	{
		if (philo->info->dead || philo->info->fin)
			return ((void *) 0);
		take_forks(philo);
		if (philo->did_left == 1 && philo->did_right == 1)
			eat_cycle(philo);
		thinking(philo);
	}
	return ((void *)0);
}

int	thread_init(t_both *both)
{
	pthread_t	thread_sup;
	pthread_t	thread_mon;
	int			i;

	i = -1;
	if (both->pro_info->tte_nb != -1)
	{
		both->pro_info->eaten = 0;
		pthread_create(&thread_mon, NULL, &monitor, both);
	}
	while (++i < both->pro_info->total_philos)
		pthread_create(&both->philo[i].thread, NULL, &routine, &both->philo[i]);
	pthread_create(&thread_sup, NULL, &supervisor, both);
	pthread_join(thread_mon, NULL);
	pthread_join(thread_sup, NULL);
	while (i--)
	{
		pthread_detach(both->philo[i].thread);
		if (both->pro_info->dead == 1 || both->pro_info->fin == 1)
			return (0);
	}
	return (0);
}
