/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   where_doc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgauvrit <mgauvrit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/27 13:39:48 by mgauvrit          #+#    #+#             */
/*   Updated: 2023/04/29 15:53:44 by mgauvrit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	limiter_child(t_data *data, char *limiter)
{
	char	*read;
	char	*lim;

	read = NULL;
	lim = ft_strjoin(limiter, "\n");
	if (!lim)
		exit(2);
	safe_close(data->pipefd[0]);
	while (1)
	{
		write(0, "> ", 2);
		read = get_next_line(0);
		if (!read || !ft_strncmp(read, lim, ft_strlen(lim)))
			break ;
		write(data->pipefd[1], read, ft_strlen(read));
		free(read);
	}
	free(lim);
	free(read);
	get_next_line(-1);
	safe_close(data->pipefd[1]);
	exit(0);
}

void	check_here_doc(t_data *data, char **args)
{	
	int	pid;

	if (!ft_strncmp(args[1], "here_doc", 9))
	{
		data->here_doc = 1;
		safe_piping(data->pipefd);
		pid = fork();
		if (pid)
		{
			safe_close(data->pipefd[1]);
			safe_dup(data->pipefd[0], STDIN_FILENO);
			safe_close(data->pipefd[0]);
		}
		else
			limiter_child(data, args[2]);
	}
}
