# TO-DO #

**->get minishell-tester to work!**

*input: $cmd*
	->get correct error msg

*input: (execute some cmds) then exit*
	->should exit on first exit!

*input: $cmd | ls (dup2 c - 1 redir input: bad fd)*
	->ignore first, no error msg, just execute ls

**input: echo hi > out > out1 > out2**
	->put "hi" into out2, also create the other two files but they stay empty

*input: ls | wc*
	->fix pipes!

**input: mkdir a; cd a; mkdir b; cd b; mkdir c; cd c; rm -r ../../../a;**
	->cd .. should display "path/to/pwd/.."
	->cd .. should display "path/to/pwd/../.."
	->cd .. should display actual pwd again (if exists)

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

**input: unset PWD; cd ..; cd /minishell**
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

**input: cntl-C**
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

**rewrite expand& echo split part**

**sort exit messages**

**add i (=index) to pipex struct instead of using c to iterate through the cmds/processes**

rewrite update_free_arr and learn loop_cmd_check