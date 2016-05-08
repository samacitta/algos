#include <iostream>
#include <stack>
#include <string>

struct Bracket {
    Bracket(char type, int position):     // type should be char instead of int???
        type(type),
        position(position)
    {}

    bool Matchc(char c) {
        if (type == '[' && c == ']')
            return true;
        if (type == '{' && c == '}')
            return true;
        if (type == '(' && c == ')')
            return true;
        return false;
    }

    char type;
    int position;
};

int main() {
    std::string text;
    getline(std::cin, text);

    std::stack <Bracket> open_brack_stack;
    int result = -1;     // -1 means no mismatched brackets
    for (int position = 0; position < text.length(); ++position) {
        char next = text[position];

        if (next == '(' || next == '[' || next == '{') {
            // Process opening bracket, write your code here
            open_brack_stack.push(Bracket(next, position));
        }

        if (next == ')' || next == ']' || next == '}') {
            // Process closing bracket, write your code here
            // no matching open bracket
            if (open_brack_stack.empty() || !open_brack_stack.top().Matchc(next)) {
                result = position;
                break;
            }
            // pop top element of stack since there was a proper match
            open_brack_stack.pop();
        }
    }

    // Printing answer, write your code here
    if (result != -1) {
        std::cout << result+1 << '\n';     // answer to be in 1-based indexing
    } else if (!open_brack_stack.empty()) {
        std::cout << open_brack_stack.top().position+1 << '\n';
    } else {
        std::cout << "Success" << '\n';
    }

    return 0;
}
