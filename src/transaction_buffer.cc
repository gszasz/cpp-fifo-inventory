/*
 * transaction_buffer.cc -- 'TransactionBuffer' class implementation.
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
 * FIFO-inventory.  If not, see <https://www.gnu.org/licenses/>.
 */

#include <iostream>  // required for <<
#include <iomanip>   // required for 'fixed' and 'setprecision'
#include <fstream>   // required for 'ifstream' and 'ofstream'
#include "transaction_buffer.hh"

using namespace std;

// Default constructor
TransactionBuffer::TransactionBuffer() {
    // To keep default constructor accessible while having also defined a
    // parameterized constructor, it is necessary to explicitly define an empty
    // argumentless constructor.
}

// Construct object from given string
TransactionBuffer::TransactionBuffer(const string& s) {
    mBuffer << s;
}

// Add transaction record to buffer via 'Transaction' structure
void TransactionBuffer::add(Transaction t) {
    mBuffer << t.item << t.type << " " << t.units << " " << fixed << setprecision(2) << t.price << endl;
}

// Add transaction record to buffer via arguments
void TransactionBuffer::add(int item, char type, int units, float price) {
    Transaction t;
    t.item = item;    // code of item
    t.type = type;    // transaction type ('B' = buy, 'S' = sell)
    t.units = units;  // number of units
    t.price = price;  // price per unit

    add(t);  // call add(const Transaction& t) member function
}

// Get reference to buffer stream
stringstream& TransactionBuffer::getStream()  {
    return mBuffer;
}

// Read buffer from file
void TransactionBuffer::read(const string& filename) {
    ifstream inputFile(filename.c_str());
    string line;
    while (getline(inputFile, line))
        mBuffer << line << endl;
    inputFile.close();
}

// Write buffer to file
void TransactionBuffer::write(const string& filename) const {
    ofstream outputFile(filename.c_str());
    outputFile << mBuffer.str();
    outputFile.close();
}

// Clear buffer
void TransactionBuffer::clear() {
    mBuffer.str("");
    mBuffer.clear();
}
