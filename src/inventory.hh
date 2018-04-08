/*
 * inventory.hh -- 'Inventory' class header file.
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

#ifndef INVENTORY_HH
#define INVENTORY_HH

#include "inventory_queue.hh"     // required for InventoryQueue
#include "transaction_buffer.hh"  // required for TransactionBuffer

class Inventory {
private:
    InventoryQueue queue[];
    int totalUnits[];
    TransactionBuffer log;

public:
    enum { MAX_ITEMS = 3 };                     // class constants

    Inventory();                                // default constructor

    // buy a batch of units
    void buy(const int& item, int units, const int& price);

    // sell given number number of units
    int sell(const int& item, int units, const int& price);

    void execute(TransactionBuffer& backlog);   // execute set of transactions

    // write transaction log to file
    void dumpLog(const std::string& filename) const;

    void printStats() const;                    // print statistics
    void printItem(const int& item) const;      // print item's inventory
};

#endif  // INVENTORY_HH
