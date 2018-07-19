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

int		ft_copyuntil(char **line, char *content, char c)
{
	int		i;
	char	*temp;

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
	t_list	*temp;
	char	*str;

	temp = *gnl;
	while (temp != NULL)
	{
		if ((int)temp->content_size == fd)
		{
			str = ft_strdup(temp->content);
			ft_strdel(&temp->temp_content);
			temp->content = str;
			return (temp);
		}
		temp = temp->next;
	}
	temp = ft_lstnew("\0", fd);
	ft_lstadd(gnl, temp);
	temp = *gnl;
	return (temp);
}

void	help_func(t_list *list_current, char **line)
{
	size_t i;

	i = ft_copyuntil(line, list_current->content, '\n');
	if (i < ft_strlen(list_current->content))
	{
		list_current->temp_content = list_current->content;
		list_current->content += (i + 1);
	}
	else
		ft_strclr(list_current->content);
}

int		get_next_line(const int fd, char **line)
{
	static t_list	*gnl;
	char			buffer[BUFF_SIZE + 1];
	int				ret;
	t_list			*list_current;
	char			*temp;

	if (fd < 0 || line == NULL || read(fd, buffer, 0) < 0)
		return (-1);
	list_current = search_fd(&gnl, fd);
	while ((ret = read(fd, buffer, BUFF_SIZE)))
	{
		buffer[ret] = '\0';
		temp = list_current->content;
		list_current->content = ft_strjoin(list_current->content, buffer);
		ft_strdel(&temp);
		if (ft_strchr(buffer, '\n'))
			break ;
	}
	if (ret < BUFF_SIZE && !ft_strlen(list_current->content))
		return (0);
	help_func(list_current, line);
	return (1);
}
