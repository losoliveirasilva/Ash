## The Ash coding style guide

This is a short document describing coding style for the Ash project. Pull
requests that do not follow these, will not be accepted.

We recommend using the [editorconfig](http://editorconfig.org/) plugin on your
preferred editor.

### I. Indentation

* Indentation should be 4 characters long and use tab characters.

* Do NOT use spaces for indentation.

* In switch statements, 'case' labels should NOT be indented:
    ```
    switch (ch) {
    case 'a':
    case 'b':
        foo = bar;
        break;
    case 'c':
    case 'd':
        /* fall through */
    default:
        break;
    }
    ```

* Don't put multiple statements on a single line.

* Don't put multiple assignments on a single line either.

### II. Breaking Long Lines

* The limit on the length of lines is 80 columns.

### III. Placing Braces and Spaces

* For if-else, for, do-while, while, switch etc, place the opening brace on the
  same line.

    ```
    if (x is true) {
        /* code goes here. */
    } else {
        /* other code goes here. */
    }

    while (condition) {
        /* code goes here */
    }
    ```

* For functions, place the opening brace on the next line:

    ```
    int foo(void)
    {
        /* code goes here. */
    }
    ```

* Do not unnecessarily use braces where a single statement will do.

### IV. Spaces

* Use a space after these keywords: if, switch, case, for, do, while.

* Do not add spaces around (inside) parenthesized expressions.

* When declaring pointer data or a function that returns a pointer type, the
  use of `*` is adjacent to the type name, not the variable or function name.

* Use one space around (on each side of) most binary and ternary operators,
  such as any of these:

    `=  +  -  <  >  *  /  %  |  &  ^  <=  >=  ==  !=  ?  :`

  But no space after unary operators:

    `&  *  +  -  ~  !  sizeof`

  No space after/before the postfix increment & decrement unary operators:

    `++  --`

### V. Variables and Naming

* Do not use mixed-cases to name your variables.

* Do not encode the type of a function into the name.

* Do not use typedef's, unless you want to cast an opaque pointer.

* Declare variables as late as possible.

* Variables names should not be related to its type, but to its use.

### VI. Commenting

* Use /* c89 */ comments in all situations.
