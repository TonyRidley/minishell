/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexing.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mschuurm <mschuurm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 13:21:14 by tridley           #+#    #+#             */
/*   Updated: 2025/05/06 16:18:33 by mschuurm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXING_H
# define LEXING_H

# include "minishell.h"

typedef enum e_token_type
{
	TOKEN_WORD,
	TOKEN_PIPE,
	TOKEN_REDIRECT_IN,
	TOKEN_REDIRECT_OUT,
	TOKEN_APPEND,
	TOKEN_HEREDOC
}	t_token_type;

typedef struct s_token
{
	t_token_type	type;
	char			*value;
	struct s_token	*next;
}	t_token;

typedef enum e_lex_state
{
	STATE_NORMAL,
	STATE_SINGLE_QUOTE,
	STATE_DOUBLE_QUOTE,
	STATE_ESCAPED
}	t_lex_state;

typedef struct s_tokenizer
{
	t_token	**tokens;
	t_token	**current;
	int		*i;
	int		*in_filename;
}	t_tokenizer;

// Helpers
int				add_token(t_token **tokens, t_token **current,
					t_token_type type, char *value);
int				skip_whitespace(const char *input);
int				is_whitespace(char c);
int				in_quotes(const char *input, int pos);
int				get_operator_length(const char *str);
int				is_escapable_in_dquote(char c);
int				is_operator(char c);
char			*extract_word(const char *input, int *i, t_lex_state state);
t_token_type	identify_token_type(const char *str, int len);
t_lex_state		get_lexer_state(t_lex_state current_state, char c, char next_c);
void			free_tokens(t_token *tokens);
int				validate_token_syntax(t_token *tokens);
void			print_syntax_error(char *token_str);
int				check_first_token(t_token *tokens);
int				validate_quotes(t_lex_state state);

// lexing
t_token			*tokenize_input(char *input);
int				handle_special_token(t_token **tokens, t_token **current,
					const char *input, int *i);
int				handle_word_token(t_token **tokens, t_token **current,
					const char *input, int *i);

#endif
