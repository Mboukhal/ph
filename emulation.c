/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   emulation.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mboukhal <mboukhal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/15 13:03:09 by mboukhal          #+#    #+#             */
/*   Updated: 2022/05/15 17:20:03 by mboukhal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void    clean_exit(t_rule *r)
{
    int i;
    
    i = -1;
    while (++i < r->philo_nb)
        pthread_join(r->philo[i].tid, NULL);
    i = -1;
    while (++i < r->philo_nb)
        pthread_mutex_destroy(&(r->fork[i]));
    pthread_mutex_destroy(&(r->cheak_meal_lock));
    pthread_mutex_destroy(&(r->stdout_lock));
}

void print_out(t_philo *p, char *message)
{
    pthread_mutex_lock(&(p->root->stdout_lock));
    if (!(p->root->die))
        printf("%lld ms %d %s\n", now_time() - p->root->start_time,
                p->id, message);
    pthread_mutex_unlock(&(p->root->stdout_lock));

}

void    start_eating(t_philo *ph)
{
    pthread_mutex_lock(&(ph->root->fork[ph->l_fork]));
    print_out(ph, "has taken a fork");
    pthread_mutex_unlock(&(ph->root->fork[ph->l_fork]));
    pthread_mutex_lock(&(ph->root->fork[ph->r_fork]));
    print_out(ph, "has taken a fork");
    pthread_mutex_unlock(&(ph->root->fork[ph->r_fork]));
    ph->meal_nb++;
}

void    *thread_action(void *arg)
{
    t_philo *ph;
    t_rule *r;

    ph = (t_philo *)arg;
    r = ph->root;
    pthread_mutex_lock(&(r->cheak_meal_lock));
    if (ph->meal_nb == r->max_meal)
        return (NULL);
    pthread_mutex_unlock(&(r->cheak_meal_lock));
    // while (!(r->die))
    // {
        start_eating(ph);
        // pthread_mutex_lock(&(r->cheak_meal_lock));
        // printf("|%d|\n", ph->meal_nb);
        // if (ph->meal_nb == r->max_meal)
        //     r->die = 0;
        // pthread_mutex_unlock(&(r->cheak_meal_lock));
        // start_eating(ph);
        // start_eating(ph);
    // }
    
    return (NULL);
}

int	emulation(t_rule *rule)
{
    int i;
    // t_philo *philo;
    // philo = rule->philo;

    rule->start_time = now_time();
    i = -1;
    while (++i < rule->philo_nb)
    {
        if (i % 2)
        {
            if (pthread_create(&(rule->philo[i].tid), NULL,
                thread_action, &(rule->philo[i])))
            {
                // clean_exit(rule, i);
                return(EXIT_FAILURE);
            }
        }
        rule->philo[i].last_meal_time = now_time();
    }
    i = -1;
    while (++i < rule->philo_nb)
    {
        if (!(i % 2))
        {
            if (pthread_create(&(rule->philo[i].tid), NULL, thread_action, &(rule->philo[i])))
                if (w_error("Thread fail creation !"))
                    return(EXIT_FAILURE);
            rule->philo[i].last_meal_time = now_time();
        }
    }
    clean_exit(rule);

    return (EXIT_SUCCESS);
}