#!/usr/bin/env python3

# Compile C++ project to a single executable
# without recompiling objects with no modification
# (c) Justus Languell, 2021

# I use Python for build systems as an alternative
# to shell scripts, Make, and CMake because, despite
# being an actual language, it is easier to write 
# and understable than said alternatives.

import os
import sys
import time

SRC_DIR = 'src'
BIN_DIR = 'bin'
BIN = 'basm'

# Compilers
# '<extension'> : ('<compiler>', '<args'>),
COMPILERS = {
    'c' : ('gcc', ''),
    'cc': ('g++', '-std=c++20'),
    'cpp': ('g++', '-std=c++20'),
}

CACHE = './.build-cache'

if __name__ == '__main__':
    
    if 'mingw' in sys.argv:
        COMPILERS['cc'] = ('g++', '-std=c++17')

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
    
        if os.path.isfile(CACHE):
            with open(CACHE, 'r') as f:
                last = float(f.read())
                f.close()
        else:
            last = 0.

        if '-a' in sys.argv:
            last = 0.

        fplens = []
        for (dirpath, dirnames, filenames) in os.walk(SRC_DIR):
            for filename in filenames:
                fplens.append(len(dirpath + '/' + filename))
        padding = max(fplens) + 1

        object_files = []
        for (dirpath, dirnames, filenames) in os.walk(SRC_DIR):
            print('\033[1m\033[34mCompiling modified sources to object files\033[m')
            for filename in filenames:
                for extension in COMPILERS.keys():
                    if filename.split('.')[-1] == extension:
                        object_file = f'{BIN_DIR}/{dirpath}/{filename}.o'
                        outputstr=f' \033[33m{(dirpath + "/" + filename).ljust(padding)}\033[m was '
                        #outputstr=f' \033[33m{(dirpath + "/" + filename)}\033[m was '
                        if os.path.getmtime(f'{dirpath}/{filename}') > last:
                            outputstr += '\033[31m[MODIFIED]\033[m Compiling to '
                            outputstr += f'\033[33m{object_file}\033[m'
                            compiler, args = COMPILERS[extension]
                            os.system(f'{compiler} {args} -c {dirpath}/{filename} -o {object_file}')
                        else:
                            outputstr += '\033[32m[NOT MODIFIED]\033[m'
                        print(outputstr)
                        object_files.append(object_file)
        print('\033[1m\033[35mLinking object files to binary\033[m')
        for object_file in object_files:
            print(f'\033[32m Linking \033[36m{object_file}\033[m')
        os.system(COMPILERS['cc'][0] + ' ' + ' '.join(object_files) + f' -o {BIN_DIR}/{BIN}')
        print(f'\033[1m\033[34mBinary produced \033[32m[SUCCESSFULLY]\033[m\033[1m as\033[33m {BIN_DIR}/{BIN}')  

        with open(CACHE, 'w') as f:
            f.write(str(time.time()))
            f.close()

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
