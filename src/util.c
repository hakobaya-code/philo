/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hakobaya <hakobaya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/25 18:23:37 by hakobaya          #+#    #+#             */
/*   Updated: 2024/10/25 18:24:18 by hakobaya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int ft_strlen(char *str)
{
    int i;

    i = 0;
    while (str[i] != '\0')
        i++;
    return (i);
}

void    ft_put_fd(int fd, char *msg)
{
    write(fd, msg, ft_strlen(msg));
}

int    args_error()
{
    ft_put_fd(ERROR_FD, "ERROR: Invalid arguments\n");
    ft_put_fd(ERROR_FD, "USAGE: ");
    ft_put_fd(ERROR_FD, "./philo num die eat sleep\n");
    ft_put_fd(ERROR_FD, "num : number of philosophers\n");
    ft_put_fd(ERROR_FD, "die : time to die [ms]\n");
    ft_put_fd(ERROR_FD, "eat : time to eat [ms]\n");
    ft_put_fd(ERROR_FD, "sleep : time to sleep [ms]\n");
    ft_put_fd(ERROR_FD, "option : [number_of_times_each_philosopher_must_eat] [ms]\n");
    ft_put_fd(ERROR_FD, "example [./philo 4 500 200 200]\n");
    return (1);
}


long ft_atol(char *str)
{
    int i;
    long num;

    i = 0;
    num = 0;
    while (str[i])
    {
        if (str[i] < '0' || str[i] > '9')
            return (-1);
        num = num * 10 + (str[i] - '0');
        if (num > LONG_MAX)
            return (-1);
        i++;
    }
    return (num);
}

void    free_all(t_config *config, pthread_mutex_t *forks, t_philo *philosophers, pthread_mutex_t *print_mutex)
{
    int i;

    i = 0;
    while (i < config->number_of_philosophers)
    {
        pthread_mutex_destroy(&forks[i]);
        i++;
    }
    pthread_mutex_destroy(print_mutex);
    free(forks);
    free(philosophers);
    free(config);
}