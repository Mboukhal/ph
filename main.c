/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mboukhal <mboukhal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/15 11:38:04 by mboukhal          #+#    #+#             */
/*   Updated: 2022/05/15 17:17:15 by mboukhal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long long	now_time(void)
{
	struct timeval	t;

	gettimeofday(&t, NULL);
	return ((t.tv_sec * 1000) + (t.tv_usec / 1000));
}

static unsigned int	ft_atoi(char *s)
{
	unsigned int	result;
	int				i;

	i = 0;
	result = 0;
	if (s[0] == '+')
		i++;
	while (s[i])
		result = (result * 10) + (s[i++] - 48);
	return (result);
}

static int	init_rules(t_rule *rules, char **av, int ac)
{
	int	i;
	int	j;

	i = 0;
	while (++i < ac)
	{
		j = -1;
		while (av[i][++j])
			if (!((av[i][j] >= 48 && av[i][j] <= 57) || av[i][0] == '+'))
				if (w_error("Expected unsigned integers arguments !"))
                    return (EXIT_FAILURE);

	}
	if (ac == 6)
		rules->max_meal = ft_atoi(av[5]);
	if (rules->max_meal <= 0 && ac == 6)
    {
		if (w_error("Last can not be less then 1"))
            return (EXIT_FAILURE);
    }
	else
		rules->max_meal = -1;
	rules->philo_nb = ft_atoi(av[1]);
	rules->tt_die = ft_atoi(av[2]);
	rules->tt_eat = ft_atoi(av[3]);
	rules->tt_sleep = ft_atoi(av[4]);
	if (rules->philo_nb < 2 || rules->philo_nb > 250 || rules->tt_die < 0
		|| rules->tt_eat < 0 || rules->tt_sleep < 0)
		if (w_error("Invalid arguments"))
            return (EXIT_FAILURE);
    rules->die = 0;
    return (EXIT_SUCCESS);
}

static int  init_locks(t_rule *lock)
{
    int i;

    i = -1;
    while (++i < lock->philo_nb)
	{
        if (pthread_mutex_init(&(lock->fork[i]), NULL))
            if (w_error("Mutex init intializing error !"))
                break;
		// printf("|%d|\n", i);
        lock->philo[i].id = i;
        lock->philo[i].l_fork = i;
        lock->philo[i].r_fork = (i + 1) % lock->philo_nb;
		lock->philo[i].root = lock;
		lock->philo[i].meal_nb = 0;
	}
    if (i == lock->philo_nb - 1)
        while (--i >= 0)
            pthread_mutex_destroy(&(lock->fork[i]));
    if (i == 0)
            return (EXIT_FAILURE);
    if (pthread_mutex_init(&(lock->cheak_meal_lock), NULL))
        if (w_error("Mutex init intializing error !"))
            return (EXIT_FAILURE);
	if (pthread_mutex_init(&(lock->stdout_lock), NULL))
        if (w_error("Mutex init intializing error !"))
            return (EXIT_FAILURE);
    return (EXIT_SUCCESS);
}

int main(int ac, char **av)
{
    t_rule  philo_rules;

	if (ac < 5 || ac > 6)
		return (w_error("Invalid argument"));
    if (init_rules(&philo_rules, av, ac) || init_locks(&philo_rules))
        return (EXIT_FAILURE);
    if (emulation(&philo_rules))
        return (EXIT_FAILURE);
    return (EXIT_SUCCESS);
}