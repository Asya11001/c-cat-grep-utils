# S21 Cat Utility

## Overview
The S21 Cat Utility is a command-line tool inspired by the Unix `cat` utility. It reads one or more files and concatenates them to standard output, optionally numbering the output lines.

## Features
- **File Concatenation**: Concatenate the contents of one or more files and write them to standard output.
- **Line Numbering**: Optionally number the output lines.
- **Special Characters Display**: Optionally display non-printable characters using caret notation.
- **Tab and End-of-Line Marking**: Optionally display tab characters and end-of-line characters using special symbols.

## Usage
To use the S21 Cat Utility, follow the syntax:
```
s21_cat [OPTIONS] [FILE...]
```
Where:
- `OPTIONS` are optional command-line flags to customize the output format.
- `FILE...` are optional file paths to concatenate. If not provided, the utility reads from standard input.

## Command-line Options
- `-b, --number-nonblank`: Number non-blank output lines.
- `-n, --number`: Number all output lines.
- `-s, --squeeze-blank`: Suppress repeated empty output lines.
- `-e, --show-ends`: Display a `$` symbol at the end of each line.
- `-t, --show-tabs`: Display tab characters using caret notation.
- `-v, --show-nonprinting`: Display non-printable characters using caret notation.

## Example
![Build and usage](dvi/s21-cat-overview.gif)

---

Please provide the GIF files for the build and usage, and I can incorporate them into the markdown file.

# S21 Grep Utility

## Overview
The S21 Grep Utility is a command-line tool inspired by the Unix `grep` utility. It allows users to search for patterns within text files and perform various operations based on the matching lines.

## Features
- **Pattern Matching**: Search for patterns within text files.
- **Flexible Options**: Support for various command-line options to customize search behavior.
- **Multiple Patterns**: Search for multiple patterns simultaneously.
- **Regular Expressions**: Support for regular expressions for advanced pattern matching.
- **Output Control**: Control the output format and verbosity.
- **File Handling**: Process multiple files and directories recursively.

## Usage
To use the S21 Grep Utility, follow the syntax:
```
s21_grep [OPTIONS] PATTERN [FILE...]
```
Where:
- `OPTIONS` are optional command-line flags to customize the search behavior.
- `PATTERN` is the pattern to search for within the specified files.
- `FILE...` are optional file paths to search within. If not provided, the utility reads from standard input.

## Command-line Options
- `-e, --pattern=PATTERN`: Specify the pattern to search for.
- `-i, --ignore-case`: Perform case-insensitive matching.
- `-v, --invert-match`: Invert the match, i.e., select non-matching lines.
- `-c, --count`: Print only a count of matching lines.
- `-l, --files-with-matches`: Print only the names of files containing matches.
- `-n, --line-number`: Print line numbers with output lines.
- `-h, --no-filename`: Suppress the prefixing of filenames on output.
- `-s, --no-messages`: Suppress error messages about nonexistent or unreadable files.
- `-f, --file=PATTERN_FILE`: Read one or more newline-separated patterns from a file.
- `-o, --only-matching`: Print only the matched (non-empty) parts of matching lines.

## Example
To search for the pattern "error" in the file `log.txt`:
```
s21_grep error log.txt
```

For more advanced usage, search for multiple patterns ignoring case, printing line numbers, and only displaying matching parts of lines:
```
s21_grep -i -n -o -e "error" -e "warning" log.txt
```

---

Please provide the GIF files for the build and usage, and I can incorporate them into the markdown file.