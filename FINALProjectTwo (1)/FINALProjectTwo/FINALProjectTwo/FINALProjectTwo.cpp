#include <algorithm>
#include <iostream>
#include <time.h>

#include "CSVparser.hpp"

using namespace std;

double strToDouble(string str, char ch);

// define a structure to hold bid information
struct Bid {
    string bidId; // unique identifier
    string title;
    string fund;
    double amount;
    Bid() {
        amount = 0.0;
    }
};

void displayBid(Bid bid) {
    cout << bid.bidId << ": " << bid.title << " | " << bid.amount << " | "
        << bid.fund << endl;
    return;
}

Bid getBid() {
    Bid bid;

    cout << "Enter Id: ";
    cin.ignore();
    getline(cin, bid.bidId);

    cout << "Enter title: ";
    getline(cin, bid.title);

    cout << "Enter fund: ";
    cin >> bid.fund;

    cout << "Enter amount: ";
    cin.ignore();
    string strAmount;
    getline(cin, strAmount);
    bid.amount = strToDouble(strAmount, '$');

    return bid;
}

vector<Bid> loadBids(string csvPath) {
    cout << "Loading CSV file " << csvPath << endl;

    // Define a vector data structure to hold a collection of bids.
    vector<Bid> bids;

    // initialize the CSV Parser using the given path
    csv::Parser file = csv::Parser(csvPath);

    try {
        // loop to read rows of a CSV file
        for (int i = 0; i < file.rowCount(); i++) {

            // Create a data structure and add to the collection of bids
            Bid bid;
            bid.bidId = file[i][1];
            bid.title = file[i][0];
            bid.fund = file[i][8];
            bid.amount = strToDouble(file[i][4], '$');

            //cout << "Item: " << bid.title << ", Fund: " << bid.fund << ", Amount: " << bid.amount << endl;

            // push this bid to the end
            bids.push_back(bid);
        }
    }
    catch (csv::Error& e) {
        std::cerr << e.what() << std::endl;
    }
    return bids;
}

int partition(vector<Bid>& bids, int begin, int end) {
    string pivot = bids[end].title; // Use the last element as the pivot
    int low = begin - 1;

    for (int j = begin; j < end; ++j) {
        if (bids[j].title <= pivot) {
            ++low;
            swap(bids[low], bids[j]);
        }
    }

    // Place the pivot in the correct position
    swap(bids[low + 1], bids[end]);
    return low + 1;
}

void quickSort(vector<Bid>& bids, int begin, int end) {
    if (begin < end) {
        // Partition the vector and get the pivot index
        int pivotIndex = partition(bids, begin, end);

        // Recursively sort the left and right parts
        quickSort(bids, begin, pivotIndex - 1);
        quickSort(bids, pivotIndex + 1, end);
    }
}

void selectionSort(vector<Bid>& bids) {
    int minIndex;
    for (int i = 0; i < bids.size() - 1; i++) {
        minIndex = i;
        for (int j = i + 1; j < bids.size(); j++) {
            if (bids[j].title < bids[minIndex].title) {
                minIndex = j;
            }
        }
        swap(bids[i], bids[minIndex]);
    }
}

double strToDouble(string str, char ch) {
    str.erase(remove(str.begin(), str.end(), ch), str.end());
    return atof(str.c_str());
}

/**
 * The one and only main() method
 */
