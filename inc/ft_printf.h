/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbarru <kbarru@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/11 11:04:33 by kbarru            #+#    #+#             */
/*   Updated: 2025/06/11 11:30:44 by kbarru           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdarg.h>
# include <unistd.h>
# include <stddef.h>

# define HEX_BASE_LOWER "0123456789abcdef"
# define HEX_BASE_UPPER "0123456789ABCDEF"
# define DECIMAL_BASE "0123456789"

# define FTPRINTF_FORMAT_SPECIFIERS "cspdiuxX"

# define SIGNED_FORMAT_SPECIFIERS "di"
# define UNSIGNED_FORMAT_SPECIFIERS "Xxu"

# define NUMERICAL_FORMAT_SPECIFIERS "diuxXp"

/* ft_printf */
int		ft_printf(const char *format, ...);
void	ft_putstr_fd(char *s, int fd);
void	ft_putnbr_fd(int nb, int fd);
void	ft_putchar_fd(char c, int fd);
int		ft_put_ul_base(unsigned long nbr, char *base, int size);
int		ft_is_in(const char c, const char *str);
size_t	ft_strlen(const char *s);
int		ft_putnbr_base(int nbr, char *base, int size);
int		ft_putchar(char c);
#endif
