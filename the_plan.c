/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   the_plan.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rboudwin <rboudwin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/30 10:41:05 by rboudwin          #+#    #+#             */
/*   Updated: 2024/02/05 15:54:39 by rboudwin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
	* check for four arguments DONE
	* parse paths - path env variable, : separated, third main arg DONE
	* find a way to bring in environmental variables DONE
	* check if input file exist
	* check if output has the right permissions if it exists
	* check if cmd exists in path
	* check permissions of files with access
	* check permissions of relevant cmd
	* ensure parameters of cmds are separated 
		from cmds and stored and handled appropriately
	* open and read from file
	* close file
	* send output to command, with appropriate parameters
	* direct output of command to read pipe for second command
	* open and write output of second command to file
	* close file
	* consider timing of processes, waiting for child processes to complete, etc
	* consider heredoc?
	* choose an appropriate test case
		maybe: < textfile.txt cat | head -1 > output
		also: < textfile.txt grep | grep -v > output
	iterations:
	1) make it possible to run '< filename cmd' without pipes
	2) add ability to pipe once
	3) add the ability to use unlimited pipes

	consider directories, non-existent commands
	open with O_DIRECTORY can detect the directory case. 
	make sure you can handle "" as a file or cmd.
*/