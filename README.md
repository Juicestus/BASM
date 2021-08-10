# BASM

BASM stands for "Bad Assembly Language" and is an esoteric programming language.\
BASM is designed to be a challange to write, but not too hard to the point where it isn't fun.\
BASM consists of many improvments off previous language K0D3 which make it just useable.

## Getting started

After you [install](##Install) the language interpreter, you can get started writing BASM code.

### Hello world

In `helloworld.basm` write the BASM code for our Hello World program.

```
( Prints hello world to the console )
print: "Hello, World!\n";
```

Now, run the following command in the terminal. This uses the BASM interpreter to interpret our BASM program. This is assuming BASM is installed as `basm` in `usr/local/bin`. If this is not the case, replace `basm` with the path to the interpreter.

```
$ basm helloworld.basm
Hello, World!
```

A shebang can be used on Unix based operating systems as long as the BASM interpreter is installed as `basm` in `usr/local/bin`. Add the shebang `#!/usr/bin/env basm` to the top of the script.
```
#!/usr/bin/env basm

# As a result of shebangs, anything between a 
# '#' and a newline is not read by the compiler
# Allowing for Bash/Python type comments.

print: "Hello, World! (with shebang)\n";
```

## Install

(Releases coming soon)

### Build from source

**Current version is 0.8**
**Install is assuming Unix based operating systems**
**Full Windows support coming soon**

Requirements:

* Python 3.6 or later for build scripts
* A C/C++ compiler. (GNU g++ is used, so make alias to "g++")

To do the entire process at once, run: `./install.sh`

To build and clean, run: `./build.py build clean`\
The resulting binary located at `bin/basm`\
To use as a shell command, run: `mv bin/basm /usr/local/bin`

I wrote the build system in Python because, as quoted in the actual script:

```python
# I use Python for build systems as an alternative
# to shell scripts, Make, and CMake because, despite
# being an actual language, it is easier to write 
# and understable than said alternatives.
```

<!--
A Python interpreter of version 3.6 or newer is required to build.\
The C/C++ compilers are editable in the file, but it is setup to use gcc/g++ and to build on MacOS or Linux.
-->


