# compilers-2

There is a bug that causes an error to be thrown at line -1 char -1 if there is a space after an opening brace. If you delete the space, then the error is corrected. I didn't have time to track this down, unfortunately. It seems to be an error with my scanner.