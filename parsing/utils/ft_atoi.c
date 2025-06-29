/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: onajem <onajem@student.42.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/29 15:36:24 by onajem            #+#    #+#             */
/*   Updated: 2025/06/29 15:44:58 by onajem           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cube.h"

int	ft_space(int ch)
{
	char	*spaces;
	int		i;

	spaces = " \t\n\v\f\r";
	i = 0;
	while (spaces[i])
	{
		if (ch == spaces[i])
			return (1);
		i++;
	}
	return (0);
}

static int	is_num(char c)
{
	return (c >= '0' && c <= '9');
}

static int	num_start(const char **str)
{
	int	sign;

	sign = 1;
	if (**str == '-' || **str == '+')
	{
		if (**str == '-')
			sign *= -1;
		(*str)++;
	}
	return (sign);
}

int	ft_atoi(const char *nptr)
{
	int			sign;
	int			sum;

	sum = 0;
	sign = num_start(&nptr);
	if (!is_num(*nptr))
		return (-1);
	while (is_num(*nptr))
	{
		if (sum > sum * 10 + (*nptr - '0'))
			return (-1);
		sum = sum * 10 + (*nptr - '0');
		nptr++;
	}
	return (sum * sign);
}
