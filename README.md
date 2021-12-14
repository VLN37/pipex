# Pipex

This project serves as an introduction to interprocess communication and error management conforming to POSIX standards.


The mandatory part of the project asks us to execute and redirect input output of two Unix programs in C, simulating a bash command as in the example below:

`< filein cmd1 | cmd2 > fileout`

The bonus part of the project asks us to handle an indefinite number of pipes, as well as user input as the infile, as in the examples below:

`< file1 cmd1 | ... | cmdx > fileout`

or, with user input:

`<< limiter cmd1 | ... | cmdx > fileout`

- - -

## What i learned?

This project gives us a detailed view of things we already used in a daily basis. How the file descriptors and stdIO work in depth and how to redirect them to wherever you want.

We also have to asks the operating system information about files and update system variables accordingly.

This opens us many avenues, breaking away from the constraints of our C program, being now able to ask anything we want to know about our own system, or even in the web, and utilize that information without interrupting our running program.

## My badge

![Pipex badge](/docs/pipexm.png)

## My grade

![Pipex grade](/docs/pipexgrade.png)

## Requirements

* linux system with GCC and bash (it doesn't work in zsh due to how the quotes are handled)

## How to use

Clone the repository:

`git clone --recurse-submodules https://github.com/VLN37/pipex`

Compile the program with:

`make`

Run the program in the format below. Some examples are:

`./pipex .gitignore "tr a b" "tr b c" "tr c d" outfile`

`./pipex EOF "tr a b" "tr b c" outfile`

`./pipex .gitignore "ping 8.8.8.8" "grep ms" outfile`

Or any unix command you want!

## License

This project is licensed under the MIT terms, [available here](LICENSE)
