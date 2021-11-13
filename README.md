# minishell

## Description

This is group project. We create a simple shell like bash. This project is about processing and file descriptors.


In this project we use my own library - [libft](https://github.com/mishgod/libft). Also we wrote some utils function to different tasks.

Compilation was with flags: `gcc -Wall -Wextra -Werror`.

Project has written in accordance with the Norminette. 

No memory leaks.

## Requirements

* We interpret:  

    * special character `\` like `'\\''`; 

    * sequence of characters for $;

    * single and double quotes.

* Minishell has working history;


* The right executable search and launch based on the PATH variable or by using
relative or absolute path;


* Working redirections (`<`, `<<`, `>`, `>>`);


* Working pipes;


* Signals (`ctrl-C`, `ctrl-D` and `ctrl-\`)

Also we realised some commands: `echo`, `cd`, `pwd`, `export`, `unset`, `env` and `exit`. 

## Using

Use `make` to compile the executable file.

Use `./minishell` to launch program.

Use `make re` to recompile.

Use `make clean` to delete `.o`files.

Use `make fclean` to delete `minishell`, `libft.a` and `.o`files.