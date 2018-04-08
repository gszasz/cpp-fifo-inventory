/*
 * inventory.cc -- 'Inventory' class implementation.
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
#include <cstdio>
#include "inventory.hh"
using namespace std;

// Default constructor
Inventory::Inventory() {
    InventoryQueue queue[MAX_ITEMS];
    int totalUnits[MAX_ITEMS];
    for (int i = 0; i < MAX_ITEMS; i++)
        totalUnits[i] = 0;
    TransactionBuffer log;
}

// Buy batch of units
void Inventory::buy(const int& item, int units, const int& price) {
    if (units == 0)
        cout << "warning: zero units in transaction" << endl;
    queue[item-1].emplace(units, price);
    totalUnits[item-1] += units;
    log.add(item, 'B', units, price);
}

// Sell units from the inventory
int Inventory::sell(const int& item, int units, const int& price) {
    if (units < totalUnits[item-1]) {
        cout << endl << "Transaction failed: not enough units in the inventory";
        return -1;
    }
    else if (units == 0) {
        cout << "warning: zero units in transaction" << endl;
        return 0;
    }
    totalUnits[item-1] -= units;
    Batch batch = queue[item-1].front();
    int cogs = 0;
    while (units >= batch.units) {
        cogs += batch.units * batch.price;
        units -= batch.units;
        queue[item-1].pop();
        batch = queue[item-1].front();
    }
    cogs += units * batch.price;
    batch.units -= units;

    log.add(item, 'S', units, price);
    return cogs;
}

// Execute set of transactions from the transaction backlog
void Inventory::execute(TransactionBuffer& backlog) {
    stringstream& backlogStream = backlog.getStream();
    string line;
    while(getline(backlogStream, line)) {
        Transaction t;
        sscanf(line.c_str(), "%d%c %d @ %f EUR", &t.item, &t.type, &t.units, &t.price);
        switch(t.type) {
        case 'B':
            buy(t.item, t.units, t.price);
            break;
        case 'S':
            sell(t.item, t.units, t.price);
            break;
        default:
            cout << line << ": invalid transaction" << endl;
            break;
        }
    }
}

// Write transaction log to file
void Inventory::dumpLog(const string& filename) const {
    log.write(filename);
}

// Print statistics
void Inventory::printStats() const {
    for (int i = 0; i < MAX_ITEMS; i++) {
        InventoryQueue q(queue[i]);

        cout << "Item " << i + 1 << ":" << endl;
        int sum = 0;
        while (!q.empty()) {
            Batch b = q.front();
            sum += b.units * b.price;
            cout << "\t" << b.units << "\t@\t" << b.price << endl;
            q.pop();
        }
        cout << "\t" << "---------------------------------" << endl;
        cout << "\t" << "Sum\t\t" << sum << endl;
    }
}

// Print item's inventory
void Inventory::printItem(const int& i) const {
    InventoryQueue q(queue[i-1]);
    while (!q.empty()) {
        Batch b = q.front();
        cout << b.units << "\t@\t" << b.price << endl;
        q.pop();
    }
}
