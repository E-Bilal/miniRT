/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bel-bouc <bel-bouc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/11 02:28:31 by bel-bouc          #+#    #+#             */
/*   Updated: 2024/07/18 16:41:43 by bel-bouc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../miniRT.h"

int	ft_strncmp(char const *str1, char const *str2, size_t n)
{
	size_t	i;

	if (n == 0)
		return (0);
	i = 0;
	while (str1[i] == str2[i] && str1[i] != '\0' && i < n - 1)
	{
		i++;
	}
	return ((unsigned char)(str1[i]) - (unsigned char)str2[i]);
}

/*
int main(void)
{
	char *str1 = "Hellobbb";
	char *str2 = "Hellfbbb";

	printf("%d" ,ft_strncmp(str1, str2, 8));

}
*/
