/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtol.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nasamadi <nasamadi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/27 10:13:39 by nasamadi          #+#    #+#             */
/*   Updated: 2023/06/29 13:25:55 by nasamadi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/ft_str.h"
#include "libft/ft_char.h"
#include <limits.h>

int	check_sign(const char **str, int sign)
{
	if (**str == '-')
	{
		sign = -1;
		(*str)++;
	}
	else if (**str == '+')
		(*str)++;
	return (sign);
}

int	check_base(const char **str, int *base, char **endptr)
{
	if (*base < 0 || *base == 1 || *base > 36)
	{
		if (endptr)
			*endptr = (char *)*str;
		return (0);
	}
	if (*base == 0)
	{
		if (**str == '0' && ft_tolower((*str)[1]) == 'x'
			&& ft_isdigit((*str)[2]))
		{
			*base = 16;
			(*str) += 2;
		}
		else if (**str == '0')
			*base = 8;
		else
			*base = 10;
	}
	return (1);
}

int	convert_digit(const char **str, int *base)
{
	int	digit;

	if (ft_isdigit(**str))
		digit = **str - '0';
	else if (ft_isalpha(**str))
		digit = ft_tolower(**str) - 'a' + 10;
	else
		return (-1);
	if (digit >= *base)
		return (-1);
	return (digit);
}

long	handle_conversion(const char **str, int base,
			long result, char **endptr)
{
	int	digit;

	while (1)
	{
		digit = convert_digit(str, &base);
		if (digit == -1)
			break ;
		if (result > (LONG_MAX - digit) / base)
		{
			result = LONG_MAX;
			break ;
		}
		result = result * base + digit;
		(*str)++;
	}
	if (endptr)
		*endptr = (char *)*str;
	return (result);
}

long	ft_strtol(const char *str, char **endptr, int base)
{
	long	result;
	int		sign;

	result = 0;
	sign = 1;
	while (ft_isspace(*str))
		str++;
	sign = check_sign(&str, sign);
	if (check_base(&str, &base, endptr) == 0)
		return (result);
	result = handle_conversion(&str, base, result, endptr);
	return (sign * result);
}
