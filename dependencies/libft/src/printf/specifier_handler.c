/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   specifier_handler.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tridley <tridley@student.codam.nl>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/21 12:25:12 by tridley           #+#    #+#             */
/*   Updated: 2024/12/28 15:00:43 by tridley          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	specifier_handler(char specifier, va_list args)
{
	if (specifier == '%')
		return (conversion_prc());
	if (specifier == 'c')
		return (conversion_c(args));
	if (specifier == 'd')
		return (conversion_d(args));
	if (specifier == 'i')
		return (conversion_i(args));
	if (specifier == 'p')
		return (conversion_p(args));
	if (specifier == 's')
		return (conversion_s(args));
	if (specifier == 'u')
		return (conversion_u(args));
	if (specifier == 'X')
		return (conversion_ex(args));
	if (specifier == 'x')
		return (conversion_x(args));
	return (write(1, &specifier, 1));
}
