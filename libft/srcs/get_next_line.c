/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   get_next_line.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: lskrauci <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/01/24 09:51:50 by lskrauci      #+#    #+#                 */
/*   Updated: 2019/01/24 09:51:52 by lskrauci      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
** get_next_line has a read buffer.
** It is a minivan to transport stuff to warehouse - store_buffer.
** The size of minivan can change, so times it needs to drive varies.
** Initially warehouse is empty.
** Using strjoin we place items delivered by minivan at the warehouse.
** We clear the minivan with bzero to have nothing from previous deliveries.
** We then insert into the minivan BUFF_SIZE items.
** We must ensure items are safe thus we null terminate aka close
** the doors of minivan with read items.
** We then will deliver to warehouse and add to current stock of items.
** We will keep doing this until we deliver '\n' or deliver all items.
** Once we find newline in the warehouse, we want to locate it.
** We want to further give client all items up to the newline item.
** But there are items left for our next clients, so we will first store
** them in leftover buffer. Then clean the whole warehouse using free
** and then put from leftover buffer to store buffer items we have kept.
** Next delivery will add more items to items at the warehouse.
*/

/*
** @desc Iterate over linked list to find file descriptor's node.
** @desc If no node is found, append newly created node.
** @param const int fd is a file descriptor.
** @param t_gnl **god is an address of head pointer.
** @return Node's address to manage specific file descriptor.
*/

static t_gnl		*ft_find_fd_node(const int fd, t_gnl **god)
{
	t_gnl	*head;
	t_gnl	*new_node;

	head = *god;
	while (head->next != NULL)
	{
		if (head->fd == fd)
			return (head);
		head = head->next;
	}
	if (head->fd == fd)
		return (head);
	new_node = (t_gnl *)malloc(sizeof(t_gnl));
	if (new_node != NULL)
	{
		new_node->fd = fd;
		new_node->blocker = 0;
		new_node->store_buffer = (char *)ft_memalloc(1);
		new_node->next = NULL;
	}
	head->next = new_node;
	return (new_node);
}

/*
** @desc Replaces the first '\n' character in storage buffer with '\0'.
** @desc Ft_strdup then duplicates up to '\0', thus creating a line.
** @desc If EOF is read and '\n' can't be found, don't replace anything.
** @param char *store_buffer is storage buffer where read data is stored.
** @return If '\n' is replaced with '\0', return index of next character.
** @return Thus index of first leftover character is stored for duplicate.
** @return If last line ends with EOF, return index of '\0' in storage buffer.
** @return Thus last ft_strdup will be done until '\0'.
*/

static int			ft_terminate_return(char *store_buffer)
{
	int i;

	i = 0;
	while (store_buffer[i] != '\n' && store_buffer[i] != '\0')
	{
		i++;
	}
	if (store_buffer[i] == '\0')
	{
		return (i);
	}
	store_buffer[i] = '\0';
	i = i + 1;
	return (i);
}

/*
** @desc Perform ft_strjoin and ft_strdup and free old memory
** @param t_gnl *h is address of file descriptor's node
** @param int command tells to use ft_strjoin or ft_strdup
** @return void
*/

static void			ft_refresh_store_buffer(t_gnl *h, int command)
{
	char	*new_node;
	char	*temp;

	new_node = NULL;
	if (command == 1)
	{
		temp = h->store_buffer;
		new_node = ft_strjoin(h->store_buffer, h->read_buffer);
		free(temp);
		h->store_buffer = new_node;
	}
	else
	{
		temp = h->store_buffer;
		new_node = ft_strdup(h->store_buffer + h->new_start);
		free(temp);
		h->store_buffer = new_node;
	}
}

/*
** @desc Check if data was read from file descriptor or an error occured.
** @desc Manipulate data read from a file descriptor.
** @desc BUFF_SIZE bytes are read and appended to store buffer
** @desc until '\n' is found or line has no '\n'.
** @desc Store line and save data read after line.
** @param t_gnl *h is address of file descriptor's node.
** @param char **line is pointer to address that stores line.
** @return -1 in case of read() encounters an error.
** @return 0 in case of file being completely read.
** @return 1 in case of line being read.
*/

static int			ft_file_descriptor(t_gnl *h, char **line)
{
	ft_bzero(h->read_buffer, BUFF_SIZE);
	if (ft_strchr(h->store_buffer, '\n') == NULL)
	{
		h->read_val = read(h->fd, h->read_buffer, BUFF_SIZE);
		if (h->read_val == 0 && ft_strlen(h->store_buffer) == 0)
			return (0);
		else if (h->read_val == -1)
			return (-1);
		h->read_buffer[BUFF_SIZE] = '\0';
		ft_refresh_store_buffer(h, 1);
		while (ft_strchr(h->store_buffer, '\n') == NULL && h->blocker != 2)
		{
			ft_bzero(h->read_buffer, BUFF_SIZE);
			h->read_val = read(h->fd, h->read_buffer, BUFF_SIZE);
			if (h->read_val < BUFF_SIZE)
				h->blocker = 2;
			h->read_buffer[BUFF_SIZE] = '\0';
			ft_refresh_store_buffer(h, 1);
		}
		h->blocker = 0;
	}
	h->new_start = ft_terminate_return(h->store_buffer);
	*line = ft_strdup(h->store_buffer);
	ft_refresh_store_buffer(h, 0);
	return (1);
}

/*
** @desc Check validity of file descriptor and if line is not NULL.
** @desc If linked list is empty, create the first node.
** @desc Launches search for file descriptor's node to manipulate it.
** @param const int fd is file descriptor.
** @param char **line is pointer to address that stores line.
** @return -1 in case of read() encounters an error.
** @return -1 in case file descriptor is invalid or line is NULL.
** @return 0 in case of file being completely read, store no data.
** @return 1 in case of line being read.
*/

int					get_next_line(const int fd, char **line)
{
	int				ret;
	static t_gnl	*head;
	t_gnl			**god;
	t_gnl			*fd_node;

	ret = -1;
	god = &head;
	if (fd < 0 || line == NULL)
		return (ret);
	ft_printf("🔥 > ");
	if (*god == 0)
	{
		*god = (t_gnl *)malloc(sizeof(t_gnl));
		if (*god != NULL)
		{
			(*god)->fd = fd;
			(*god)->blocker = 0;
			(*god)->store_buffer = (char *)ft_memalloc(1);
			(*god)->next = NULL;
		}
	}
	fd_node = ft_find_fd_node(fd, god);
	ret = ft_file_descriptor(fd_node, line);
	*line = (ret == 0 ? 0 : *line);
	return (ret);
}
