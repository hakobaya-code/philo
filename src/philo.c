/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hakobaya <hakobaya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/25 18:23:00 by hakobaya          #+#    #+#             */
/*   Updated: 2024/10/26 00:34:16 by hakobaya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long    current_time()
{
    struct timeval time;
    gettimeofday(&time, NULL);
    return ((time.tv_sec * 1000) + (time.tv_usec / 1000));    
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
