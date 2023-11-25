/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpawson < tpawson@student.42adel.org.au    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/18 13:23:50 by tpawson           #+#    #+#             */
/*   Updated: 2023/11/24 16:36:23 by tpawson          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

//A process is an independent program with its own memory space and resources, 
// threads are within a process and can run concurrently, sharing the same 
// memory space and resources. Threads within the same process can communicate 
// better than processes, beacause they have the same address space.

int	ft_close(t_both *both, int flag)
{
	int	i;

	i = -1;
	while (++i < both->pro_info->total_philos)
		pthread_mutex_destroy(&both->philo[i].left);
	free(both->philo);
	free(both->pro_info);
	if (flag == 1)
		printf("ERR, CLOSING");
	if (flag == 0)
		printf("\n\033[0;35m:::::\033[0;36mFINISHED\033[0;35m:::::\n\n");
	return (0);
}

void	thinking(t_philo *philo)
{
	announce("is thinking", philo);
	while (1)
	{
		take_forks(philo);
		if (philo->did_left == 1 && philo->did_right == 1)
			return ;
	}
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
	t_both	both;

	if (err_check(argc, argv))
		return (printf("\n\n\033[1;31mARG ERROR!!!\n\n\n"));
	program_setup(argv, &both);
	thread_init(&both);
	return (ft_close(&both, 0));
}
