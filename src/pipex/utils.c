/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                	                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgauvrit <mgauvrit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/23 13:19:59 by mgauvrit          #+#    #+#             */
/*   Updated: 2023/01/27 14:15:23 by mgauvrit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/pipex.h"

void	struct_init(t_data *data)
{
	data->infile = -1;
	data->outfile = -1;
	data->index = 0;
	data->paths = NULL;
	data->cmd_paths = NULL;
	data->cmd_options = NULL;
	data->cmd = NULL;
	data->n_cmd = 0;
	data->pid = 0;
	data->status = 0;
	data->wait = 0;
	data->here_doc = 0;
}

void	dup_n_close(t_data *data, int toggle)
{
	if (toggle == 0)
	{
		safe_close(data->pipefd[1]);
		safe_dup(data->pipefd[0], STDIN_FILENO);
		safe_close(data->pipefd[0]);
	}
	if (toggle == 1)
	{
		safe_close(data->pipefd[0]);
		safe_dup(data->pipefd[1], STDOUT_FILENO);
		safe_close(data->pipefd[1]);
	}
}

void	waiting(int waitin)
{
	while (waitin--)
		wait(NULL);
}

void	check_void_arg(char **av)
{
	int	i;

	i = 0;
	while (av[i])
	{
		if (av[i][0] == '\0')
		{
			printf("Arg %d : syntax error\n", (i + 1));
			exit (2);
		}
		i++;
	}
}

void	ft_parse(int ac, char **av)
{
	(void)av;
	if (ac < 5)
	{
		wrong_args();
		exit(1);
	}
}
