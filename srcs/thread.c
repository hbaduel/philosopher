/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbaduel <hbaduel@student.42perpignan.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/21 11:08:26 by hbaduel           #+#    #+#             */
/*   Updated: 2023/12/02 23:59:53 by hbaduel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

int	ft_sleep(t_data	*data, t_philo *philo)
{
	long	temp;

	if (philo->status == 4)
	{
		temp = ft_timestamp();
		pthread_mutex_lock(&data->print);
		printf("%s[%ld ms] %d is sleeping.\n", BLUE, \
		temp - data->currenttime, philo->n);
		pthread_mutex_unlock(&data->print);
		if (data->ts + data->te >= data->td)
		{
			ft_usleep(data->td);
			ft_checkdeath(data, philo);
			return (1);
		}
		ft_usleep(data->ts);
		philo->status = 0;
	}
	return (0);
}

void	ft_eat(t_data *data, t_philo *philo)
{
	long	temp;

	if (philo->status == 3)
	{
		temp = ft_timestamp();
		pthread_mutex_lock(&data->print);
		printf("%s[%ld ms] %d is eating. (repas numero %d)\n", GREEN, \
		temp - data->currenttime, philo->n, data->tme - philo->musteat + 1);
		pthread_mutex_unlock(&data->print);
		philo->lasteat = temp;
		ft_usleep(data->te);
		pthread_mutex_lock(&philo->fork);
		philo->used = 0;
		pthread_mutex_unlock(&philo->fork);
		pthread_mutex_lock(&philo->next->fork);
		philo->next->used = 0;
		pthread_mutex_unlock(&philo->next->fork);
		philo->musteat--;
		philo->status++;
	}
}

void	ft_takefork(t_philo *philo, pthread_mutex_t *fork, int *used)
{
	long	temp;

	if (philo->status == 1 || philo->status == 2)
	{
		pthread_mutex_lock(fork);
		if (*used == 0)
		{
			*used = 1;
			pthread_mutex_unlock(fork);
			philo->status++;
			temp = ft_timestamp();
			pthread_mutex_lock(&philo->data->print);
			printf("%s[%ld ms] %d has taken a fork.\n", \
			PURPLE, temp - philo->data->currenttime, philo->n);
			pthread_mutex_unlock(&philo->data->print);
		}
		else
		{
			pthread_mutex_unlock(fork);
			usleep(250);
		}
	}
}

void	ft_think(t_data	*data, t_philo *philo)
{
	long	temp;

	if (philo->status == 0)
	{
		philo->status++;
		temp = ft_timestamp();
		pthread_mutex_lock(&data->print);
		printf("%s[%ld ms] %d is thinking.\n", \
		YELLOW, temp - data->currenttime, philo->n);
		pthread_mutex_unlock(&data->print);
	}
}

void	*ft_admortem(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	while (philo->musteat != 0)
	{
		if (ft_checkdeath(philo->data, philo) == 1)
			return (NULL);
		ft_think(philo->data, philo);
		if (ft_checkdeath(philo->data, philo) == 1)
			return (NULL);
		ft_takefork(philo, &philo->fork, &philo->used);
		if (ft_checkdeath(philo->data, philo) == 1)
			return (NULL);
		ft_takefork(philo, &philo->next->fork, &philo->next->used);
		if (ft_checkdeath(philo->data, philo) == 1)
			return (NULL);
		ft_eat(philo->data, philo);
		if (ft_checkdeath(philo->data, philo) == 1)
			return (NULL);
		if (ft_sleep(philo->data, philo) == 1)
			return (NULL);
		if (philo->musteat == -2147483648)
			philo->musteat = -1;
	}
	return (NULL);
}
