# minishell

## 💡 Overview
**minishell** is a project from [42 Lisboa](https://www.42lisboa.com) that challenges students to create a simplified UNIX shell.  
It focuses on **command parsing**, **process creation**, and **file redirection**, reinforcing understanding of UNIX system calls.

---

## Key Concepts
- Process creation using `fork`
- Executing commands with `execve`
- Pipes (`|`) and redirections (`>`, `<`, `>>`)
- Signal handling (`Ctrl+C`, `Ctrl+D`, `Ctrl+\`)
- Environment variable management
- Error handling and exit codes

---

## Features
- Execute simple commands
- Handle multiple commands with pipes
- Implement built-in commands: `echo`, `cd`, `pwd`, `export`, `unset`, `env`, `exit`
- Handle quotes and spaces correctly
- Robust signal handling

---

## Installation / Compilation
```bash
git clone https://github.com/martimsaunders/minishell.git
cd minishell
make
./minishell
```

---

## Usage Examples

$ ./minishell
minishell> echo "Hello, World!"
Hello, World!
minishell> ls | grep minishell
minishell.c
minishell.h

## Tech Stack
- C
- UNIX API (`fork`, `execve`, `pipe`, `dup2`)
- GNU readline

## ⚡ Challenges / Lessons Learned
- Parsing complex commands with quotes and spaces
- Properly handling child processes and signals
- Managing file descriptors and pipelines
- Writing modular and maintainable C code

## Author
- Mateus Ferreira && Martim Saunders

