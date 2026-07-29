/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   conversion_ex.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tridley <tridley@student.codam.nl>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 13:58:42 by tridley           #+#    #+#             */
/*   Updated: 2024/12/21 12:56:39 by tridley          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	ft_putnbr_hex(unsigned long nbr, char *base, int count);

int	conversion_ex(va_list args)
{
	unsigned int	value;

	value = va_arg(args, unsigned int);
	return (ft_putnbr_hex(value, "0123456789ABCDEF", 0));
}

static int	ft_putnbr_hex(unsigned long nbr, char *base, int count)
{
	if (nbr >= 16)
		count = ft_putnbr_hex(nbr / 16, base, count);
	write(1, &base[nbr % 16], 1);
	return (count + 1);
}
