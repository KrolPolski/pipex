/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rboudwin <rboudwin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/07 16:40:16 by rboudwin          #+#    #+#             */
/*   Updated: 2024/02/17 15:16:34 by rboudwin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	firstborn_process(t_pipex *p)
{
	int	dup_ret;

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
		return ;
	}
}

void	child_process(t_pipex *p)
{
	int	dup_ret;

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
	if (execve(p->cmd_with_path[1], p->cmd2, p->env) == -1)
	{
		return ;
	}
}

void	parent_process(t_pipex *p)
{
	int		pid1_status;
	int		pid2_status;

	close(p->input);
	p->child2_pid = fork();
	if (p->child2_pid == 0)
		child_process(p);
	close(p->pipefd[1]);
	close(p->pipefd[0]);
	waitpid(p->child2_pid, &pid2_status, 0);
	waitpid(p->child1_pid, &pid1_status, 0);
	close(p->output);
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
