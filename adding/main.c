/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbaumeis <lbaumeis@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/07 16:39:21 by lbaumeis          #+#    #+#             */
/*   Updated: 2024/08/14 16:21:20 by lbaumeis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
/*
void	parse_and_init(t_pipex *p)
{
	t_minishell_l	*lexed;
	t_minishell_p	*parsed;
	t_raw_in		input;
	
	ft_bzero(&input, sizeof(t_raw_in));
	init_raw(&input);
	if (!get_line_cnc(&input))
		error("syntax error", 0);
	lexed = lexer(&input);
	parsed = parser(lexed, &input);
	init_p(p, parsed);
	print_parsed(parsed);
	free_raw(&input);
}

int	main(int ac, char **av, char **envp)
{
	//t_pipex			p;
	//int				c;
	t_minishell_l	*lexed;
	t_minishell_p	*parsed;
	t_raw_in		input;

	if (ac > 4 || av[1] != NULL || !envp)
	{
		ft_putendl_fd("invalid input", 2);
		exit(EXIT_FAILURE);
	}
	//ft_bzero(&p, sizeof(t_pipex));
	//first_init(&p, envp);
	while (1)
	{
		ft_bzero(&input, sizeof(t_raw_in));
		init_raw(&input);
		if (!get_line_cnc(&input))
			error("syntax error", 0);
		lexed = lexer(&input);
		parsed = parser(lexed, &input);
		print_parsed(parsed);
		//init_p(&p, parsed);
		free_raw(&input);
		//c = 0;
		//if (p.cmd_count > 500)
		//	error("too many commands", p.status);
		//if (p.cmd_count == 1)
		//	single_exec(&p);
		//while (c < p.cmd_count && p.cmd_count > 1)
		//{
		//	p.pid[c] = fork();
		//	if (p.pid[c] == -1)
		//		error("fork failed", p.status);
		//	if (p.pid[c] == 0)
		//		do_child(&p, &c);
		//	c++;
		//	p.x++;
		//}
		//if (wait(NULL) != -1 && p.cmd_count > 1)
		//{
		//	if (WIFEXITED(p.status))
		//		p.status = WEXITSTATUS(p.status);
		//}
	}
	//err_free(&p);
	//return (p.status);
}
*/

int	main(void)
{
	t_minishell_l	*lexed;
	t_minishell_p	*parsed;
	t_raw_in		input;

	while (1)
	{
		ft_bzero(&input, sizeof(t_raw_in));
		init_raw(&input);
		if (!get_line_cnc(&input))
			return (error("syntax error", 0));
		//printf("%s\n", input.input);
		lexed = lexer(&input);
		parsed = parser(lexed, &input);//fucks up here
		print_parsed(parsed);
		free_raw(&input);
	}
}
