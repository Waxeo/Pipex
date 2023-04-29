/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgauvrit <mgauvrit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/12 13:41:09 by mgauvrit          #+#    #+#             */
/*   Updated: 2023/04/29 15:32:06 by mgauvrit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <string.h>
# include <errno.h>
# include <stdint.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <fcntl.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 5
# endif

typedef struct s_data
{
	int		pipefd[2];
	int		infile;
	int		outfile;
	int		index;
	char	*paths;
	char	**cmd_paths;
	char	**cmd_options;
	char	*cmd;
	int		n_cmd;
	int		n_pipes;
	int		*pipes;
	int		child_id;
	pid_t	pid;
	int		status;
	int		wait;
	int		here_doc;
}	t_data;

/*pipex.c*/
void	execmd(t_data *data, char **argv, int toggle);
void	first_n_mid_childs(t_data *data, char **argv);
void	last_one(t_data *data, char **argv);
void	launcher(t_data *data, char **argv);

/*paths.c*/
char	*get_cmd_path(char **env);
int		check_cmd(char *av3);
char	*cmd_final_slash(char *cmd);
char	*cmd_final_state(char **path, char *cmd);

/*errors.c*/
void	kill_da_process(char *msg);
void	wrong_args(void);
void	minishell_perror_cmd(t_data *data, char *error, int i);
void	minishell_perror_glo(char *error);
void	file_error(t_data *data, char *msg);

/*utils.c*/
void	dup_n_close(t_data *data, int toggle);
void	struct_init(t_data *data);
void	waiting(int waitin);
void	check_void_arg(char **av);
void	ft_parse(int ac, char **av);

/*files.c*/
void	open_in(t_data *data, char *infile);
void	open_out(t_data *data, char *outfile);

/*leaks.c*/
void	free_all_splitz(t_data *data);
void	free_child_split(t_data *data);
void	free_parent_split(t_data *data);

/*where_doc.c*/
void	check_here_doc(t_data *data, char **args);
void	limiter_child(t_data *data, char *limiter);

/*security.c*/
void	safe_piping(int *pipefd);
void	safe_exe(char *cmd, char **options, char **env);
void	safe_close(int fd);
void	safe_dup(int oldfd, int newfd);

/*libft*/
char	**ft_split(const char *s, char c);
char	*ft_strjoin(char *s1, char *s2);
char	*ft_strchr(const char *s, int c);
size_t	ft_strlen(const char *str);
void	ft_putstr_fd(char *s, int fd);
void	ft_putendl_fd(char *s, int fd);
int		ft_strncmp(const char *s1, const char *s2, size_t len);
size_t	ft_strlcpy(char *dest, const char *src, size_t size);
char	*ft_strchr(const char *s, int c);
void	*ft_calloc(size_t nbr, size_t size);
char	*get_next_line(int fd);
char	*ft_read_and_save(int fd, char *stock);
char	*ft_stock(char *stock);
char	*ft_line_return(char *stock);
char	*ft_gnljoin(char *s1, char *s2);
#endif
