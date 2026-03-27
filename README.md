*This project has been created as part of the 42 curriculum by mbiusing.*

# get_next_line

This project is about making a function that returns a line read from a **file descriptor** or **fd**.

## DESCRIPTION

The project `get_next_line` is to create a function that takes in a `file descriptor` and outputs the next line in the file as a C-style string (unless an error occurs, or there is nothing left to read).

A file descriptor is an **integer** like an **identifier** for a file that's in the program's **open file table**. 

When a file is opened, it's given a file descriptor (the lowest positive integer that hasn't been used yet, starting from 3). 

#### Standard File Descriptors
When any process starts, then that process file descriptors table’s fd(file descriptor) 0, 1, 2 open automatically, (By default) each of these 3 fd references file table entry for a file named /dev/tty

* `stdin` (file descriptor 0): Standard **input** stream, whenever we write any character from the keyboard, it reads from stdin through fd 0 and saves to a file named /dev/tty.
* `stdout` (file descriptor 1): Standard **output** stream, any output to the video screen, it’s from the file named /dev/tty and written to stdout in screen through fd 1.
* `stderr` (file descriptor 2): We see any **error** to the video screen, it is also from that file write to stderr in screen through fd 2.

Negative values are used to indicate errors in opening files. File descriptors can also be used for other things, such as network connections.

The function get_next_line() lets you read from file descriptors, one line at a time, which makes it much easier to parse data in human-readable formats.

## INSTRUCTION

## ALGORITHM

The implementation is based on a persistent buffer (stash) using a static variable.

#### Core Idea
A static variable (stash) stores leftover data between function calls. The function reads chunks of size BUFFER_SIZE using read(). Each chunk is appended to the stash until a newline (\n) is found.

Once a newline is detected:

A line is extracted and returned. Then, remaining data is kept in the stash for the next call.

#### Steps
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

1. [gnl guide gitbook](https://42-cursus.gitbook.io/guide/1-rank-01/get_next_line)
2. [whats a buffer](https://stackoverflow.com/questions/27993971/understanding-buffering-in-c)
3. [what is flushing](https://stackoverflow.com/questions/47735850/what-exactly-is-flushing)
4. [gnl tester](https://github.com/Tripouille/gnlTester) <- after own self testing

### Resources Suggested By Peers

* https://www.geeksforgeeks.org/c/input-output-system-calls-c-create-open-close-read-write/
* https://youtu.be/saMebwRO-Q8?si=5Huhk3zbo61y-W3j
* https://youtu.be/bNzMz6rb_3Y?si=nlCNNvTLOY4BhTpz

### AI Usage

* Used to help to debug
* Identify where memory leak errors are in the code
* Used to help explain certain stuff I couldn't really grasp from some websites

[^1]: [Static Variable : Geeks for Geeks](https://www.geeksforgeeks.org/c/static-variables-in-c/)