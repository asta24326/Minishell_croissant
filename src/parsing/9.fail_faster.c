/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   0.fail_faster.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kschmitt <kschmitt@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/12 17:09:10 by kschmitt          #+#    #+#             */
/*   Updated: 2025/12/12 17:13:42 by kschmitt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>

void	handle_quotes(char **arr, char *str) // needs to be linked to t_cmd args
{
	int	i;

	i = -1;
	if (arr)
	{
		while (arr[++i])
			printf("arr!\n");
	}
	else
		printf("str\n");
}

int	main(void)
{
	char	*str;

	str = "hello\n";
	handle_quotes(NULL, str);
}
