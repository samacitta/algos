#include <iostream>
#include <string>
#include <vector>
#include <boost/timer.hpp>

using std::string;
using std::vector;
using std::cin;    using std::cout;    using std::endl;
typedef unsigned long long ull;

struct Data {
    string pattern, text;
};

Data read_input() {
    Data data;
    std::cin >> data.pattern >> data.text;
    return data;
}

void print_occurrences(const std::vector<int>& output) {
    for (size_t i = 0; i < output.size(); ++i)
        std::cout << output[i] << " ";
    std::cout << "\n";
}

std::vector<int> get_occurrences(const Data& input) {
    const string& s = input.pattern, t = input.text;
    std::vector<int> ans;
    for (size_t i = 0; i + s.size() <= t.size(); ++i)
        if (t.substr(i, s.size()) == s)
            ans.push_back(i);
    return ans;
}

// test for equality of two strings
bool areEqual(const string& s1, const string& s2) {
    if (s1.size() != s2.size())
        return false;
    for (size_t i = 0; i < s1.size(); ++i) {
        if (s1[i] != s2[i])
            return false;
    }
    return true;
}

// polynomial hash function
long long polyHash(const string& s, const long long prime,
                   const long long multiplier) {
    long long hash = 0;
    for (int i = static_cast<int> (s.size()) - 1; i >= 0; --i)
        hash = (hash * multiplier + s[i]) % prime;
    return hash;
}

// precompute hashes
vector<long long> precomputeHashes(const string& text, const int pLength,
                                   const long long prime, const long long multiplier) {
    int tLength = text.size();
    vector<long long> hashes(tLength-pLength+1);
    string sub = text.substr(tLength-pLength, tLength-1);
    hashes[tLength - pLength] = polyHash(sub, prime, multiplier);
    long long y = 1;
    for (int i = 1; i <= pLength; ++i)
        y = (y * multiplier) % prime;
    for (int i = (tLength-pLength-1); i >= 0; --i) {
        hashes[i] = (multiplier*hashes[i+1] + text[i] - y*text[i+pLength]) % prime;
    }
    return hashes;
}

// Rabin-Karp algorithm for substring search
vector<int> rabinKarp(const string& text, const string& pattern) {
    static const long long multiplier = 263;
    static const long long prime = 1000000007;
    vector<int> result;
    long long pHash = polyHash(pattern, prime, multiplier);
    for (size_t i = 0; i <= text.size()-pattern.size(); ++i) {
        long long tHash = polyHash(text.substr(i, pattern.size()), prime, multiplier);
        if (pHash != tHash)
            continue;
        if (areEqual(text.substr(i, pattern.size()), pattern))
            result.push_back(i);
    }

    return result;
}

int main() {
    std::ios_base::sync_with_stdio(false);
    Data inputData = read_input();

    boost::timer t1;
    vector<int> result = get_occurrences(inputData);
    print_occurrences(result);
    cout << "elapsed time = " << t1.elapsed() << endl;

    boost::timer t2;
    result = rabinKarp(inputData.text, inputData.pattern);
    print_occurrences(result);
    cout << "elapsed time = " << t2.elapsed() << endl;

    return 0;
}
