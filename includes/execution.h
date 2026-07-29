/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mschuurm <mschuurm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 16:31:14 by mschuurm          #+#    #+#             */
/*   Updated: 2025/07/09 15:04:59 by mschuurm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTION_H
# define EXECUTION_H

# include "minishell.h"
# include "parsing.h"

typedef struct s_pipeline
{
	char	**env;
	int		pipe_fd[2];
	int		prev_pipe_read;
	t_cmd	*current;
	pid_t	last_pid;
}	t_pipeline;

// Functions
int		execute_command(t_cmd *command, char ***env_ptr);
int		execute_pipeline(t_cmd *cmd, char ***env_ptr);

// Pipeline
int		execute_pipeline_child(t_pipeline *pl);
int		wait_for_children(pid_t last_pid);

// External command functions
int		execute_external_command(t_cmd *command, char **env);
int		has_non_empty_args(t_cmd *command);
void	shift_until_non_empty(t_cmd *command);
int		file_exists(const char *path);
int		is_directory(const char *path);
char	*try_command_paths(char **paths, const char *cmd);

// Builtins
int		builtin_cd(t_cmd *command, char ***env_ptr);
int		builtin_echo(t_cmd *command);
int		builtin_env(char **env, char **args);
int		builtin_exit(t_cmd *command);
int		builtin_export(t_cmd *command, char ***env_ptr);

// export_1.c
char	**sortand_copy_env(char ***env_ptr);
void	free_string_array(char **array);
void	print_export_format(char *env_string);
int		add_to_env(char *var, char ***env_ptr, int equals_pos);
int		add_new_var(char *var, char ***env_ptr);

int		builtin_pwd(void);
int		builtin_unset(t_cmd *command, char ***env_ptr);
int		remove_env_ptr(char *var_name, char ***env_ptr);
void	free_command_list(t_cmd *command);
int		check_pwd_exists(char ***env_ptr);

// Export helpers
char	**sortand_copy_env(char ***env_ptr);
void	bubble_sort(char **array, int count);
void	free_string_array(char **array);
void	print_export_format(char *env_string);
int		is_valid_identifier(char *str);

// Redirections
int		setup_redirections(t_cmd *command, int *original_stdin,
			int *original_stdout, char **env);
void	restore_redirections(int original_stdin, int original_stdout);
int		setup_heredoc(t_cmd *command, char **env);
int		process_heredocs(t_cmd *command, char **env, int pipe_fd);
int		setup_heredoc_pipes(int *pipe_fd, int *t_fd, int *saved_stdin);
int		heredoc_read_loop_discard(char *delimiter);
void	process_heredoc_line(char *line, int is_quoted,
			int pipe_fd, char **env);
int		heredoc_read_loop(char *delimiter, int is_quoted,
			int pipe_fd, char **env);
int		finalize_heredoc(int *pipe_fd, int t_fd, int saved_stdin, int ir);
char	*read_line_simple(void);

#endif