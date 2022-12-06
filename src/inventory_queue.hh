/*
 * inventory_queue.hh -- 'InventoryQueue' class header file.
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

#ifndef INVENTORY_QUEUE_HH
#define INVENTORY_QUEUE_HH

// Declaration of a single batch of inventory units
struct Batch {
    int units;    // number of units
    float price;  // price per unit
};

// Declaration of a single node used to construct linked list.  The list
// represents the FIFO unbounded queue of individual data entries.  The oldest
// entry is located at the front, while the newly added one comes to the rear.
struct Node {
    Batch data;  // data structure
    Node* next;  // pointer to the next node
};

// Abstract implementation of a FIFO unbounded queue using linked list of nodes.
class InventoryQueue {

private:
    Node* mHead;  // pointer to the front element of the list
    Node* mTail;  // pointer to the rear element of the list

public:
    InventoryQueue();                         // default constructor
    InventoryQueue(const InventoryQueue& q);  // copy constructor
    ~InventoryQueue();                        // explicit destructor

    void push(Batch data);  // append new node to the back
    void pop();             // remove node at the front

    // construct new Batch structure and append node to the back
    void emplace(int units, float price);

    Batch& front();  // return reference to the data of the head node
    Batch& back();   // return reference to the date of the tail node

    int size() const;     // return number of nodes in the queue
    bool empty() const;   // test whether the queue is empty

    // helper function for making a deep copy of the list
    void copyList(Node* head, Node*& cloneHead, Node*& cloneTail);
    void printList() const;
};

#endif  // INVENTORY_QUEUE_HH
