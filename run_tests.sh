#! /usr/bin/env zsh

dir="$PWD"
minishell="$(realpath ./minishell)"
success_count=0
failure_count=0

title() {#{{{
	printf "\n\e[36m >>>>>>>>><<<<<<<<<\n"
				printf "\n > STARTING TESTS <\n"
				printf "\n >>>>>>>>><<<<<<<<<\e[0m\n\n"
}
title
#}}}

# ============================= TESTS STDIN/OUT ============================== #

t() # test stdout diff with bash{{{
{
	cd /tmp
	local bash_diff="$(diff <(echo "$@" | tr -s \; "\n" | tr -s \\ / 2>/dev/null | $minishell) <(echo "$@" | tr -s \; "\n" | tr -s \\ / 2>/dev/null | bash))"
	if [ -n "$bash_diff" ]; then
		printf "❌\e[31m Error:\e[33m > %s \e[0m (diff: me / bash)\n%s\n" "$@" "$bash_diff"
		((failure_count++))
	else
		printf "✅\n"
		((success_count++))
	fi
}

basic_tests() {
	printf "\n\e[32m >>>>>>>>><<<<<<<<<<\n"
				printf "\n > STDIN/OUT TESTS <\n"
				printf "\n >>>>>>>>><<<<<<<<<<\e[0m\n\n"
}
#}}}

run_basic_tests(){#{{{
	basic_tests
	t 'echo "hello world"'
	t 'ls -l'
	# Quote tests:
	t 'echo "hello world" yo oy'
	t 'echo yo"hello world"oy hi'
	t 'echo a b"c  d" e"f g"h i   j k'"'l  op'q "
	# t 'printf "$HOME\n"'#TODO: handle escapes
	# Env expansion tests:
	t 'echo $HOME'
	t 'echo $HOM'
	t 'echo $HOMES'
	t 'echo $ d "$.$HOME" "$d $ x$,"'
	t 'echo $HOME-R$UN'
	t 'echo \$HOME-R\$UN'
	t 'echo "$HOME-R$UN"'
	t 'echo "\"\\$HOME-R\$UN\""'
	t 'echo \"$HOME-R$UN\"'
	t 'echo '"'"'$HOME-R$UN'"'"
	# t 'echo "$HOME;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;"' # if replaced with \n, we would have a multi-line string. Not to be tested
	t 'echo "$HOME aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa$USER"'
	t 'echo "\\\\"'
	t 'echo "\\""'
	t 'cd; echo "\e[37m$PWD \e[36m$USER\t\e[31m❯ \e[0m"' #PWD mac can be an issue (/tmp vs /private/tmp)
	# t 'echo "\\"' does not automatically work
	t 'echo "hello\\world\"yo"'
	t 'cd; echo path is $PATH and workind dir $PWD and test $USER$PWD'
	# t 'echo "a$HOME b"'
	# Multi-command tests:
	t 'echo hello ; echo world'
	t 'echo hello;echo world; echo haha'
	t 'echo hello;efdscho world; echo yo'
	# Pipe commands
	t 'ls | rg e'
	t 'cat /etc/hosts | grep lo | grep :'
	t 'cat /XXX/hosts | grep lo | grep :'
	t 'cat /etc/hosts | fail_pipe'
	t 'cat /etc/hosts | fail_pipe | grep :'
	# t 'echo hi > test_file | echo ho>>test_file | grep i < test_file ; rm -f test_file ; ls' # can differ on bash, maybe because bash is slower ?
	# for example the following returns in zsh but not in bash. it's like zsh is wait for last but one pipe, and bash not
	# t 'grep -R a /usr/share/man > test_file | grep e < test_file | grep e'
	# Builtin: echo
	t 'echo -n hello world'
	t 'echo -n -n hello world fsdf'
	t 'echo -n-n hello lala'
	t 'echo -nfds fsd'
	t 'echo'
	# Bultin: export
	# t 'export lll=ooo -fdsfs=fds xxx=iii; echo $lll $fdsfs $xxx; export lll+=yo; echo $lll; export xxx; echo $xxx; export cc; echo $cc; export HELLO_WORLD=yo! ; echo $HELLO_WORLD; echo "$cc"' # export is not supposed to take args anymore
	t 'export'
	# Builtin: unset
	t 'unset lll -fdsfs LANG=fds xxx; echo $lll $fdsfs $xxx $LANG'
	# Builtin: cd / pwd
	# t 'cd;pwd; cd .. ; pwd; cd /etc; pwd; cd /;pwd;cd etc;pwd;cd ../var/log; pwd' # MAC does not really have an /etc folder but a /private/etc, idem for /var -> /private/var
	t 'cd;pwd;echo $PWD; cd ..;pwd;echo $PWD; cd /usr;pwd;echo $PWD; cd /;pwd;cd usr;pwd;cd ../usr/lib; pwd'
	# fail to open
	t 'echo hello > i/n/e/x/is/tent'
}
#}}}
run_basic_tests

