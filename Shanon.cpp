#include "All.hpp"
#include "Shanon.hpp"

#include <iomanip>
#include <ranges>
#include <cmath>

#include <set>
#include <vector>
#include <bitset>

void Shanon::decode(char in[], char out[]) {
    std::ifstream instream;
    instream.open(in);
    if (!instream) return;

    std::ofstream outstream;
    outstream.open(out);
    if (!outstream) return;
    char c = 0;

    using Ai = std::pair<char, char*>;
    std::map<char, char> a;

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
    float charsNumber = 0;
    std::map<char, Shanon::Data> a;

    while (true) {
        instream.get(c);
        if (instream.eof()) break;
        // outstream << (char)((int) 127 - (int) c);
        charsNumber += 1;
        chars.insert(c);
    }

    instream.clear();
    instream.seekg(0, std::ios::beg);

    while (true) {
        instream.get(c);
        if (instream.eof()) break;
        a[c].p += 1;
    }

    instream.clear();
    instream.seekg(0, std::ios::beg);

    for (auto &i : a) {
        i.second.p /= charsNumber;
        continue;
    }

    using Ai = std::pair<const char, Shanon::Data>;
    std::vector<Ai*> asort(a.size());
    short h = 0;

    for (auto &i : a) {
        asort.at(h) = &i;
        h++;
    }

    std::sort(asort.begin(), asort.end(), [](Ai* a, Ai* b){
        bool result = (*a).second.p > (*b).second.p;
        return result;
    });

    for (auto &i : asort) {
        for (auto &j : asort) {
            if (i->first == j->first) break;
            i->second.b += j->second.p;
        }

        i->second.l = std::ceil(
            -std::logb(
                i->second.p
            )
        );

        for (char j = 1; j <= i->second.l; j++) {
            i->second.code += (
                (int) std::trunc(
                    i->second.b * std::pow(2, j)
                ) % 2
            ) + '0';
        }
    }

    std::ofstream table;
    table.open(std::string(out) + ".table");

    for (auto &i : asort) {
        table
            << i->first
            << (unsigned char) i->second.code.size();

        table.write(
            i->second.code.data(),
            i->second.code.size()
        );
    }

    while (true) {
        instream.get(c);
        if (instream.eof()) break;

        outstream.write(
            a[c].code.data(),
            a[c].code.size()
        );
    }

    table.close();
    outstream.close();
    instream.close();
    return;
}
