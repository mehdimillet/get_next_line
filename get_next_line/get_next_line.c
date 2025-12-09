/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: memillet <memillet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/29 15:21:27 by memillet          #+#    #+#             */
/*   Updated: 2025/11/06 04:41:38 by memillet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static char	*ft_extract_line(char *buff_stay)
{
	char	*pos;
	int		len;

	if (!buff_stay || !*buff_stay)
		return (NULL);
	pos = ft_strchr(buff_stay, '\n');
	if (pos)
		len = pos - buff_stay + 1;
	else
		len = ft_strlen(buff_stay);
	return (ft_substr(buff_stay, 0, len));
}

static char	*ft_stay(char *buff_stay)
{
	char	*pos;
	char	*temp;
	int		len;

	pos = ft_strchr(buff_stay, '\n');
	if (!pos)
		return (free(buff_stay), NULL);
	len = pos - buff_stay + 1;
	temp = ft_substr(buff_stay, len, ft_strlen(buff_stay) - len);
	free(buff_stay);
	return (temp);
}

char	*get_next_line(int fd)
{
	static char	*buff_stay;
	char		*buffer;
	char		*line;
	int			buff_read;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	buffer = malloc(BUFFER_SIZE + 1);
	if (!buffer)
		return (NULL);
	if (!buff_stay)
		buff_stay = ft_substr("", 0, 0);
	while (!ft_strchr(buff_stay, '\n')
		&& (buff_read = read(fd, buffer, BUFFER_SIZE)) > 0)
	{
		buffer[buff_read] = '\0';
		buff_stay = ft_strjoin(buff_stay, buffer);
	}
	free(buffer);
	line = ft_extract_line(buff_stay);
	buff_stay = ft_stay(buff_stay);
	return (line);
}

int	main(void)
{
	int		fd;
	char	*line;

	fd = open("test.txt", O_RDONLY);
	if (fd < 0)
		return (1);
	while ((line = get_next_line(fd)) != NULL)
	{
		printf("%s", line);
		free(line);
	}
	get_next_line(-1);
	close(fd);
	return (0);
}
