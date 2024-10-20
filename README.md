# Synopsys Liberty Parser

Please, refer to COPYING.pdf for the license.

## Compilation Instructions

Ensure that `cmake` and `make` are installed. Then run:

```
rm -rf build
mkdir build
cd build
cmake ..
make -j8
```

The binary will be located at `build/parse_liberty`.

## Copyright

Copyright (c) 1996-2005 Synopsys, Inc.    ALL RIGHTS RESERVED


This package is contains various tools for working with
liberty, a standard developed by Synopsys for describing cell libraries. 

## Dependencies

To build this package, you will need, as a minimum, the following
utilities. They may be substituted with local favorites, hopefully
with little tweaking of the makefiles or code:

- bison  version 1.875  (1.22 will not work; 1.28 does)  and up. Earlier versions than
       1.875 will work fine, except syntax errors generate slightly different messages,
       which cause some regression tests to fail.
- flex   version 2.5.2 and up.
- gperf  version 3.0    (2.5 will not work-- some OK .lib files will not pass check)
- gcc    version 2.8.1, egcs 2.91.60, 2.95.2, or above

Optionally useful, perhaps required:

- GNU make   version 3.79.1  and up... ** non-gnu makes probably won't work! **
- diffutils  version 2.7  if your system can't handle "diff -q ..."
- sh-utils   version 2.0  if your echo can't handle the -n option...
- libtool    version 1.4.2 ;; most users will not need need this unless
                            seriously wanting to change things in 
                            developer mode.

You can pick up GNU software from:

