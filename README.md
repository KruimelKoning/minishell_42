# minishell_42

## What we learned from this project: ✅
- The ins and outs of Bash
- How to manage complex group projects
- How to parse complex strings
- How to debug a large codebase
- How to use pipes and signals

## Project Goals: 🎯
- Recreate bash
- Store variables in an environment (env)
- Handle the following signals: `ctrl-C`, `ctrl-D` & `ctrl-\`
- Recreate bash builtins such as: `echo`, `cd`, `pwd`, `export`, `unset`, `env` & `exit`

## Images: 📷
### A basic use case of minishell, where you can use `< test.txt grep ":D" | wc -l` to find the amount of lines with a `:D` in a file
![image](https://github.com/user-attachments/assets/c447edec-d84c-4e4c-b182-10f2b52626f5)

### Some basic error handeling. After running the incorrect command, it's return value is retrieved using `$?`
![image](https://github.com/user-attachments/assets/fbc342bc-e0eb-4d01-8e8e-22855ef8253d)

### Manually inserting text using heredoc (using `<<`). The string after the `<<` is the delimiter, stopping the process
![image](https://github.com/user-attachments/assets/4f6e6afb-a885-4a72-a469-abde46ee49cb)

### Made by Lasse Bartels & Alijn Kuijer - March & April 2024
