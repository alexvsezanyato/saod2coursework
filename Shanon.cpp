#include "All.hpp"
#include "Shanon.hpp"
#include <ranges>
#include <set>
#include <vector>
#include <iomanip>

Shanon::Code Shanon::next(Shanon::Code current) {
    Code result = current;
    return result;
}

void Shanon::decode(char in[], char out[]) {
    std::ifstream instream;
    instream.open(in);
    if (!instream) return;

    std::ofstream outstream;
    outstream.open(out);
    if (!outstream) return;
    char c = 0;

    while (true) {
        instream.get(c);
        if (instream.eof()) break;
        outstream << (char)((int) 127 - (int) c);
    }

    outstream.close();
    instream.close();
    return;
}

void Shanon::encode(char in[], char out[]) {
    std::ifstream instream;
    instream.open(in);
    if (!instream) return;

    std::ofstream outstream;
    outstream.open(out);
    if (!outstream) return;
    char c = 0;
    std::set<char> chars;
    std::map<char, long> probs; // char -> probability (count)
    std::multimap<long, char> rprobs;
    std::map<char, std::string> codes; // char -> code

    while (true) {
        instream.get(c);
        if (instream.eof()) break;
        // outstream << (char)((int) 127 - (int) c);
        chars.insert(c);
    }

    instream.clear();
    instream.seekg(0, std::ios::beg);
    for (auto &i : chars) probs[i] = 0;
    for (auto &i : chars) codes[i] = "";

    while (true) {
        instream.get(c);
        if (instream.eof()) break;
        // outstream << (char)((int) 127 - (int) c);
        probs[c] += 1;
    }

    instream.clear();
    instream.seekg(0, std::ios::beg);

    for (auto &i : probs) {
        rprobs.insert(
            std::make_pair(
                i.second, i.first
            )
        );
    }

    using std::ranges::views::reverse;
    Code code = "0";

    for (auto &i : rprobs | reverse) {
        codes[i.second] = code;
        code = next(code);
    }

    for (auto [key, value] : probs) {
        std::cout
            << std::setw(1)
            << key
            << ": "
            << value
            << '\n';
    }

    std::cout
        << "[~]"
        << '\n';

    for (auto [key, value] : codes) {
        std::cout
            << std::setw(1)
            << key
            << ": "
            << value
            << '\n';
    }

    outstream.close();
    instream.close();
    return;
}
