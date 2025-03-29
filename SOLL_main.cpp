#include "SOLL.h"

int main() {
    frankenstein<int> francky;

    // Add elements
    francky.push_back(10);
    francky.push_front(5);
    francky.push_back(20);
    francky.push_front(2);

    // Print the francky in various orders
    francky.printfrom_head();  // Output: 2 5 10 20
    francky.printfrom_tail();  // Output: 20 10 5 2
    francky.printfrom_asc();   // Output: 2 5 10 20
    francky.printfrom_desc();  // Output: 20 10 5 2

    // Insert an element at a specific position
    francky.insert(15, 2);
    francky.printfrom_head();  // Output: 2 5 10 15 20

    // Erase an element
    francky.erase(2);
    francky.printfrom_head();  // Output: 2 5 15 20
}
