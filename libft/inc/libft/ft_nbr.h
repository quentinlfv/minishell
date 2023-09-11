/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_nbr.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nasamadi <nasamadi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/20 16:35:38 by nasamadi          #+#    #+#             */
/*   Updated: 2023/06/29 13:44:32 by nasamadi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_NBR_H
# define FT_NBR_H

// char
int		ft_isspace(int c);

// int
int		ft_atoi(const char *str);
int		ft_atoi_base(const char *str, const char *base);
char	*ft_convert_base(char *nbr, char *base_from, char *base_to);
int		ft_intlen(int n);
int		ft_intlen_base(int n, int base_len);
char	*ft_itoa(int n);
char	*ft_itoa_base(int n, const char *base);

// unsigned int
int		ft_uintlen(unsigned int n);
int		ft_uintlen_base(unsigned int n, int base_len);

// unsigned long
int		ft_ulonglen(unsigned long n);
int		ft_ulonglen_base(unsigned long n, int base_len);

#endif
