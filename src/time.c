/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: david <david@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/19 10:57:44 by david             #+#    #+#             */
/*   Updated: 2025/04/27 12:20:30 by david            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

// =============================================================================
// current_time :
//
// gettimeofday() remplit cette structure avec le temps actuel
// le calcul final convertit tout en millisecondes
// time.tv_sec * 1000 : convertit les secondes en millisecondes
// time.tv_usec / 1000 : convertit les microsecondes en millisecondes
//
// =============================================================================
// ft_usleep :
//
// enregistre le temps de depart
// entre dans une boucle qui :
// vérifie continuellement le temps écoulé
// verifie aussi si la simulation est arreter
// compare avec la durée souhaitée
// fait une micro-pause de 500 microsecondes à chaque itération
//
// =============================================================================

size_t	current_time(void)
{
	struct timeval	time;

	if (gettimeofday(&time, NULL) == -1)
	{
		write(2, "gettimeofday() error\n", 22);
		return (0);
	}
	return (time.tv_sec * 1000 + time.tv_usec / 1000);
}

int	ft_usleep(size_t ms, t_table *table)
{
	size_t	start;

	start = current_time();
	while (current_time() - start < ms)
	{
		pthread_mutex_lock(&table->death_lock);
		if (table->program_run == false)
		{
			pthread_mutex_unlock(&table->death_lock);
			break ;
		}
		pthread_mutex_unlock(&table->death_lock);
		usleep(500);
	}
	return (0);
}
