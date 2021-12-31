/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asabani <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/05 09:10:53 by asabani           #+#    #+#             */
/*   Updated: 2021/11/11 11:24:01 by asabani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H
# include <unistd.h>
# include <stdlib.h>
# include <stddef.h>

// function needed prototypes
char	*get_next_line(int fd);

// linked list prototypes 
typedef struct s_list
{
	char			*chunk;
	size_t			chunk_size;
	struct s_list	*next;
}	t_list;
void	list_append(t_list	**head, char *chunk, size_t chunk_size);
size_t	list_get_chunks_size(t_list *head);
char	*list_join_chunks(t_list **head);

// utils function prototypes
void	*ft_memcpy(void *dst, void *src, size_t len);
char	*ft_strndup(const char *src, size_t	n);
size_t	ft_strichr(char *str, char c);

#endif
