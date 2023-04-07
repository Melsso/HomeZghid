/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smallem <smallem@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/06 14:26:15 by smallem           #+#    #+#             */
/*   Updated: 2023/04/07 17:16:27 by smallem          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libftprintf.h"

int			count_hex(unsigned long number)
{
	int	i;

	i = 0;
	if (!number)
		return (1);
	while (number)
	{
		number /= 16;
		i++;
	}
	return (i);
}


int			int_len(int	nb)
{
	unsigned int	number;
	int i;

	i = 0;
	if (!nb)
		return (1);
	if (nb < 0)
	{
		i++;
		number = -nb;
	}	
	else
		number = nb;
	while (number)
	{
		number /= 10;
		i++;
	}
	return (i);
}

int		int_lend(unsigned int nb)
{
	int	i;

	i = 0;
	if (!nb)
		return (1);
	while (nb)
	{
		nb /= 10;
		i++;
	}
	return (i);	
}

void		print_hex(unsigned long nb, char c)
{
	char	*hex = "0123456789abcdef";
	char	*hexC = "0123456789ABCDEF";
	char	res[100];
	int		i;

	i = 0;
	if (c == 'X')
	{
		while (nb >= 16)
		{
			res[i] = hexC[nb % 16];
			nb = nb / 16;
			i++;
		}
	}
	else
	{
		while (nb >= 16)
		{
			res[i] = hex[nb % 16];
			nb = nb / 16;
			i++;
		}
	}
	if (c == 'X')
		res[i] = hexC[nb];
	else
		res[i] = hex[nb];
	while (i >= 0)
	{
		ft_putchar_fd(res[i], 1);
		i--;
	}
}

const char	*parse_format(va_list arg, const char *format, ptf *s)
{	
	if (*format == 'c')
	{
		int	c = va_arg(arg, int);
		s->len += 1;
		ft_putchar_fd(c, 1);
	}
	else if (*format == 's')
	{
		char	*str = va_arg(arg, char *);
		if (str == NULL)
		{
			write(1, "(null)", 6);
			s->len += 6;
		}
		else
		{
			ft_putstr_fd(str, 1);
			s->len += ft_strlen(str);
		}
	}
	else if (*format == 'd' || *format == 'i')
	{
		int		d = va_arg(arg, int);
		ft_putnbr_fd(d, 1);
		s->len += int_len(d);
	}
	else if (*format == 'u') 
	{
		unsigned int	d = va_arg(arg, unsigned int);
		ft_putnbr_fd_u(d, 1);
		s->len += int_lend(d);
	}
	else if (*format == '%')
	{
		s->len += 1;
		ft_putchar_fd('%', 1);
	}
	else if (*format == 'x' || *format == 'X' || *format == 'p')
	{
		unsigned long	d = va_arg(arg, unsigned long);
		if (*format == 'p')
		{
			write(1, "0x", 2);
			s->len += 2;
		}
		print_hex(d, *format);
		s->len += count_hex(d);
	}
	else
		return (NULL);
	format++;
	return (format);
}

const char	*text(ptf *s, const char *format)
{
	char	*str;

	str = ft_strchr(format, '%');
	if (str)
		s->size = str - format;
	else
		s->size = ft_strlen(format);
	
	write(1, format, s->size);
	s->len += s->size;
	while (*format && *format != '%')
		format++;
	return (format);
}

int	ft_printf(const char *format, ...)
{
	va_list	arg;
	ptf	s;
	
	s.len = 0;
	s.size = 0;
	va_start(arg, format);
	while (*format)
	{ 
		if (*format == '%')
			format = parse_format(arg, format + 1, &s);
		else
			format = text(&s, format);
		if (format == NULL)
		{
			write(1, "(null)", 6);
			va_end(arg);
			return (s.len);
		}
	}
	va_end(arg);
	return (s.len);
}
int main(void){
	int i = 100000;
	char c = 'h';
	int res, res1;
	unsigned int d = 400000000;
	res1 = ft_printf("percent:%% char:%c decimal:%d integer:%i unsigned:%u ptr:%p hex:%x hexC:%X\n", c, i, i, d, &c, d, d);
	res = printf("percent:%% char:%c decimal:%d integer:%i unsigned:%u ptr:%p hex:%x hexC:%X\n", c, i, i, d, &c, d, d);
	printf("my res:%d\nprintf res:%d\n", res1, res);
}