/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memory.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgauvrit <mgauvrit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/29 11:52:02 by mgauvrit          #+#    #+#             */
/*   Updated: 2023/04/03 14:37:57 by mgauvrit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/pipex.h"

void	free_child_split(t_data *data)
{
	int	i;

	i = 0;
	while (data->cmd_options[i])
	{
		free(data->cmd_options[i]);
		i++;
	}
	free(data->cmd_options);
	free(data->cmd);
}

void	free_parent_split(t_data *data)
{
	int	i;

	i = 0;
	while (data->cmd_paths[i])
	{
		free(data->cmd_paths[i]);
		i++;
	}
	free(data->cmd_paths);
}

void	free_all_splitz(t_data *data)
{
	int	i;

	i = 0;
	while (data->cmd_options[i])
	{
		free(data->cmd_options[i]);
		i++;
	}
	free(data->cmd_options);
	free(data->cmd);
	i = 0;
	while (data->cmd_paths[i])
	{
		free(data->cmd_paths[i]);
		i++;
	}
	free(data->cmd_paths);
}
