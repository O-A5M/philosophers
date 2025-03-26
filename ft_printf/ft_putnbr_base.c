/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_base.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oakhmouc <oakhmouc@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/07 14:32:49 by oakhmouc          #+#    #+#             */
/*   Updated: 2024/12/10 14:16:18 by oakhmouc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "ft_printf.h"
#include <stdio.h>

int	ft_putnbr_base(unsigned int lnbr, char *base)
{
	int	ret;

	ret = 0;
	if (lnbr >= 16)
		ret += ft_putnbr_base(lnbr / 16, base);
	ret += ft_putchar_fd_int(base[lnbr % 16], 1);
	return (ret);
}
