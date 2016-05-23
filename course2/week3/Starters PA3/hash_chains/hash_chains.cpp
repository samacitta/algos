#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <list>

using std::string;
using std::vector;
using std::list;
using std::cin;    using std::cout;    using std::endl;

struct Query {
    string type, s;
    size_t ind;
};

class QueryProcessor {
    int bucket_count;

    /*   ktr
    // store all strings in one vector
    vector<string> elems;
    */

    // store all strings in a hash table
    vector<list<string> > elems;

    size_t hash_func(const string& s) const {
        static const size_t multiplier = 263;
        static const size_t prime = 1000000007;
        unsigned long long hash = 0;
        for (int i = static_cast<int> (s.size()) - 1; i >= 0; --i)
            hash = (hash * multiplier + s[i]) % prime;
        return hash % bucket_count;
    }

public:
    explicit QueryProcessor(int bucket_count): bucket_count(bucket_count),
                                               elems(bucket_count)
    {
        for (auto &e : elems) {
            e = list<string>();
        }
    }

    Query readQuery() const {
        Query query;
        cin >> query.type;
        if (query.type != "check")
            cin >> query.s;
        else
            cin >> query.ind;
        return query;
    }

    void writeSearchResult(bool was_found) const {
        std::cout << (was_found ? "yes\n" : "no\n");
    }

    void processQuery(const Query& query) {
        list<string>* bucket_list;
        if (query.type == "check") {

            // write elements of list stored in bucket identified by query.ind
            bucket_list = &elems[query.ind];
            list<string>::iterator it = (*bucket_list).begin();
            while (it != (*bucket_list).end()) {
                cout << *it << " ";
                ++it;
            }
            cout << "" << endl;

        } else {

            bucket_list = &elems[hash_func(query.s)];
            list<string>::iterator it = std::find((*bucket_list).begin(), (*bucket_list).end(), query.s);

            if (query.type == "add") {

                if (it == (*bucket_list).end())
                    (*bucket_list).push_front(query.s);

            } else if (query.type == "del") {

                if (it != (*bucket_list).end())
                    (*bucket_list).erase(it);

            } else if (query.type == "find") {

                string result = "no";
                if (it != (*bucket_list).end())
                    result = "yes";
                cout << result << endl;
            }
        }
    }

    void processQueries() {
        int n;
        cin >> n;
        for (int i = 0; i < n; ++i)
            processQuery(readQuery());
    }
};

int main() {
    std::ios_base::sync_with_stdio(false);
    int bucket_count;
    cin >> bucket_count;
    QueryProcessor proc(bucket_count);
    proc.processQueries();
    return 0;
}
