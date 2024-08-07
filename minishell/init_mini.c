/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_mini.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbaumeis <lbaumeis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/07 10:39:19 by lbaumeis          #+#    #+#             */
/*   Updated: 2024/08/07 16:16:15 by lbaumeis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	init_raw(t_raw_in *in)
{
	in->del_s = NULL;
	in->del_str = NULL;
	in->input = NULL;
	in->n_hd = 0;
	in->n_pipe = 0;
	in->n_red = 0;
	in->n_words = 0;
	in->out = NULL;
	in->n_chd = 0;
	in->open_pipe = false;
}
/*
void	init_mini_part2(t_ms *ms)
{
	ms->e->in = false;
	ms->e->out = false;
	here_or_not(ms);
	ms->e->fileout = -1;
	if (ms->e->out == true)
		check_fileout(ms);
	ms->e->status = 0;
	ms->e->pid = NULL;
	ms->e->args = NULL;
	ms->e->paths = NULL;
	ms->e->path = NULL;
	ms->e->executable = NULL;
	ms->e->part = NULL;
	ms->e->cmd = NULL;
	ms->e->pid = malloc(sizeof(pid_t) * ms->e->cmd_count);
	if (!ms->e->pid)
		error(ms, "malloc failed", 1);
	ms->e->pip = NULL;
	init_pipes(ms);
}
*/
//void	init_mini_part1(t_ms *ms)
//{
	//t_raw_in	in;
	//t_mini_l	lex;
	//t_mini_p	parse;
	//t_exec		e;
	
	//ft_bzero(&e, sizeof(t_exec));
	//ft_bzero(&in, sizeof(t_raw_in));
	//ft_bzero(&lex, sizeof(t_mini_l));
	//ft_bzero(&parse, sizeof(t_mini_p));
	//ms->e = &e;
	//ms->in = &in;
	//ms->lex = &lex;
	//ms->parse = &parse;
	//init_raw(ms);
	//get_menv(ms, envp);
	//get_pwd(ms);
	//go_up_oldpwd(ms);
	//ms->e->home = get_env(ms, "HOME");
	//if (!ms->e->home)
	//	error(ms, "get_env failed", 1);
	//ms->e->mpath = get_env(ms, "PATH");
	//if (!ms->e->home)
	//	error(ms, "get_env failed", 1);
	//combine_export(ms);
	//ms->e->cwd = NULL;
	//ms->e->copy_stdout = dup(STDOUT_FILENO);
	//if (ms->e->copy_stdout == -1)
	//	error(ms, "dup failed", 1);
	//init_mini_part2(ms);
//}
