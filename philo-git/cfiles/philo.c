/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpawson < tpawson@student.42adel.org.au    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/18 13:23:50 by tpawson           #+#    #+#             */
/*   Updated: 2023/11/22 05:22:35 by tpawson          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

//A process is an independent program with its own memory space and resources, 
// threads are within a process and can run concurrently, sharing the same 
// memory space and resources. Threads within the same process can communicate 
// better than processes, beacause they have the same address space.

int	ft_close(t_info *pro_info, int flag)
{
	int	i;

	i = -1;
	while (++i < pro_info->total_philos)
	{
		pthread_mutex_destroy(&pro_info->philo[i].lock);
		pthread_mutex_destroy(&pro_info->forks[i]);
	}
	pthread_mutex_destroy(&pro_info->lock);
	pthread_mutex_destroy(&pro_info->write);
	if (flag == 0)
		printf("\n\033[0;35m:::::\033[0;36mFINISHED\033[0;35m:::::\n\n");
	return (1);
}

int	philo_one_case(t_info *pro_info)
{
	pro_info->start_t = get_time();
	if (pro_info->start_t == 0)
		ft_close(pro_info, 1);
	if (pthread_create(&pro_info->thread_id[0],
			NULL, &routine, &pro_info->philo[0]))
		return (ft_close(pro_info, 1));
	pthread_detach(pro_info->thread_id[0]);
	while (pro_info->dead == 0)
		usleep_helper(0);
	ft_close(pro_info, 0);
	return (0);
}

int	err_check(int argc, char **argv)
{
	int	i;
	int	k;

	if (argc != 5 && argc != 6)
		return (1);
	i = 1;
	while (argv[i])
	{
		k = 0;
		while (argv[i][k])
		{
			while (argv[i][k] == ' ')
				k++;
			if (argv[i][k] < '0' || argv[i][k] > '9')
				return (1);
			k++;
		}
		i++;
	}
	return (0);
}

int	main(int argc, char **argv)
{
	t_info	pro_info;

	if (err_check(argc, argv))
		return (printf("\n\n\033[1;31mARG ERROR!!!\n\n\n"));
	program_setup(argv, &pro_info);
	if (pro_info.total_philos == 1)
		return (philo_one_case(&pro_info));
	else
		if (thread_init(&pro_info))
			ft_close(&pro_info, 1);
	ft_close(&pro_info, 0);
	return (0);
}
