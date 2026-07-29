/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   conversion_p.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tridley <tridley@student.codam.nl>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 13:58:08 by tridley           #+#    #+#             */
/*   Updated: 2024/12/21 12:55:41 by tridley          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	ft_putnbr_hex(unsigned long nbr, char *base, int count);

int	conversion_p(va_list args)
{
	void			*ptr;
	unsigned long	address;
	int				char_count;

	char_count = 0;
	ptr = va_arg(args, void *);
	if (ptr == NULL)
	{
		write(1, "(nil)", 5);
		return (5);
	}
	address = (unsigned long)ptr;
	write(1, "0x", 2);
	char_count += 2;
	char_count += ft_putnbr_hex(address, "0123456789abcdef", 0);
	return (char_count);
}

static int	ft_putnbr_hex(unsigned long nbr, char *base, int count)
{
	if (nbr >= 16)
		count = ft_putnbr_hex(nbr / 16, base, count);
	write(1, &base[nbr % 16], 1);
	return (count + 1);
}
