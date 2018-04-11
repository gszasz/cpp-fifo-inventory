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

#include <iostream>  // required for 'cout' and <<
#include <iomanip>   // required for 'fixed' and 'setprecision'
#include <cstdio>    // required for 'sscanf'
#include "inventory.hh"

using namespace std;

// Default constructor
Inventory::Inventory() {
    for (int i = 0; i < inventory::MAX_ITEMS; i++)
        mTotalUnits[i] = 0;
}

// Buy batch of units
bool Inventory::buy(int item, int units, float cost) {
    if (item > inventory::MAX_ITEMS) {
        cout << item << ": item out of range." << endl;
        return false;
    }
    else if (units <= 0) {
        cout << units << ": invalid number of units" << endl;
        return false;
    }
    mTotalUnits[item-1] += units;
    mQueue[item-1].emplace(units, cost);

    mLog.add(item, 'B', units, cost);
    return true;
}

// Sell units from the inventory
float Inventory::sell(int item, int units, float price) {
    if (item > inventory::MAX_ITEMS) {
        cout << item << ": item out of range." << endl;
        return -1;
    }
    else if (units > mTotalUnits[item-1]) {
        cout << units << ": not enough units in the inventory (units available: " << mTotalUnits[item-1] << ")" << endl;
        return -1;
    }
    else if (units <= 0) {
        cout << units << ": invalid number of units" << endl;
        return -1;
    }
    mTotalUnits[item-1] -= units;
    float cogs = 0;
    int remainingUnits = units;
    // mQueue[item-1].front() returns reference to Batch.  Since the reference in
    // C++ cannot be changed once assigned to variable, we need convert it to
    // pointer here, otherwise batch could not be reassigned during iterations.
    Batch* batch = &(mQueue[item-1].front());
    while (remainingUnits >= batch->units) {
        cogs += batch->units * batch->price;
        remainingUnits -= batch->units;
        mQueue[item-1].pop();
        batch = &(mQueue[item-1].front());
    }
    if (remainingUnits > 0) {
        cogs += remainingUnits * batch->price;
        batch->units -= remainingUnits;
    }
    mLog.add(item, 'S', units, price);
    return cogs;
}

// Execute set of transactions from the transaction backlog
void Inventory::execute(TransactionBuffer& backlog) {
    stringstream& backlogStream = backlog.getStream();
    string line;
    while (getline(backlogStream, line)) {
        Transaction t;
        sscanf(line.c_str(), "%d%c %d %f", &t.item, &t.type, &t.units, &t.price);
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
    mLog.write(filename);
}

// Print statistics
void Inventory::printStats() const {
    for (int i = 0; i < inventory::MAX_ITEMS; i++) {
        InventoryQueue q(mQueue[i]);

        cout << endl << "Item " << i + 1 << ":" << endl << endl;
        float sum = 0;
        while (!q.empty()) {
            Batch b = q.front();
            sum += b.units * b.price;
            cout << "\t" << b.units << "\t@\t" << fixed << setprecision(2) << b.price << " EUR" << endl;
            q.pop();
        }
        cout << "\t" << "------------------------------" << endl;
        cout << "\t" << "Total cost\t" << fixed << setprecision(2) << sum << " EUR" << endl;
    }
}

// Print item's inventory
void Inventory::printItem(int i) const {
    if (i > inventory::MAX_ITEMS) {
        cout << i << ": item out of range." << endl;
        return;
    }
    else if (mQueue[i-1].empty()) {
        cout << i << ": inventory is empty" << endl;
        return;
    }
    InventoryQueue q(mQueue[i-1]);
    while (!q.empty()) {
        Batch b = q.front();
        cout << b.units << "\t@\t" << fixed << setprecision(2) << b.price << " EUR" << endl;
        q.pop();
    }
}
