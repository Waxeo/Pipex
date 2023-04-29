/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgauvrit <mgauvrit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/12 13:41:49 by mgauvrit          #+#    #+#             */
/*   Updated: 2023/04/29 15:55:18 by mgauvrit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/pipex.h"

// Il faudra lire sur le pipefd[0] et écrire sur le pipefd[1].
// 0 = entre standard
// 1 = sortie standard

void	execmd(t_data *data, char **argv, int toggle)
{
	if (!data->cmd || !data->cmd_options || !data->cmd_paths)
	{
		if (toggle == 1)
			minishell_perror_cmd(data, argv[data->index + 2], 2);
		else
			minishell_perror_cmd(data, argv[data->index + 2], 3);
	}
	safe_exe(data->cmd, data->cmd_options, data->cmd_paths);
}

void	first_n_mid_childs(t_data *data, char **argv)
{
	(void)argv;
	safe_piping(data->pipefd);
	data->pid = fork();
	data->wait++;
	if (data->pid > 0)
		dup_n_close(data, 0);
	else
	{
		dup_n_close(data, 1);
		if (!check_cmd(argv[data->index + 2]))
		{
			free_parent_split(data);
			minishell_perror_cmd(data, argv[data->index + 2], 0);
		}
		data->cmd_options = ft_split(argv[data->index + 2], ' ');
		data->cmd = cmd_final_state(data->cmd_paths, data->cmd_options[0]);
		execmd(data, argv, 1);
		free_child_split(data);
	}
}

void	last_one(t_data *data, char **argv)
{
	if (!check_cmd(argv[data->index + 2]))
	{
		free_parent_split(data);
		minishell_perror_cmd(data, argv[data->index + 2], 4);
	}
	data->cmd_options = ft_split(argv[data->index + 2], ' ');
	data->cmd = cmd_final_state(data->cmd_paths, data->cmd_options[0]);
	data->pid = fork();
	if (data->pid)
		waitpid(data->pid, &data->status, 0);
	else
		execmd(data, argv, 0);
	free_child_split(data);
}

void	launcher(t_data *data, char **argv)
{
	if (!data->here_doc)
		safe_dup(data->infile, STDIN_FILENO);
	safe_dup(data->outfile, STDOUT_FILENO);
	if (data->here_doc)
		data->index++;
	while (data->index < data->n_cmd - 1)
	{
		if (data->index == 0)
			first_n_mid_childs(data, argv);
		else
			first_n_mid_childs(data, argv);
		data->index++;
	}
	last_one(data, argv);
}

int	main(int ac, char **av, char **env)
{
	t_data	data;

	ft_parse(ac, av);
	check_void_arg(av);
	struct_init(&data);
	check_here_doc(&data, av);
	if (!data.here_doc)
		open_in(&data, av[1]);
	open_out(&data, av[ac - 1]);
	data.n_cmd = ac - 3;
	data.paths = get_cmd_path(env);
	if (data.paths == NULL)
		kill_da_process("PATH not found\n");
	data.cmd_paths = ft_split(data.paths, ':');
	launcher(&data, av);
	if (!data.here_doc)
		safe_dup(data.infile, STDIN_FILENO);
	safe_dup(data.outfile, STDOUT_FILENO);
	waiting(data.wait);
	safe_close(data.outfile);
	if (!data.here_doc)
		safe_close(data.infile);
	free_parent_split(&data);
	return (WEXITSTATUS(data.status));
}
