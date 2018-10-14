# Hash: Command line interpreter

**Ha**rsha **Sh**ell, is a command line interpreter written in C.

## Features and Usage

Initially when the shell is started, only commands from the /bin/ directory can be run.

```bash
>hash ls -la
```

'>hash' is output after execution after each command.

User defined paths can be appended to the internal path variable.

```bash
>hash $PATH -a /usr/bin/
/usr/bin/
```

And yes, the trailing '/' is necessary. After execution of the above command use the commands from the new directory as before.

```bash
>hash wc hash.c
 145  317 3546 hash.c
 ```
 
 Three built-in commands are provided:
 - cd   : can be used to change the working directory
 - exit : exit from hash
 - path : used to overwrite the path variable with a single path
 
 ```bash
 >hash path " "
 >hash ls
 'ls' command not found in the current path.
 Try adding the path of the command through: $PATH -a [path].
```

In the above test, path variable was cleared, and ls couldn't be found!!

Output from a command can be redirected to a desired file.

```bash
>hash ls > output
```

output file contains the result of ls.

## Stuff to add
- [ ] Facility for batch processing
- [ ] run many commands in parallel
