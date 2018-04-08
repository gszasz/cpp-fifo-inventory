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
 * FIFO-inventory.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <iostream>
#include <fstream>
#include "transaction_buffer.hh"
using namespace std;

// Default constructor
TransactionBuffer::TransactionBuffer() { }

// Construct object from given string
TransactionBuffer::TransactionBuffer(const string& s) {
    buffer << s;
}

// Add transaction record to buffer via 'Transaction' structure
void TransactionBuffer::add(const Transaction& t) {
    buffer << t.item << t.type << " " << t.units << " @ " << t.price << " EUR" << endl;
}

// Add transaction record to buffer via arguments
void TransactionBuffer::add(const int& item, const char& type, const int& units, const int& price) {
    Transaction t;
    t.item = item;    // code of item
    t.type = type;    // transaction type ('B' = buy, 'S' = sell)
    t.units = units;  // number of units
    t.price = price;  // price per unit

    add(t);
}

// Get reference to buffer stream
stringstream& TransactionBuffer::getStream()  {
    return buffer;
}

// Read buffer from file
void TransactionBuffer::read(const string& filename) {
    ifstream inputFile(filename.c_str());
    string line;
    while(getline(inputFile, line))
        buffer << line << endl;
    inputFile.close();
}

// Write buffer to file
void TransactionBuffer::write(const string& filename) const {
    ofstream outputFile(filename.c_str());
    outputFile << buffer.str();
    outputFile.close();

}

// Clear buffer
void TransactionBuffer::clear() {
    buffer.clear();
}


// int main() {

//     TransactionBuffer inputBuf, outputBuf;
//     stringstream stream;

//     Transaction t[] = { { 1, 'B', 10, 15.6 },
//                         { 1, 'S', 11, 15.6 },
//                         { 2, 'B', 12, 15.6 } };

//     int n = sizeof t / sizeof t[0];

//     for(int i=0; i<n; i++)
//         outputBuf.add(t[i]);

//     outputBuf.add(3, 'S', 13, 15.8);

//     outputBuf.write("test.txt");

//     inputBuf.read("test.txt");

//     stringstream& ss = inputBuf.getStream();


//     int item;
//     char type;
//     int units;
//     float price;

//     char test[20];

//     string line;
//     while(getline(ss, line)) {
//         sscanf(line.c_str(), "%d%c %d @ %f EUR", &item, &type, &units, &price);
//         cout << item << type << " " << units << " @ " << price << " EUR" << endl;
//     }

//     return 0;
// }
