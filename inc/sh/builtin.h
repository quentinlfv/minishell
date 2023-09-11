/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nasamadi <nasamadi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/20 16:33:38 by nasamadi          #+#    #+#             */
/*   Updated: 2023/06/27 14:42:44 by nasamadi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTIN_H
# define BUILTIN_H

/** INCLUDES ***/

# include "libft/ft_str.h"
# include "libft/ft_lst.h"
# include <ctype.h>
# include <limits.h>

/*** DATA ***/

typedef struct s_blti	t_blti;

struct s_blti {
	char	*name;
	int		(*f)(char **);
	t_blti	*next;
};

typedef struct s_dir	t_dir;

struct	s_dir
{
	char	**dir;
	char	*tmp;
	char	*pwd;
};

typedef struct s_env	t_env;

struct s_env
{
	char	**new_env;
	int		i;
	char	*aux2;
};

/*** PROTOTYPES ***/

/* built in */
int		ft_export(char **new_env);
int		ft_get_wdir(char **n);
int		ft_env(char **n);
int		ft_changedir(char **dir);
int		ft_echo(char **str);
int		ft_unset(char **unset);
long	ft_strtol(const char *str, char **endptr, int base);
int		ft_exit(char **exit);

/* built in utils */
void	update_env(t_list **env);
int		add_env(char *const *new_env, int i);
int		export_var(char **new_env, char *tmp, char *aux, char *aux2);
void	update_var(char *var_name, char *var);
void	free_aux(char *tmp, char *aux);
int		home_handler(void);
void	set_env(t_list *head);
int		locate_env(t_list *head);
int		goto_home(void);
int		error_handle(char *new_env);
int		set_oldpwd(t_list *head, char *aux, char *pwd);
int		print_error(const char *dir);
int		try_to_goto_olpwd(t_list **head);
int		unset_error_handle(char *new_env);

#endif
