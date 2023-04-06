/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smallem <smallem@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/06 14:26:15 by smallem           #+#    #+#             */
/*   Updated: 2023/04/06 19:40:51 by smallem          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libftprintf.h"

int			count_hex(unsigned int number, int i)
{
	while (number)
	{
		number /= 16;
		i++;
	}
	return (i);
}

int			int_len(int	nb, char c)
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
	if (c == 'd' || c == 'i')
	{
		while (number)
		{
			number /= 10;
			i++;
		}
	}
	if (c == 'x' || c == 'X')
		i = count_hex(number, i);
	return (i);
}

void		print_hex(unsigned int nb)
{
	char	*hex = "0123456789abcdef";
	char	res[100];
	int		i;

	i = 0;
	while (nb >= 16)
	{
		res[i] = hex[nb % 16];
		nb = nb / 16;
		i++;
	}
	res[i] = hex[nb];
	while (i >= 0)
	{
		ft_putchar_fd(res[i], 1);
		i--;
	}
}

const char	*parse_format(va_list arg, const char *format, ptf *s)
{	
	if (*format == 's')
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
	else if (*format == 'd')
	{
		int		d = va_arg(arg, int);
		ft_putnbr_fd(d, 1);
		s->len += int_len(d, *format);
	}
	else if (*format == 'x')
	{
		unsigned int	d = va_arg(arg, unsigned int);
		print_hex((unsigned long)d);
		s->len += int_len((int)d, *format);
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
	//int res = ft_printf("hello\n");
	//int res1 = printf("hello\n");

	ft_printf("The string is: %s\nThe length of the string is : %d\n", "halaw", ft_strlen("halaw"));
}