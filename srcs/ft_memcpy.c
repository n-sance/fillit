/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsance <nsance@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/04 20:32:13 by nsance            #+#    #+#             */
/*   Updated: 2019/10/19 16:36:56 by nsance           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

void	*ft_memcpy(void *to, const void *from, size_t numbytes)
{
	char	*local_to;
	char	*local_from;

	local_to = (char *)to;
	local_from = (char *)from;
	if (!numbytes || to == from)
		return (to);
	while (numbytes)
	{
		*local_to++ = *local_from++;
		numbytes--;
	}
	return (to);
}
