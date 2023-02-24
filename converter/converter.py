#! /usr/bin/env python3

import argparse
import typing as tp


def convert(source: str, output: tp.Optional[str]) -> None:
    if output is None:
        output = "/dev/stdout"
    
    with open(output, "w") as fout:
        print("""#include <stdio.h>

char stack[30000];
char *ptr = stack;

int main() {""", file=fout)
        pref = "\t"
        with open(source, "r") as fin:
            for c in (symb for line in fin for symb in line):
                if c == '[':
                    print(pref + "while (*ptr) {", file=fout)
                    pref += "\t";
                if c == ']':
                    pref = pref[:-1]
                    print(pref + "}", file=fout)
                if c == '+':
                    print(pref + "++*ptr;", file=fout)
                if c == '-':
                    print(pref + "--*ptr;", file=fout)
                if c == '>':
                    print(pref + "++ptr;", file=fout)
                if c == '<':
                    print(pref + "--ptr;", file=fout)
                if c == '.':
                    print(pref + "putchar(*ptr);", file=fout)
                if c == ',':
                    print(pref + "*ptr = getchar();", file=fout)

        print("}", file=fout)


def main() -> None:
    parser = argparse.ArgumentParser()
    parser.add_argument('source')
    parser.add_argument('-o', '--output', type=str)

    args = parser.parse_args()
    convert(args.source, args.output)


if __name__ == '__main__':
    main()
