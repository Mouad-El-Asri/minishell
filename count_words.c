/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   count_words.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moel-asr <moel-asr@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/16 21:46:58 by moel-asr          #+#    #+#             */
/*   Updated: 2023/02/16 21:56:07 by moel-asr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


int	count_words(char *str)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (str[i])
	{
		if ((str[i] == ' ' && str[i + 1] != ' ' && str[i + 1]) \
			|| (i == 0 && str[i] != ' '))
			count++;
		i++;
	}
	return (count);
}
