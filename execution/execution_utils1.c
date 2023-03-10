/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_utils1.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ceddibao <ceddibao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/05 00:27:31 by moel-asr          #+#    #+#             */
/*   Updated: 2023/03/08 22:12:54 by ceddibao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

extern t_global	*g_global_vars;

t_node	*ft_lstnew(void)
{
	t_node	*ret;

	ret = (t_node *)malloc(sizeof(t_node));
	ret->next = NULL;
	return (ret);
}

void	ft_lstaddback(t_node **l, t_node **new)
{
	t_node	*lst;

	lst = *l;
	if ((*l) == NULL)
	{
		*l = *new;
	}
	else
	{
		while (lst->next)
			lst = lst->next;
		lst->next = (*new);
	}
}

void	del(void *str)
{
	free(str);
}

void	ft_lstdelone(t_node **lst, t_node *todel, void (*del)(void*))
{
	t_node	*tmp;

	if (ft_llsize(*lst) > 1)
		tmp = *lst;
	else
		tmp = NULL;
	if (todel == *lst)
	{
		del(todel->cmd);
		free(todel);
		*lst = (*lst)->next;
		return ;
	}
	while (*lst && (*lst)->next != todel)
	{
		(*lst) = (*lst)->next;
	}
	(*lst)->next = (*lst)->next->next;
	del(todel->cmd);
	free(todel);
	todel = NULL;
	*lst = tmp;
}

int	contain_equal(char *s)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (s[i] == '=')
			return (1);
		i++;
	}
	return (0);
}
