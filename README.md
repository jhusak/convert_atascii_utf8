# convert_atascii_utf8

Toolset to convert ATASCII files with negative characters (as in Action!, where they do as comment) to/from UTF8 for editing with favourite text editor.

However, inversed chars cannot be entered from keyboard, only from char picker.

In addition a special font:

    TrueType/EightBit Atari-Standard.ttf

is needed (and installed in the system) from repository:

    https://github.com/a8bit/EightBit-Atari-Fonts/

(for convinience placed here)

## Tools
### convertatasciitoutf8

Usage: convertatasciitoutf8 [-7] <atasciifilein> <utf8fileout>

converts ATASCII files to UTF-8 encoded files, that look the same as on Atari 8-bit. Optional 7 bit mode (-7 option) strips eight bit, making inverse characters not inversed. The files can be edited then, and then backconverted with tool:

### convertutf8toatascii

Usage: convertutf8toatascii <utf8filein> <atasciifileout>

which converts UTF-8 files with inverse characters encoded - back to plain ATASCII 8-bit files. If eight bit was not stripped, this operation is reversible to previous.

### change inverse filter
The chinv command changes inverse of ATASCII characters, when inversed characters are stored as unicode codes, and converting plain <128 characters to unicode inversed.

You may use it in vim as a block text filter, for example:

- first select text to be changed and then press
- shift-: and append !chinv, then press enter.

Under the hood it changes all characters from stdin, and when <128 (but 0xa) it outputs them to stdout as unicode inversed, and when in unicode inversed form - outputs  back to plain
ascii uninversed.
Special font EightBit Atari-Standard.ttf must be used to properly display inversed ATASCII characters.

please use those tools as you wish :)

Jakub Husak (11.2023), Poland.
# Building

type

    make
    
(make tool and C compiler needed)

and copy them somewhere where the PATH can look into.

# Example:

![](/example_view.png)
