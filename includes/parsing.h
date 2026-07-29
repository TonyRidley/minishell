/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tridley <tridley@student.codam.nl>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 15:29:46 by tridley           #+#    #+#             */
/*   Updated: 2025/05/16 15:29:52 by tridley          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

# include "lexing.h"

typedef struct s_cmd
{
	char			**args;
	int				args_count;
	char			*path;

	char			*redirect_in;
	char			*redirect_out;
	char			*append;
	char			**heredocs;
	int				*heredoc_quoted;
	int				heredoc_count;

	int				redir_failed;
	char			*failed_redir;

	struct s_cmd	*next;
	struct s_cmd	*previous;
}	t_cmd;

typedef struct s_expand_state
{
	int		i;
	int		j;
	int		len;
	int		in_single_quote;
	int		in_double_quote;
	char	**envp;
}	t_expand_state;

typedef struct s_token_data
{
	int		*i;
	int		*arg_count;
	char	**env;
	int		*skip_next;
}	t_token_data;

// Parsing
void	parse_token(t_token *token, char **env, t_cmd *command);
int		token_to_cmd(t_token *token, t_cmd *command, char **env);
void	free_cmd(t_cmd *command);

// Expand
char	*get_env_value(char *name, char **env);
char	*expand_env_vars(char *str, char **env);
int		expand_vars_from_cmd(t_cmd *command, char **env);
char	*remove_quotes(char *str);
int		get_var_name_length(char *str, int start);
char	*extract_var_name(char *str, int start, int *var_len);
void	handle_variable(t_expand_state *state, char *str, char *result);
int		calculate_expanded_length(char *str, char **env);
void	perform_expansion(char *str, char *result, char **env);
int		count_args(t_token *token);

// Handle Tokens
int		handle_parse_word_token(t_cmd *command, t_token *token, int *i,
			int arg_count);
int		handle_redirect_token(t_cmd *command, t_token **token, char **env);
int		handle_pipe_token(t_cmd **command, t_token *token, int *i,
			int *arg_count);
int		handle_open_error(char *filename, t_cmd *command);
int		validate_redirection(t_token *tok, char *filename, t_cmd *command);
int		set_redirect_field(t_cmd *command, int token_type, char *value);
int		cmd_datafill(t_cmd *command, t_token **token, int token_type,
			char **env);
int		handle_redirect_in(char *filename, t_cmd *command);
int		handle_redirect_out(int type, char *filename, t_cmd *command);

#endif
