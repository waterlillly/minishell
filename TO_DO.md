# TO-DO #

**->get minishell-tester to work!**

*input: $cmd*
	->get correct error msg

*input: (execute some cmds) then exit*
	->should exit on first exit!

*input: $cmd | ls (dup2 c - 1 redir input: bad fd)*
	->ignore first, no error msg, just execute ls

*input: echo hi > out > out1 > out2*
	->put "hi" into out2, also create the other two files but they stay empty

*input: ls | wc*
	->fix pipes!

*input: mkdir a; cd a; mkdir b; cd b; mkdir c; cd c; rm -r ../../../a;*
	->cd .. should display "path/to/pwd/.."
	->cd .. should display "path/to/pwd/../.."
	->cd .. should display actual pwd again (if exists)

	/home/lbaumeis/CCore/projects/minishell> mkdir a
	/home/lbaumeis/CCore/projects/minishell> cd a
	/home/lbaumeis/CCore/projects/minishell/a> mkdir b
	/home/lbaumeis/CCore/projects/minishell/a> cd b
	/home/lbaumeis/CCore/projects/minishell/a/b> mkdir c
	/home/lbaumeis/CCore/projects/minishell/a/b> cd c
	/home/lbaumeis/CCore/projects/minishell/a/b/c> rm -r ../../../a
	/home/lbaumeis/CCore/projects/minishell/a/b/c> cd ..
		cd: /home/lbaumeis/CCore/projects/minishell/a/b/c/..: No such file or directory
	/home/lbaumeis/CCore/projects/minishell/a/b/c/..> echo $PWD $OLDPWD
	/home/lbaumeis/CCore/projects/minishell/a/b/c/.. /home/lbaumeis/CCore/projects/minishell/a/b/c
	/home/lbaumeis/CCore/projects/minishell/a/b/c/..> cd ..
		cd: /home/lbaumeis/CCore/projects/minishell/a/b/c/../..: No such file or directory
	/home/lbaumeis/CCore/projects/minishell/a/b/c/../..> echo $PWD $OLDPWD
	/home/lbaumeis/CCore/projects/minishell/a/b/c/../.. /home/lbaumeis/CCore/projects/minishell/a/b/c/..
	/home/lbaumeis/CCore/projects/minishell/a/b/c/../..> cd ..
	/home/lbaumeis/CCore/projects/minishell> echo $PWD $OLDPWD
	/home/lbaumeis/CCore/projects/minishell /home/lbaumeis/CCore/projects/minishell/a/b/c/../..
	/home/lbaumeis/CCore/projects/minishell> cd -
		cd: /home/lbaumeis/CCore/projects/minishell: No such file or directory
	/home/lbaumeis/CCore/projects/minishell> cd ..
	/home/lbaumeis/CCore/projects> echo $PWD $OLDPWD
	/home/lbaumeis/CCore/projects /home/lbaumeis/CCore/projects/minishell
	/home/lbaumeis/CCore/projects> cd ..
->	/home/lbaumeis/CCore> cd p
->		pipex/      pre_exec.c  
->	/home/lbaumeis/CCore> ls
->		buildins   lexparse  Makefile	  more_cmds.c  redir.c	  testing.txt
->		execute.c  libft     minishell	  pipex        signals.c  TO_DO.md
->		exit.c	   main.c    minishell.h  pre_exec.c   start.c
	/home/lbaumeis/CCore> pwd
	/home/lbaumeis/CCore
	/home/lbaumeis/CCore> echo $PWD $OLDPWD
	/home/lbaumeis/CCore /home/lbaumeis/CCore/projects
->	/home/lbaumeis/CCore> cd projects
	/home/lbaumeis/CCore/projects> cd minishell/
	/home/lbaumeis/CCore/projects/minishell> 

**input: echo ""$"" (same for ''$'')**
	->should display a nl
	->only for a single $-sign
	->if double_quote_count % 2 == 0: only nl
	->else: display $-sign with a nl

*input: echo hi$$$*
	->should print the whole thing, do not leave out the dollar signs!

**input: expr $? + $?**
	->expand values (exitcodes) before passing values to execve

*input: echo $?*
	->should print the right exitcode

**input: exit 2 | exit 42**
	->should not exit the shell, just update the exitstatus to the second part (42)
	(if echo $? gets called afterwards it should say 42!)
	-> if multiple exits and ls at the end: exit with ls exit code (0) and display ls!

*>>(real) exit 42 | exit -1*
*>>(real) echo $?*
*>>255*
*>>(real) exit 42 | exit -10*
*>>(real) echo $?*
*>>246*
*>>(real) exit 42 | exit -100*
*>>(real) echo $?*
*>>156*

