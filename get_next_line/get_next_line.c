/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bel-bouc <bel-bouc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/26 22:07:06 by bel-bouc          #+#    #+#             */
/*   Updated: 2024/11/23 23:33:47 by bel-bouc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdio.h>
#include <stdbool.h>

static int	ft_free(char *buffer, char **statarr, char *line, int exitstatus)
{
	if (buffer != NULL)
		free(buffer);
	if (statarr != NULL)
	{
		free (*statarr);
		*statarr = NULL;
	}
	if (line != NULL)
	{
		free (line);
		line = NULL;
	}
	if (exitstatus == -1)
		return (-1);
	if (exitstatus == 0)
		return (0);
	if (exitstatus == 1)
		return (1);
	return (-1);
}

size_t	ft_findnewline(char *str)
{
	size_t	i;

	i = 0;
	while ((str)[i])
	{
		if ((str)[i] == '\n')
		{
			i++;
			break ;
		}
		i++;
	}
	return (i);
}

size_t	ft_strlengnl(char *str)
{
	size_t	i;

	i = 0;
	if (!str)
		return (0);
	while (str[i] != '\0')
		i++;
	return (i);
}

int	ft_printline(char **s1, char **line)
{
	char		*temp;
	size_t		i;
	size_t		y;

	i = ft_findnewline(*s1);
	y = ft_strlengnl(*s1) - i;
	*line = ft_strdup(*s1, i);
	if (*line == NULL)
		return (ft_free(NULL, s1, NULL, -1));
	if (y == 0)
		return (ft_free(NULL, s1, NULL, 1));
	temp = ft_strdup(*s1 + i, y);
	if (temp == NULL)
		return (ft_free(NULL, s1, *line, -1));
	free (*s1);
	*s1 = ft_strdup(temp, y);
	free (temp);
	if (*s1 == NULL)
		return (ft_free(NULL, s1, *line, -1));
	return (1);
}

int	get_next_line(int fd, char **line)
{
	static char	*arr;
	char		*buffer;
	int			read_nb;

	if (BUFFER_SIZE <= 0 || fd < 0)
		return (-1);
	while (true)
	{
		buffer = malloc(sizeof(char) * (BUFFER_SIZE + 1));
		if (buffer == NULL)
			return (ft_free(NULL, &arr, NULL, -1));
		read_nb = read(fd, buffer, BUFFER_SIZE);
		if (read_nb == -1)
			return (ft_free(buffer, &arr, NULL, -1));
		if (read_nb == 0 && !arr)
			return (ft_free(buffer, NULL, NULL, 0));
		if (ft_strjoin(&arr, buffer, read_nb) == -1)
			return (ft_free(buffer, &arr, NULL, -1));
		free(buffer);
		if ((ft_strchr(arr, '\n') || read_nb == 0))
			return (ft_printline(&arr, line));
	}
	return (0);
}

// int	main(void)
// {
// 	int fd = open("./sup.txt", O_RDONLY);
//     char *s;
//     int i;

//     i = 0;
//     while ((s = get_next_line(fd)) != NULL)
//     {
//         printf("%s",s);
//         free(s);
//     }
// 	close(fd);
// 	return (0);
// }
