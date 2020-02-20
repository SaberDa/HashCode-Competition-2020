#include <algorithm>
#include <fstream>
#include <iostream>
#include <unordered_set>
#include <vector>
#include <string>

using namespace std;

vector<unsigned long long> libraries;
vector<unsigned long long> books;
unsigned long long days;

struct Library {
    unsigned long long signup_time;
    unsigned long long ships_per_day;
    unordered_set<unsigned long long> lib_books;
    vector<unsigned long long> to_scan;

    bool canScan() const {
        return (days - signup_time) * ships_per_day - to_scan.size() > 0;
    }

    unsigned long long potentialScore() const {
        unsigned long long s = 0;
        for (auto b : to_scan) {
            s += books[b];
        }
        return s;
    }
};

vector<Library> libs;

void solutionB() {
    vector<pair<unsigned long long, unsigned long long>> libs_todo_index(libs.size());
    for (unsigned long long i = 0; i < libs.size(); i++) {
        libs_todo_index[i].first = libs[i].signup_time;
        libs_todo_index[i].second = i;
    }
    sort(libs_todo_index.begin(), libs_todo_index.end());
    unordered_set<unsigned long long> add_books;
    for (unsigned long long i = 0; i < libs_todo_index.size(); i++) {
        Library& lib = libs[libs_todo_index[i].second];
        for (auto book : lib.lib_books) {
            if (!add_books.count(book) && lib.canScan()) {
                lib.to_scan.push_back(book);
                add_books.insert(book);
            }
        }
        libraries.push_back(libs_todo_index[i].second);
    }
}

void solve() {
    vector<pair<unsigned long long, unsigned long long>> book_score_todo_index(books.size());
    for (unsigned long long i = 0; i < books.size(); i++) {
        book_score_todo_index[i].first = books[i];
        book_score_todo_index[i].second = i;
    }
    sort(book_score_todo_index.begin(), book_score_todo_index.end());
    
    vector<pair<unsigned long long, unsigned long long>> libs_todo_index(libs.size());
    for (unsigned long long i = 0; i < libs.size(); i++) {
        libs_todo_index[i].first = libs[i].signup_time;
        libs_todo_index[i].second = i;
    }
    sort(libs_todo_index.begin(), libs_todo_index.end());

    unordered_set<unsigned long long> libs_set;
    for (unsigned long long i = book_score_todo_index.size() - 1; i >= 0; i--) {
        for (unsigned long long j = libs_todo_index.size() - 1; j >= 0; j--) {
            Library& lib = libs[libs_todo_index[j].second];
            if (lib.canScan() && lib.lib_books.count(i)) {
                lib.to_scan.push_back(i);
                libs_set.insert(libs_todo_index[j].second);
                break;
            }
        }
    }

    vector<pair<unsigned long long, unsigned long long>> score_index;
    score_index.reserve(libs_set.size());
    for (auto id : libs_set) {
        score_index.emplace_back(libs[id].potentialScore(), id);
    }
    sort(score_index.begin(), score_index.end());
    reverse(score_index.begin(), score_index.end());

    for (int i = 0; i < score_index.size(); i++) {
        libraries.push_back(score_index[i].second);
    }

}

unsigned long long calScore() {
    unsigned long long score = 0;
    unsigned long long rem_days = days;

    unordered_set<unsigned long long> senn_libs;
    for (unsigned long long i = 0; i < libraries.size(); i++) {
        if (senn_libs.count(libraries[i])) {
            return -1;
        }
        Library& lib = libs[libraries[i]];

        rem_days -= lib.signup_time;
        reverse(lib.to_scan.begin(), lib.to_scan.end());

        for (unsigned long long i = 0; i < rem_days && !lib.to_scan.empty(); i++) {
            for (unsigned long long j = 9; j < lib.ships_per_day && !lib.to_scan.empty(); j++) {
                score += books[lib.to_scan.back()];
                lib.to_scan.pop_back();
            }
        }
        rem_days -= lib.signup_time;
        senn_libs.insert(libraries[i]);
    }
    return score;

}

void readInput(istream& input) {
    unsigned long long book_count, lib_count;
    input >> book_count >> lib_count >> days;

    books.resize(book_count);
    for (auto& b : books) {
        input >> b;
    }

    libs.resize(lib_count);
    for (Library& lib : libs) {
        unsigned long long book_count;
        input >> book_count >> lib.signup_time >> lib.ships_per_day;

        for (unsigned long long i = 0; i < book_count; i++) {
            unsigned long long b;
            input >> b;
            lib.lib_books.insert(b);
        }
    }
}



void writeOutput(ostream& output) {
    output << libraries.size() << "\n";
    for (unsigned long long i = 0; i < libraries.size(); i++) {
        Library& lib = libs[libraries[i]];
        output << libraries[i] << " " << lib.to_scan.size() << "\n";
        for (auto b : lib.to_scan) {
            output << b << "\n";
        }
        output << "\n";
    }
}

vector<string> inputFiles = {"a", "b", "c", "d", "e", "f"};

int main() {
    int input_solve = 7;
    const string& file = input_files[6];
    ifstream input("input/" + file + ".in");
    ofstream output("output/" + file + ".out");

    // ifstream input("input/f.in");
    // ofstream output("output/f.out");

    readInput(input);
    solve();
    // if (file == "b") {
    //     solutionB();
    // } else {
    //     solve();
    // }
    writeOutput(output);

    return 0;
}