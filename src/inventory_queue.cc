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
    head = tail = NULL;
}

// Copy constructor
InventoryQueue::InventoryQueue(const InventoryQueue& q) {
    if (q.head == NULL)
        head = tail = NULL;
    else
        copyList(q.head, head, tail);
}

// Explicit destructor
InventoryQueue::~InventoryQueue() {
    Node* currentNode;
    while (head != NULL) {
        currentNode = head;
        head = head->next;
        delete currentNode;
    }
}

// Append new node to the back
void InventoryQueue::push(const Batch& data) {

    Node* node = new Node;

    node->data = data;
    node->next = NULL;
    if (head == NULL)
        head = tail = node;
    else {
        tail->next = node;
        tail = node;
    }
}

// Remove node at the front
void InventoryQueue::pop() {
    if (!empty()) {
        Node* currentNode = head;
        head = head->next;
        delete currentNode;
    }
}

// Construct new Batch structure and append node to the back
void InventoryQueue::emplace(const int& units, const float& price) {
    Batch data;
    data.units = units;
    data.price = price;
    push(data);
}

// Return reference to the data of the head node
Batch& InventoryQueue::front() {
    return head->data;
}

// Return reference to the date of the tail node
Batch& InventoryQueue::back() {
    return tail->data;
}

// Return number of nodes in the queue
int InventoryQueue::size() const {
    Node* currentNode = head;

    int listSize = 0;
    while (currentNode != NULL) {
        listSize++;
        currentNode = currentNode->next;
    }
    return listSize;
}

// Test whether the queue is empty
bool InventoryQueue::empty() const {
    return (head == NULL);
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
