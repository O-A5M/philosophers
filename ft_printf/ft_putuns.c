/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putuns.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oakhmouc <oakhmouc@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/06 15:13:32 by oakhmouc          #+#    #+#             */
/*   Updated: 2024/12/09 05:34:08 by oakhmouc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_putuns(unsigned int n, int fd)
{
	unsigned int	nb;
	int				ret;

	nb = n;
	ret = 0;
	if (nb > 9)
	{
		ret += ft_putuns(nb / 10, fd);
		ret += ft_putuns(nb % 10, fd);
	}
	else
		ret += ft_putchar_fd_int(nb + '0', fd);
	return (ret);
}
