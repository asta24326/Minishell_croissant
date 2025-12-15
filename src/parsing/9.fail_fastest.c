/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   9.fail_fastest.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kschmitt <kschmitt@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/11 17:04:13 by kschmitt          #+#    #+#             */
/*   Updated: 2025/12/15 11:33:41 by kschmitt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>

void	fd(char *filename)
{
	static int	fd;

	printf("fd @ start: %i\n", fd);
	if (fd > 0) //bzw darf auch nicht einer der bereits belegten sein
		close(fd);
	fd = creat(filename, 0644);
	printf("fd: %i\n", fd);
}

void	fd2(char *filename)
{
	static int	fd;

	printf("fd2 @ start: %i\n", fd);
	if (fd > 0) //bzw darf auch nicht einer der bereits belegten sein
		close(fd);
	fd = creat(filename, 0644);
	printf("fd2: %i\n", fd);
}

int	main(void)
{
	fd("file1");
	fd("file2");
	fd2("XXX");
	fd2("KKK");
	fd("file3");
	fd2("888");
}