# ============================ TEST REDIRECTIONS ============================= #

t_redir() # test redirections{{{
{
	cd /tmp

	local cmd="$(printf "$@" | tr -s \; "\n" | tr -s \\ / 2>/dev/null)"
	local bash_result="$(printf "$@" | tr -s \; "\n" | tr -s \\ / 2>/dev/null| bash)"
	local bash_diff
	local -a bash_file_content
	local -a mini_file_content
	local -a adiff
	local i=1
	local file

	# record file content from bash
	for file in "${@:2}";do
		((i++))
		bash_file_content[$i]="$(cat "$file")"
		rm "$file"
	done

	# stdout diff
	local minishell_result="$(printf "$@" | tr -s \; "\n" | tr -s \\ / 2>/dev/null | $minishell)"
	bash_diff="$(diff <(echo "$minishell_result") <(echo "$bash_result"))"

	# record file content from minishell and diff with bash
	i=1
	for file in "${@:2}";do
		((i++));
		mini_file_content[$i]="$(cat "$file")"
		adiff[$i]="$(diff <(echo "${mini_file_content[$i]}") <(echo "${bash_file_content[$i]}"))"
		rm "$file"
	done

	# count file diff
	while [ $i -ge 2 ];do
		if [ -n "${adiff[$i]}" ]; then
			printf "❌\e[31m Error:\e[33m %s \e[0m with file [%s] (diff: me / bash)\n%s\n" "$cmd" "${@[$i]}" "${adiff[$i]}"
			((failure_count++))
		else
		printf "✅\n"
			((success_count++))
		fi
		((i--))
	done

	# count stdout diff
	if [ -n "$bash_diff" ]; then
		printf "❌\e[31m Error:\e[33m %s \e[0m (diff: me / bash)\n%s\n" "$cmd" "$bash_diff"
		((failure_count++))
	else
		printf "✅\n"
		((success_count++))
	fi

}

title_redir() {
printf "\n\e[32m >>>>>>>>>>><<<<<<<<<<<\n"
			printf "\n > REDIRECTIONS TESTS <\n"
			printf "\n >>>>>>>>>>><<<<<<<<<<<\e[0m\n\n"
}
#}}}

run_redir_tests() {#{{{
	title_redir
	t_redir 'echo hello > %s\n' 'test_redir_file'
	t_redir 'echo hello world > %1$s; echo yo >> %1$s; head -n1 < %1$s\n' 'test_redir_file'
	t_redir 'echo hello world > %1$s; echo yo >> %1$s ; cat < %1$s\n' 'test_redir_file'
	t_redir 'ls /usr > %1$s | cat /etc/hosts | grep lo ; cat %1$s\n' 'test_redir_file'
}
#}}}
run_redir_tests

# ============================ TEST RETURN VALUES ============================ #

rv() #test return values{{{
{
	cd /tmp
	touch test_file
	cmd="$@"
	echo "$cmd" | tr -s \; "\n" | tr -s \\ / 2>/dev/null| $minishell >/dev/null
	ret_mini="$?"
	echo "$cmd" | tr -s \; "\n" | tr -s \\ / 2>/dev/null| bash >/dev/null
	ret_bash="$?"
	if [ "$ret_mini" -ne "$ret_bash" ]; then
		printf "❌\e[31m Error:\e[33m > %s \e[0m (return: me[%d] - bash[%d])\n%s\n" "$cmd" "$ret_mini" "$ret_bash"
		((failure_count++))
	else
		printf "✅\n"
		((success_count++))
	fi
	rm test_file
	echo
}

title_returns() {
	printf "\n\e[32m >>>>>>>>>|<<<<<<<<<\n"
				printf "\n > RET VALUE TESTS <\n"
				printf "\n >>>>>>>>>|<<<<<<<<<\e[0m\n\n"
}
#}}}

