/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bel-bouc <bel-bouc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/05 20:24:47 by bel-bouc          #+#    #+#             */
/*   Updated: 2024/11/23 23:33:42 by bel-bouc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

void	ft_strlcpy(char *dest, char *src, size_t n)
{
	size_t	i;

	i = 0;
	if (n <= 0)
		return ;
	while (i < n && src[i] != '\0')
	{
		dest[i] = src[i];
		i++;
	}
}

char	*ft_strchr(const char *str, int c)
{
	char		*cstr;

	cstr = (char *)str;
	if (!cstr)
		return (NULL);
	while (*cstr != '\0' && *cstr != (unsigned char) c)
		cstr++;
	if (*cstr != (unsigned char) c && (unsigned char) c != '\0')
		return (0);
	return (cstr);
}

char	*ft_strdup(char *str, int len)
{
	char	*cstr;
	int		i;

	cstr = (char *)malloc(sizeof(char) * (len + 1));
	if (!cstr)
		return (NULL);
	i = 0;
	while (i < len)
	{
		cstr[i] = str[i];
		i++;
	}
	cstr[i] = '\0';
	return (cstr);
}

int	ft_strjoin(char **arr, char *buffer, int buf_len)
{
	char	*dest;
	int		arr_len;

	arr_len = ft_strlengnl(*arr);
	dest = malloc(sizeof(char) * (arr_len + buf_len + 1));
	if (!dest)
		return (-1);
	ft_strlcpy(dest, *arr, arr_len);
	ft_strlcpy(dest + arr_len, buffer, buf_len);
	free (*arr);
	*arr = ft_strdup(dest, arr_len + buf_len);
	free (dest);
	if (*arr == NULL)
		return (-1);
	return (1);
}
