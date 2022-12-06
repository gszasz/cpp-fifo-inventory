# FIFO-inventory

An example of a FIFO inventory management system implementation in C++.  Since
the code serves purely for educational purposes, it deliberately omits templates
and inheritance.  See [documentation](docs/README.md) for more details.

## Installation

### Linux

```bash
$ make
# make install

```

## Usage

The program does not provide any command line options.  It runs only
interactively.

```
$ fifo-inventory

Welcome to FIFO-inventory.
An example of building-up a FIFO inventory implementation in C++ created
for educational purposes.

Copyright (C) 2018  Gabriel Szasz
This program comes with ABSOLUTELY NO WARRANTY; for details type 'd'.
This is free software, and you are welcome to redistribute it under
certain conditions; type `c' for details.


Command (h for help): h

Help:

  Introspect queues
   i    list inventory for the item
   p    print statistics of all items

  Queue operations
   b    'buy' specified amount of units of the selected item
   s    'sell' specified amount of units of the selected item

  Load & Save
   r    read inventory from file ('inventory.txt')
   w    write inventory to file ('inventory.txt')

  Exiting
   q    quit program

  License info
   d    show warranty disclaimer
   c    show copyright information


Command (h for help):
```


## License

FIFO-inventory -- An example FIFO inventory management system implementation.

Copyright (C) 2018  Gabriel Szasz <gabriel.szasz1@gmail.com>

This program is free software: you can redistribute it and/or modify it under
the terms of the GNU General Public License as published by the Free Software
Foundation, either version 3 of the License, or (at your option) any later
version.

This program is distributed in the hopet hat it will be useful, but WITHOUT ANY
WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A
PARTICULAR PURPOSE. See the GNU General Public License for more details.

You should have received a copy of the GNU General Public License along with
this program. If not, see <https://www.gnu.org/licenses/>.