(an up-to-date listing of ftp sites is at:
	http://www.gnu.org/order/ftp.html )

- gatekeeper.dec.com/pub/GNU
- ftp.keystealth.org/pub/gnu
- ftp.itcentrx.com/pub/gnu
- uiarchive.cso.uiuc.edu/pub/ftp/ftp.gnu.org/gnu
- ftp.cs.columbia.edu/archives/gnu/prep



Other versions may be used, both older or newer. The above versions 
"work"; others may or may not "work".



NEW--NEW--NEW--NEW--NEW--NEW--NEW--NEW--NEW--NEW--NEW--NEW--NEW--NEW--NEW--NEW

A good forum for discussions about liberty and Physical Liberty (plib) is at:

http://synopsys.infopop.net/OpenTopic

Bugs and enhancement requests and pleas for aid can be posted there, as well as late-breaking news.

NEW--NEW--NEW--NEW--NEW--NEW--NEW--NEW--NEW--NEW--NEW--NEW--NEW--NEW--NEW--NEW

Included in this distribution are the files PI.c and si2dr_liberty.h, an
implementation of a procedural interface modeled after the SI2DR
interface (see www.si2.org or www.edaopen.org). This PI is the
foundation of this toolkit, and provides the capability of building,
traversing, reading, writing, and modifying liberty data. It presents
64 functions (to date).

The excutable, syntax_parse, will read the Synopsys supplied files in
the desc directory, and generate a series files that will be compiled and
linked into the program liberty_parse.

The executable, liberty_parse, will read a liberty file, and then
perform a set of syntax/semantic checks on the data.

Using the including PI, other applications can be swiftly built around
the liberty file standard.

The main goal of this project was to make the code ridiculously simple
to maintain; it's all written in C as simply and straightforwardly as
I could manage, and uses no runtime interfaces beyond the command line.

The syntax is very simple: You have groups, attributes (attrs), and
define statements. Attrs can be complex or simple. Groups can have
several names. The parser could not care less about group names, attr
names, or types. The Checking routine will report all unrecognized
group names and attr names to make sure they are allowed within the
context of the technology and timing models declared.

The reason for this kind of seperation of the syntax from the
semantics was so that future enhancements and upgrades should be very
easy to implement in this toolkit as liberty grows and matures.

The syntax/semantic checking is built on a foundation of syntax
description files that are provided by Synopsys. I have placed a set
of these in the desc directory. If extensions or changes are mode to
liberty, these files can be updated, and the parser regenerated with
"make".

From these syntax description files, a series of automatic checks can
be made. The rest of the checks are hand coded. Not all possible
checks have been coded to date. It is hoped that the user community
will help by contributing to this effort.

### Syntax/semantic checks

#### Automatic checks

Using the files in desc/, these checks are performed:

1. Group names are correct.

2. The number of names included in the
   parenthesis are correct (some groups do not allow a name, others have
   a single name, others have an optional name, others have one or more
   names, etc.)

3. Group ownership is checked. Not every group may contain a certain group.

4. attribute ownership is checked. Each group is allowed to contain a
   specific subset of the attributes.  

5. Attribute types (simple vs complex) are checked.  

6. Attribute value types are checked (string vs. float vs. boolean
   vs. int, etc).  

7. Attribute value ranges (where specified) are checked.  

8. name space (ie. scoping) rules are checked. It is illegal to
   declare two similar group types with the same name.  Some group
   names are really references; these have to be excluded from this
   check by hand, as the distinction is not made in the syntax descriptions. 

#### Hand-coded checks

1. table checks: the index, value specs in timing groups vs. templates are made. 
   The code will indicate if the wrong number of entries are present.

2. It will verify that "members", if present, is the first entry.

3. if both "clear" and "preset" attrs are given, it will check for
   "clear_preset_var1" and/or "clear_preset_var2".

4. pin/bus direction compatibility is checked.

5. pin&bus driver_types are checked to make sure they are compatible
   with each other and with pin direction.

6. timing subgroups are checked for compatibility.

7. the delay_model and technology are checked to insure that the
   delay_model is specified first.

8. each bus must have a "bus_type" attribute, that references
   an existing "type".

9. The index_xxx attributes must not have any negative numbers, or
   an error is given.


### Regression tests

Simple, small regression tests exist in the test/ subdirectory. The
script, "runtests" is provided to run them. Each of the previously
mentioned checks should be checked at least once by the regression
tests, both for success and failure. They are very useful in
demonstrating weaknesses in the code, and keeping old bugs from being
resurrected.

### Files:

Here is a list of files (with some description) that come with the distribution:

- PI.c                    - main file for the si2dr_liberty interface
- libhash.c               - hashing functions used all over the place
- libstrtab.c             - a string table implementation that uses libhash.
- main.c                  - the main func for liberty_parse
- mymalloc.c              - malloc front ends for error checking
- syntax_checks.c         - the semantic checks are almost all in this file
- syntform.c              - functions to generate code from the syntax description files
- liberty_parser.y        - yacc source for the liberty parser
- syntax_parser.y         - yacc source for the desc files code generator
- synttok.l               - lex source for the desc files code generator
- token.l                 - lex source for the liberty parser
- liberty_structs.h       - structures used in PI.c
- libhash.h               - definitions for the hash package
- libstrtab.h             - definitions for a string table implementation built on libhash.
- mymalloc.h              - definitions for the malloc front end
- si2dr_liberty.h         - The Official .h for the si2dr_liberty interface
- syntax.h                - definitions used in the desc files code generator
- desc/                   - this directory holds syntax description files for different techs.
- desc/syntax.cmos.desc
- desc/syntax.fpga.desc
- AUTHORS                 - a list of contributors
- COPYING.pdf             - the SYNOPSYS Open Source License Version 1.0
- ChangeLog               - a list of changes made to files
- INSTALL                 - installation instructions.
- Makefile.am             - used to build makefiles
- Makefile.in             - used to build makefiles
- NEWS                    - news about the state of the program
- README                  - useful for learning many things
- acinclude.m4            - used to make makefiles, configure scripts, etc
- aclocal.m4              - used to make makefiles, configure scripts, etc
- bnf
- configure.in            - used to make the configure script
- config.sub              - used in the configure process
- config.guess            - used in the configure process
- configure               - run this to configure and generate makefiles
- install-sh              - used in the install process
- ltconfig                - used in the configure process -- in version 1.4 & up, this is no longer necc.
- ltmain.sh               - used in the configure process
- missing                 - needed to build makefiles
- mkinstalldirs           - used in the install process
- si2dr_liberty-PI.txt    - documentation for the si2dr_liberty interface
- test/                   - this directory hold the regression tests
- test/runtests           - the script to run all the tests (also, make check)
- ylwrap                  - a wrapper to call yacc/lex/bison/flex


