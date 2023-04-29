/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c	                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgauvrit <mgauvrit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/16 13:58:21 by mgauvrit          #+#    #+#             */
/*   Updated: 2023/02/23 15:17:36 by mgauvrit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/pipex.h"

void	kill_da_process(char *msg)
{
	ft_putendl_fd("Error", 2);
	ft_putstr_fd(msg, 2);
	exit(1);
}

void	wrong_args(void)
{
	write(2, "Try that way: ./pipex [file1] <cmds> [file2]\n", 45);
	exit(1);
}

void	minishell_perror_cmd(t_data *data, char *error, int i)
{
	if ((error[0] != 'c' || error[1] != 'd'))
	{
		ft_putstr_fd(error, 2);
		ft_putstr_fd(": command not found\n", 2);
	}
	safe_close(data->outfile);
	safe_close(data->infile);
	if (i == 4)
		exit(127);
	if (i == 3)
	{
		free_all_splitz(data);
		exit(127);
	}
	if (i == 2)
		free_all_splitz(data);
	exit(0);
}

void	minishell_perror_glo(char *error)
{
	perror(error);
	exit(1);
}

void	file_error(t_data *data, char *msg)
{
	safe_close(data->infile);
	ft_putstr_fd(msg, 2);
	ft_putstr_fd(": Permission denied\n", 2);
	exit(1);
}
