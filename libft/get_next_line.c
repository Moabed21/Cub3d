/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moabed <moabed@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/17 16:43:50 by melshata          #+#    #+#             */
/*   Updated: 2026/07/18 14:18:19 by moabed           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*extract_line(char *temp)
{
	char	*line;
	ssize_t	i;

	if (schr(temp, '\n'))
		line = malloc(ll(temp) - ll(schr(temp, '\n')) + 2);
	else
		line = malloc(ll(temp) + 1);
	if (!line)
		return (fullfree(&temp, NULL, NULL));
	i = 0;
	while (temp[i])
	{
		line[i] = temp[i];
		if (temp[i++] == '\n')
			break ;
	}
	line[i] = '\0';
	return (line);
}

static char	*update_leftover(char *temp)
{
	char	*left;

	if (!schr(temp, '\n') || !temp || !*temp || !ll(schr(temp, '\n') + 1))
		return (NULL);
	left = my_strjoin(NULL, schr(temp, '\n') + 1);
	if (!left)
		return (NULL);
	return (left);
}

static char	*subfun(int fd, char *temp)
{
	ssize_t	rs;
	char	*buff;
	char	*tt;

	rs = 1;
	buff = malloc(BUFFER_SIZE + 1);
	if (!buff)
		return (fullfree(&temp, NULL, NULL));
	while (!schr(temp, '\n') && rs != 0)
	{
		rs = read(fd, buff, BUFFER_SIZE);
		if (rs == -1)
			return (fullfree(&buff, &temp, NULL));
		buff[rs] = '\0';
		tt = my_strjoin(temp, buff);
		if (!tt)
			return (fullfree(&temp, &buff, NULL));
		fullfree(&temp, NULL, NULL);
		temp = tt;
	}
	fullfree(&buff, NULL, NULL);
	return (temp);
}

char	*get_next_line(int fd)
{
	char		*line;
	char		*temp;
	static char	*left = NULL;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	temp = my_strjoin(left, NULL);
	if (!temp)
		return (fullfree(&left, NULL, NULL));
	temp = subfun(fd, temp);
	if (!temp)
		return (fullfree(&left, NULL, NULL));
	line = extract_line(temp);
	if (!line)
		return (fullfree(&left, NULL, NULL));
	if (!*line)
		return (fullfree(&temp, &line, &left));
	fullfree(&left, NULL, NULL);
	left = update_leftover(temp);
	fullfree(&temp, NULL, NULL);
	return (line);
}
