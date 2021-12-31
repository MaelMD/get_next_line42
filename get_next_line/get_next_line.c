/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asabani <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/05 09:10:08 by asabani           #+#    #+#             */
/*   Updated: 2021/11/11 11:26:43 by asabani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_strndup(const char *src, size_t	n)
{
	char	*str;
	char	*p;
	size_t	len;

	len = 0;
	while (src[len])
		len++;
	if (n < len)
		len = n;
	str = malloc(len + 1);
	p = str;
	while (*src && n--)
		*p++ = *src++;
	*p = '\0';
	return (str);
}

int	read_from_buffer(t_list **head, char *buffer, char **buffer_remainder)
{
	size_t	bl_index;
	char	*tmp;

	tmp = *buffer_remainder;
	bl_index = ft_strichr(buffer, '\n');
	list_append(head, buffer, bl_index);
	if (buffer[bl_index] == '\n')
	{
		if (buffer[bl_index + 1] != '\0')
			*buffer_remainder = ft_strndup(buffer + bl_index + 1, \
					BUFFER_SIZE + 1);
		else
			*buffer_remainder = NULL;
		free(tmp);
		tmp = NULL;
		return (1);
	}
	free(*buffer_remainder);
	*buffer_remainder = NULL;
	return (0);
}

void	read_from_file(int fd, t_list **head, char **buffer_remainder)
{
	ssize_t	nbyte;
	size_t	bl_index;
	char	buffer[BUFFER_SIZE + 1];

	nbyte = read(fd, buffer, BUFFER_SIZE);
	while (nbyte && nbyte != -1)
	{
		buffer[nbyte] = '\0';
		bl_index = ft_strichr(buffer, '\n');
		list_append(head, buffer, bl_index);
		if (buffer[bl_index] == '\n')
		{
			if (buffer[bl_index + 1] != '\0')
				*buffer_remainder = ft_strndup(buffer + bl_index + 1, \
						BUFFER_SIZE);
			break ;
		}
		nbyte = read(fd, buffer, BUFFER_SIZE);
	}
}

char	*get_next_line(int fd)
{
	t_list		*head;
	static char	*buffer_remainder;

	head = NULL;
	if (BUFFER_SIZE <= 0 || fd < 0)
		return (NULL);
	if (buffer_remainder && *buffer_remainder)
		if (read_from_buffer(&head, buffer_remainder, &buffer_remainder))
			return (list_join_chunks(&head));
	read_from_file(fd, &head, &buffer_remainder);
	return (list_join_chunks(&head));
}
