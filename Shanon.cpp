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
    instream.open(in, std::ios::binary);
    if (!instream) return;

    std::ifstream table;
    table.open(std::string(in) + ".table", std::ios::binary);
    if (!instream) return;

    std::ofstream outstream;
    outstream.open(out, std::ios::binary);
    if (!outstream) return;
    // char c = 0;
    unsigned char ml = 0;

    using Ai = std::pair<char, char*>;
    std::map<std::string, char> a;

    while (true) {
        unsigned char length = 0;
        // there's a problem with reading unsigned chars
        // the stream reads 2 bytes
        char helper = 0;
        char ch = 0;
        char* code = nullptr;

        // std::cout << ++h << ". {1}: " << table.tellg() << "; ";
        table.read(&ch, 1);
        // std::cout << "char: [" << ch << "]; {2}: " << table.tellg() << "; ";
        table.read(&helper, 1);
        length = (unsigned char) helper;
        if (length > ml) ml = length;
        // std::cout << "length: " << (int) length << "; {3}: " << table.tellg() << "; ";
        code = new char[length + 1];
        table.read(code, length);
        code[length] = '\0';
        // std::cout << "code: " << code << "; {4}: " << table.tellg() << "; \n";

        if (table.eof()) break;
        a[std::string(code)] = ch;
        delete [] code;
    }

    while (!instream.eof()) {
        bool overflow = false;
        if (overflow) break;
        char ch = 0;
        std::string code = "";

        while (true) {
            instream.read(&ch, 1);
            if (instream.eof()) break;
            code += ch;

            if (code.size() > ml) {
                overflow = true;
                break;
            }

            if (a.contains(code)) {
                outstream.write(&a[code], 1);
                break;
            }
        }
    }

    outstream.close();
    instream.close();
    return;
}

void Shanon::encode(char in[], char out[]) {
    std::ifstream instream;
    instream.open(in, std::ios::binary);
    if (!instream) return;

    std::ofstream outstream;
    outstream.open(out, std::ios::binary);
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
    float entropy = 0;

    for (auto &i : a) {
        auto pi = i.second.p;
        entropy -= pi * log2(pi);
    }

    std::cout
        << "The file's entropy: "
        << entropy
        << '\n'
        << std::endl;

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

    short number = 0;
    for (auto &i : a) number += i.second.code.size();
    float average = 0.f;
    average = number / a.size();

    std::cout
        << "The codes are: "
        << std::endl;

    for (auto &i : a) std::cout
        << '['
        << std::setw(2)
        << std::setfill('0')
        << i.second.code.size()
        << "]: "
        << i.second.code
        << '\n';

    std::cout
        << '\n'
        << "The file's entropy: "
        << entropy
        << '\n';

    std::cout
        << "The total code number is: "
        << a.size()
        << std::endl;

    std::cout
        << "Average length (code word): "
        << average
        << std::endl;

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
    using std::ios;

    instream.open(in, ios::ate | ios::binary);
    long sourceSize = instream.tellg();
    instream.close();

    instream.open(out, ios::ate | ios::binary);
    long targetSize = instream.tellg();
    instream.close();
    float compression = 1.f - (targetSize / 8.f) / sourceSize;

    std::cout
        << "Compression ratio: "
        << std::round(compression * 100)
        << "%"
        << std::endl;
}
