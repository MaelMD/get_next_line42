/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asabani <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/06 12:31:58 by asabani           #+#    #+#             */
/*   Updated: 2021/11/11 11:30:09 by asabani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t	ft_strichr(char *str, char c)
{
	size_t	i;

	i = 0;
	while (*(str + i))
		if (*(str + i++) == c)
			return (i - 1);
	return (i);
}

void	*ft_memcpy(void *dst, void *src, size_t len)
{
	size_t	i;

	i = 0;
	while (i < len)
	{
		*((char *)dst + i) = *((char *)src + i);
		i++;
	}
	return (dst);
}

void	list_append(t_list **head, char *chunk, size_t chunk_size)
{
	t_list	*last;
	t_list	*new_node;

	if (chunk && !*chunk)
		return ;
	if (chunk[chunk_size] == '\n')
		chunk_size++;
	new_node = (t_list *)malloc(sizeof(t_list));
	if (!new_node)
		return ;
	new_node->chunk = ft_strndup(chunk, chunk_size);
	new_node->chunk_size = chunk_size;
	new_node->next = NULL;
	if (!*head)
	{
		*head = new_node;
		return ;
	}
	last = *head;
	while (last->next)
		last = last->next;
	last->next = new_node;
}

size_t	list_get_chunks_size(t_list *head)
{
	size_t	chunks_size;

	chunks_size = 0;
	while (head)
	{
		chunks_size += head->chunk_size;
		head = head->next;
	}
	return (chunks_size);
}

char	*list_join_chunks(t_list **head)
{
	t_list	*tmp;
	char	*joined_chunks;
	size_t	chunks_size;
	size_t	j;

	if (!*head)
		return (NULL);
	j = 0;
	chunks_size = list_get_chunks_size(*head);
	joined_chunks = (char *)malloc((chunks_size + 1) * sizeof(char));
	while (*head)
	{
		tmp = *head;
		ft_memcpy(joined_chunks + j, (*head)->chunk, (*head)->chunk_size);
		j += (*head)->chunk_size;
		*head = (*head)->next;
		free(tmp->chunk);
		free(tmp);
	}
	joined_chunks[j] = '\0';
	return (joined_chunks);
}
