/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expr.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbaumeis <lbaumeis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 16:49:22 by lbaumeis          #+#    #+#             */
/*   Updated: 2024/09/04 17:49:36 by lbaumeis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

bool	ft_issign(int c)
{
	if (c == '+' || c == '-' || c == '*' || c == '/' || c == '%')
		return (true);
	return (false);
}

// int	code_count(char *str)
// {
// 	int	c;
// 	int	x;

// 	c = 0;
// 	x = 0;
// 	while (str[x])
// 	{
// 		if (str[x] == '$')
// 		{
// 			x++;
// 			if (str[x] && str[x] == '?')
// 			{
// 				x++;
// 				c++;
// 			}
// 			else
// 				return (ft_putendl_fd("xpr: non-integer argument", 2), -1);
// 		}
// 		else if (ft_isdigit(str[x]))
// 			x++;
// 		else if (ft_issign(str[x]) && x != 0 && !ft_issign(str[x - 1]))
// 		{
// 			if (str[x + 1] && !ft_issign(str[x + 1]))
// 				x++;
// 			else
// 				return (-1);
// 		}
// 	}
// 	return (c);
// }

// int	expr_single(t_pipex *p, char *str)
// {
// 	int		x;
// 	int		y;
// 	int		len;
// 	char	*code;
// 	char	*new;

// 	x = 0;
// 	y = 0;
// 	if (code_count(str) == -1)
// 		return (1);
// 	code = NULL;
// 	code = ft_itoa_long(p->status);
// 	len = code_count(str) * ft_strlen(code) - code_count(str);
// 	new = NULL;
// 	new = ft_calloc(ft_strlen(str) - len + 1, sizeof(char));
// 	if (!new)
// 		return (1);
// 	while(str[x])
// 	{
// 		if (str[x] && str[x + 1] && str[x] == '$' && str[x + 1] == '?')
// 		{
// 			x += 2;
// 			while (*code)
// 			{
// 				new[y] = *code;
// 				code++;
// 				y++;
// 			}
// 		}
// 		else
// 			new[y++] = str[x++];
// 	}
// 	ft_putendl_fd(new, 1);
// 	return (free(new), new = NULL, 0);
// }

bool	valid_expr_args(char **str)
{
	int	x;

	x = 1;
	while (str[x])
	{
		if (ft_strcmp_bool(ft_itoa_long(ft_atoi_long(str[x])), str[x]))
			x++;
		else if (ft_strcmp_bool(str[x], "$?"))
			x++;
		else if (ft_strlen(str[x]) == 1 && ft_issign(str[x][0]))
			x++;
		//add crosschecks!!
		else
			return (false);
	}
	return (true);
}

int	expr_multi(t_pipex *p, char **str)
{
	if (!valid_expr_args(str))
		return (ft_putendl_fd("xpr: non-integer argument", 2), 2);
	//while loop to iterate through args and calculate!
	//putnbr_fd + add nl
}

int	expr(t_pipex *p, char **str)
{
	if (!str)
		return (1);//err
	else if (ft_arrlen(str) == 1)
		return (1);//err
	else if (ft_arrlen(str) == 2)
		return (do_echo(p, str, 1));//return (expr_single(p, str[1]));//USE ECHO!!
	else
		return (expr_multi(p, str));
}
/*
	Exit status:
	0 if EXPRESSION is neither null nor 0
	1 if EXPRESSION is null or 0
	2 if EXPRESSION is syntactically invalid
	3 if an error occurred.
*/