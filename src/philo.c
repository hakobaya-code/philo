/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hakobaya <hakobaya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/25 18:23:00 by hakobaya          #+#    #+#             */
/*   Updated: 2024/10/26 01:16:25 by hakobaya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void    *monitoring_routine(void *arg)
{
    t_config *config;
    int i;

    config = (t_config *)arg;
    while (1)
    {
        i = 0;
        while (i < config->number_of_philosophers)
        {
            pthread_mutex_lock(&config->print_mutex);
            if ((current_time() - config->philosophers[i].last_eat_time) > config->time_to_die)
            {
                printf("Philosopher %d died\n", config->philosophers[i].id);
                pthread_mutex_unlock(&config->print_mutex);
                exit(0);
            }
            pthread_mutex_unlock(&config->print_mutex);
            i++;
        }
        usleep(1000);
    }
    return (NULL);
}



void    *philo_routine(void *arg)
{
    t_philo *philo;

    philo = (t_philo *)arg;
    while (1)
    {
        // 考える
        pthread_mutex_lock(&philo->config->print_mutex);
        printf("Philosopher %d is thinking\n", philo->id);
        pthread_mutex_unlock(&philo->config->print_mutex);

        // 右フォークを取得
        pthread_mutex_lock(&philo->config->forks[philo->right_fork]);
        pthread_mutex_lock(&philo->config->print_mutex);
        printf("Philosopher %d has taken a fork\n", philo->id);
        pthread_mutex_unlock(&philo->config->print_mutex);
        
        // 左フォークを取得
        pthread_mutex_lock(&philo->config->forks[philo->left_fork]);
        pthread_mutex_lock(&philo->config->print_mutex);
        printf("Philosopher %d has taken a fork\n", philo->id);
        pthread_mutex_unlock(&philo->config->print_mutex);
        
        // 食べる
        pthread_mutex_lock(&philo->config->print_mutex);
        printf("Philosopher %d is eating\n", philo->id);
        pthread_mutex_unlock(&philo->config->print_mutex);
        philo->eat_count++;
        
        // 最後に食事をした時間を現在の時間に更新
        philo->last_eat_time = current_time();
        
        // 食事時間のシミュレーション
        usleep(philo->config->time_to_eat * 1000);

        // フォークを返す
        pthread_mutex_unlock(&philo->config->forks[philo->left_fork]);
        pthread_mutex_unlock(&philo->config->forks[philo->right_fork]);

        // 眠る
        pthread_mutex_lock(&philo->config->print_mutex);
        printf("Philosopher %d is sleeping\n", philo->id);
        pthread_mutex_unlock(&philo->config->print_mutex);
        usleep(philo->config->time_to_sleep * 1000);
    }
    return (NULL);
}
