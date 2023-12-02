/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbaduel <hbaduel@student.42perpignan.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/20 12:04:04 by hbaduel           #+#    #+#             */
/*   Updated: 2023/12/03 00:00:02 by hbaduel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void	ft_exiterror(char *str, t_data *data)
{
	if (data)
		free(data);
	printf("%s", str);
	exit(0);
}

void	ft_freephilo(t_data *data, t_philo *philo)
{
	t_philo	*temp;
	int		i;

	i = 0;
	while (i < data->nphilo)
	{
		pthread_mutex_destroy(&philo->fork);
		temp = philo->next;
		free(philo);
		philo = temp;
		i++;
	}
}

int	main(int argc, char **argv)
{
	t_data	*data;

	if (argc < 5 || argc > 6)
		ft_exiterror("ERROR : respect <./philo number_of_philosophers time_to_die time_to_eat \
time_to_sleep [number_of_times_each_philosopher_must_eat]>.\n", NULL);
	data = ft_setup(argc, argv);
	ft_initthread(data);
	ft_freephilo(data, data->philo);
	pthread_mutex_destroy(&data->print);
	free(data);
	return (0);
}
