/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rboudwin <rboudwin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/07 16:40:16 by rboudwin          #+#    #+#             */
/*   Updated: 2024/02/09 11:57:34 by rboudwin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	firstborn_process(t_pipex *p)
{
	//char	*line;

	close(p->pipefd[0]);
	dup2(p->input, STDIN_FILENO);
	dup2(p->pipefd[1], STDOUT_FILENO);
	//check for dup errors
	close(p->pipefd[1]);
	close(p->input);
	/*line = get_next_line(p->input);
	while (line)
	{
		write(0, line, ft_strlen(line));
		line = get_next_line(p->input);
	}*/
	//dup2(p->pipefd2[1], 1);
//	close(p->pipefd2[1]);
	if (execve(p->cmd1[0], p->cmd1, p->env) == -1)
	{
		perror("execve failed");
		return (-1);
	}
	return (1);
}
int	child_process(t_pipex *p)
{
	//char *line;
	close(p->pipefd[1]);
	if (p->output == 1)
	{
		p->output = open(p->argv[p->argc - 1], O_CREAT | O_WRONLY, 0666);
		if (p->output == -1)
		{
			perror("Output file cannot be opened");
			exit(-1);
		}
	}
	//if we get here then we should have a valid output file
	//close(p->pipefd2[1]);
	dup2(p->pipefd[0], STDIN_FILENO);
	dup2(p->output, STDOUT_FILENO);
	close(p->pipefd[0]);
	if (execve(p->cmd2[0], p->cmd2, p->env) == -1)
	{
		perror("execve failed on 2nd command");
		return (-1);
	}
	//does this part matter?
	//close(p->pipefd[0]);
	return (1);
}

int parent_process(t_pipex *p)
{
	int		pid1_status;
	int		pid2_status;
	//char	*line;
	
	//close(p->pipefd[0]);
	//line = get_next_line(p->input);
	/*while (line)
	{
		write(p->pipefd[1], line, ft_strlen(line));
		line = get_next_line(p->input);
	}*/
	close(p->input);
	
	waitpid(p->child1_pid, &pid1_status, 0);
//	ft_printf("My firstborn ended with exit code %d\n", pid1_status);
	close(p->pipefd[1]);
	p->child2_pid = fork();
	if (p->child2_pid == 0)
		child_process(p);
	//dup2(p->pipefd[1], 1);
//	ft_printf("second child born\n");
	waitpid(p->child2_pid, &pid2_status, 0);
//	ft_printf("My second child ended with exit code %d\n", pid2_status);
	close(p->output);
	return (1);
}

int	pipex(t_pipex *p)
{
	if (pipe(p->pipefd) == -1) //|| pipe(p->pipefd2) == -1)
	{
		perror("Pipe");
		return (0);
	}
	//we need to make a child process to run the command, and then send the input file
	//on stdin to that process.
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