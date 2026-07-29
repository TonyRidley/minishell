/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   conversion_u.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tridley <tridley@student.codam.nl>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 13:58:33 by tridley           #+#    #+#             */
/*   Updated: 2024/12/21 12:56:09 by tridley          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	ft_unsigned_putnbr(unsigned int n, int count);

int	conversion_u(va_list args)
{
	unsigned int	value;
	int				char_count;

	char_count = 0;
	value = va_arg(args, unsigned int);
	char_count = ft_unsigned_putnbr(value, 0);
	return (char_count);
}

static int	ft_unsigned_putnbr(unsigned int n, int count)
{
	char	c;

	if (n >= 10)
		count = ft_unsigned_putnbr(n / 10, count);
	c = (n % 10) + '0';
	write(1, &c, 1);
	return (count + 1);
}
