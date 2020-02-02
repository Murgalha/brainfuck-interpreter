# Brainfuck interpreter

## About

This repo contains an interpreter for the [Brainfuck language](https://esolangs.org/wiki/Brainfuck).

### Conventions and strictness

This interpreter supports a tape of size 30000, with each cell being an unsigned 32-bit one.
Although the wiki says to ignore non-valid, I've implemented a strict version that throws error whenever a non-valid (excluding spaces) character appears on the source file.

## Dependencies

This project depends on any C++ compiler compatible with C++11.

## Compile

One can simply run `make` or manually compile the src/main.cpp file to run the interpreter.

## Run

Run the compiled version named `brainfuck-interpreter` (if you compiled with the Makefile) passing the input file as the only argument. The program will output the possible errors and the eventual output.
