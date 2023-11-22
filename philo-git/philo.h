/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpawson < tpawson@student.42adel.org.au    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/13 13:51:04 by tpawson           #+#    #+#             */
/*   Updated: 2023/11/22 04:08:39 by tpawson          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H
# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <sys/time.h>
# include <pthread.h>

typedef struct s_info
{
	u_int64_t		start_t;
	u_int64_t		tte;
	u_int64_t		tts;
	u_int64_t		ttd;
	int				tte_nb;
	int				total_philos;
	int				finished;
	int				dead;
	pthread_t		*thread_id;
	pthread_mutex_t	*forks;
	pthread_mutex_t	write;
	pthread_mutex_t	lock;
	struct s_philo	*philo;
}			t_info;

typedef struct s_philo
{
	t_info			*info;
	pthread_t		thread;
	int				philo_nb;
	int				times_eaten;
	int				state;
	int				e_bool;
	u_int64_t		t_until_d;
	pthread_mutex_t	*left;
	pthread_mutex_t	*right;
	pthread_mutex_t	lock;
}			t_philo;

//utils
void		usleep_helper(useconds_t time);
long long	ft_atoll(char *s);
int			ft_atoi(char *s);
int			ft_strcmp(char *s1, char *s2);

//init
int			program_setup(char **argv, t_info *pro_info);

//state_n_time
u_int64_t	get_time(void);
void		announce(char *s, t_philo *philo);
void		eat_cycle(t_philo *philo);

//threads
int			thread_init(t_info *pro_info);
void		*routine(void *ptr);

//philo
int			main(int argc, char **argv);
int			ft_close(t_info *pro_info, int flag);

#endif
