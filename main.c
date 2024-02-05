/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rboudwin <rboudwin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/29 17:17:53 by rboudwin          #+#    #+#             */
/*   Updated: 2024/02/05 11:34:48 by rboudwin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	**parse_paths(char **env)
{
	int		i;
	char	**paths;

	i = 0;
	while (env[i] != NULL)
	{
		if (ft_strnstr(env[i], "PATH=", 5))
			paths = ft_split(env[i] + 5, ':');
		i++;
	}
	return (paths);
}

int	validate_arguments(char **argv)
{
	int	a;
	int	b;
	int	c;
	int	d;

	a = open(argv[1], O_RDONLY);
	if (a == -1)
		perror("Failed to open file");
	//ft_printf("a is now %d\n", a);
	return (1);
}

int	main(int argc, char **argv, char **env)
{
	char	**paths;
	int		i;

	i = 0;
	if (argc != 5)
	{
		ft_putstr_fd("ERROR: exactly four arguments required\n", 2);
		exit(EXIT_FAILURE);
	}
	paths = parse_paths(env);
//	while (paths[i])
//		ft_printf("%s\n", paths[i++]);
	validate_arguments(argv);
}