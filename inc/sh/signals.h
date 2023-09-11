/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nasamadi <nasamadi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/20 16:34:11 by nasamadi          #+#    #+#             */
/*   Updated: 2023/05/20 16:34:12 by nasamadi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SIGNALS_H
# define SIGNALS_H

/*** DEFINES ***/

# define SIGINT_EXIT 130
# define SIGQUIT_EXIT 131

/*** PROTOTYPES ***/

/* utils/signals.c */
void	sig_heredoc(void);
void	sig_child(void);
void	sig_parent(void);
void	sig_ignore(void);

#endif
