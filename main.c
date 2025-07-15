/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iaskour <iaskour@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/14 10:24:56 by iaskour           #+#    #+#             */
/*   Updated: 2025/07/15 13:19:14 by iaskour          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	parsing(char **argv)
{
	int i = 1;
	while (argv[i]){
		if ()
		i++;
	}
}


int main (int argc, char **argv)
{
	(void)argc;
	(void)argv;

	if (argc != 5 && argc != 6)
		return (printf("invalid arguments number\n"), 1);
	parse_args(argv);
	return 1;
}