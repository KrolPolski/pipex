/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   the_plan.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rboudwin <rboudwin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/30 10:41:05 by rboudwin          #+#    #+#             */
/*   Updated: 2024/02/20 12:04:40 by rboudwin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
	* He had unused variables in his struct's typedef - I'm unsure if that's
		 technically a norme error. DONE
	* Other things we found was that he was doing some error checks too 
		early: an incorrect permission for the outfile should not prevent
		the first command from running. 
	* The output file was not closed properly after using dup2. DONE
	* Execve failing still resulted in an EXIT_SUCCESS. 
	* The way he used access() did not allow to distinguish between errors 
		stemming from non-existent files or just missing permissions.
	* Handle relative and absolute paths.
	* Handle fork errors in both places.
	* fix dangling pointers in free_2d DONE
	* ensure second command runs even if first command fails
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
	need to handle timeouts appropriately. DONE
	something is wrong with my wait or something. DONE
*/