run_return_values_tests(){#{{{
title_returns
	rv echo "hello wolrd"
	rv commande_qui_n_existe_pas argument_a_la_noix
	rv './test_file'
	rv './gfdsa'
	rv '/bin'
	# fail to open
	rv 'echo hello > i/n/e/x/is/tent'
	rv 'export'
	rv 'exit 42'
	rv 'fsdfsd ; exit'
	rv 'export ='
}
#}}}
run_return_values_tests

# ================================ TEST LEAKS ================================ #

# leak_test() {{{
leaks=0

leak_report () {
	local report="$(cat /tmp/minishell_leak_report)"
	printf "$report"
	if [ -n "$report" ]; then ((leaks++)); else printf "✅\n"; fi
}

leak_test() {
	if [ "$1" = "-unit-test" ]; then opt="$1"; shift; fi
	cmd="$@"
	if [ "$(uname)" = "Darwin" ]; then
		touch ./minishell_leak_report # to test leaks when executing a file without permission
		echo "$cmd" | tr -s \; "\n" | tr -s \\ / | $minishell -leaks ${opt:-} > /dev/null & pid=$!
		(leaks $pid | rg -A2 LEAK) && printf "\e[33mwith command: $cmd\e[0m\n" && ((leaks++))
		rm ./minishell_leak_report
	elif ! which valgrind >/dev/null; then
		printf "\e[31mValgrind not installed.\n"
	else
		valgrind -q --log-file=/tmp/minishell_leak_report --leak-check=full --show-leak-kinds=all --track-origins=yes $minishell <<< "$cmd" &>/dev/null
		leak_report
	fi
}

title_leaks() {
	printf "\n\e[32m >>>>>>>>><<<<<<<<<\n"
				printf "\n > LEAKING  TESTS <\n"
				printf "\n >>>>>>>>><<<<<<<<<\e[0m\n\n"
}
#}}}

run_leak_tests(){#{{{
	title_leaks
	leak_test echo kanpai
	leak_test ps -a
	leak_test /bin/ls
	leak_test 'echo a b"c  d" e"f g"h i   j k'"'l  op'q "
	leak_test 'echo path is $PATH and workind dir $PWD and test $USER$PWD'
	leak_test 'echo path is $PATH and $fsdf is unknown'
	leak_test 'printf "path is $PATH and $fsdf is unknown"'
	# Multi-command tests:
	leak_test 'echo hello;echo world;'
	# Leaks errors
	leak_test 'fsafsd'
	leak_test './Makefile'
	leak_test './minishell_leak_report'
	# Leaks with redir
	leak_test 'rm -f test_file; echo hello world > test_file; echo yo >> test_file ; cat < test_file ; rm test_file'
	# Leak test with pipe
	leak_test 'cat /etc/hosts | grep lo | grep :; echo hello | world | grep ya; printf yo; echo ha; echo hi > test_file | grep x; echo hi > test_file | grep i < test_file'
	# Bultin: export
	leak_test 'export lll=ooo -fdsfs=fds xxx=iii; echo $lll $fdsfs $xxx;export;export; export lll+=xxx; echo $lll'
	# Builtin: unset
	leak_test 'unset lll -fdsfs LANG=fds xxx; echo $lll $fdsfs $xxx $LANG'
	# Builtin: cd / pwd
	leak_test 'cd;pwd;echo $PWD; cd ..;pwd;echo $PWD; cd /usr;pwd;echo $PWD; cd /;pwd;cd usr;pwd;cd ../usr/lib; pwd'
	leak_test 'mkdir test_dir ; cd test_dir ; rm -rf ../test_dir ; cd . ; pwd ; cd . ; pwd ; cd .. ; pwd'
	# Syntax error
	leak_test 'echo hello ;; t world'
	# Unit-test leaks:
	leak_test -unit-test echo hello
}
#}}}
run_leak_tests

result() {#{{{
	if [ $failure_count -eq 0 ]; then
		COLOR_FAIL="\e[32m"
	else
		COLOR_FAIL="\e[31m"
	fi
	if [ $leaks -eq 0 ]; then
		COLOR_LEAKS="\e[32m"
	else
		COLOR_LEAKS="\e[31m"
	fi
	printf "\n\e[36m-----------------\n"
	printf "|| Success: \e[32m%02d\e[36m ||\n" $success_count
	printf "|| Failure: "$COLOR_FAIL"%02d\e[36m ||\n" $failure_count
	printf "|| LEAKS: "$COLOR_LEAKS"  %02d\e[36m ||\n" $leaks
	printf -- "-----------------\e[0m\n"
}
#}}}
result
cd "$dir"
# vim: fdm=marker
