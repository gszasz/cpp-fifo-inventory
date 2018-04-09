/*
 * main.cc -- Main program of the FIFO-inventory.
 *
 * Copyright (C) 2018  Gabriel Szasz <gabriel.szasz1@gmail.com>
 *
 * This file is part of FIFO-inventory
 *
 * FIFO-inventory is free software: you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the Free
 * Software Foundation, either version 3 of the License, or (at your option) any
 * later version.
 *
 * FIFO-inventory is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
 * FOR A PARTICULAR PURPOSE.  See the GNU General Public License for more
 * details.
 *
 * You should have received a copy of the GNU General Public License along with
 * FIFO-inventory.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <iostream>  // required for 'cout', 'cin', << and >>
#include <iomanip>   // required for 'fixed' and 'setprecision'
#include <string>    // required for 'string'
#include "inventory.hh"

using namespace std;

// Interactive dialog showing list of inventory for the given item
void list_inventory_dialog(Inventory& i) {
    int item = 1;  // item

    cout << "Item: ";
    cin >> item;

    i.printItem(item);
}

// Interactive dialog for buying an inventory item
void purchase_dialog(Inventory& i) {
    int item = 1;       // item
    int units = 0;      // number of units
    float cost = 0.0;   // cost per unit

    cout << "Item: ";
    cin >> item;
    cout << "Number of units: ";
    cin >> units;
    cout << "Price per unit: ";
    cin >> price;
    cout << endl;

    i.buy(item, units, price);
}

// Interactive dialog for selling an inventory item
void sale_dialog(Inventory& i) {
    int item = 1;       // item
    int units = 0;      // number of units
    float price = 0.0;  // price per unit

    cout << "Item: ";
    cin >> item;
    cout << "Number of units: ";
    cin >> units;
    cout << "Price per unit: ";
    cin >> price;
    cout << endl;

    i.sell(item, units, price);
}

// Main program
int main(int argc, char **argv) {

    const string WELCOME =
        "\nWelcome to FIFO-inventory.\n"
        "An example of building-up a FIFO inventory implementation in C++ created\n"
        "for educational purposes.\n\n"
        "Copyright (C) 2018  Gabriel Szasz\n"
        "This program comes with ABSOLUTELY NO WARRANTY; for details type 'd'.\n"
        "This is free software, and you are welcome to redistribute it under\n"
        "certain conditions; type `c' for details.";

    const string HELP =
        "\nHelp:\n\n"
        "  Introspect queues\n"
        "   i    list inventory for the item\n"
        "   p    print statistics of all items\n\n"
        "  Queue operations\n"
        "   b    'buy' specified amount of units of the selected item\n"
        "   s    'sell' specified amount of units of the selected item\n\n"
        "  Load & Save\n"
        "   r    read inventory from file ('inventory.txt')\n"
        "   w    write inventory to file ('inventory.txt')\n\n"
        "  Exiting\n"
        "   q    quit program\n\n"
        "  License\n"
        "   d   show warranty disclaimer\n"
        "   c   show copyright information";

    const string WARRANTY_DISCLAIMER =
        "\nTHERE IS NO WARRANTY FOR THE PROGRAM, TO THE EXTENT PERMITTED BY\n"
        "APPLICABLE LAW.  EXCEPT WHEN OTHERWISE STATED IN WRITING THE COPYRIGHT\n"
        "HOLDERS AND/OR OTHER PARTIES PROVIDE THE PROGRAM \"AS IS\" WITHOUT\n"
        "WARRANTY OF ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING, BUT NOT\n"
        "LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A\n"
        "PARTICULAR PURPOSE.  THE ENTIRE RISK AS TO THE QUALITY AND PERFORMANCE\n"
        "OF THE PROGRAM IS WITH YOU.  SHOULD THE PROGRAM PROVE DEFECTIVE, YOU\n"
        "ASSUME THE COST OF ALL NECESSARY SERVICING, REPAIR OR CORRECTION.\n";

    const string COPYRIGHT_INFO =
        "\nFIFO-inventory -- An example FIFO inventory implementation in C++.\n\n"
        "Copyright (C) 2018  Gabriel Szasz\n\n"
        "FIFO-inventory is free software: you can redistribute it and/or modify\n"
        "it under the terms of the GNU General Public License as published by the\n"
        "Free Software Foundation, either version 3 of the License, or (at your\n"
        "option) any later version.\n\n"
        "FIFO-inventory is distributed in the hope that it will be useful, but\n"
        "WITHOUT ANY WARRANTY; without even the implied warranty of\n"
        "MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU\n"
        "General Public License for more details.\n\n"
        "You should have received a copy of the GNU General Public License along\n"
        "with FIFO-inventory.  If not, see <https://www.gnu.org/licenses/>.";

    const string PROMPT = "\n\nCommand (h for help): ";

    Inventory inventory;
    TransactionBuffer backlog;

    char command;

    cout << WELCOME;

    do {
        cout << PROMPT;
        cin >> command;

        switch (command) {
        case 'i':  // list inventory for the item
            list_inventory_dialog(inventory);
            break;
        case 'p':  // print statistics of all items
            inventory.printStats();
            break;
        case 'b':  // 'buy' specified amount of units of the selected item
            purchase_dialog(inventory);
            break;
        case 's':  // 'sell' specified amount of units of the selected item
            sale_dialog(inventory);
            break;
        case 'r':  // read inventory from file ('inventory.txt')
            backlog.read("inventory.txt");
            inventory.execute(backlog);
            backlog.clear();
            break;
        case 'w':  // write inventory to file ('inventory.txt')
            inventory.dumpLog("inventory.txt");
            break;
        case 'q':  // quit program
            break;
        case 'd':  // show warranty disclaimer
            cout << WARRANTY_DISCLAIMER;
            break;
        case 'c':  // show copyright info
            cout << COPYRIGHT_INFO;
            break;
        case 'h':  // show help
            cout << HELP;
            break;
        default:
            cout << command << ": unknown command";
            break;
        }

    } while (command != 'q');

    cout << endl;
    return 0;
}
