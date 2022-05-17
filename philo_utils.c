/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mboukhal <mboukhal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/15 13:00:21 by mboukhal          #+#    #+#             */
/*   Updated: 2022/05/16 21:17:02 by mboukhal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	w_error(char *str)
{
	int	len;

	len = 0;
	while (str[len])
		len++;
	write(STDERR_FILENO, "\e[0;31mError:\e[0m\n\t\e[0;35m", 27);
	write(STDERR_FILENO, str, len);
	write(STDERR_FILENO, "\e[0m\n", 5);
	return (EXIT_FAILURE);
}

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

int	init_rules(t_rule *rules, char **av, int ac)
{
	int	i;
	int	j;

	i = 0;
	while (++i < ac)
	{
		j = -1;
		while (av[i][++j])
			if (!((av[i][j] >= 48 && av[i][j] <= 57) || av[i][0] == '+'))
                    return (w_error("Expected unsigned integers arguments !"));
	}
	if (ac == 6)
		rules->max_meal = ft_atoi(av[5]);
	if (rules->max_meal <= 0 && ac == 6)
            return (w_error("Last can not be less then 1"));
	else
		rules->max_meal = -1;
	rules->philo_nb = ft_atoi(av[1]);
	rules->tt_die = ft_atoi(av[2]);
	rules->tt_eat = ft_atoi(av[3]);
	rules->tt_sleep = ft_atoi(av[4]);
	if (rules->philo_nb < 2 || rules->philo_nb > 250 || rules->tt_die < 0
		|| rules->tt_eat < 0 || rules->tt_sleep < 0)
            return (w_error("Invalid arguments"));
    return (EXIT_SUCCESS);
}