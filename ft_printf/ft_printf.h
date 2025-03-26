/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oakhmouc <oakhmouc@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/05 00:26:19 by oakhmouc          #+#    #+#             */
/*   Updated: 2024/12/10 13:55:49 by oakhmouc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H
# include <stdarg.h>
# include <stdio.h>

int	ft_printf(const char *s, ...);
int	ft_putnbr_base(unsigned int nbr, char *base);
int	ft_putuns(unsigned int n, int fd);
int	ft_putstr_fd_int(char *s, int fd);
int	ft_putchar_fd_int(char c, int fd);
int	ft_putnbr_fd_int(int n, int fd);
int	ft_putadr(long long unsigned int nb);

#endif
