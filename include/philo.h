/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hakobaya <hakobaya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/25 16:57:45 by hakobaya          #+#    #+#             */
/*   Updated: 2024/10/25 18:02:42 by hakobaya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <limits.h>
# include <stdbool.h>
# include <string.h>
# include <sys/time.h>
# include <unistd.h>
# include <stdlib.h>

# include <stdio.h>

# define ERROR_FD 2

typedef enum e_status
{
	THINKING,
	EATING,
	SLEEPING,
	FORK,
	DIED
}	t_status;

typedef struct s_config
{
	int				number_of_philosophers;       // 哲学者の数
	long			time_to_die;      // 死亡するまでの時間
	long			time_to_eat;      // 食事にかかる時間
	long			time_to_sleep;    // 睡眠にかかる時間
	int				number_of_times_each_philosopher_must_eat;        // 必須の食事回数
    pthread_mutex_t    *forks;
    pthread_mutex_t    print_mutex;

}	t_config;

typedef struct s_philo
{
    int             id;
    int             left_fork;
    int             right_fork;
    int             eat_count;
    long            last_eat_time;
    t_config        *config;
    pthread_t       thread;
}   t_philo;


int     ft_strlen(char *str);
void    ft_put_fd(int fd, char *msg);
int     args_error();
long    ft_atol(char *str);
bool    is_number(char *str);
bool    config_init(int ac, char **av, t_config *config);
bool    mutex_init(t_config *config, pthread_mutex_t **forks, pthread_mutex_t *print_mutex);
bool    philo_init(t_philo **philosophers, t_config *config);
bool    create_threads(t_philo *philosophers, int num_philosophers);
void    *philo_routine(void *arg);
void    free_all(t_config *config, pthread_mutex_t *forks, t_philo *philosophers, pthread_mutex_t *print_mutex);

#endif