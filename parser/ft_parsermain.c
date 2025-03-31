/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parsermain.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bel-bouc <bel-bouc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 00:56:31 by bel-bouc          #+#    #+#             */
/*   Updated: 2024/11/25 13:02:04 by senayat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../miniRT.h"

static void	ft_free_exit(char **arr, char *line)
{
	int	i;

	if (line != NULL)
		free(line);
	if (arr != NULL)
	{
		i = -1;
		while (arr[++i])
			free((arr[i]));
		free(arr);
	}
	exit(EXIT_FAILURE);
}

static void	ft_free(char **arr)
{
	int	i;

	if (arr != NULL)
	{
		i = -1;
		while (arr[++i])
			free((arr[i]));
		free(arr);
	}
}

static int	ft_checklimits(t_scene scene)
{
	if (scene.amb_limit == 1 && scene.cam_limit == 1 && scene.light_limit == 1)
		return (1);
	if (scene.amb_limit != 1)
		write(1, "Error\nScene needs one ambient lighting.\n", 41);
	else if (scene.cam_limit != 1)
		write(1, "Error\nScene needs one camera.\n", 31);
	else if (scene.light_limit != 1)
		write(1, "Error\nScene needs one light.\n", 30);
	return (-1);
}

void	parse_line(char *line, t_scene *scene)
{
	char	**arr;
	int		err_status;

	err_status = 0;
	arr = ft_split(line, ' ');
	if (arr == NULL || arr[0] == NULL)
	{
		ft_free(arr);
		return ;
	}
	if (ft_strlen(arr[0]) == 1 && arr[0][0] == 'A')
		err_status = parse_ambientl(arr, scene);
	else if (ft_strlen(arr[0]) == 1 && arr[0][0] == 'C' )
		err_status = parse_cam(arr, scene);
	else if (ft_strlen(arr[0]) == 1 && arr[0][0] == 'L' )
		err_status = parse_light(arr, scene);
	else if (ft_strlen(arr[0]) == 2 && ft_strncmp(arr[0], "sp", 2) == 0)
		err_status = parse_sphere(arr, scene);
	else if (ft_strlen(arr[0]) == 2 && ft_strncmp(arr[0], "pl", 2) == 0)
		err_status = parse_plane(arr, scene);
	else if (ft_strlen(arr[0]) == 2 && ft_strncmp(arr[0], "cy", 2) == 0)
		err_status = parse_cylinder(arr, scene);
	if (err_status == -1)
		ft_free_exit(arr, line);
	ft_free(arr);
}

void	ft_parse_file(char *filename, t_scene *scene)
{
	int		status;
	int		fd;
	char	*line;

	fd = ft_openfile(filename);
	while (true)
	{
		status = get_next_line(fd, &line);
		if (status == -1)
			exit(EXIT_FAILURE);
		if (status == 0)
			break ;
		parse_line(line, scene);
		free(line);
	}
	close (fd);
	if (ft_checklimits(*scene) == -1)
		exit(EXIT_FAILURE);
}
