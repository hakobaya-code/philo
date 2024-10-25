/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hakobaya <hakobaya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/25 18:21:57 by hakobaya          #+#    #+#             */
/*   Updated: 2024/10/25 18:22:36 by hakobaya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"


bool mutex_init(t_config *config, pthread_mutex_t **forks, pthread_mutex_t *print_mutex)
{
    int i;

    *forks = malloc(sizeof(pthread_mutex_t) * config->number_of_philosophers);
    if (!forks)
        return (false);
    i = 0;
    while (i < config->number_of_philosophers)
    {
        if (pthread_mutex_init(&(*forks)[i], NULL) != 0)
            return (false);
    }
    if (pthread_mutex_init(print_mutex, NULL) != 0)
        return (false);
    return (true);
}

// 各フォークを管理するミューテックス配列を確保、出力用のミューテックスも確保
bool config_init(int ac, char **av, t_config *config)
{
    if (!is_number(av[1]) || !is_number(av[2]) || !is_number(av[3]) || !is_number(av[4]))
        return false;
    config->number_of_philosophers = (int)ft_atol(av[1]);
    config->time_to_die = ft_atol(av[2]);
    config->time_to_eat = ft_atol(av[3]);
    config->time_to_sleep = ft_atol(av[4]);
    if (ac == 6)
    {
        if (!is_number(av[5]))
            return (false);
        config->number_of_times_each_philosopher_must_eat = (int)ft_atol(av[5]);
    }
    else
        config->number_of_times_each_philosopher_must_eat = -1;
    if (config->number_of_philosophers <= 0 || config->time_to_die <= 0 ||
        config->time_to_eat <= 0 || config->time_to_sleep <= 0 ||
        (ac == 6 && config->number_of_times_each_philosopher_must_eat <= 0))
        return (false);
    return (true);
}

bool    philo_init(t_philo **philosophers, t_config *config)
{
    int i;

    *philosophers = (t_philo *)malloc(sizeof(t_philo) * config->number_of_philosophers);
    if (!*philosophers)
        return (false);
    i = 0;
    while (i < config->number_of_philosophers)
    {
        (*philosophers)[i].id = i + 1;
        (*philosophers)[i].left_fork = i;
        (*philosophers)[i].right_fork = (i + 1) % config->number_of_philosophers;
        (*philosophers)[i].eat_count = 0;
        (*philosophers)[i].last_eat_time = 0;
        (*philosophers)[i].config = config;
        i++;
    }
    return (true);
}
