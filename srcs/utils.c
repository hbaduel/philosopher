/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbaduel <hbaduel@student.42perpignan.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/20 14:54:36 by hbaduel           #+#    #+#             */
/*   Updated: 2023/12/02 23:59:50 by hbaduel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void	ft_usleep(int time)
{
	long	start;

	start = ft_timestamp();
	while (ft_timestamp() - start < time)
		usleep(250);
}

long	ft_timestamp(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_usec / 1000) + (tv.tv_sec * 1000));
}

int	ft_strisdigit(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] != '-' && str[i] != '+' && (str[i] < '0' || str[i] > '9'))
			return (1);
		i++;
	}
	return (0);
}

void	ft_checkatoi(char *str, long result, t_data *data)
{
	if (ft_strisdigit(str) == 1)
		ft_exiterror("ERROR : Use only digit character.\n", data);
	if (result > 2147483647 || result < -2147483648)
		ft_exiterror("ERROR : Don't exceed INT MAX or INT MIN.\n", data);
}

int	ft_atoi_modif(char *str, t_data *data)
{
	long	result;
	int		sign;
	int		i;

	i = 0;
	result = 0;
	sign = 1;
	while (str[i] == '+' || str[i] == '-')
	{
		if (str[i] == '-')
			sign *= -1;
		i++;
	}
	while (str[i])
	{
		result *= 10;
		result += str[i] - 48;
		i++;
	}
	result *= sign;
	ft_checkatoi(str, result, data);
	return ((int)result);
}
