/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oakhmouc <oakhmouc@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/05 00:25:53 by oakhmouc          #+#    #+#             */
/*   Updated: 2024/12/10 14:13:13 by oakhmouc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	check_s(char *str)
{
	int	i;

	i = 0;
	if (!str)
		i = ft_putstr_fd_int("(null)", 1);
	else
		i = ft_putstr_fd_int(str, 1);
	return (i);
}

int	check_p(void *p)
{
	int	i;

	i = 0;
	if (!p)
		i = ft_putstr_fd_int("(nil)", 1);
	else
		i = ft_putadr((unsigned long long)p);
	return (i);
}

int	print_var(va_list str, const char *str1, int i)
{
	int	ret;

	ret = 0;
	if (str1[i] == 's')
		ret = check_s(va_arg(str, char *));
	else if (str1[i] == 'c')
		ret = ft_putchar_fd_int(va_arg(str, int), 1);
	else if (str1[i] == 'd' || str1[i] == 'i')
		ret = ft_putnbr_fd_int(va_arg(str, int), 1);
	else if (str1[i] == 'x')
		ret = ft_putnbr_base(va_arg(str, int), "0123456789abcdef");
	else if (str1[i] == 'X')
		ret = ft_putnbr_base(va_arg(str, int), "0123456789ABCDEF");
	else if (str1[i] == 'u')
		ret = ft_putuns(va_arg(str, unsigned int), 1);
	else if (str1[i] == 'p')
		ret = check_p(va_arg(str, void *));
	else if (str1[i] == '%')
		ret = ft_putchar_fd_int('%', 1);
	return (ret);
}

int	ft_printf(const char *str1, ...)
{
	va_list	str;
	int		i;
	int		ret;

	i = 0;
	ret = 0;
	if (str1 == NULL)
		return (-1);
	va_start(str, str1);
	while (str1[i])
	{
		if (str1[i] != '%')
			ret += ft_putchar_fd_int(str1[i], 1);
		else
		{
			i++;
			ret += print_var(str, str1, i);
		}
		i++;
	}
	va_end(str);
	return (ret);
}
