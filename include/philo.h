/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hakobaya <hakobaya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/25 16:57:45 by hakobaya          #+#    #+#             */
/*   Updated: 2024/10/25 17:10:25 by hakobaya         ###   ########.fr       */
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
}	t_config;

#endif