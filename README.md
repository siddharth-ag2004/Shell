# Description

# Assumptions

1. Since in seek, newfolder as target prints newfolder.txt ,ive assumed that the target word must be a prefix of the actual file.

2. seek cannot see hidden files.

3. If the total time taken by all the processes in a single line of commands is greater than 2, then im printing the whole commmand line in the next prompt.

4. In seek , assumed that flags cannot be combined into one flag(for eg, -fe , -de ,etc are not valid flags).

5. In pastevents, if two commands have the same execution, but differ in number of spaces , then they are considered to be different commands when pastevents is run.

6. Max number of commands in a single line is 100, and maximum length of each command is 200.

7. In pastevents execute, the command to be executed will completely replace the original command. Having 2 or more pastevent executes in one command line will add the corresponding number of commands to pastevents.

8. In proclore, my shell is the only foreground process continuously running in foreground, any other process except for ./a.out will not print '+' sign.

9. Exit command has not been handled yet as that is not a specification.

10. peek - has been assumed to be a valid command and is equivalent to the ls of the previous directory.
