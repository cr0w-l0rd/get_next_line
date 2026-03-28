*This project has been created as part of the 42 curriculum by mbiusing.*

# get_next_line

## DESCRIPTION

The project `get_next_line` is to create a function that takes in a `file descriptor` and outputs the next line in the file.

#### What is a file descriptor?

A file descriptor (fd) is an **integer** like an **identifier** for a file that's in the program's **open file table**. 

When a file is opened, it's given a fd, the lowest positive integer that hasn't been used yet, starting from 3. Why is that so?...

#### Standard File Descriptors
When any process starts, the process fd table’s fd 0, 1, 2 open automatically, (by default) each of these 3 fd references file table entry for a file named `dev/tty`

* `stdin` / Standard **input** stream : fd 0
* `stdout` / Standard **output** stream : fd 1
* `stderr` / Standard **error** stream : fd 2

**Negative values** are used to indicate errors in opening files

## INSTRUCTIONS

#### Step 1

`cc -Wall -Wextra -Werror -c get_next_line.c get_next_line_utils.c`

#### Step 2

`ar rcs get_next_line.a get_next_line.o get_next_line_utils.o`

#### Step 3

`cc -Wall -Wextra -Werror <whatevertestfile or prolly a main.c> get_next_line.a -o test.out`

#### Step 4

`./test.out <a file u wanna open/read from if ure using argv/argc or without adding a file if youre not>`

### Example main.c file

```
#include <fcntl.h>
#include <stdio.h>
#include "get_next_line.h"

int	main(int argc, char *argv[])
{
	int		fd;
	char	*line;
	int		i;

	if (argc != 2)
		return (printf("Usage: ./test <file>\n"), 1);

	fd = open(argv[1], O_RDONLY);
	if (fd < 0)
		return (perror("open failed"), 1);

	i = 1;
	line = get_next_line(fd);
	while (line)
	{
		printf("line %d: [%s]\n", i, line);
		free(line);
		i++;
		line = get_next_line(fd);
	}
	printf("\nline %d: [NULL]\n", i);
	close(fd);
	return (0);
}
```

## ALGORITHM

The implementation is based on a persistent buffer (stash) using a static variable.

#### Core Idea
A **static variable** (*stash*) stores leftover data between function calls. The function reads chunks of size BUFFER_SIZE using read(). Each chunk is appended to the stash until a newline (\n) is found.

Once a newline is detected:

A line is extracted and returned. Then, remaining data is kept in the stash for the next call.

#### Here's a basic rundown of how it goes
1. Read from fd into a buffer
2. Append buffer content to the stash
3. Check if a newline exists in the stash
4. If yes:
* Extract the line
* Update the stash (remove extracted part)
5. If EOF is reached:
* Return remaining data if any
6. Return NULL when no data remains

#### Justification

This algorithm is necessary because:

read() does not guarantee full-line reads.
Lines may span multiple reads.
Multiple lines may be read in a single call.

Using a static stash ensures:

No data is lost between calls.
The function behaves correctly across multiple invocations.
It supports arbitrarily long lines.

### Main Things Learnt
* `Static Variables`[^1]
* `read()` function
* `open()` function
* file descriptors

## RESOURCES

### Things I searched up

1. [gnl guide gitbook](https://42-cursus.gitbook.io/guide/1-rank-01/get_next_line) <- idea on how to start
2. [whats a buffer](https://stackoverflow.com/questions/27993971/understanding-buffering-in-c)
3. [what is flushing](https://stackoverflow.com/questions/47735850/what-exactly-is-flushing)
4. [gnl tester](https://github.com/Tripouille/gnlTester) <- after own self mediocre minimal testing

### Resources Suggested By Peers

* https://www.geeksforgeeks.org/c/input-output-system-calls-c-create-open-close-read-write/
* https://youtu.be/saMebwRO-Q8?si=5Huhk3zbo61y-W3j
* https://youtu.be/bNzMz6rb_3Y?si=nlCNNvTLOY4BhTpz

### AI Usage

* Used to help to debug
* Identify where memory leak errors are in the code
* Used to help explain certain stuff I couldn't really grasp from some websites

[^1]: [Static Variable : Geeks for Geeks](https://www.geeksforgeeks.org/c/static-variables-in-c/)