#!/usr/bin/env python3

# Python script to go through source files in 
# a directory and replace < and > signs with 
# their HTML escape codes in JDoc style comments

# Justus Languell 2021

import os
import sys

exts = ['c', 'h', 'cpp', 'hpp', 'java', 'js']

def docrepl(fn):
    oldfile = ''
    with open(fn, 'r') as f:
        for l in f:
            oldfile += l 
        f.close()

    newfile = ''
    injdoc = False
    for char in oldfile:
        if len(newfile) >= 2:
            if char == '*' and newfile[-1] == '*' and newfile[-2] == '/':
                injdoc = True
            elif char == '/' and newfile[-1] == '*':
                injdoc = False
            if injdoc:
                if char == '<':
                    newfile += '&lt;'
                elif char == '>':
                    newfile += '&gt;'
                else:
                    newfile += char
            else:
                newfile += char
        else:
            newfile += char

    with open(fn, 'w') as f:
        f.write(newfile)
        f.close()

if __name__ == '__main__':
    
    arg = sys.argv[1]
    if os.path.isfile(arg):
        if arg.split('.')[-1] in exts:
            docrepl(arg)
        else:
            print("Not an allowed filetype")
    elif os.path.isdir(arg):
        for (dirpath, dirnames, filenames) in os.walk(arg):
            for filename in filenames:
                if filename.split('.')[-1] in exts:
                    docrepl(f'{dirpath}/{filename}')


