# minishell
# Minishell  
As beautiful as a shell  
Based on the official 42 subject and evaluation scale.

## Overview  
Minishell is a simplified Bash-like command interpreter written in C.  
It recreates essential shell behavior — parsing, pipelines, redirections, environment handling, built-ins, and signal management — providing a practical understanding of UNIX process control and file descriptors.

This project follows 42 School requirements and respects the Norm.

## Features

### Core Functionality
- Interactive prompt with command history  
- Command execution via PATH lookup or absolute/relative path  
- Environment variable expansion (`$VAR`, `$?`)  
- Quote handling:  
  - `'single quotes'` → literal  
  - `"double quotes"` → literal except `$VAR`  
- Redirections:  
  - `<` input  
  - `>` truncate output  
  - `>>` append  
  - `<<` heredoc  
- Pipeline support using `|`  
- Correct handling of whitespace and empty commands  
- Exactly one allowed global variable (signal storage)

### Signal Behavior  
Matches bash in interactive mode:
- `ctrl-C` → new prompt  
- `ctrl-D` → exit minishell  
- `ctrl-\` → no effect  
- Proper behavior when running blocking commands (`cat`, `grep`, etc.)

### Built-ins
- `echo` with `-n`  
- `cd`  
- `pwd`  
- `export`  
- `unset`  
- `env`  
- `exit`

### Memory & Error Handling
- No crashes or undefined behavior  
- No memory leaks from user code (readline leaks ignored by subject)  
- Consistent error codes aligned with bash  

---

## Architecture

### Parsing
- Tokenizer supporting quotes and operators  
- Environment variable expansion  
- Command + argument node construction  
- Redirection and pipe detection  
- Syntax validation (unclosed quotes, invalid sequences)

### Execution Engine
- Forking and piping with `pipe()` and `dup2()`  
- Redirection setup per command node  
- Built-ins executed in parent or child depending on semantics  
- PATH resolution and error reporting  
- Correct propagation of exit status

### Signal Handling
- One global variable storing signal number  
- Custom handlers for interactive mode  
- Safe heredoc interrupt behavior  

---

## Installation
```bash
make
./minishell
