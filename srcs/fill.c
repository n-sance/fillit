/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsance <nsance@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/14 19:52:53 by dnaruto           #+#    #+#             */
/*   Updated: 2019/10/18 21:38:20 by nsance           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

/*
** Checks whether it is possible to put tetrim in the table starting
** from the "start_point" and exactly puts if it is.
*/

int			put_figure(t_list *ls, t_square *sq, t_point *st)
{
	size_t	i;
	char	**tbl;
	t_tet	*co;
	char	*l;

	co = (t_tet*)ls->content;
	i = 0;
	tbl = sq->table;
	l = co->table;
	while (l[i] != '\0')
	{
		if (!l[i] || !l[i + 1] || (int)(l[i] - '0' + st->x) >= (int)sq->size ||
		(int)(l[i + 1] - '0' + st->y) >= (int)sq->size ||
		tbl[l[i + 1] - '0' + st->y][l[i] - '0' + st->x] != '.')
			return (0);
		i += 2;
	}
	i = 0;
	while (l[i] != '\0')
	{
		tbl[l[i + 1] - '0' + st->y][l[i] - '0' + st->x] = co->symbol;
		i += 2;
	}
	return (i == 8 ? 1 : 0);
}

int			ft_solve_sq(t_square *square, t_list *lst)
{
	t_point		*s_p;
	t_tet		*piece;

	if (lst == NULL)
		return (1);
	piece = (t_tet *)lst->content;
	s_p = ft_create_p(0, 0);
	while (s_p->y < square->size)
	{
		s_p->x = 0;
		while (s_p->x < square->size)
		{
			if (put_figure(lst, square, s_p))
			{
				if (ft_solve_sq(square, lst->next))
					return (ft_memdel_c((void **)&s_p));
				else
					free_table(square->table, piece->symbol);
			}
			s_p->x++;
		}
		s_p->y++;
	}
	free(s_p);
	return (0);
}

/*
** Counts list nodes
*/

int			ft_lstcnt(t_list *lst)
{
	int		i;
	t_list	*temp;

	i = 0;
	temp = lst;
	while (temp)
	{
		i++;
		temp = temp->next;
	}
	return (i);
}

/*
** Creates table. Calculates minimal size.
** Tries to fill the table and if not - increments table's size
*/

t_square	*ft_fill_square(t_list **lst)
{
	int			size;
	t_square	*square;

	size = 0;
	while (size * size < ft_lstcnt(*lst) * 4)
		size++;
	square = ft_create_sq(size);
	while (!ft_solve_sq(square, *lst))
	{
		size++;
		square = free_square(square);
		square = ft_create_sq(size);
	}
	return (square);
}
