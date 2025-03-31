/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bel-bouc <bel-bouc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/05 20:52:15 by bel-bouc          #+#    #+#             */
/*   Updated: 2024/11/23 23:33:55 by bel-bouc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1
# endif

# include <unistd.h>
# include <stdlib.h>

int		get_next_line(int fd, char **line);
size_t	ft_findnewline(char *str);
size_t	ft_strlengnl(char *str);
void	ft_strlcpy(char *dest, char *src, size_t n);
char	*ft_strchr(const char *str, int c);
char	*ft_strdup(char *str, int len);
int		ft_strjoin(char **arr, char *buffer, int buf_len);
int		ft_printline(char **s1, char **line);
#endif
