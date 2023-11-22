/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_init.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpawson < tpawson@student.42adel.org.au    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/27 15:41:12 by tpawson           #+#    #+#             */
/*   Updated: 2023/11/22 05:08:11 by tpawson          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

//Mutexes are used to prevent data races, where multiple 
// threads access shared data concurrently, resulting
// in inconsistencies

//Threads are units of execution that 
// run concurrently within a process they may need 
// mutexes to help with syching, like this task requires

int	philo_setup(t_info *pro_info)
{
	int	i;

	i = -1;
	while (++i < pro_info->total_philos)
	{
		pro_info->philo[i].info = pro_info;
		pro_info->philo[i].t_until_d = pro_info->ttd;
		pro_info->philo[i].state = 0;
		pro_info->philo[i].e_bool = 0;
		pro_info->philo[i].times_eaten = 0;
		pro_info->philo[i].philo_nb = i + 1;
		pthread_mutex_init(&pro_info->philo[i].lock, NULL);
	}
	return (0);
}

int	fork_setup(t_info *pro_info)
{
	int	i;

	i = -1;
	while (++i < pro_info->total_philos)
		pthread_mutex_init(&pro_info->forks[i], NULL);
	pro_info->philo[0].left = &pro_info->forks[0];
	pro_info->philo[0].right = &pro_info->forks[pro_info->total_philos - 1];
	i = 0;
	while (++i < pro_info->total_philos)
	{
		pro_info->philo[i].left = &pro_info->forks[i];
		pro_info->philo[i].right = &pro_info->forks[i - 1];
	}
	return (0);
}

int	allocate(t_info *pro_info)
{
	pro_info->thread_id = malloc(sizeof(pthread_t)
			* pro_info->total_philos * 1024);
	pro_info->forks = malloc(sizeof(pthread_mutex_t) * pro_info->total_philos);
	pro_info->philo = malloc(sizeof(t_philo) * pro_info->total_philos);
	if (!pro_info->philo || !pro_info->forks || !pro_info->thread_id)
		return (1);
	else
		return (0);
}

int	program_setup(char **argv, t_info *pro_info)
{
	int	err_check;

	err_check = 0;
	pro_info->total_philos = ft_atoi(argv[1]);
	pro_info->ttd = (u_int64_t) ft_atoll(argv[2]);
	pro_info->tte = (u_int64_t) ft_atoll(argv[3]);
	pro_info->tts = (u_int64_t) ft_atoll(argv[4]);
	if (argv[5])
		pro_info->tte_nb = ft_atoi(argv[5]);
	else
		pro_info->tte_nb = -1;
	if (pro_info->total_philos <= 0 || pro_info->total_philos > 200
		|| pro_info->ttd < 0 || pro_info->tte < 0 || pro_info->tts < 0)
		return (ft_close(pro_info, 1));
	err_check += allocate(pro_info);
	err_check += fork_setup(pro_info);
	err_check += philo_setup(pro_info);
	if (err_check >= 1)
		return (ft_close(pro_info, 1));
	pro_info->dead = 0;
	pro_info->finished = 0;
	pthread_mutex_init(&pro_info->lock, NULL);
	pthread_mutex_init(&pro_info->write, NULL);
	return (0);
}
