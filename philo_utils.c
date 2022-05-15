/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mboukhal <mboukhal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/15 13:00:21 by mboukhal          #+#    #+#             */
/*   Updated: 2022/05/15 13:00:48 by mboukhal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	w_error(char *str)
{
	int	len;

	len = 0;
	while (str[len])
		len++;
	write(STDERR_FILENO, "\e[0;31mError:\e[0m\n\t", 20);
	write(STDERR_FILENO, str, len);
	write(STDERR_FILENO, "\n", 1);
	return (EXIT_FAILURE);
}