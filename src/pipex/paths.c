/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   paths.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgauvrit <mgauvrit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/03 14:25:37 by mgauvrit          #+#    #+#             */
/*   Updated: 2023/04/27 13:02:12 by mgauvrit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/pipex.h"

char	*get_cmd_path(char **env)
{
	int	i;

	i = 0;
	while (env[i])
	{
		if (ft_strncmp("PATH", env[i], 4) == 0)
			return (env[i] + 5);
		i++;
	}
	return (NULL);
}

int	check_cmd(char *av2)
{
	int	i;

	i = 0;
	while (av2[i] != '\0')
	{
		if (av2[i] != ' ')
			return (1);
		i++;
	}
	return (0);
}

char	*cmd_final_slash(char *cmd)
{
	char	*final_command;
	int		i;

	final_command = NULL;
	i = 0;
	if (access(cmd, 0) == 0)
	{
		final_command = ft_calloc(sizeof(char), (ft_strlen(cmd) + 1));
		while (cmd[i])
		{
			final_command[i] = cmd[i];
			i++;
		}
		final_command[i] = '\0';
		return (final_command);
	}	
	else
		return (NULL);
}

char	*cmd_final_state(char **path, char *cmd)
{
	char	*join;
	char	*final_command;
	int		i;

	i = 0;
	join = NULL;
	final_command = NULL;
	if (ft_strchr(cmd, '/'))
		return (cmd_final_slash(cmd));
	while (path[i])
	{
		join = ft_strjoin(path[i], "/");
		final_command = ft_strjoin(join, cmd);
		free(join);
		if (access(final_command, 0) == 0)
			return (final_command);
		free(final_command);
		i++;
	}
	return (NULL);
}
