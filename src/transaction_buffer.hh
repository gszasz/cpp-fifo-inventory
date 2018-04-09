/*
 * transaction_buffer.hh -- 'TransactionBuffer' class header file.
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

#ifndef TRANSACTION_BUFFER_HH
#define TRANSACTION_BUFFER_HH

#include <sstream>  // required for 'std::stringstream'
#include <string>   // required for 'std::string'

// decraration of a structure holiding single transaction entry
struct Transaction {
    int item;     // code of item
    char type;    // transaction type ('B' = buy, 'S' = sell)
    int units;    // number of units
    float price;  // price per unit
};

class TransactionBuffer {
private:
    std::stringstream buffer;  // internal string stream buffer

public:
    TransactionBuffer();                      // default constructor
    TransactionBuffer(const std::string& s);  // constructor from given string

    void add(const Transaction& t);  // add transaction record to buffer
    void add(const int& item, const char& type, const int& units, const float& price);

    std::stringstream& getStream();  // get reference to buffer stream

    void read(const std::string& filename);         // read buffer from file
    void write(const std::string& filename) const;  // write buffer to file

    void clear();  // clear buffer
};

#endif  // TRANSACTION_BUFFER_HH
