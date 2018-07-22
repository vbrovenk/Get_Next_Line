/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbrovenk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/14 13:17:17 by vbrovenk          #+#    #+#             */
/*   Updated: 2018/07/14 13:17:19 by vbrovenk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <fcntl.h>
#include <stdio.h>

int main(int argc, char **argv)
{
	char *line;

	int ret;
	int fd;

	fd = open("input.txt", O_RDONLY);

	// fd = open(argv[1], O_RDONLY);

	// printf("fd = %d\n", fd);

	int i = 0;
	// while (i < 1)
	// {
	// 	ret = get_next_line(fd, &line);
	// 	printf("line = %s | ret = %d\n", line, ret);
	// 	// free(line);
	// 	i++;
	// } 

	// while ((ret = get_next_line(fd, &line)) > 0)
	// {
	// 	printf("%s\n", line);
	// 	free(line);
	// }

	ret = get_next_line(fd, &line);
	// free(line);
	printf("line = %s\n", line);


	ret = get_next_line(fd, &line);
	// free(line);
	printf("line = %s\n", line);
	// system("leaks a.out");
	
	// printf("%s 	| return %d\n", line, ret);


	
	return (0);
}
