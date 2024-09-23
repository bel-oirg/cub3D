/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bel-oirg <bel-oirg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 21:34:54 by bel-oirg          #+#    #+#             */
/*   Updated: 2024/09/21 01:23:49 by bel-oirg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub.h"

static int	count_digits(int n)
{
	int	counter;

	counter = 0;
	while (n / 10)
	{
		counter++;
		n /= 10;
	}
	return (1 + counter);
}

char	*ft_itoa(int n)
{
	char		*itoa;
	int			counter;
	long int	ln;

	ln = n;
	counter = count_digits(n);
	if (ln < 0)
	{
		counter++;
		ln = -ln;
	}
	itoa = (char *)malloc(sizeof(char) * (counter + 1));
	if (!itoa)
		return (NULL);
	itoa[0] = '-';
	itoa[counter] = 0;
	while (ln / 10)
	{
		itoa[--counter] = (ln % 10) + '0';
		ln /= 10;
	}
	itoa[--counter] = ln % 10 + '0';
	return (itoa);
}
