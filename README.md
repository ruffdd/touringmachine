# TouringMaschiene

This Program Simulates a Touring Machine

## Compile and Run
You can just download or clone this repo to your locale machine.
```bash
git clone https://github.com/ruffdd/touringmachine.git
```
Then go into the root folder and execute the makefile.
```bash
make
```
the execute able is in the bin folder, that gets created and can be run by:
```bash
bin/touring $path_to_a_tm_file_to_run
```
## .tm files
A tm file ends with .tm and contains the "code" for a concrete toruingmachine.

Syntax:
```bash
start:"start state"
empthy:"empty symbol"
end:"end state"

"old state"    "old char"     "new state"  "new char"   "next direction"
```
- Space and tabs are equal, also the number of spaces/tabs is unimportend.
- Leading and traling whitespaces, will be ignored.
- Only Ascii is supported 