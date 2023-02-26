/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ceddibao <ceddibao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/13 22:18:36 by ceddibao          #+#    #+#             */
/*   Updated: 2023/02/21 13:03:21 by ceddibao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 100
# endif 

# include <stdlib.h>
# include <fcntl.h>
# include <unistd.h>

void	ft_bzero(void *s, int n);
char	*ft_strdup(char const *s);
char	*get_bef(char *storage);
char	*get_next_line(int fd);
char	*ft_strjoin(char const *s1, char const *s2);
char	*after_n(char *storage);
char	*ft_strchr(const char *str, int c);
char	*read_from_fd(int fd, char *storage);

#endif
