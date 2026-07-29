/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printf.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tridley <tridley@student.codam.nl>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/21 12:41:02 by tridley           #+#    #+#             */
/*   Updated: 2024/12/21 15:26:11 by tridley          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdarg.h>
# include "libft.h"

int	ft_printf(const char *format, ...);
int	specifier_handler(char specifier, va_list args);
int	conversion_s(va_list args);
int	conversion_c(va_list args);
int	conversion_d(va_list args);
int	conversion_i(va_list args);
int	conversion_p(va_list args);
int	conversion_prc(void);
int	conversion_u(va_list args);
int	conversion_ex(va_list args);
int	conversion_x(va_list args);

#endif
