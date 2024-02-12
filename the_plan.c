/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   the_plan.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rboudwin <rboudwin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/30 10:41:05 by rboudwin          #+#    #+#             */
/*   Updated: 2024/02/12 15:24:18 by rboudwin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
	* check for four arguments DONE
	* parse paths - path env variable, : separated, third main arg DONE
	* find a way to bring in environmental variables DONE
	* check if input file exist DONE
	* check if output has the right permissions if it exists DONE
	* check if cmd exists in path DONE
	* check permissions of files with access DONE
	* check permissions of relevant cmd DONE
	* ensure parameters of cmds are separated DONE
		from cmds and stored and handled appropriately
	* open and read from file DONE
	* close file
	* send output to command, with appropriate parameters DONE
	* direct output of command to read pipe for second command
	* open and write output of second command to file
	* close file
	* consider timing of processes, waiting for child processes to complete, etc
	* consider heredoc?
	consider directories, non-existent commands
	open with O_DIRECTORY can detect the directory case. 
	make sure you can handle "" as a file or cmd. DONE
	consider what to do if cmd1 or cmd2 segfaults.
	DONE handle execve failures appropriately
		//check for dup errors DONE
	need to handle timeouts appropriately. something is wrong with my wait or something.
*/