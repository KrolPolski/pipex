/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rboudwin <rboudwin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/07 16:40:16 by rboudwin          #+#    #+#             */
/*   Updated: 2024/02/10 12:40:39 by rboudwin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	firstborn_process(t_pipex *p)
{
	close(p->pipefd[0]);
	dup2(p->input, STDIN_FILENO);
	dup2(p->pipefd[1], STDOUT_FILENO);
	close(p->pipefd[1]);
	close(p->input);
	if (execve(p->cmd1[0], p->cmd1, p->env) == -1)
	{
		perror("");
		return (-1);
	}
	return (1);
}

int	child_process(t_pipex *p)
{
	close(p->pipefd[1]);
	if (p->output == 1)
	{
		p->output = open(p->argv[p->argc - 1], O_CREAT | O_WRONLY, 0666);
		if (p->output == -1)
		{
			perror("");
			exit(EXIT_FAILURE);
		}
	}
	dup2(p->pipefd[0], STDIN_FILENO);
	dup2(p->output, STDOUT_FILENO);
	close(p->pipefd[0]);
	if (execve(p->cmd2[0], p->cmd2, p->env) == -1)
	{
		perror("");
		return (-1);
	}
	return (1);
}

int	parent_process(t_pipex *p)
{
	int		pid1_status;
	int		pid2_status;

	close(p->input);
	waitpid(p->child1_pid, &pid1_status, 0);
	close(p->pipefd[1]);
	p->child2_pid = fork();
	if (p->child2_pid == 0)
		child_process(p);
	waitpid(p->child2_pid, &pid2_status, 0);
	close(p->output);
	return (1);
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
		firstborn_process(p);
	else
		parent_process(p);
	return (1);
}