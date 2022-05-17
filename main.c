/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mboukhal <mboukhal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/15 11:38:04 by mboukhal          #+#    #+#             */
/*   Updated: 2022/05/16 21:18:11 by mboukhal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int  init_locks(t_rule *lock)
{
    int i;

    i = -1;
    while (++i < lock->philo_nb)
	{
        if (pthread_mutex_init(&(lock->fork[i]), NULL))
                break;
        lock->philo[i].id = i;
        lock->philo[i].l_fork = i;
        lock->philo[i].r_fork = (i + 1) % lock->philo_nb;
		lock->philo[i].root = lock;
		lock->philo[i].meal_nb = 0;
	}
	lock->die = 0;
    if (i == lock->philo_nb - 1)
        while (--i >= 0)
            pthread_mutex_destroy(&(lock->fork[i]));
    if (i == 0)
            return (w_error("Mutex init intializing error !"));
    if (pthread_mutex_init(&(lock->cheak_meal_lock), NULL))
            return (w_error("Mutex init intializing error !"));
	if (pthread_mutex_init(&(lock->stdout_lock), NULL))
            return (w_error("Mutex init intializing error !"));
    return (EXIT_SUCCESS);
}

int main(int ac, char **av)
{
    t_rule  philo_rules;

	if (ac < 5 || ac > 6)
		return (w_error("Invalid argument ..."));
    if (init_rules(&philo_rules, av, ac) || init_locks(&philo_rules))
        return (EXIT_FAILURE);
	return (emulation(&philo_rules));
}