/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpawson < tpawson@student.42adel.org.au    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/13 13:51:04 by tpawson           #+#    #+#             */
/*   Updated: 2023/11/24 13:04:14 by tpawson          ###   ########.fr       */
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
	int				fin;
	int				eaten;
	int				dead;
}			t_info;

typedef struct s_philo
{
	struct s_info	*info;
	pthread_t		thread;
	int				is_dead;
	int				philo_nb;
	int				times_eaten;
	int				first;
	int				did_left;
	int				did_right;
	int				t_forks;
	int				l_locked;
	int				*r_locked;
	u_int64_t		last_ate;
	pthread_mutex_t	left;
	pthread_mutex_t	*right;
}			t_philo;

typedef struct s_both {
	struct s_philo	*philo;
	struct s_info	*pro_info;
}	t_both;

//utils
void		usleep_helper(useconds_t time);
u_int64_t	get_time(void);
long long	ft_atoll(char *s);
int			ft_atoi(char *s);
int			ft_strcmp(char *s1, char *s2);

//init
int			program_setup(char **argv, t_both *both);

//state_n_time
void		thinking(t_philo *philo);
void		announce(char *s, t_philo *philo);
void		eat_cycle(t_philo *philo);
void		take_forks(t_philo *philo);

//threads
int			thread_init(t_both *both);
void		*routine(void *ptr);

//philo
int			main(int argc, char **argv);
int			ft_close(t_both *both, int flag);

#endif
