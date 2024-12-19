#include "mainHeader.hpp"
#include <fstream>
#include <string>
#include <iostream>
#include "node.hpp"
#include <sstream>
using namespace std;

void Queue::pop() {
    if (front == nullptr) {
        cout << "Queue is empty." << endl;
        return;
    }
    Node* temp = front;
    front = front->next;
    if (front == nullptr) {
        end = nullptr;
    }
    delete temp;
    size--;
}

void Queue::print() {
    Node* temp = front;
    while (temp != nullptr) {
        cout << temp->data << " ";
        temp = temp->next;
    }
    cout << endl;
}
void Queue::saveToFile(const string& filename) {
    ofstream outFile(filename);
    if (!outFile.is_open()) {
        cout << "Cannot open file for writing: " << filename << endl;
        return;
    }
    Node* temp = front;
    while (temp) {
        outFile << temp->data << endl;
        temp = temp->next;
    }
    outFile.close();
}

void Queue::loadFromFile(const string& filename) {
    ifstream inFile(filename);
    if (!inFile.is_open()) {
        cout << "Cannot open file for reading: " << filename << endl;
        return;
    }
    string line;
    while (getline(inFile, line)) {
        push(line);
    }
    inFile.close();
}