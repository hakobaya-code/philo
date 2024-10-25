/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hakobaya <hakobaya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/25 16:49:18 by hakobaya          #+#    #+#             */
/*   Updated: 2024/10/25 18:24:31 by hakobaya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

bool is_number(char *str)
{
    int i;

    i = 0;
    if (str[i] == '\0')
        return (false);
    while (str[i])
    {
        if (str[i] < '0' || str[i] > '9')
            return (false);
        i++;
    }
    return (true);
}

bool create_threads(t_philo *philosophers, int num_philosophers)
{
    int i;

    i = 0;
    while (i < num_philosophers)
    {
        if (pthread_create(&philosophers[i].thread, NULL, philo_routine, &philosophers[i]) != 0)
        return (false);
    }
    return (true);
}

int main(int ac, char **av)
{
    t_config *config;
    pthread_mutex_t *forks;
    pthread_mutex_t print_mutex;
    t_philo *philosophers;
    int i;

    if (ac != 5 && ac != 6)
        return (args_error());

    config = (t_config *)malloc(sizeof(t_config));
    if (!config)
    {
        ft_put_fd(ERROR_FD, "ERROR: malloc error\n");
        return (1);
    }
    if (!(config_init(ac, av, config)))
    {
        ft_put_fd(ERROR_FD, "Initialization failed\n");
        free(config);
        return (1);
    }
    if (!mutex_init(config, &forks, &print_mutex))
    {
        ft_put_fd(ERROR_FD, "ERROR: Mutex initialization failed\n");
        free(config);
        return (1);
    }
    if (!philo_init(&philosophers, config))
    {
        ft_put_fd(ERROR_FD, "ERROR: Philosopher initialization failed\n");
        // ミューテックスの破棄
        i = 0;
        while (i < config->number_of_philosophers)
        {
            pthread_mutex_destroy(&forks[i]);
            i++;
        }
        pthread_mutex_destroy(&print_mutex);
        free(forks);
        free(config);
        return (1);
    }
    if (!create_threads(philosophers, config->number_of_philosophers))
    {
        ft_put_fd(ERROR_FD, "ERROR: Thread creation failed\n");
        // ミューテックスの破棄とメモリの解放
        i = 0;
        while (i < config->number_of_philosophers)
        {
            pthread_mutex_destroy(&forks[i]);
            i++;
        }
        pthread_mutex_destroy(&print_mutex);
        free(forks);
        free(philosophers);
        free(config);
        return (1);
    }
    ft_put_fd(1, "OK\n");
    i = 0;
    while (i < config->number_of_philosophers)
    {
        pthread_join(philosophers[i].thread, NULL);
        i++;
    }
    free_all(config, forks, philosophers, &print_mutex);
    return (0);
}