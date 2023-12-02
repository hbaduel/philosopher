/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   second_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbaduel <hbaduel@student.42perpignan.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/27 00:32:48 by hbaduel           #+#    #+#             */
/*   Updated: 2023/12/02 23:59:58 by hbaduel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

int	ft_checkdeath(t_data *data, t_philo *philo)
{
	long	temp;

	pthread_mutex_lock(&philo->data->die);
	if (data->death == 1)
	{
		pthread_mutex_unlock(&philo->data->die);
		return (1);
	}
	temp = ft_timestamp();
	if (temp - philo->lasteat >= philo->data->td)
	{
		philo->data->death = 1;
		pthread_mutex_unlock(&philo->data->die);
		pthread_mutex_lock(&philo->data->print);
		printf("%s[%ld ms] %d died.\n", \
		RED, temp - philo->data->currenttime, philo->n);
		pthread_mutex_unlock(&philo->data->print);
		return (1);
	}
	else
		pthread_mutex_unlock(&philo->data->die);
	return (0);
}
