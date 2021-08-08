#!/usr/bin/env python3

# JCMS: 
# -Justus's
# -C++
# -Make
# -System

# Compile C++ project to a single executable
# (c) Justus Languell, 2021

# I use Python for build systems as an alternative
# to shell scripts, Make, and CMake because, despite
# being an actual language, it is easier to write 
# and understable than said alternatives.

import os
import sys

SRC_DIR = 'src'
#OBJ_DIR = 't'
BIN_DIR = 'bin'
BIN = 'basm'

# Compilers
# '<extension'> : ('<compiler>', '<args'>),
COMPILERS = {
    'c' : ('gcc', ''),
    'cpp': ('g++', '-std=c++20'),
}

if __name__ == '__main__':

    if 'new' in sys.argv:
        if not os.path.isdir(SRC_DIR):
            os.mkdir(SRC_DIR)
        if not os.path.isfile(SRC_DIR + '/' + BIN + '.cpp'):
            with open(SRC_DIR + '/' + BIN + '.cpp', 'w') as f:
                f.write('#include <iostream>\n\n'
                        + '// This is the main function\n'
                        + 'int main(int argc, char **argv)\n{\n'
                        + '    std::cout << "Hello, world!" << std::endl;'
                        + '\n    return 0;\n}\n')
            f.close()

    if 'build' in sys.argv:
        if not os.path.isdir(BIN_DIR):
            os.mkdir(BIN_DIR)

        if not os.path.isdir(BIN_DIR + '/' + SRC_DIR):
            os.mkdir(BIN_DIR + '/' + SRC_DIR)

        object_files = []
        for (dirpath, dirnames, filenames) in os.walk(SRC_DIR):
            for filename in filenames:
                for extension in COMPILERS.keys():
                    if filename.split('.')[-1] == extension:
                        object_file = f'{BIN_DIR}/{dirpath}/{filename}.o'
                        compiler, args = COMPILERS[extension]
                        os.system(f'{compiler} {args} -c {dirpath}/{filename} -o {object_file}')
                        object_files.append(object_file)
        os.system(COMPILERS['cpp'][0] + ' ' + ' '.join(object_files) + f' -o {BIN_DIR}/{BIN}')

    if 'run' in sys.argv:
        args = ''
        for_program = False
        for arg in sys.argv:
            if arg == 'run':
                for_program = True
            if for_program:
                args += ' ' + arg
        os.system(BIN_DIR + '/' + BIN + args)

    if 'clean' in sys.argv:
        os.system(f'rm -rf {BIN_DIR}/{SRC_DIR}')
