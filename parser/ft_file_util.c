/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_file_util.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bel-bouc <bel-bouc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/31 17:17:08 by bel-bouc          #+#    #+#             */
/*   Updated: 2024/11/25 12:58:35 by senayat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../miniRT.h"

static void	ft_extension_exit(int exit_type, char *filename)
{
	if (exit_type == 1)
		write(1, "Error\nFile needs an extension.\n", 32);
	else if (exit_type == 2)
		write(1, "Error\nExtension needs to be 'rt'.\n", 35);
	else if (exit_type == 3)
	{
		write(1, "Error\nrt file does not exist or dir is not ", 44);
		write(1, "correct or file doesn't have the correct permissions.\n", 55);
	}
	else if (exit_type == 4)
	{
		write(1, "Error\nSomething went wrong with ", 33);
		write(1, "allocating memory for the 'clean' filename.\n", 45);
	}
	else if (exit_type == 5)
		write(1, "Error\nArgument cant be empty.\n", 31);
	if (filename != NULL)
		free(filename);
	exit (EXIT_FAILURE);
}

static void	check_emptyfile(char *filename)
{
	int	begin;

	if (ft_strlen(filename) == 0)
		ft_extension_exit(5, NULL);
	begin = 0;
	while (filename[begin] == ' ')
		begin++;
	if (ft_strlen(filename)-begin == 0)
		ft_extension_exit(5, NULL);
}

static char	*remove_spaces(char *filename)
{
	char	*temp;
	int		begin;
	int		end;
	int		i;

	begin = 0;
	while (filename[begin] == ' ')
		begin++;
	end = ft_strlen(filename) - 1;
	while (filename[end] == ' ')
		end--;
	end++;
	temp = malloc(sizeof(char) * (end - begin) + 1);
	if (!temp)
		ft_extension_exit(4, NULL);
	temp[end - begin] = '\0';
	i = 0;
	while (begin != end)
	{
		temp[i] = filename[begin];
		i++;
		begin++;
	}
	return (temp);
}

int	ft_checkextension(char *filename)
{
	int		i;
	int		fd;
	char	*clean_filename;

	clean_filename = remove_spaces(filename);
	i = ft_strlen(clean_filename) - 1;
	while (i >= 0)
	{
		if (clean_filename[i] == '.')
			break ;
		i--;
	}
	i++;
	if (i == 0)
		ft_extension_exit(1, clean_filename);
	if (ft_strncmp(clean_filename + i, "rt", 2) != 0)
		ft_extension_exit(2, clean_filename);
	if (ft_strlen(clean_filename + i) != 2)
		ft_extension_exit(2, clean_filename);
	fd = open(clean_filename, O_RDONLY);
	if (fd == -1)
		ft_extension_exit(3, clean_filename);
	free(clean_filename);
	return (fd);
}

int	ft_openfile(char *filename)
{
	int	fd;

	check_emptyfile(filename);
	fd = ft_checkextension(filename);
	return (fd);
}
