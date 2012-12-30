nou-tuple4
==========

A experimental expression parser.

## Expression Grammer

The grammar used in this parser is a classical expression grammer, as is shown below:

  E := E a T | T
  T := T b F | T
  F := i | (E)

The non-terminal character is E, T, F while others are terminal characters. The 'a' here is one of '+' or '-' and b is one of '*' or '/'. The 'i' here is the integer(no float point number).

## Parser Type

The project implements three classical kind of parser: top-down parser(recursive method and LL(1)) and bottom-up parser(SLR(1)).

All the parser classes are named with ExpBuilder and they are all sub-classes of ExpBuilder.
