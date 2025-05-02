#include <iostream>
#include <array>
#include <string_view>
#include <algorithm> // For std::swap

struct Pair {
    int first;
    int second;
};

void sort_pairs_by_first(std::array<Pair, 5>& pairs) {
    for (size_t i = 0; i < pairs.size(); ++i) {
        for (size_t j = 0; j < pairs.size() - 1; ++j) {
            if (pairs[j].first > pairs[j + 1].first) {
                std::swap(pairs[j], pairs[j + 1]);
            }
        }
    }
}

void print_separator(std::string_view separator) {
    std::cout << separator << std::endl;
}

void process_and_print_pairs(const std::array<Pair, 5>& pairs) {
    for (const auto& pair : pairs) {
        int result;
        if (pair.first % 2 == 0) {
            result = (pair.second % 2 == 0) ? pair.first * pair.second : pair.first + pair.second;
        } else {
            result = (pair.second % 2 == 0) ? pair.first - pair.second : pair.first;
        }
        std::cout << result << std::endl;
    }
}

void process_pairs(std::array<Pair, 5>& pairs) {
    sort_pairs_by_first(pairs);
    print_separator("===");
    print_separator("Output:");
    print_separator("---");
    process_and_print_pairs(pairs);
}

int main() {
    std::array<Pair, 5> pairs = {{
        {5, 1},
        {2, 4},
        {3, 7},
        {1, 6},
        {4, 5},
    }};

    process_pairs(pairs);
    return 0;
}
