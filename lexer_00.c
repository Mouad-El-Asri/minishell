/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_00.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moel-asr <moel-asr@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/06 18:22:29 by moel-asr          #+#    #+#             */
/*   Updated: 2023/02/14 18:36:34 by moel-asr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/minishell.h"

t_lexer	*init_lexer(char *content)
{
	t_lexer	*lexer;

	lexer = (t_lexer *)malloc(sizeof(t_lexer));
	if (!lexer)
		return (NULL);
	lexer->content = content;
	lexer->i = 0;
	lexer->c = content[lexer->i];
	return (lexer);
}

void	lexer_advance(t_lexer *lexer)
{
	if (lexer->c && lexer->i < ft_strlen(lexer->content))
	{
		lexer->i++;
		lexer->c = lexer->content[lexer->i];
	}
}

void	lexer_skip_whitespace(t_lexer *lexer)
{
	while (lexer->c && (lexer->c == ' ' || lexer->c == '\t'))
		lexer_advance(lexer);
}

t_token	*lexer_get_string_in_quotes(t_lexer *lexer, char character)
{
	char	*str;
	char	*c;
	t_token	*token;
	int		dollar_sign_count;

	str = ft_strdup("");
	dollar_sign_count = 0;
	lexer_advance(lexer);
	while (lexer->c && lexer->c != character)
	{
		if (lexer->c == '$')
			dollar_sign_count++;
		if (lexer->c == '$' && (dollar_sign_count % 2) && character == '"' && \
			lexer_skip_whitespace_backwards(lexer) == 0 && \
			(ft_isalnum(lexer->content[lexer->i + 1]) || \
			lexer->content[lexer->i + 1] == '_'))
			str = ft_free(ft_strjoin(str, lexer_expand_variable(lexer)), str);
		else
		{
			c = lexer_get_char_as_string(lexer);
			str = ft_free(ft_free(ft_strjoin(str, c), c), str);
			lexer_advance(lexer);
		}
	}
	lexer_advance(lexer);
	token = init_token(str, TOKEN_STRING_IN_QUOTES);
	// free(str);
	return (token);
}

char	*lexer_expand_variable(t_lexer *lexer)
{
	char	*c;
	char	*str;
	char	*dollars;

	str = NULL;
	lexer_advance(lexer);
	while (lexer->c && (ft_isalnum(lexer->c) || lexer->c == '_'))
	{
		c = lexer_get_char_as_string(lexer);
		str = ft_free(ft_free(ft_strjoin(str, c), c), str);
		lexer_advance(lexer);
	}
	str = ft_free(getenv(str), str);
	if (str)
		return (str);
	else
		return ("");
}
