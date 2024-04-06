# compilers-2
Link to GitHib: https://github.com/jtfox142/compilers-2

This program simulates a parser. It tests tokens fetched from the scanner against grammatical rules of a made up HLL. If the rules are satisfied, then a parse tree is returned to main and printed to screen. If it fails, then an error is thrown directing the user's attention to (hopefully) the appropriate line and character number of the offending input.

There is a bug that causes an error to be thrown at line -1 char -1 if there is a space after an opening brace. If you delete the space, then the error is corrected and it parses everything else as expected. I didn't have time to track this down, unfortunately. It seems to be an error with my scanner.

The error messages are not as descriptive as I would like to be, but they work well enough most of the time. Any error involving an opening brace will not show the correct line number, however. Similar to the bug mentioned above, the complete absence of an expected opening brace will produce an error at line -1 char -1. To my knowledge, this type of bug only happens with braces.

The program can be compiled using the included makefile by typing "make".

It can be run by typing "./p2 [yourFileHere]". Example: "./p2 test.txt".