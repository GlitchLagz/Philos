/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_init.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpawson < tpawson@student.42adel.org.au    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/27 15:41:12 by tpawson           #+#    #+#             */
/*   Updated: 2023/11/24 16:39:44 by tpawson          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

//Mutexes are used to prevent data races, where multiple 
// threads access shared data/resources concurrently, resulting
// in inconsistencies

//Threads are units of execution that 
// run concurrently within a process they may need 
// mutexes to help with syching, like this task requires

static void	mutex_setup(t_both *both)
{
	int	i;

	both->philo = malloc(sizeof(t_philo) * both->pro_info->total_philos);
	i = -1;
	while (++i < both->pro_info->total_philos)
	{
		both->philo[i].philo_nb = i + 1;
		both->philo[i].last_ate = get_time();
		both->philo[i].info = both->pro_info;
		pthread_mutex_init(&both->philo[i].left, NULL);
	}
	i = -1;
	while (++i < both->pro_info->total_philos)
	{
		both->philo[i].right = &both->philo[(i + 1)
			% both->pro_info->total_philos].left;
		both->philo[i].r_locked = &both->philo[(i + 1)
			% both->pro_info->total_philos].l_locked;
	}
}

void	im_a_philophile(t_both *both)
{
	int	i;

	i = -1;
	while (++i < both->pro_info->total_philos)
	{
		if ((both->philo[i].philo_nb % 2 == 0)
			&& (*both->philo[i].r_locked == 0))
		{
			both->philo[i].first = 1;
			both->philo[i].l_locked = 1;
			*both->philo[i].r_locked = 1;
			both->philo[i].did_left = 1;
			both->philo[i].did_right = 1;
		}
	}
}

void	fuck_philo_pile_of_shit(t_both *both, char **argv)
{
	both->pro_info = malloc(sizeof(t_info));
	both->pro_info->total_philos = ft_atoi(argv[1]);
	both->pro_info->ttd = ft_atoi(argv[2]);
	both->pro_info->tte = ft_atoi(argv[3]);
	both->pro_info->tts = ft_atoi(argv[4]);
	if (argv[5])
		both->pro_info->tte_nb = ft_atoi(argv[5]);
	else
		both->pro_info->tte_nb = -1;
}

int	program_setup(char **argv, t_both *both)
{
	fuck_philo_pile_of_shit(both, argv);
	mutex_setup(both);
	im_a_philophile(both);
	both->pro_info->start_t = get_time();
	return (0);
}
