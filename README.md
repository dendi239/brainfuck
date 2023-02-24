# Brainfuck

This is source of my brainfuck interpreter and debugger combined.
The brainfuck itself is pretty straightforward, so this implementation contains certain optimizations on top of it.

## Quickstart

Project is built with bazel, target you need is `//brainfuck:brainfuck`.
There's debugger at `//brainfuck:debugger`.

```sh
bazel run //brainfuck:brainfuck
```

## Why?

Out of nowhere I decided to solve some competitive programming problem in brainfuck.
I spent several hours to develop solution for it and struggled to figure out if something wrong with implementation I used or it's me.
Once I found the one and finished developing code for initial problem, I ran into TL.
I decided to try and fix this by improving interpreter itself, so this project was born.
However, once I completed a few parts of it, it came to my attention that I still had some bugs in code which led to TL verdict.

### Problem

The original problem is following: there're multiple strings (`t < 1000`) and you're to decide if they're _appropriate_.
A string called appropriate if it doesn't have either `V` or `Z`.
For each test case you need to print `YES` or `NO`.

At first glance, it's quite easy problem, however things become complicated once you try solve it in brainfuck.
Here're some aspects:
- You can't store number of tests in a single memory cell, so you need to perform two-registers arifmetics on your own.
- Every time you need to output string, you're likely to put cycle just to advance by 89 because you don't want to put 89 `+`-es in a row.
- You need to tell if string's completed and you need to move on the next one.
- You need to perform `and`/`or` of two cells.

## Optimizations

There're several primitive optimizations (like compressing multiple additions into a single one) and one rather advanced.
I call it **short cycle elimination** which runs short plain cycles only once.

### Rationale

All of aspects mentioned in the previous paragraph do a lot with adding/removing some ascii codes of certain letters and comparing it to zero.
And "simple" adding/removing ascii code is usually nested cycle of depths of two because of my lazyness.

### Formal definition

Short cycle elimination works with cycles under following conditions:
- it's not a nested cycle;
- it doesn't do any I/O inside it;
- it doesn't move counter address.

Under these conditions cycle will change only impacted cells by amount which is multiplication of expected cycle runs and changes performed by a single cycle run.
Note that in a runtime no shifts will actually will be performed.

## Implementation

The implementation has three different concepts: `Memory`, `Program` and `IO`.
Which of these classes have version for debugging (and dumping information to the user).
Current implementation simply uses inheritance, however one can speed virtual calls up with CRTP, however it's not an issue right now.

## Credits

Made with :heart: by Denys Smirnov.
