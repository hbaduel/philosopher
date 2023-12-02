/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbaduel <hbaduel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/20 12:05:00 by hbaduel           #+#    #+#             */
/*   Updated: 2023/09/29 17:47:23 by hbaduel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <unistd.h>
# include <string.h>
# include <stdio.h>
# include <stdlib.h>
# include <pthread.h>
# include <sys/time.h>

# define BLACK  "\e[1;30m"
# define RED  "\e[1;31m"
# define GREEN  "\e[1;32m"
# define YELLOW  "\e[1;33m"
# define BLUE  "\e[1;34m"
# define PURPLE  "\e[1;35m"
# define WHITE  "\e[1;37m"

typedef struct s_philo {
	pthread_mutex_t		fork;
	pthread_t			thread;
	int					n;
	int					used;
	int					status;
	int					musteat;
	long				lasteat;
	struct s_philo		*next;
	struct s_data		*data;
}		t_philo;

typedef struct s_data {
	pthread_mutex_t		print;
	pthread_mutex_t		die;
	int					nphilo;
	int					td;
	int					te;
	int					ts;
	int					tme;
	int					death;
	long				currenttime;
	t_philo				*philo;
}		t_data;

void	*ft_admortem(void *arg);
void	ft_usleep(int time);
void	ft_exiterror(char *str, t_data *data);
void	ft_initthread(t_data *data);
long	ft_timestamp(void);
t_data	*ft_setup(int argc, char **argv);
int		ft_atoi_modif(char *str, t_data *data);
int		ft_checkdeath(t_data *data, t_philo *philo);

#endif
