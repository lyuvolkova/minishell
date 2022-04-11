/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_structs.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lubov <lubov@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/09 22:04:36 by lubov             #+#    #+#             */
/*   Updated: 2022/04/07 00:33:07 by lubov            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_STRUCTS_H
# define FT_STRUCTS_H

typedef struct s_cmd
{
	char				*str;
	int					flags;
	struct s_cmd		*next;
}						t_cmd;

typedef struct s_line
{
	t_cmd				*cmd;
	int					input;
	int					output;
	int					pipe;
	struct s_line		*next;
}						t_line;

typedef struct s_parse
{
	int					in_simple;
	int					in_double;
	int					pos;
	int					i;
}						t_parse;

typedef struct s_vec
{
	int	i;
	int	j;
	int	k;
}				t_vec;

typedef struct s_fds
{
	char	*last_out;
	char	*last_in;
	int		which_redir;
	int		in;
	int		out;
}				t_fds;

typedef enum s_tokens
{
	T_DQ,
	T_SQ,
	T_SEMI,
	T_SPACE,
	T_REDIR1,
	T_REDIR2,
	T_REDIR3,
	T_REDIR4,
	T_REDIR5,
	T_ARGS,
	T_CMD,
	T_FD,
	T_OPT,
	T_DELIMITER,
	T_EQUAL,
	T_PIPE,
	T_OP_BRA,
	T_CL_BRA,
	T_OP_PAR,
	T_CL_PAR,
	T_ENV,
	T_BSLASH,
	T_AND,
	T_RES,
	T_NULL
}					t_tokens;

typedef struct s_elem
{
	char			*str;
	int				len;
	int				this_pipe;
	t_tokens		type;
	int				quotes;
}					t_elem;

typedef struct s_global
{
	int			ret;
	char		*buf;
	char		**cpenv;
	int			sigint;
	int			sigquit;
	pid_t		pid;
}				t_global;

extern t_global	g_global;

#endif