/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hakobaya <hakobaya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/25 16:49:18 by hakobaya          #+#    #+#             */
/*   Updated: 2024/10/25 17:26:47 by hakobaya         ###   ########.fr       */
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

int ft_atoi(char *str)
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
        if (num > INT_MAX)
            return (-1);
        i++;
    }
    return ((int)num);
}

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

bool    validate_args(int ac, char **av)
{
    int i;

    i = 1;
    while (i < ac)
    {
        if (!is_number(av[i]))
            return (false);
        i++;
    }
    return (true);
}

// 引数を解析し、構造体に格納する関数
bool config_init(int ac, char **av, t_config *config)
{
    if (!is_number(av[1]) || !is_number(av[2]) || !is_number(av[3]) || !is_number(av[4]))
        return false;
    config->number_of_philosophers = ft_atoi(av[1]);
    config->time_to_die = ft_atoi(av[2]);
    config->time_to_eat = ft_atoi(av[3]);
    config->time_to_sleep = ft_atoi(av[4]);
    if (ac == 6)
    {
        if (!is_number(av[5]))
            return (false);
        config->number_of_times_each_philosopher_must_eat = ft_atoi(av[5]);
    }
    else
        config->number_of_times_each_philosopher_must_eat = -1;
    if (config->number_of_philosophers <= 0 || config->time_to_die <= 0 ||
        config->time_to_eat <= 0 || config->time_to_sleep <= 0 ||
        (ac == 6 && config->number_of_times_each_philosopher_must_eat <= 0))
        return (false);
    return (true);
}

int main(int ac, char **av)
{
    t_config *config;

    config = (t_config *)malloc(sizeof(t_config));
    if (!config)
        return (1);
    if (ac == 5 || ac == 6)
    {
        if (!validate_args(ac, av))
            return (1);
        if (!(config_init(ac, av, config)))
            return (1);
        ft_put_fd(1, "OK\n");
    }
    else
        return (args_error());
}