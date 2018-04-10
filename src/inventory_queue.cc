/*
 * inventory_queue.cc -- 'InventoryQueue' class implementation.
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

#include <cstddef>  // required for NULL
#include "inventory_queue.hh"

using namespace std;

// Standard constructor
InventoryQueue::InventoryQueue() {
    mHead = mTail = NULL;
}

// Copy constructor
InventoryQueue::InventoryQueue(const InventoryQueue& q) {
    if (q.mHead == NULL)
        mHead = mTail = NULL;
    else
        copyList(q.mHead, mHead, mTail);
}

// Explicit destructor
InventoryQueue::~InventoryQueue() {
    Node* frontNode;
    while (mHead != NULL) {
        frontNode = mHead;
        mHead = mHead->next;
        delete frontNode;
    }
}

// Append new node to the back
void InventoryQueue::push(const Batch& data) {
    Node* newNode = new Node;
    newNode->data = data;
    newNode->next = NULL;
    if (mHead == NULL)
        mHead = mTail = newNode;
    else {
        mTail->next = newNode;
        mTail = newNode;
    }
}

// Remove node at the front
void InventoryQueue::pop() {
    if (mHead != NULL) {
        Node* frontNode = mHead;
        mHead = mHead->next;
        delete frontNode;
    }
}

// Construct new Batch structure and append new node to the back
void InventoryQueue::emplace(const int& units, const float& price) {
    Batch data;
    data.units = units;
    data.price = price;
    push(data);
}

// Return reference to the data of the front node
Batch& InventoryQueue::front() {
    return mHead->data;
}

// Return reference to the date of the back node
Batch& InventoryQueue::back() {
    return mTail->data;
}

// Return number of nodes in the queue
int InventoryQueue::size() const {
    Node* node = mHead;

    int listSize = 0;
    while (node != NULL) {
        listSize++;
        node = node->next;
    }
    return listSize;
}

// Test whether the queue is empty
bool InventoryQueue::empty() const {
    return (mHead == NULL);
}

// Helper function for making a deep copy of the list.  This implementation uses
// tail recursion and uses its last two arguments to return both head and tail
// pointers to the resulting cloned list.  The function is designed to be called
// from the copy constructor.
void InventoryQueue::copyList(Node* head, Node*& cloneHead, Node*& cloneTail) {
    Node* cloneNode = NULL;

    if (head != NULL) {
        copyList(head->next, cloneHead, cloneTail);

        cloneNode = new Node;
        cloneNode->data = head->data;
        cloneNode->next = cloneHead;
        if (head->next == NULL)
            cloneTail = cloneNode;
    }
    cloneHead = cloneNode;
}
