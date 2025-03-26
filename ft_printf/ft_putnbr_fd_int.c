/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oakhmouc <oakhmouc@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 11:00:34 by oakhmouc          #+#    #+#             */
/*   Updated: 2024/12/08 17:27:18 by oakhmouc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include <stdio.h>

int	ft_putnbr_fd_int(int n, int fd)
{
	long int	nb;
	int			ret;

	nb = n;
	ret = 0;
	if (nb < 0)
	{
		nb = -nb;
		ret += ft_putchar_fd_int('-', fd);
	}
	if (nb > 9)
	{
		ret += ft_putnbr_fd_int(nb / 10, fd);
		ret += ft_putnbr_fd_int(nb % 10, fd);
	}
	else
		ret += ft_putchar_fd_int(nb + '0', fd);
	return (ret);
}
