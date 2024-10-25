/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hakobaya <hakobaya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/25 16:49:18 by hakobaya          #+#    #+#             */
/*   Updated: 2024/10/25 17:04:40 by hakobaya         ###   ########.fr       */
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
    ft_put_fd(ERROR_EXIT, "ERROR: Invalid arguments\n");
    ft_put_fd(ERROR_EXIT, "USAGE: ");
    ft_put_fd(ERROR_EXIT, "./philo num die eat sleep\n");
    ft_put_fd(ERROR_EXIT, "num : number of philosophers\n");
    ft_put_fd(ERROR_EXIT, "die : time to die [ms]\n");
    ft_put_fd(ERROR_EXIT, "eat : time to eat [ms]\n");
    ft_put_fd(ERROR_EXIT, "sleep : time to sleep [ms]\n");
    ft_put_fd(ERROR_EXIT, "option : [number_of_times_each_philosopher_must_eat] [ms]\n");
    ft_put_fd(ERROR_EXIT, "example [./philo 4 500 200 200]\n");
    return (1);
}

int main(int ac, char **av)
{
    (void)av;
    if (ac == 5 || ac == 6)
        printf("OK\n");
    else
        return (args_error());
}