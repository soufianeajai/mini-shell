/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afanidi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 11:48:43 by afanidi           #+#    #+#             */
/*   Updated: 2023/11/17 18:42:07 by afanidi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H
# include <stdlib.h>
# include <unistd.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 100000
# endif

char		*get_next_line(int fd);
char		*ft_ft_strjoin(char *s1, char *s2);
char		*ft_ft_strdup(char *s1);
int			check_new_line(char *p);
size_t		ft_ft_strlen(const char *s);

#endif
