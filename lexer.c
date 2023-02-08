/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moel-asr <moel-asr@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/06 18:22:29 by moel-asr          #+#    #+#             */
/*   Updated: 2023/02/08 17:27:42 by moel-asr         ###   ########.fr       */
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
	if (lexer->c != '\0' && lexer->i < ft_strlen(lexer->content))
	{
		lexer->i++;
		lexer->c = lexer->content[lexer->i];
	}
}

void	lexer_skip_whitespace(t_lexer *lexer)
{
	while (lexer->c == ' ')
		lexer_advance(lexer);
}

t_token	*lexer_get_token(t_lexer *lexer)
{
	char	*c;
	char	*str;
	t_token	*token;

	str = NULL;
	while (lexer->c && lexer->i < ft_strlen(lexer->content))
	{
		if (lexer->c == ' ')
			lexer_skip_whitespace(lexer);
		if (lexer->c == '"' || lexer->c == '\'')
			return (lexer_get_string(lexer, lexer->c));
		if (lexer->c == '|')
		{
			c = lexer_get_char_as_string(lexer);
			token = init_token(c, TOKEN_PIPE);
			free(c);
			return (lexer_advance_with_token(lexer, token));
		}
		else if (lexer->c == '>' && lexer->content[lexer->i + 1] == '>')
		{
			c = lexer_get_char_as_string(lexer);
			lexer_advance(lexer);
			str = lexer_get_char_as_string(lexer);
			str = ft_free(ft_strjoin(c, str), str);
			token = init_token(str, TOKEN_APPEND_OUT);
			free(c);
			free(str);
			return (lexer_advance_with_token(lexer, token));
		}
		else if (lexer->c == '<' && lexer->content[lexer->i + 1] == '<')
		{
			c = lexer_get_char_as_string(lexer);
			lexer_advance(lexer);
			str = lexer_get_char_as_string(lexer);
			str = ft_free(ft_strjoin(c, str), str);
			token = init_token(str, TOKEN_APPEND_IN);
			free(c);
			free(str);
			return (lexer_advance_with_token(lexer, token));
		}
		else if (lexer->c == '>')
		{
			c = lexer_get_char_as_string(lexer);
			token = init_token(c, TOKEN_REDRECT_OUT);
			free(c);
			return (lexer_advance_with_token(lexer, token));
		}
		else if (lexer->c == '<')
		{
			c = lexer_get_char_as_string(lexer);
			token = init_token(c, TOKEN_REDRECT_IN);
			free(c);
			return (lexer_advance_with_token(lexer, token));
		}
		else
		{
			while (lexer->c && lexer->c != ' ' && lexer->c != '|' \
				&& lexer->c != '>' && lexer->c != '<' && lexer->c != '\'' \
				&& lexer->c != '"')
			{
				c = lexer_get_char_as_string(lexer);
				str = ft_free(ft_strjoin(str, c), str);
				free(c);
				lexer_advance(lexer);
			}
			token = init_token(str, TOKEN_STRING);
			free(str);
			return (token);
		}
	}
	return (NULL);
}

t_token	*lexer_get_string(t_lexer *lexer, char character)
{
	char	*str;
	char	*c;
	t_token	*token;

	str = NULL;
	if (character)
		lexer_advance(lexer);
	while (lexer->c != character)
	{
		if (lexer->c == '$')
			lexer_expand_variable(lexer);
		c = lexer_get_char_as_string(lexer);
		str = ft_free(ft_free(ft_strjoin(str, c), c), str);
		lexer_advance(lexer);
		if (character)
		{
			if (lexer->c != character && !lexer->content[lexer->i + 1])
				ft_perror("Unclosed quote\n");
		}
	}
	lexer_advance(lexer);
	token = init_token(str, TOKEN_STRING);
	free(str);
	return (token);
}

char	*lexer_expand_variable(t_lexer *lexer)
{
	lexer_advance(lexer);
	while (ft_isalnum(lexer->c) || lexer->c == '_')
	{
		lexer_advance(lexer);
	}
}

char	*lexer_get_char_as_string(t_lexer *lexer)
{
	char	*str;

	str = (char *)malloc(2 * sizeof(char));
	str[0] = lexer->c;
	str[1] = '\0';
	return (str);
}

t_token	*lexer_advance_with_token(t_lexer *lexer, t_token *token)
{
	lexer_advance(lexer);
	return (token);
}
