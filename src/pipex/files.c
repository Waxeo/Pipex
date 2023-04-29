/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   files.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgauvrit <mgauvrit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/06 11:56:49 by mgauvrit          #+#    #+#             */
/*   Updated: 2023/04/29 15:35:03 by mgauvrit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/pipex.h"

void	open_in(t_data *data, char *infile)
{
	data->infile = open(infile, O_RDWR);
	if (data->infile < 0)
		file_error(data, infile);
}

void	open_out(t_data *data, char *outfile)
{
	data->outfile = open(outfile, O_TRUNC | O_CREAT | O_RDWR, 0664);
	if (data->outfile < 0)
	{
		safe_close(data->infile);
		minishell_perror_glo(outfile);
	}
}
