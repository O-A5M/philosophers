/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putadr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oakhmouc <oakhmouc@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/09 19:39:05 by oakhmouc          #+#    #+#             */
/*   Updated: 2024/12/10 14:17:25 by oakhmouc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

unsigned int	ft_putnbr_base_long(long long unsigned int lnbr, char *base)
{
	int			ret;

	ret = 0;
	if (lnbr >= 16)
		ret += ft_putnbr_base_long(lnbr / 16, base);
	ret += ft_putchar_fd_int(base[lnbr % 16], 1);
	return (ret);
}

int	ft_putadr(long long unsigned int nb)
{
	int	i;

	i = ft_putstr_fd_int("0x", 1);
	i += ft_putnbr_base_long(nb, "0123456789abcdef");
	return (i);
}
