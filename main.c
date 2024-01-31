/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rboudwin <rboudwin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/29 17:17:53 by rboudwin          #+#    #+#             */
/*   Updated: 2024/01/31 14:11:08 by rboudwin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	**parse_paths(char **env)
{
	int	i;

	i = 0;
	//ft_printf("'%s'", env[0]);
	while (env[i] != NULL)
		ft_printf("%s\n", env[i++]);
	return (env);
}

int	main(int argc, char **argv, char **env)
{
//	if (argc != 5)
//		exit(EXIT_FAILURE);
	parse_paths(env);
}