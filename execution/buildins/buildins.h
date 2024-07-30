/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buildins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbaumeis <lbaumeis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/27 12:49:02 by lbaumeis          #+#    #+#             */
/*   Updated: 2024/07/30 16:15:17 by lbaumeis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILDINS_H
# define BUILDINS_H

# include <features.h>
# include <signal.h>
# include <sys/signal.h>
# include <term.h>
# include <dirent.h>
# include <sys/ioctl.h>
# include "../../libft/libft.h"
# include <sys/wait.h>
# include <stdlib.h>
# include <stddef.h>
# include <unistd.h>
# include <string.h>
# include <stdio.h>
# include <fcntl.h>
# include <errno.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <complex.h>
# include <stdbool.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <dirent.h>
# include "../../parsing/minishell.h"

typedef struct s_buildins
{
	char	**envp;
	char	*cdpath;
	char	**menv;
	char	*mpath;
	char	**export;
	char	*home;
	char	*oldpwd;
	char	*pwd;
}			t_buildins;

/*UTILS*/
bool	is_access(char *dir);
void	err_or(char *s);
int		find_arg(char **s, char *a);
void	buildins_init(t_buildins *vars);

/*PWD*/
void	reset_old_pwd(t_buildins *vars, char *path);
void	get_oldpwd(t_buildins *vars);
void	join_oldpwd(t_buildins *vars, char **temp, char *oldpwd);
void	go_up_oldpwd(t_buildins *vars);

/*ENV*/
void	get_pwd(t_buildins *vars);
char	*get_env(t_buildins *vars, char *str);
void	get_menv(t_buildins *vars);

/*CDPATH*/
void	get_cdpath(t_buildins *vars);
void	set_cdpath(t_buildins *vars, char **token);

/*CD_FIND_PATH*/
int		add_to_path(t_buildins *vars, char *t);
int		go_back(t_buildins *vars, int print);
char	*check_slash(char *tok, char *temp);
int		go_slash(t_buildins *vars, char **token, int x);
int		go_full_path(t_buildins *vars, char **token, int x);

/*CD*/
int		cd_home(t_buildins *vars);
int		fill_path(t_buildins *vars, char **token, int x);
int		cd(t_buildins *vars, char **token);

#endif

/*
shell;
session_manager;
qt_accessibility;
colorterm;
xdg_config_dirs;
ssh_agent_launcher;
xdg_session_path;
xdg_menu_prefix;
gnome_desktop_session_id;
gtk_im_module;
language;
ssh_auth_sock;
xmodifiers;
desktop_session;
ft_hook_name;
gtk_modules;
dbus_starter_bus_type;
ft_hook_pathname;
krb5ccname;
pwd;
logname;
xdg_session_desktop;
xdg_session_type;
gpg_agent_info;
systemd_exec_pid;
xauthority;
xdg_greeter_data_dir;
gdm_lang;
home;
lang;
ls_colors;
xdg_current_desktop;
vte_version;
xdg_seat_path;
gnome_terminal_screen;
xdg_session_class;
term;
libvirt_default_uri;
user;
gnome_terminal_service;
display;
shlvl;
qt_im_module;
dbus_starter_address;
xdg_runtime_dir;
docker_host;
xdg_data_dirs;
path;
gdmsession;
dbus_session_bus_address;
oldpwd;
x;
*/