(our) exit abc | exit 24
(real) echo $?
24
(real) exit abc | exit 24
bash: exit: abc: numeric argument required
(real) echo $?
24

*input: unset PWD; cd ..; cd /minishell*
	->should work& also update env and export as soon as there is a valid pwd/oldpwd again

*input: start minishell without env; show env+export* (handled for now with check in main)
	-> has to have backup env and export!
	-> 'env -i ./minishell'

*input: echo hi | echo hello (dup2 c - 1 redir input: bad fd) (ostrich-fix)*
	->should display only hello

*input: echo hi > out | echo hello > out1 (dup2 c - 1 redir input: bad fd) (ostrich-fix)*
	->should create two files with hi in out and hello in out1

*input: any builtin*
	-> should change return and the data should change in parent

input: 	/home/lbaumeis/CCore/projects/minishell> cd ..
		/home/lbaumeis/CCore/projects> cd minishell/
		/home/lbaumeis/CCore/projects/minishell/> cd ..
		/home/lbaumeis/CCore/projects> cd minishell
		/home/lbaumeis/CCore/projects/minishell> 

*input: cntl-C*
	->exit code: 130 and exits!
	->cntl-D ->sets exit code to 130?

**input: cntl+Z**
	->should not exit bash, cntl+D should! (cntl+C should start a new promt)

*input: (mostly when piping I think)*
	->minishell and bash suddenly dont display input anymore but still execute commands

*input: -> export cmd=" -l" = [export] [md= -l]*

*input: cd ..*
	->if executed in child: doesnt work
	->if (buildins) moved to run/parent process:
		echo hi | echo hello displays both because forking only happens if its not a buildin then

*rewrite expand& echo split part*

**sort exit messages**

rewrite update_free_arr and learn loop_cmd_check

**simplify (file xport.c) create_add_export -> too many temps**

in export the name of the variable cannot contain qoutes, $ or start with a number

several empty sq or dq width quotes crashes

WORKS:
echo "hi"''hello$HOME'""' $$$fuck'hello$hello$$$PWD$'""
	->hihello/home/lbaumeis"" 524212hello$hello$$$PWD$
echo hi" "hi
	->hi hi
echo " hi"
	-> hi
echo hi""hi
	->hihi
echo hi"  "hi
	->hi  hi
echo hi"$USER"hi
	->hilbaumeishi
echo hi" $USER"hi
	->hi lbaumeishi
echo hi"$USER "hi
	->hilbaumeis hi
echo " $USER"
	-> lbaumeis
echo "hi"'hi""'"hi"
	->hihi""hi
echo "hi"'hi ""'"hi"
	->hihi ""hi
echo ''"hi''"''
	->hi''
echo ""'hi"'
	->hi"
echo '"hi''"'
	->"hi"
echo "''""''"'''""'"""'"
	->''''""'
echo "abc''"'"acb""''""'"'abc'"
	->abc''"acb""""'abc'
echo "abc''"'""abc""''""'"'abc'"
	->abc''""abc""""'abc'
echo '"$USER"'
	 ->"$USER"
echo hi "" "" hi
	->hi    hi
echo "'"'''""$""'''"'"
	->'""$""'
echo $PWD"''"$
	->/home/lbaumeis/CCore/projects/minishell''$

**DOESNT WORK:**


**input: export cmd=" -l"**
	export cmd=" -l"
	ls$cmd
	->cmd not found (BUT: expanded correctly: pars->ps[0]: ls -l, but should be: pars->ps[0]: ls and pars->ps[1]: -l)


*add check for unset vars*

input: export var="'what'"
	-> should be 'what'
input: export var='"what"'
	-> should be "what"
input: export var="$USER"
	-> should be mehras
input: export var='ABC'
	-> should be ABC
input: export var='$USER'
	-> should be $USER
input: export var=' $USER'
	-> should be  $USER (extra space)
input: export var= $USER
	-> should declare 2 vriables var="" and mehras (mehras should not have an equal sign nor dqs)
input: export var1 var2
	-> var2 is missing
note: if a variable already is set before minishell starts trying to reset that var causes segfault


doesn't expand:
/bin/echo ''$?''"42"
/bin/echo "'$USER'"
/bin/echo '"'$USER'"'
/bin/echo "''$USER''"
/bin/echo "$?"
/bin/echo "'$?'"
/bin/echo '$USER' "$USER" "text  ' text"
/bin/echo $USER =intergalaktikus miaf szomez

**execute heredoc(s) even though syntax error occured**

**dup2 filein: Bad fd**
	cat <minishell.h|ls
	->dup2 filein: Bad file descriptor (still executes ls though)

