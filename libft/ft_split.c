/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bel-bouc <bel-bouc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/09 02:53:37 by bel-bouc          #+#    #+#             */
/*   Updated: 2024/11/25 10:15:10 by senayat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../miniRT.h"

static void	free_array(int i, char **array)
{
	while (i >= 0)
	{
		free(array[i]);
		i--;
	}
	free(array);
}

static int	arr_len(char const *s, char c)
{
	int	i;
	int	len;

	i = 0;
	len = 0;
	while (s[i] != '\0')
	{
		if (s[i] != c && s[i] != '\n')
		{
			while (s[i] != c && s[i] != '\n' && s[i] != '\0')
				i++;
			len++;
		}
		else
			i++;
	}
	return (len);
}

static char	**count_words(char const *s, char c, char **arr, int len)
{
	int	y;

	y = 0;
	while (*s != '\0')
	{
		len = 0;
		if (*s != c && *s != '\n')
		{
			while (*s != c && *s != '\n' && *s != '\0')
			{
				len++;
				s++;
			}
			arr[y] = (char *)malloc(sizeof(char) * (len + 1));
			if (!arr[y])
			{
				free_array(y - 1, arr);
				return (0);
			}
			y++;
		}
		else
			s++;
	}
	return (arr);
}

static char	**copy_words(char const *s, char c, char **arr)
{
	int	i;
	int	y;
	int	x;

	i = 0;
	y = 0;
	x = 0;
	while (s[i] != '\0')
	{
		if (s[i] != c && s[i] != '\n')
		{
			while (s[i] != c && s[i] != '\n' && s[i] != '\0')
			{
				arr[x][y] = s[i];
				y++;
				i++;
			}
			arr[x][y] = '\0';
			x++;
			y = 0;
		}
		else
			i++;
	}
	return (arr);
}

char	**ft_split(char *s, char c)
{
	int		len;
	char	**array;

	len = arr_len(s, c);
	array = (char **)malloc(sizeof(char *) * (len + 1));
	if (!array)
		return (NULL);
	array[len] = NULL;
	array = count_words(s, c, array, len);
	if (!array)
		return (NULL);
	array = copy_words(s, c, array);
	return (array);
}
