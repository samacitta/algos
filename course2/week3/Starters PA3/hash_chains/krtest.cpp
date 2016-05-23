#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <list>

using std::string;
using std::vector;
using std::list;
using std::cin;    using std::cout;    using std::endl;


int main() {
    int n = 10;
    vector<list<string>> ht(n);
    cout << "ht size = " << ht.size() << endl;

    ht[0].push_front("kevin");
    cout << "ht[0].front() = " << ht[0].front() << endl;

    ht[0].push_front("karen");
    cout << "ht[0].front() = " << ht[0].front() << endl;

    cout << "ht[0].size() = " << ht[0].size() << endl;


    return 0;
}
