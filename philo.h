/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mboukhal <mboukhal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/17 14:01:02 by mboukhal          #+#    #+#             */
/*   Updated: 2022/05/17 10:46:36 by mboukhal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <sys/time.h>
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <pthread.h>

// *[number_of_philo] 		philo_nb
// *[time_to_die] 			tt_die
// *[time_to_eat] 			tt_eat
// *[time_to_sleep] 		tt_sleep
// [number_of_times_each_	max_meal
//	philosopher_must_eat] 


struct s_rules;
//			privet
typedef struct philo
{
	pthread_t		tid;
	int				id;
	int				l_fork;
	int				r_fork;
	int				meal_nb;
	long long		last_meal_time;
	struct s_rules *root;

}			t_philo;

//			public
typedef struct s_rules
{
	int				philo_nb;
	int				tt_die;
	int				tt_sleep;
	int				tt_eat;
	int				max_meal;
	long long		start_time;
	int				die;
	pthread_mutex_t	fork[250];
	pthread_mutex_t	stdout_lock;
	pthread_mutex_t	cheak_meal_lock;
	t_philo			philo[250];		

}				t_rule;

int			w_error(char *str);
int			emulation(t_rule *rule);
int			init_rules(t_rule *rules, char **av, int ac);
long long	now_time(void);

#endif // !PHILO_H
