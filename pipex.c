/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rboudwin <rboudwin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/07 16:40:16 by rboudwin          #+#    #+#             */
/*   Updated: 2024/02/23 12:23:25 by rboudwin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	check_input(t_pipex *p)
{
	char	*error_str;

	p->input = open(p->argv[1], O_RDONLY);
	if (p->input == -1)
	{
		error_str = strerror(errno);
		ft_putstr_fd(error_str, 2);
		ft_putstr_fd(": ", 2);
		ft_putstr_fd(p->argv[1], 2);
		ft_putchar_fd('\n', 2);
	}
}

int	firstborn_process(t_pipex *p)
{
	int	dup_ret;

	check_input(p);
	close(p->pipefd[0]);
	dup_ret = dup2(p->input, STDIN_FILENO);
	if (dup_ret == -1)
	{
		perror("");
		exit(EXIT_FAILURE);
	}
	dup_ret = dup2(p->pipefd[1], STDOUT_FILENO);
	if (dup_ret == -1)
	{
		perror("");
		exit(EXIT_FAILURE);
	}
	close(p->pipefd[1]);
	close(p->input);
	if (execve(p->cmd_with_path[0], p->cmd1, p->env) == -1)
	{
		return (0);
	}
	return (1);
}

int	child_process(t_pipex *p)
{
	int	dup_ret;

	open_output(p);
	close(p->pipefd[1]);
	dup_ret = dup2(p->pipefd[0], STDIN_FILENO);
	if (dup_ret == -1)
	{
		perror("");
		exit(EXIT_FAILURE);
	}
	dup_ret = dup2(p->output, STDOUT_FILENO);
	if (dup_ret == -1)
	{
		perror("");
		exit(EXIT_FAILURE);
	}
	close(p->pipefd[0]);
	close(p->output);
	if (execve(p->cmd_with_path[1], p->cmd2, p->env) == -1)
	{
		return (0);
	}
	return (1);
}

int	parent_process(t_pipex *p)
{
	int		pid1_status;
	int		pid2_status;
	int		child_return;

	child_return = 1;
	close(p->input);
	p->child2_pid = fork();
	if (p->child1_pid < 0)
	{
		perror("Fork");
		return (0);
	}
	if (p->child2_pid == 0)
		child_return = child_process(p);
	close(p->pipefd[1]);
	close(p->pipefd[0]);
	waitpid(p->child2_pid, &pid2_status, 0);
	waitpid(p->child1_pid, &pid1_status, 0);
	close(p->output);
	return (child_return);
}

int	pipex(t_pipex *p)
{
	if (pipe(p->pipefd) == -1)
	{
		perror("Pipe");
		return (0);
	}
	p->child1_pid = fork();
	if (p->child1_pid < 0)
	{
		perror("Fork");
		return (0);
	}
	else if (p->child1_pid == 0)
	{
		if (!firstborn_process(p))
			return (0);
	}
	else
	{
		if (!parent_process(p))
			return (0);
	}
	return (1);
}