int main(int argc, char* argv[]) {

    // process command line arguments
    string csvPath;
    switch (argc) {
    case 2:
        csvPath = argv[1];
        break;
    default:
        csvPath = "eBid_Monthly_Sales.csv";
    }

    // Define a vector to hold all the bids
    vector<Bid> bids;

    // Define a timer variable
    clock_t ticks;

    int choice = 0;
    while (choice != 9) {
        cout << "Menu:" << endl;
        cout << "  1. Load Bids" << endl;
        cout << "  2. Display All Bids" << endl;
        cout << "  3. Selection Sort All Bids" << endl;
        cout << "  4. Quick Sort All Bids" << endl;
        cout << "  9. Exit" << endl;
        cout << "Enter choice: ";
        cin >> choice;

        switch (choice) {

        case 1:
            // Initialize a timer variable before loading bids
            ticks = clock();

            // Complete the method call to load the bids
            bids = loadBids(csvPath);

            cout << bids.size() << " bids read" << endl;

            // Calculate elapsed time and display result
            ticks = clock() - ticks; // current clock ticks minus starting clock ticks
            cout << "time: " << ticks << " clock ticks" << endl;
            cout << "time: " << ticks * 1.0 / CLOCKS_PER_SEC << " seconds" << endl;

            break;

        case 2:
            // Loop and display the bids read
            for (int i = 0; i < bids.size(); ++i) {
                displayBid(bids[i]);
            }
            cout << endl;

            break;

#include <iostream>
#include <vector>
#include <string>

            struct Bid {
                std::string bidId;
                std::string title;
                double amount;

                // Constructor for convenience
                Bid() : bidId(""), title(""), amount(0.0) {}
                Bid(std::string id, std::string t, double a) : bidId(id), title(t), amount(a) {}
            };


            class LinkedList {
            private:
                // Internal structure for list entries
                struct Node {
                    Bid bid;
                    Node* next;

                    Node(Bid b) : bid(b), next(nullptr) {}
                };

                Node* head;   // Pointer to the first node
                Node* tail;   // Pointer to the last node
                size_t size;  // Number of nodes in the list

            public:
                // Constructor to initialize housekeeping variables
                LinkedList() : head(nullptr), tail(nullptr), size(0) {}

                // Destructor to clean up memory
                ~LinkedList() {
                    Node* current = head;
                    while (current != nullptr) {
                        Node* temp = current;
                        current = current->next;
                        delete temp;
                    }
                }

                // Task 3: Append a bid to the end of the list
                void append(Bid bid) {
                    Node* newNode = new Node(bid);
                    if (head == nullptr) { // List is empty
                        head = newNode;
                        tail = newNode;
                    }
                    else {
                        tail->next = newNode;
                        tail = newNode;
                    }
                    size++;
                }

                // Task 4: Prepend a bid to the front of the list
                void prepend(Bid bid) {
                    Node* newNode = new Node(bid);
                    if (head == nullptr) { // List is empty
                        head = newNode;
                        tail = newNode;
                    }
                    else {
                        newNode->next = head;
                        head = newNode;
                    }
                    size++;
                }

                // Task 5: Print all bid entries
                void printList() const {
                    Node* current = head;
                    while (current != nullptr) {
                        std::cout << "Bid ID: " << current->bid.bidId << ", Title: "
                            << current->bid.title << ", Amount: $" << current->bid.amount << std::endl;
                        current = current->next;
                    }
                }

                // Task 6: Remove a bid by bid ID
                bool remove(std::string bidId) {
                    Node* current = head;
                    Node* previous = nullptr;

                    while (current != nullptr && current->bid.bidId != bidId) {
                        previous = current;
                        current = current->next;
                    }

                    if (current == nullptr) { // Bid ID not found
                        return false;
                    }

                    if (previous == nullptr) { // Removing head
                        head = current->next;
                        if (head == nullptr) { // List became empty
                            tail = nullptr;
                        }
                    }
                    else {
                        previous->next = current->next;
                        if (current->next == nullptr) { // Removed last element
                            tail = previous;
                        }
                    }

                    delete current;
                    size--;
                    return true;
                }

                // Task 7: Search for a bid by bid ID
                Bid search(std::string bidId) const {
                    Node* current = head;
                    while (current != nullptr) {
                        if (current->bid.bidId == bidId) {
                            return current->bid;
                        }
                        current = current->next;
                    }
                    return Bid(); // Return empty Bid if not found
                }

                // Additional: Get the size of the list
                size_t getSize() const {
                    return size;
                }
            };
            int main() {
                LinkedList list;

                // Task 3: Append bids
                list.append(Bid("1001", "Bid One", 500.0));
                list.append(Bid("1002", "Bid Two", 1500.0));

                // Task 4: Prepend a bid
                list.prepend(Bid("1000", "Bid Zero", 300.0));

                // Task 5: Print all bids
                std::cout << "Current Bids:\n";
                list.printList();

                // Task 7: Search for a bid
                std::string searchId = "1002";
                Bid foundBid = list.search(searchId);
                if (foundBid.bidId != "") {
                    std::cout << "\nFound Bid - ID: " << foundBid.bidId
                        << ", Title: " << foundBid.title
                        << ", Amount: $" << foundBid.amount << std::endl;
                }
                else {
                    std::cout << "\nBid ID " << searchId << " not found.\n";
                }

                // Task 6: Remove a bid
                std::string removeId = "1001";
                bool removed = list.remove(removeId);
                if (removed) {
                    std::cout << "\nBid ID " << removeId << " removed successfully.\n";
                }
                else {
                    std::cout << "\nBid ID " << removeId << " not found.\n";
                }

                // Print bids after removal
                std::cout << "\nBids after removal:\n";
                list.printList();

                // Add bid ID 98109
                list.append(Bid("98109", "Bid NineEightOneZeroNine", 2500.0));

                // Print bids after adding
                std::cout << "\nBids after adding ID 98109:\n";
                list.printList();

                // Search for bid ID 98109
                Bid testBid = list.search("98109");
                if (testBid.bidId != "") {
                    std::cout << "\nFound Bid - ID: " << testBid.bidId
                        << ", Title: " << testBid.title
                        << ", Amount: $" << testBid.amount << std::endl;
                }
                else {
                    std::cout << "\nBid ID 98109 not found.\n";
                }

                // Remove bid ID 98109
                if (list.remove("98109")) {
                    std::cout << "\nBid ID 98109 removed successfully.\n";
                }
                else {
                    std::cout << "\nBid ID 98109 not found.\n";
                }

                // Final list
                std::cout << "\nFinal Bids:\n";
                list.printList();

                return 0;
            }

            break;

#include <algorithm>
#include <climits>
#include <iostream>
#include <string> // atoi
#include <time.h>

#include "CSVparser.hpp"

            using namespace std;

            //============================================================================
            // Global definitions visible to all methods and classes
            //============================================================================

            const unsigned int DEFAULT_SIZE = 179;

            // forward declarations
            double strToDouble(string str, char ch);

            // define a structure to hold bid information
            struct Bid {
                string bidId; // unique identifier
                string title;
                string fund;
                double amount;
                Bid() {
                    amount = 0.0;
                }
            };

            //============================================================================
            // Hash Table class definition
            //============================================================================

            /**
             * Define a class containing data members and methods to
             * implement a hash table with chaining.
             */
            class HashTable {

            private:
                // Define structures to hold bids
                struct Node {
                    Bid bid;
                    unsigned int key;
                    Node* next;

                    // default constructor
                    Node() {
                        key = UINT_MAX;
                        next = nullptr;
                    }

                    // initialize with a bid
                    Node(Bid aBid) : Node() {
                        bid = aBid;
                    }

                    // initialize with a bid and a key
                    Node(Bid aBid, unsigned int aKey) : Node(aBid) {
                        key = aKey;
                    }
                };

                vector<Node> nodes;

                unsigned int tableSize = DEFAULT_SIZE;

                unsigned int hash(int key);

            public:
                HashTable();
                HashTable(unsigned int size);
                virtual ~HashTable();
                void Insert(Bid bid);
                void PrintAll();
                void Remove(string bidId);
                Bid Search(string bidId);
                size_t Size();
            };

            /**
             * Default constructor
             */
            HashTable::HashTable() {
                // Initialize the structures used to hold bids
                nodes.resize(tableSize);
            }

            /**
             * Constructor for specifying size of the table
             * Use to improve efficiency of hashing algorithm
             * by reducing collisions without wasting memory.
             */
            HashTable::HashTable(unsigned int size) {
                // invoke local tableSize to size with this->
                // resize nodes size
            }


            /**
             * Destructor
             */
            HashTable::~HashTable() {
                //Implement logic to free storage when class is destroyed
                for (unsigned int i = 0; i < tableSize; i++) {
                    Node* current = nodes[i].next;
                    while (current != nullptr) {
                        Node* temp = current;
                        current = current->next;
                        delete temp;
                    }
                }
            }

            /**
             * Calculate the hash value of a given key.
             * Note that key is specifically defined as
             * unsigned int to prevent undefined results
             * of a negative list index.
             *
             * @param key The key to hash
             * @return The calculated hash
             */
            unsigned int HashTable::hash(int key) {
                // Implement logic to calculate a hash value
                return key % tableSize;
            }

            /**
             * Insert a bid
             *
             * @param bid The bid to insert
             */
            void HashTable::Insert(Bid bid) {
                // Implement logic to insert a bid
                unsigned int key = hash(atoi(bid.bidId.c_str()));
                Node* newNode = new Node(bid, key);

                if (nodes[key].key == UINT_MAX) {
                    nodes[key] = *newNode;
                }
                else {
                    Node* current = &nodes[key];
                    while (current->next != nullptr) {
                        current = current->next;
                    }
                    current->next = newNode;
                }
            }

            /**
             * Print all bids
             */
            void HashTable::PrintAll() {
                // Implement logic to print all bids
                for (unsigned int i = 0; i < tableSize; i++) {
                    Node* current = &nodes[i];
                    while (current != nullptr) {
                        if (current->key != UINT_MAX) {
                            cout << "Key: " << current->key << " | ";
                            displayBid(current->bid);
                        }
                        current = current->next;
                    }
                }
            }

            /**
             * Remove a bid
             *
             * @param bidId The bid id to search for
             */
            void HashTable::Remove(string bidId) {
                // Implement logic to remove a bid
                unsigned int key = hash(atoi(bidId.c_str()));
                Node* current = &nodes[key];
                Node* prev = nullptr;

                while (current != nullptr) {
                    if (current->key != UINT_MAX && current->bid.bidId == bidId) {
                        if (prev == nullptr) {
                            // The bid to remove is the first node in the list
                            nodes[key] = Node(); // Clear the node
                        }
                        else {
                            prev->next = current->next;
                            delete current;
                        }
                        return;
                    }
                    prev = current;
                    current = current->next;
                }
            }

            /**
             * Search for the specified bidId
             *
             * @param bidId The bid id to search for
             */
            Bid HashTable::Search(string bidId) {
                Bid bid;

                // Implement logic to search for and return a bid
                unsigned int key = hash(atoi(bidId.c_str()));
                Node* current = &nodes[key];

                while (current != nullptr) {
                    if (current->key != UINT_MAX && current->bid.bidId == bidId) {
                        return current->bid;
                    }
                    current = current->next;
                }

                return bid;
            }

            //============================================================================
            // Static methods used for testing
            //============================================================================

            /**
             * Display the bid information to the console (std::out)
             *
             * @param bid struct containing the bid info
             */
            void displayBid(Bid bid) {
                cout << bid.bidId << ": " << bid.title << " | " << bid.amount << " | "
                    << bid.fund << endl;
                return;
            }

            /**
             * Load a CSV file containing bids into a container
             *
             * @param csvPath the path to the CSV file to load
             * @return a container holding all the bids read
             */
            void loadBids(string csvPath, HashTable * hashTable) {
                cout << "Loading CSV file " << csvPath << endl;

                // initialize the CSV Parser using the given path
                csv::Parser file = csv::Parser(csvPath);

                // read and display header row - optional
                vector<string> header = file.getHeader();
                for (auto const& c : header) {
                    cout << c << " | ";
                }
                cout << "" << endl;

                try {
                    // loop to read rows of a CSV file
                    for (unsigned int i = 0; i < file.rowCount(); i++) {

                        // Create a data structure and add to the collection of bids
                        Bid bid;
                        bid.bidId = file[i][1];
                        bid.title = file[i][0];
                        bid.fund = file[i][8];
                        bid.amount = strToDouble(file[i][4], '$');

                        //cout << "Item: " << bid.title << ", Fund: " << bid.fund << ", Amount: " << bid.amount << endl;

                        // push this bid to the end
                        hashTable->Insert(bid);
                    }
                }
                catch (csv::Error& e) {
                    std::cerr << e.what() << std::endl;
                }
            }

            /**
             * Simple C function to convert a string to a double
             * after stripping out unwanted char
             *
             * credit: http://stackoverflow.com/a/24875936
             *
             * @param ch The character to strip out
             */
            double strToDouble(string str, char ch) {
                str.erase(remove(str.begin(), str.end(), ch), str.end());
                return atof(str.c_str());
            }

            /**
             * The one and only main() method
             */
            int main(int argc, char* argv[]) {

                // process command line arguments
                string csvPath, bidKey;
                switch (argc) {
                case 2:
                    csvPath = argv[1];
                    bidKey = "98223";
                    break;
                case 3:
                    csvPath = argv[1];
                    bidKey = argv[2];
                    break;
                default:
                    csvPath = "eBid_Monthly_Sales.csv";
                    bidKey = "98223";
                }

                // Define a timer variable
                clock_t ticks;

                // Define a hash table to hold all the bids
                HashTable* bidTable;

                Bid bid;
                bidTable = new HashTable();

                int choice = 0;
                while (choice != 9) {
                    cout << "Menu:" << endl;
                    cout << "  1. Load Bids" << endl;
                    cout << "  2. Display All Bids" << endl;
                    cout << "  3. Find Bid" << endl;
                    cout << "  4. Remove Bid" << endl;
                    cout << "  9. Exit" << endl;
                    cout << "Enter choice: ";
                    cin >> choice;

                    switch (choice) {

                    case 1:

                        // Initialize a timer variable before loading bids
                        ticks = clock();

                        // Complete the method call to load the bids
                        loadBids(csvPath, bidTable);

                        // Calculate elapsed time and display result
                        ticks = clock() - ticks; // current clock ticks minus starting clock ticks
                        cout << "time: " << ticks << " clock ticks" << endl;
                        cout << "time: " << ticks * 1.0 / CLOCKS_PER_SEC << " seconds" << endl;
                        break;

                    case 2:
                        bidTable->PrintAll();
                        break;

                    case 3:
                        ticks = clock();

                        bid = bidTable->Search(bidKey);

                        ticks = clock() - ticks; // current clock ticks minus starting clock ticks

                        if (!bid.bidId.empty()) {
                            displayBid(bid);
                        }
                        else {
                            cout << "Bid Id " << bidKey << " not found." << endl;
                        }

                        cout << "time: " << ticks << " clock ticks" << endl;
                        cout << "time: " << ticks * 1.0 / CLOCKS_PER_SEC << " seconds" << endl;
                        break;

                    case 4:
                        bidTable->Remove(bidKey);
                        break;
                    }
                }

#include <iostream>
#include <time.h>

#include "CSVparser.hpp"

                using namespace std;

                //============================================================================
                // Global definitions visible to all methods and classes
                //============================================================================

                // forward declarations
                double strToDouble(string str, char ch);

                // define a structure to hold bid information
                struct Bid {
                    string bidId; // unique identifier
                    string title;
                    string fund;
                    double amount;
                    Bid() {
                        amount = 0.0;
                    }
                };

                // Internal structure for tree node
                struct Node {
                    Bid bid;
                    Node* left;
                    Node* right;

                    // default constructor
                    Node() {
                        left = nullptr;
                        right = nullptr;
                    }

                    // initialize with a bid
                    Node(Bid aBid) :
                        Node() {
                        bid = aBid;
                    }
                };

                //============================================================================
                // Binary Search Tree class definition
                //============================================================================

                /**
                 * Define a class containing data members and methods to
                 * implement a binary search tree
                 */
                class BinarySearchTree {

                private:
                    Node* root;

                    void addNode(Node* node, Bid bid);
                    void inOrder(Node* node);
                    void postOrder(Node* node);
                    void preOrder(Node* node);
                    Node* removeNode(Node* node, string bidId);

                public:
                    BinarySearchTree();
                    virtual ~BinarySearchTree();
                    void InOrder();
                    void PostOrder();
                    void PreOrder();
                    void Insert(Bid bid);
                    void Remove(string bidId);
                    Bid Search(string bidId);
                };

                /**
                 * Default constructor
                 */
                void BinarySearchTree::Insert(Bid bid) {
                    if (root == nullptr) {
                        root = new Node(bid);
                    }
                    else {
                        addNode(root, bid);
                    }
                }

                /**
                 * Destructor
                 */
                void BinarySearchTree::Remove(string bidId) {
                    root = removeNode(root, bidId);
                }

                /**
                 * Traverse the tree in order
                 */
                void BinarySearchTree::InOrder() {
                    inOrder(root);
                }

                /**
                 * Traverse the tree in post-order
                 */
                void BinarySearchTree::PostOrder() {
                    postOrder(root);
                }

                /**
                 * Traverse the tree in pre-order
                 */
                void BinarySearchTree::PreOrder() {
                    preOrder(root);
                }



                /**
                 * Insert a bid
                 */
                void BinarySearchTree::Insert(Bid bid) {
                    if (root == nullptr) {
                        root == new Node;
                        root->info = bid;
                    }
                    else {
                        addNode(root, bid);
                    }
                }

                /**
                 * Remove a bid
                 */
                void BinarySearchTree::Remove(string bidId) {
                    root = removeNode(root, bidId);
                }

                /**
                 * Search for a bid
                 */
                Bid BinarySearchTree::Search(string bidId) {
                    Node* current = root;
                    while (current != nullptr) {
                        if (current->info.bidId == bidId) {
                            return current->info;
                        }
                        if (bidId < current->info.bidId) {
                            current = current->left;
                        }
                        else {
                            current = current->right;
                        }
                    }
                    return Bid();
                }


                void BinarySearchTree::addNode(Node * node, Bid bid) {
                    if (bid.bidId < node->info.bidId) {
                        if (node->left == nullptr) {
                            node->left = new Node;
                            node->left->info = bid;
                        }
                        else {
                            addNode(node->left, bid);
                        }
                    }
                    else {
                        if (node->right == nullptr) {
                            node->right = new Node;
                            node->right->info = bid;
                        }
                        else {
                            addNode(node->right, bid);
                        }
                    }
                }

                void BinarySearchTree::inOrder(Node * node) {
                    if (node != nullptr) {
                        inOrder(node->left);
                        cout << node->info.bidId << " " << node->info.title << " " << node->info.amount << " " << node->info.fund << endl;
                        inOrder(node->right);
                    }
                }
                void BinarySearchTree::postOrder(Node * node) {
                    if (node != nullptr) {
                        postOrder(node->left);
                        postOrder(node->right);
                        cout << node->info.bidId << " " << node->info.title << " " << node->info.amount << " " << node->info.fund << endl; // Output bid information.
                    }

                }

                void BinarySearchTree::preOrder(Node * node) {
                    if (node != nullptr) {
                        cout << node->info.bidId << " " << node->info.title << " " << node->info.amount << " " << node->info.fund << endl; // Output bid information.
                        preOrder(node->left);
                        preOrder(node->right);
                    }
                }

                /**
                 * Remove a bid from some node (recursive)
                 */
                Node* BinarySearchTree::removeNode(Node * node, string bidId) {
                    if (node == nullptr) {
                        return node;
                    }

                    if (bidId < node->info.bidId) {
                        node->left = removeNode(node->left, bidId);
                    }
                    else if (bidId > node->info.bidId) {
                        node->right = removeNode(node->right, bidId);
                    }
                    else {
                        if (node->left == nullptr) {
                            Node* temp = node->right;
                            delete node;
                            return temp;
                        }
                        else if (node->right == nullptr) {
                            Node* temp = node->left;
                            delete node;
                            return temp;
                        }

                        Node* temp = findMinNode(node->right);
                        node->info = temp->info; /
                            node->right = removeNode(node->right, temp->info.bidId);
                    }

                    return node;
                }




                //============================================================================
                // Static methods used for testing
                //============================================================================

                /**
                 * Display the bid information to the console (std::out)
                 *
                 * @param bid struct containing the bid info
                 */
                void displayBid(Bid bid) {
                    cout << bid.bidId << ": " << bid.title << " | " << bid.amount << " | "
                        << bid.fund << endl;
                    return;
                }

                /**
                 * Load a CSV file containing bids into a container
                 *
                 * @param csvPath the path to the CSV file to load
                 * @return a container holding all the bids read
                 */
                void loadBids(string csvPath, BinarySearchTree * bst) {
                    cout << "Loading CSV file " << csvPath << endl;

                    // initialize the CSV Parser using the given path
                    csv::Parser file = csv::Parser(csvPath);

                    // read and display header row - optional
                    vector<string> header = file.getHeader();
                    for (auto const& c : header) {
                        cout << c << " | ";
                    }
                    cout << "" << endl;

                    try {
                        // loop to read rows of a CSV file
                        for (unsigned int i = 0; i < file.rowCount(); i++) {

                            // Create a data structure and add to the collection of bids
                            Bid bid;
                            bid.bidId = file[i][1];
                            bid.title = file[i][0];
                            bid.fund = file[i][8];
                            bid.amount = strToDouble(file[i][4], '$');

                            //cout << "Item: " << bid.title << ", Fund: " << bid.fund << ", Amount: " << bid.amount << endl;

                            // push this bid to the end
                            bst->Insert(bid);
                        }
                    }
                    catch (csv::Error& e) {
                        std::cerr << e.what() << std::endl;
                    }
                }

                /**
                 * Simple C function to convert a string to a double
                 * after stripping out unwanted char
                 *
                 * credit: http://stackoverflow.com/a/24875936
                 *
                 * @param ch The character to strip out
                 */
                double strToDouble(string str, char ch) {
                    str.erase(remove(str.begin(), str.end(), ch), str.end());
                    return atof(str.c_str());
                }

                /**
                 * The one and only main() method
                 */
                int main(int argc, char* argv[]) {

                    // process command line arguments
                    string csvPath, bidKey;
                    switch (argc) {
                    case 2:
                        csvPath = argv[1];
                        bidKey = "98223";
                        break;
                    case 3:
                        csvPath = argv[1];
                        bidKey = argv[2];
                        break;
                    default:
                        csvPath = "eBid_Monthly_Sales.csv";
                        bidKey = "98223";
                    }

                    // Define a timer variable
                    clock_t ticks;

                    // Define a binary search tree to hold all bids
                    BinarySearchTree* bst;
                    bst = new BinarySearchTree();
                    Bid bid;

                    int choice = 0;
                    while (choice != 9) {
                        cout << "Menu:" << endl;
                        cout << "  1. Load Bids" << endl;
                        cout << "  2. Display All Bids" << endl;
                        cout << "  3. Find Bid" << endl;
                        cout << "  4. Remove Bid" << endl;
                        cout << "  9. Exit" << endl;
                        cout << "Enter choice: ";
                        cin >> choice;

                        switch (choice) {

                        case 1:

                            // Initialize a timer variable before loading bids
                            ticks = clock();

                            // Complete the method call to load the bids
                            loadBids(csvPath, bst);

                            //cout << bst->Size() << " bids read" << endl;

                            // Calculate elapsed time and display result
                            ticks = clock() - ticks; // current clock ticks minus starting clock ticks
                            cout << "time: " << ticks << " clock ticks" << endl;
                            cout << "time: " << ticks * 1.0 / CLOCKS_PER_SEC << " seconds" << endl;
                            break;

                        case 2:
                            bst->InOrder();
                            break;

                        case 3:
                            ticks = clock();

                            bid = bst->Search(bidKey);

                            ticks = clock() - ticks; // current clock ticks minus starting clock ticks

                            if (!bid.bidId.empty()) {
                                displayBid(bid);
                            }
                            else {
                                cout << "Bid Id " << bidKey << " not found." << endl;
                            }

                            cout << "time: " << ticks << " clock ticks" << endl;
                            cout << "time: " << ticks * 1.0 / CLOCKS_PER_SEC << " seconds" << endl;

                            break;

                        case 4:
                            bst->Remove(bidKey);
                            break;
                        }
                    }

#include <iostream>
#include <time.h>

#include "CSVparser.hpp"

                    using namespace std;

                    //============================================================================
                    // Global definitions visible to all methods and classes
                    //============================================================================

                    // forward declarations
                    double strToDouble(string str, char ch);

                    // define a structure to hold bid information
                    struct Bid {
                        string bidId; // unique identifier
                        string title;
                        string fund;
                        double amount;
                        Bid() {
                            amount = 0.0;
                        }
                    };

                    // Internal structure for tree node
                    struct Node {
                        Bid bid;
                        Node* left;
                        Node* right;

                        // default constructor
                        Node() {
                            left = nullptr;
                            right = nullptr;
                        }

                        // initialize with a bid
                        Node(Bid aBid) :
                            Node() {
                            bid = aBid;
                        }
                    };

                    //============================================================================
                    // Binary Search Tree class definition
                    //============================================================================

                    /**
                     * Define a class containing data members and methods to
                     * implement a binary search tree
                     */
                    class BinarySearchTree {

                    private:
                        Node* root;

                        void addNode(Node* node, Bid bid);
                        void inOrder(Node* node);
                        void postOrder(Node* node);
                        void preOrder(Node* node);
                        Node* removeNode(Node* node, string bidId);

                    public:
                        BinarySearchTree();
                        virtual ~BinarySearchTree();
                        void InOrder();
                        void PostOrder();
                        void PreOrder();
                        void Insert(Bid bid);
                        void Remove(string bidId);
                        Bid Search(string bidId);
                    };

                    /**
                     * Default constructor
                     */
                    void BinarySearchTree::Insert(Bid bid) {
                        if (root == nullptr) {
                            root = new Node(bid);
                        }
                        else {
                            addNode(root, bid);
                        }
                    }

                    /**
                     * Destructor
                     */
                    void BinarySearchTree::Remove(string bidId) {
                        root = removeNode(root, bidId);
                    }

                    /**
                     * Traverse the tree in order
                     */
                    void BinarySearchTree::InOrder() {
                        inOrder(root);
                    }

                    /**
                     * Traverse the tree in post-order
                     */
                    void BinarySearchTree::PostOrder() {
                        postOrder(root);
                    }

                    /**
                     * Traverse the tree in pre-order
                     */
                    void BinarySearchTree::PreOrder() {
                        preOrder(root);
                    }



                    /**
                     * Insert a bid
                     */
                    void BinarySearchTree::Insert(Bid bid) {
                        if (root == nullptr) {
                            root == new Node;
                            root->info = bid;
                        }
                        else {
                            addNode(root, bid);
                        }
                    }

                    /**
                     * Remove a bid
                     */
                    void BinarySearchTree::Remove(string bidId) {
                        root = removeNode(root, bidId);
                    }

                    /**
                     * Search for a bid
                     */
                    Bid BinarySearchTree::Search(string bidId) {
                        Node* current = root;
                        while (current != nullptr) {
                            if (current->info.bidId == bidId) {
                                return current->info;
                            }
                            if (bidId < current->info.bidId) {
                                current = current->left;
                            }
                            else {
                                current = current->right;
                            }
                        }
                        return Bid();
                    }


                    void BinarySearchTree::addNode(Node * node, Bid bid) {
                        if (bid.bidId < node->info.bidId) {
                            if (node->left == nullptr) {
                                node->left = new Node;
                                node->left->info = bid;
                            }
                            else {
                                addNode(node->left, bid);
                            }
                        }
                        else {
                            if (node->right == nullptr) {
                                node->right = new Node;
                                node->right->info = bid;
                            }
                            else {
                                addNode(node->right, bid);
                            }
                        }
                    }

                    void BinarySearchTree::inOrder(Node * node) {
                        if (node != nullptr) {
                            inOrder(node->left);
                            cout << node->info.bidId << " " << node->info.title << " " << node->info.amount << " " << node->info.fund << endl;
                            inOrder(node->right);
                        }
                    }
                    void BinarySearchTree::postOrder(Node * node) {
                        if (node != nullptr) {
                            postOrder(node->left);
                            postOrder(node->right);
                            cout << node->info.bidId << " " << node->info.title << " " << node->info.amount << " " << node->info.fund << endl; // Output bid information.
                        }

                    }

                    void BinarySearchTree::preOrder(Node * node) {
                        if (node != nullptr) {
                            cout << node->info.bidId << " " << node->info.title << " " << node->info.amount << " " << node->info.fund << endl; // Output bid information.
                            preOrder(node->left);
                            preOrder(node->right);
                        }
                    }

                    /**
                     * Remove a bid from some node (recursive)
                     */
                    Node* BinarySearchTree::removeNode(Node * node, string bidId) {
                        if (node == nullptr) {
                            return node;
                        }

                        if (bidId < node->info.bidId) {
                            node->left = removeNode(node->left, bidId);
                        }
                        else if (bidId > node->info.bidId) {
                            node->right = removeNode(node->right, bidId);
                        }
                        else {
                            if (node->left == nullptr) {
                                Node* temp = node->right;
                                delete node;
                                return temp;
                            }
                            else if (node->right == nullptr) {
                                Node* temp = node->left;
                                delete node;
                                return temp;
                            }

                            Node* temp = findMinNode(node->right);
                            node->info = temp->info; /
                                node->right = removeNode(node->right, temp->info.bidId);
                        }

                        return node;
                    }




                    //============================================================================
                    // Static methods used for testing
                    //============================================================================

                    /**
                     * Display the bid information to the console (std::out)
                     *
                     * @param bid struct containing the bid info
                     */
                    void displayBid(Bid bid) {
                        cout << bid.bidId << ": " << bid.title << " | " << bid.amount << " | "
                            << bid.fund << endl;
                        return;
                    }

                    /**
                     * Load a CSV file containing bids into a container
                     *
                     * @param csvPath the path to the CSV file to load
                     * @return a container holding all the bids read
                     */
                    void loadBids(string csvPath, BinarySearchTree * bst) {
                        cout << "Loading CSV file " << csvPath << endl;

                        // initialize the CSV Parser using the given path
                        csv::Parser file = csv::Parser(csvPath);

                        // read and display header row - optional
                        vector<string> header = file.getHeader();
                        for (auto const& c : header) {
                            cout << c << " | ";
                        }
                        cout << "" << endl;

                        try {
                            // loop to read rows of a CSV file
                            for (unsigned int i = 0; i < file.rowCount(); i++) {

                                // Create a data structure and add to the collection of bids
                                Bid bid;
                                bid.bidId = file[i][1];
                                bid.title = file[i][0];
                                bid.fund = file[i][8];
                                bid.amount = strToDouble(file[i][4], '$');

                                //cout << "Item: " << bid.title << ", Fund: " << bid.fund << ", Amount: " << bid.amount << endl;

                                // push this bid to the end
                                bst->Insert(bid);
                            }
                        }
                        catch (csv::Error& e) {
                            std::cerr << e.what() << std::endl;
                        }
                    }

                    /**
                     * Simple C function to convert a string to a double
                     * after stripping out unwanted char
                     *
                     * credit: http://stackoverflow.com/a/24875936
                     *
                     * @param ch The character to strip out
                     */
                    double strToDouble(string str, char ch) {
                        str.erase(remove(str.begin(), str.end(), ch), str.end());
                        return atof(str.c_str());
                    }

                    /**
                     * The one and only main() method
                     */
                    int main(int argc, char* argv[]) {

                        // process command line arguments
                        string csvPath, bidKey;
                        switch (argc) {
                        case 2:
                            csvPath = argv[1];
                            bidKey = "98223";
                            break;
                        case 3:
                            csvPath = argv[1];
                            bidKey = argv[2];
                            break;
                        default:
                            csvPath = "eBid_Monthly_Sales.csv";
                            bidKey = "98223";
                        }

                        // Define a timer variable
                        clock_t ticks;

                        // Define a binary search tree to hold all bids
                        BinarySearchTree* bst;
                        bst = new BinarySearchTree();
                        Bid bid;

                        int choice = 0;
                        while (choice != 9) {
                            cout << "Menu:" << endl;
                            cout << "  1. Load Bids" << endl;
                            cout << "  2. Display All Bids" << endl;
                            cout << "  3. Find Bid" << endl;
                            cout << "  4. Remove Bid" << endl;
                            cout << "  9. Exit" << endl;
                            cout << "Enter choice: ";
                            cin >> choice;

                            switch (choice) {

                            case 1:

                                // Initialize a timer variable before loading bids
                                ticks = clock();

                                // Complete the method call to load the bids
                                loadBids(csvPath, bst);

                                //cout << bst->Size() << " bids read" << endl;

                                // Calculate elapsed time and display result
                                ticks = clock() - ticks; // current clock ticks minus starting clock ticks
                                cout << "time: " << ticks << " clock ticks" << endl;
                                cout << "time: " << ticks * 1.0 / CLOCKS_PER_SEC << " seconds" << endl;
                                break;

                            case 2:
                                bst->InOrder();
                                break;

                            case 3:
                                ticks = clock();

                                bid = bst->Search(bidKey);

                                ticks = clock() - ticks; // current clock ticks minus starting clock ticks

                                if (!bid.bidId.empty()) {
                                    displayBid(bid);
                                }
                                else {
                                    cout << "Bid Id " << bidKey << " not found." << endl;
                                }

                                cout << "time: " << ticks << " clock ticks" << endl;
                                cout << "time: " << ticks * 1.0 / CLOCKS_PER_SEC << " seconds" << endl;

                                break;

                            case 4:
                                bst->Remove(bidKey);
                                break;
                            }
                        }


                        cout << "Good bye." << endl;

                        return 0;
                    }
                }