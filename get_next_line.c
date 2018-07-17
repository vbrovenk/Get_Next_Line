/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbrovenk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/15 13:36:39 by vbrovenk          #+#    #+#             */
/*   Updated: 2018/04/15 13:36:41 by vbrovenk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdio.h>
#include <string.h>

// static t_list            *get_correct_file(t_list **file, int fd)
// {
//     t_list                *tmp;

//     tmp = *file;
//     while (tmp)
//     {
//         if ((int)tmp->content_size == fd)
//             return (tmp);
//         tmp = tmp->next;
//     }
//     tmp = ft_lstnew("\0", fd);
//     ft_lstadd(file, tmp);
//     tmp = *file;
//     return (tmp);
// }

// int                        get_next_line(const int fd, char **line)
// {
//     char                buf[BUFF_SIZE + 1];
//     static t_list        *file;
//     int                    i;
//     int                    ret;
//     t_list                *curr;

//     if ((fd < 0 || line == NULL || read(fd, buf, 0) < 0))
//         return (-1);
//     curr = get_correct_file(&file, fd);
//     MALLCHECK((*line = ft_strnew(1)));
//     while ((ret = read(fd, buf, BUFF_SIZE)))
//     {
//         buf[ret] = '\0';
//         MALLCHECK((curr->content = ft_strjoin(curr->content, buf)));
//         if (ft_strchr(buf, '\n'))
//             break ;
//     }
//     if (ret < BUFF_SIZE && !ft_strlen(curr->content))
//         return (0);
//     i = ft_copyuntil(line, curr->content, '\n');
//     (i < (int)ft_strlen(curr->content))
//         ? curr->content += (i + 1)
//         : ft_strclr(curr->content);
//     return (1);
// }


// void	join(char **line, char *temp_str)
// {
// 	char	*temp_for_join;

// 	temp_for_join = *line;
// 	if (temp_for_join != NULL)
// 	{
// 		*line = ft_strjoin(temp_for_join, temp_str);
// 		free(temp_for_join);
// 		free(temp_str);
// 	}
// 	else
// 		*line = temp_str;
// }

// void	get_substr(t_gnl *array, char **line, char *str_end)
// {
// 	int		size_line;
// 	int		size_end;
// 	char	*temp_str;

// 	size_line = ft_strlen(array->str);
// 	size_end = ft_strlen(str_end);
// 	if (str_end != NULL)
// 	{
// 		temp_str = ft_strsub(array->str, 0, size_line - size_end);
// 		array->size = size_end - 1;
// 		ft_memmove(array->str, str_end + 1, size_end);
// 	}
// 	else
// 	{
// 		array->size = 0;
// 		temp_str = ft_strdup(array->str);
// 	}
// 	join(line, temp_str);
// }

// int		get_next_line(const int fd, char **line)
// {
// 	char			*str_end;
// 	static t_gnl	array[4500];

// 	if (read(fd, NULL, 0) < 0 || !line ||
// 		(!(*line = 0) && (fd < 0 || fd > 4499)))
// 		return (-1);
// 	str_end = 0;
// 	while (str_end == 0)
// 	{
// 		if (array[fd].size == 0 &&
// 			(array[fd].size = read(fd, array[fd].str, BUFF_SIZE)) < 1)
// 		{
// 			if (*line != NULL)
// 				return (1);
// 			else
// 				return (0);
// 		}
// 		array[fd].str[array[fd].size] = '\0';
// 		str_end = ft_memchr(array[fd].str, '\n', array[fd].size);
// 		get_substr(&array[fd], line, str_end);
// 	}
// 	return (1);
// }


int 	ft_copyuntil(char **line, char *content, char c)
{
	int i;
	char *temp;

	i = 0;
	temp = malloc(sizeof(char) * (ft_strlen(content) + 1));

	while (content[i] != '\0' && content[i] != c)
	{
		temp[i] = content[i];
		i++;
	}
	temp[i] = '\0';
	*line = temp;

	return (i);
}

t_list	*search_fd(t_list **gnl, int fd)
{
	t_list *temp;

	temp = *gnl;
	while (temp != NULL)
	{
		if ((int)temp->content_size == fd)
			return (temp);
		temp = temp->next;
	}
	temp = ft_lstnew("\0", fd);
	ft_lstadd(gnl, temp);
	temp = *gnl;
	return (temp);
}

int		get_next_line(const int fd, char **line)
{
	static t_list *gnl;
	char	buffer[BUFF_SIZE + 1];
	int ret;
	t_list *list_current;
	size_t i;
	char *temp;

	if (fd < 0 || line == NULL || read(fd, buffer, 0) < 0)
		return (-1);

	list_current = search_fd(&gnl, fd);
	while ((ret = read(fd, buffer, BUFF_SIZE)))
	{
		buffer[ret] = '\0';
		temp = list_current->content;
		list_current->content = ft_strjoin(temp, buffer);
		free(temp);
		if (ft_strchr(buffer, '\n'))
			break ;
	}
	if (ret < BUFF_SIZE && !ft_strlen(list_current->content))
		return (0);
	
	i = ft_copyuntil(line, list_current->content, '\n');
	(i < ft_strlen(list_current->content))
		? list_current->content += (i + 1)
		: ft_strclr(list_current->content);

	return (1);
}
