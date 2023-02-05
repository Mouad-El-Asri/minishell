/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moel-asr <moel-asr@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/09 14:07:54 by moel-asr          #+#    #+#             */
/*   Updated: 2022/10/19 19:42:58 by moel-asr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static	int	ft_len(int n)
{
	int	i;

	i = 0;
	if (n == -2147483648)
	{
		i = 10;
		return (i);
	}
	if (n == 0)
		i++;
	if (n < 0)
		n *= -1;
	while (n > 0)
	{
		n /= 10;
		i++;
	}
	return (i);
}

static char	*ft_strrev(char *str)
{
	int		i;
	int		j;
	char	c;

	i = 0;
	j = ft_strlen(str) - 1;
	while (i < j)
	{
		c = str[j];
		str[j] = str[i];
		str[i] = c;
		i++;
		j--;
	}
	return (str);
}

static void	check_num(char *return_value, int n, int i, int j)
{
	if (n == -2147483648)
	{
		n = 147483648;
		return_value[j - 1] = '-';
		return_value[j - 2] = '2';
	}
	if (n == 0)
		return_value[i] = '0';
	if (n < 0)
	{
		n *= -1;
		return_value[j - 1] = '-';
	}
	if (n > 0)
	{
		while (n > 0)
		{
			return_value[i] = (n % 10) + (48);
			n /= 10;
			i++;
		}
	}
	return_value[j] = '\0';
}

char	*ft_itoa(int n)
{
	int		i;
	int		j;
	char	*return_value;

	i = 0;
	j = ft_len(n);
	if (n < 0)
		j++;
	return_value = (char *)malloc(j * sizeof(char) + 1);
	if (!return_value)
		return (NULL);
	check_num(return_value, n, i, j);
	ft_strrev(return_value);
	return (return_value);
}
