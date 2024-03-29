/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsance <nsance@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/14 19:40:28 by dnaruto           #+#    #+#             */
/*   Updated: 2019/10/18 22:21:28 by nsance           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

/*
** Reverse nodes in the list
*/

void			ft_lstrev(t_list **alst)
{
	t_list	*prev;
	t_list	*cur;
	t_list	*next;

	prev = NULL;
	cur = *alst;
	while (cur != NULL)
	{
		next = cur->next;
		cur->next = prev;
		prev = cur;
		cur = next;
	}
	*alst = prev;
}

/*
** Aux function to manage size and coordinate values
*/

t_get_arr		*set_get_arr(void)
{
	t_get_arr *out;

	out = 0;
	if ((out = (t_get_arr *)ft_memalloc(sizeof(out))))
	{
		out->col_cnt = 0;
		out->row_cnt = 0;
		out->hor_shift = 0;
		out->ver_shift = 0;
		out->fl = 0;
		out->i = 0;
	}
	return (out);
}

/*
** Write coordinates of all sharp symbols in tetrim int "char *out"
*/

void			set_sharp(t_get_arr *get, char *out)
{
	if (!get->fl)
	{
		get->fl = 1;
		get->hor_shift = get->col_cnt;
		get->ver_shift = get->row_cnt;
	}
	out[get->i++] = get->col_cnt - get->hor_shift + '0';
	out[get->i++] = get->row_cnt - get->ver_shift + '0';
}

/*
** Initialise a string which keep coordinates of every sharp symbol in tetrim
** This function already takes all coordinates shifted to the upper left side
*/

char			*get_array(char *buff)
{
	char		*out;
	t_get_arr	*get;

	if (!(out = (char *)ft_memalloc(sizeof(char) * (8 + 1))))
		return (0);
	get = set_get_arr();
	while ((*buff) != '\0')
	{
		get->col_cnt++;
		if (*buff == '\n')
		{
			get->row_cnt++;
			get->col_cnt = 0;
		}
		if (*buff == '#')
		{
			set_sharp(get, out);
		}
		buff++;
	}
	out[get->i] = '\0';
	free(get);
	return (out);
}

/*
** Read tetrimino stream from file,
** and initialise list nodes if they valid
*/

t_list			*save_file(char *filename)
{
	char	*buff;
	t_list	*new;
	t_tet	*tetris;
	t_read	*re;
	t_list	*temp;

	re = new_read();
	temp = 0;
	tetris = 0;
	new = 0;
	buff = ft_strnew(21);
	re->fd = open(filename, O_RDONLY);
	ft_bzero(buff, ft_strlen(buff));
	while ((re->r = read(re->fd, buff, 21)))
	{
		if (!could_put(filename, &tetris, buff, re->l++))
			return (free_list_and_string(new, &buff, re));
		temp = ft_lstnew(tetris, sizeof(t_tet));
		ft_lstadd(&new, temp);
		ft_memdel((void **)&tetris);
	}
	close(re->fd);
	ft_lstrev(&new);
	free_list_and_string(0, &buff, re);
	return (new);
}
