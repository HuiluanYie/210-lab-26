// COMSC-210 | Lab 26 | Huiluan Yie

#include <iostream>
#include <iomanip>
#include <chrono>
#include <vector>
#include <list>
#include <set>
#include <fstream>
#include <string>
#include <algorithm>
using namespace std;
using namespace std::chrono;

const string TESTCODE = "TESTCODE";
const int W = 10;
const int ROWS = 4, COLS = 3;
const int SLICES = 2;
const int EXPERIMENTS = 15;
const int CURRENT = 0;
const int TOTAL = 1;
// results[CURRENT] stores the the results for that particular run of the model
// results[TOTAL] hold accumulator variables that continually sum their counterparts

int main() {
    // declaration
    int results[SLICES][ROWS][COLS] = {}; // initialize to clear anything
    // preveously in memory
    string file = "names.txt";

    for (int e = 0; e < EXPERIMENTS; e++) {
        string t;
        vector < string > v;
        list < string > l;
        set < string > s;
        //READING
        for (int i = 0; i < COLS; i++) {
            // file input
            ifstream fin;
            fin.open(file);

            if (fin.good()) {
                switch (i) {
                case 0: {
                    // vector:
                    // Start timing
                    auto start = high_resolution_clock::now();
                    while (getline(fin, t)) {
                        v.push_back(t);
                    }
                    // End timing
                    auto end = high_resolution_clock::now();
                    // Calculate duration
                    auto vec_read = duration_cast < microseconds > (end - start);
                    results[CURRENT][0][i] = vec_read.count();
                    break;
                }
                case 1: {
                    // list:
                    // Start timing
                    auto start = high_resolution_clock::now();
                    while (getline(fin, t)) {
                        l.push_back(t);
                    }
                    // End timing
                    auto end = high_resolution_clock::now();
                    // Calculate duration
                    auto lst_read = duration_cast < microseconds > (end - start);
                    results[CURRENT][0][i] = lst_read.count();
                    break;
                }
                case 2: {
                    // set:
                    // Start timing
                    auto start = high_resolution_clock::now();
                    while (getline(fin, t)) {
                        s.insert(t);
                    }
                    // End timing
                    auto end = high_resolution_clock::now();
                    // Calculate duration
                    auto set_read = duration_cast < microseconds > (end - start);
                    results[CURRENT][0][i] = set_read.count();
                    break;
                }
                }
                fin.close();
            } else {
                cout << "File not found.\n";
                return 1;
            }
        }

        //SORTING
        for (int i = 0; i < COLS; i++) {
            // Start timing
            auto start = high_resolution_clock::now();
            switch (i) {
            case 0: {
                // vector:
                sort(v.begin(), v.end());
                // End timing
                auto end = high_resolution_clock::now();
                // Calculate duration
                auto vec_sort = duration_cast < microseconds > (end - start);
                results[CURRENT][1][i] = vec_sort.count();
                break;
            }
            case 1: {
                // list:
                l.sort();
                // End timing
                auto end = high_resolution_clock::now();
                // Calculate duration
                auto lst_sort = duration_cast < microseconds > (end - start);
                results[CURRENT][1][i] = lst_sort.count();
                break;
            }
            case 2: {
                // set:
                // the set's value is 0 since a set is already sorted.
                results[CURRENT][1][i] = 0;
                break;
            }
            }
        }

        //INSERTING
        for (int i = 0; i < COLS; i++) {
            // Start timing
            auto start = high_resolution_clock::now();
            switch (i) {
            case 0: {
                // vector:
                v.insert(v.begin() + v.size() / 2, TESTCODE);
                // End timing
                auto end = high_resolution_clock::now();
                // Calculate duration
                auto vec_insert = duration_cast < microseconds > (end - start);
                results[CURRENT][2][i] = vec_insert.count();
                break;
            }
            case 1: {
                // list:
                auto l_it = l.begin();
                // make the iterater point to the middle
                for (int j = 0; j < l.size() / 2; j++) {
                    l_it++;
                }
                l.insert(l_it, TESTCODE);
                // End timing
                auto end = high_resolution_clock::now();
                // Calculate duration
                auto lst_insert = duration_cast < microseconds > (end - start);
                results[CURRENT][2][i] = lst_insert.count();
                break;
            }
            case 2: {
                // set:
                s.insert(TESTCODE); // into the set
                // End timing
                auto end = high_resolution_clock::now();
                // Calculate duration
                auto set_insert = duration_cast < microseconds > (end - start);
                results[CURRENT][2][i] = set_insert.count();
                break;
            }
            }
        }

        //DELETING
        for (int i = 0; i < COLS; i++) {
            // Start timing
            auto start = high_resolution_clock::now();
            switch (i) {
            case 0: {
                // vector:
                v.erase(v.begin() + v.size() / 2);
                // End timing
                auto end = high_resolution_clock::now();
                // Calculate duration
                auto vec_del = duration_cast < microseconds > (end - start);
                results[CURRENT][3][i] = vec_del.count();
                break;
            }
            case 1: {
                // list:
                auto l_it = l.begin();
                // make the iterater point to the middle
                for (int j = 0; j < l.size() / 2; j++) {
                    l_it++;
                }
                l.erase(l_it);
                // End timing
                auto end = high_resolution_clock::now();
                // Calculate duration
                auto lst_del = duration_cast < microseconds > (end - start);
                results[CURRENT][3][i] = lst_del.count();
                break;
            }
            case 2: {
                // set:
                auto s_it = s.begin();
                // make the iterater point to the middle
                for (int j = 0; j < s.size() / 2; j++) {
                    s_it++;
                }
                s.erase(s_it);
                // End timing
                auto end = high_resolution_clock::now();
                // Calculate duration
                auto set_del = duration_cast < microseconds > (end - start);
                results[CURRENT][3][i] = set_del.count();
                break;
            }
            }
        }
        for (int r = 0; r < ROWS; r++) {
            for (int c = 0; c < COLS; c++) {
                results[TOTAL][r][c] += results[CURRENT][r][c];
            }
        }
    }

    cout << "Number of simulations: " << EXPERIMENTS << '\n';
    // Output the table of duration in microseconds (number too big in nanoseconds)
    string labels[] = {
        "Read",
        "Sort",
        "Insert",
        "Delete"
    };
    cout << setw(W) << "Operations" << setw(W) << "Vector" << setw(W) <<
        "List" << setw(W) << "Set" << endl;
    for (int i = 0; i < ROWS; i++) {
        cout << setw(W) << labels[i];
        for (int j = 0; j < COLS; j++)
            cout << setw(W) << results[TOTAL][i][j] / EXPERIMENTS;
        cout << endl;
    }
    return 0;
}

/* syntax examples:
auto start = high_resolution_clock::now()
auto end = high_resolution_clock::now()
auto duration = duration_cast<milliseconds>(end - start)
duration.count() references elapsed milliseconds
*/