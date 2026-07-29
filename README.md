# Minishell

Minishell is a small Unix shell written in C. It recreates the core behavior of
an interactive Bash-like command line: reading input, parsing commands,
expanding environment variables, applying redirections, building pipelines,
and launching built-in or external programs.

This project was developed as part of the 42 curriculum and focuses on process
management, file descriptors, signals, parsing, and careful memory management.

## Features

- Interactive prompt and command history powered by GNU Readline
- External command execution using `PATH`, `fork`, `execve`, and `wait`
- Single and double quote handling
- Environment variable expansion, including `$?`
- Multi-command pipelines with `|`
- Input and output redirections:
  - `<` reads input from a file
  - `>` writes output to a file
  - `>>` appends output to a file
  - `<<` reads a heredoc
- Variable expansion inside unquoted heredocs
- Bash-like syntax and command error reporting
- Interactive signal handling for `Ctrl-C`, `Ctrl-\`, and `Ctrl-D`

### Built-ins

| Command | Behavior |
| --- | --- |
| `echo [-n]` | Prints its arguments, optionally without a trailing newline |
| `cd [path]` | Changes directory and updates `PWD` and `OLDPWD` |
| `pwd` | Prints the current working directory |
| `export [name[=value] ...]` | Adds variables or displays the sorted environment |
| `unset [name ...]` | Removes environment variables |
| `env` | Prints exported variables |
| `exit [status]` | Exits the shell with an optional status code |

## Requirements

- A Unix-like operating system
- `cc`
- `make`
- GNU Readline headers and library

On Debian or Ubuntu, the required development packages can be installed with:

```sh
sudo apt install build-essential libreadline-dev
```

The project includes its own `libft` dependency in `dependencies/libft`.

## Building

From the repository root, run:

```sh
make
```

This builds `libft` and creates the `minishell` executable.

Other available Makefile targets are:

```sh
make clean   # remove object files
make fclean  # remove object files and the executable
make re      # perform a clean rebuild
```

## Usage

Start the shell with:

```sh
./minishell
```

Example session:

```console
Minishell>$ echo "Hello, $USER"
Hello, tridley
Minishell>$ printf "one\ntwo\n" | wc -l
2
Minishell>$ cat < input.txt | grep minishell > matches.txt
Minishell>$ echo $?
0
Minishell>$ exit
exit
```

At the interactive prompt:

- `Ctrl-C` cancels the current input and displays a fresh prompt.
- `Ctrl-\` is ignored.
- `Ctrl-D` exits the shell when the input line is empty.

## How It Works

Input passes through four main stages:

1. **Lexing** — the input is split into words, pipes, and redirection tokens
   while preserving quoted sections.
2. **Parsing and expansion** — tokens are converted into a linked list of
   command structures; quotes are removed and environment variables are
   expanded.
3. **Redirection and pipeline setup** — the shell prepares file descriptors,
   heredocs, and pipes for each command.
4. **Execution** — built-ins run directly when appropriate, while external
   commands and pipeline stages run in child processes.

The exit status of the most recently executed command is kept in
`g_exit_status` and is available through `$?`.

## Project Structure

```text
.
├── Makefile
├── dependencies/
│   └── libft/                    # Local C utility library
├── includes/
│   ├── execution.h
│   ├── lexing.h
│   ├── minishell.h
│   └── parsing.h
└── src/
    ├── main.c                    # Read-evaluate loop
    ├── signal_handling*.c        # Interactive and child signals
    ├── lexing/                   # Tokenization and syntax validation
    ├── parsing/                  # Command construction and expansion
    └── execution/
        ├── builtin/              # Shell built-ins
        ├── external_command/     # PATH lookup and execve
        ├── redirections/         # Files, heredocs, and pipeline execution
        └── pipe.c                # Pipe and child-process management
```

## Project Highlights

Minishell brings together several core Unix concepts in one cohesive program:
process creation, inter-process communication, file descriptor management,
signal handling, environment management, and command parsing. Its modular
structure keeps lexing, parsing, expansion, and execution clearly separated,
making the shell easier to understand, test, and extend.
