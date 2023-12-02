/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbaduel <hbaduel@student.42perpignan.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/27 00:22:00 by hbaduel           #+#    #+#             */
/*   Updated: 2023/12/03 00:00:06 by hbaduel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void	ft_initthread(t_data *data)
{
	t_philo	*philo;
	int		i;

	philo = data->philo;
	i = 0;
	while (i < data->nphilo)
	{
		pthread_create(&philo->thread, NULL, ft_admortem, philo);
		philo = philo->next;
		i++;
	}
	i = 0;
	while (i < data->nphilo)
	{
		pthread_join(philo->thread, NULL);
		philo = philo->next;
		i++;
	}
}

void	*ft_initphilo(t_data *data, int n, t_philo *first)
{
	t_philo	*next;
	int		index;

	first = malloc(sizeof(t_philo));
	next = first;
	index = 1;
	while (index <= n)
	{
		next->n = index;
		next->used = 0;
		next->status = 0;
		if (next->n % 2 == 0)
			next->status = 4;
		next->data = data;
		next->musteat = data->tme;
		next->lasteat = data->currenttime;
		pthread_mutex_init(&next->fork, NULL);
		if (index + 1 <= n)
		{
			next->next = malloc(sizeof(t_philo));
			next = next->next;
		}
		index++;
	}
	next->next = first;
}

void	ft_setint(t_data *data, int argc, char **argv)
{
	data->nphilo = ft_atoi_modif(argv[1], data);
	if (data->nphilo <= 0)
		ft_exiterror("ERROR : invalid number of philosopher.\n", data);
	data->td = ft_atoi_modif(argv[2], data);
	if (data->td < 60)
		ft_exiterror("ERROR : invalid time to death.\n", data);
	data->te = ft_atoi_modif(argv[3], data);
	if (data->te < 60)
		ft_exiterror("ERROR : invalid time to eat.\n", data);
	data->ts = ft_atoi_modif(argv[4], data);
	if (data->ts < 60)
		ft_exiterror("ERROR : invalid time to sleep.\n", data);
	if (argc == 6)
	{
		data->tme = ft_atoi_modif(argv[5], data);
		if (data->tme < 0)
			ft_exiterror("ERROR : invalid number of time philosopher \
must eat.\n", data);
	}
	else
		data->tme = -1;
	data->death = 0;
}

t_data	*ft_setup(int argc, char **argv)
{
	t_data	*data;

	data = malloc(sizeof(t_data));
	ft_setint(data, argc, argv);
	data->currenttime = ft_timestamp();
	pthread_mutex_init(&data->print, NULL);
	pthread_mutex_init(&data->die, NULL);
	data->philo = ft_initphilo(data, data->nphilo, data->philo);
	return (data);
}
