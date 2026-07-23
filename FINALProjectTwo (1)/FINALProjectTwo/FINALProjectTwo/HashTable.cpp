#include <iostream>
#include <vector>
#include <string>

using namespace std;

struct Course {
    string courseId;
    string title;
    vector<string> prerequisites;
};

class HashTable {
private:
    struct Node {
        Course course;
        Node* next;
        Node() : next(nullptr) {}
        Node(Course c) : course(c), next(nullptr) {}
    };

    vector<Node*> table;
    unsigned int tableSize;

    unsigned int hash(string key) {
        unsigned int hashVal = 0;
        for (char ch : key) {
            hashVal = 37 * hashVal + ch;
        }
        return hashVal % tableSize;
    }

public:
    HashTable(unsigned int size = 179) : tableSize(size) {
        table.resize(tableSize, nullptr);
    }

    ~HashTable() {
        for (unsigned int i = 0; i < tableSize; ++i) {
            Node* entry = table[i];
            while (entry != nullptr) {
                Node* prev = entry;
                entry = entry->next;
                delete prev;
            }
        }
    }

    void insert(Course course) {
        unsigned int bucket = hash(course.courseId);
        Node* newNode = new Node(course);
        newNode->next = table[bucket];
        table[bucket] = newNode;
    }

    Course search(string courseId) {
        unsigned int bucket = hash(courseId);
        Node* entry = table[bucket];
        while (entry != nullptr) {
            if (entry->course.courseId == courseId) {
                return entry->course;
            }
            entry = entry->next;
        }
        return Course();
    }
};
