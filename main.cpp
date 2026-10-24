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

int main() {
    // declaration
    int results[ROWS][COLS];
    string t;
    vector<string> v;
    list<string> l;
    set<string> s;
    string file = "names.txt";

    cout << setw(W) << "Operations" << setw(W) << "Vector" << setw(W) << "List" << setw(W) << "Set" << endl;
    cout << setw(W) << "READING";
    //READING
    for (int i = 0; i < COLS; i++)
    {
        /* code */

    
        // file input
        ifstream fin;
        fin.open(file);
        
        if (fin.good()) {
            switch(i) {
            case 0: 
            // vector:
            // Start timing
            auto start = high_resolution_clock::now();
            while (getline(fin, t)) {
                v.push_back(t);
            }
            // End timing
            auto end = high_resolution_clock::now();
            // Calculate duration
            auto vec_read = duration_cast<nanoseconds>(end - start);
            cout << setw(W) << vec_read.count();
            fin.close();
        } 
        else
        {
            cout << "File not found.\n";
            return 1;
        }
            
        // list:
        fin.open(file);
        if (fin.good())
        {
            // Start timing
            auto start = high_resolution_clock::now();
            while (getline(fin, t)) {
                l.push_back(t);
            }
            // End timing
            auto end = high_resolution_clock::now();
            // Calculate duration
            auto lst_read = duration_cast<nanoseconds>(end - start);
            cout << setw(W) << lst_read.count();
            fin.close();
        } 
        else
        {
            cout << "File not found.\n";
            return 1;
        }

        // set:
        fin.open(file);
        if (fin.good())
        {
            // Start timing
            auto start = high_resolution_clock::now();
            while (getline(fin, t)) {
                s.insert(t);
            }
            // End timing
            auto end = high_resolution_clock::now();
            // Calculate duration
            auto set_read = duration_cast<nanoseconds>(end - start);
            cout << setw(W) << set_read.count() << endl;
            fin.close();
        } 
        else
        {
            cout << "File not found.\n";
            return 1;
        }

    }        
    //SORTING
    // vector:
    // Start timing
    auto start = high_resolution_clock::now();
    sort(v.begin(), v.end());
    // End timing
    auto end = high_resolution_clock::now();
    // Calculate duration
    auto vec_sort = duration_cast<nanoseconds>(end - start);

    // list:
    // Start timing
    start = high_resolution_clock::now();
    l.sort();
    // End timing
    end = high_resolution_clock::now();
    // Calculate duration
    auto lst_sort = duration_cast<nanoseconds>(end - start);
    
    // set:
    // the set's value is -1 since a set is already sorted.
    auto set_sort = -1;


    //INSERTING
    // vector:
    // Start timing
    start = high_resolution_clock::now();
    auto v_it = v.begin();
    // make the iterater point to the middle
    for (int i = 0; i <= v.size() / 2; i++)
    {
        v_it++;
    }
    v.insert(v_it, TESTCODE);
    // End timing
    end = high_resolution_clock::now();
    // Calculate duration
    auto vec_insert = duration_cast<nanoseconds>(end - start);

    // list:
    // Start timing
    start = high_resolution_clock::now();
    auto l_it = l.begin();
    // make the iterater point to the middle
    for (int i = 0; i <= l.size() / 2; i++)
    {
        l_it++;
    }
    l.insert(l_it, TESTCODE);
    // End timing
    end = high_resolution_clock::now();
    // Calculate duration
    auto lst_insert = duration_cast<nanoseconds>(end - start);
    
    // set:
    // Start timing
    start = high_resolution_clock::now();
    s.insert(TESTCODE); // into the set
    // End timing
    end = high_resolution_clock::now();
    // Calculate duration
    auto set_insert = duration_cast<nanoseconds>(end - start);
    
    //DELETING
    // vector:
    // Start timing
    start = high_resolution_clock::now();
    v.erase(v.begin() + v.size() / 2);
    // End timing
    end = high_resolution_clock::now();
    // Calculate duration
    auto vec_del = duration_cast<nanoseconds>(end - start);

    // list:
    // Start timing
    start = high_resolution_clock::now();
    l_it = l.begin();
    // make the iterater point to the middle
    for (int i = 0; i <= l.size() / 2; i++)
    {
        l_it++;
    }
    l.erase(l_it);
    // End timing
    end = high_resolution_clock::now();
    // Calculate duration
    auto lst_del = duration_cast<nanoseconds>(end - start);
    
    // set:
    // Start timing
    start = high_resolution_clock::now();
    auto s_it = s.begin();
    // make the iterater point to the middle
    for (int i = 0; i <= s.size() / 2; i++)
    {
        s_it++;
    }
    s.erase(s_it);
    // End timing
    end = high_resolution_clock::now();
    // Calculate duration
    auto set_del = duration_cast<nanoseconds>(end - start);

    // Output the table of duration in nanoseconds
    cout << setw(W) << "SORTING" << setw(W) << vec_sort.count() << setw(W) << lst_sort.count() << setw(W) << set_sort << endl;
    cout << setw(W) << "INSERTING" << setw(W) << vec_insert.count() << setw(W) << lst_insert.count() << setw(W) << set_insert.count() << endl;
    cout << setw(W) << "DELETING" << setw(W) << vec_del.count() << setw(W) << lst_del.count() << setw(W) << set_del.count() << endl;

    return 0;
}

/* syntax examples:
auto start = high_resolution_clock::now()
auto end = high_resolution_clock::now()
auto duration = duration_cast<milliseconds>(end - start)
duration.count() references elapsed milliseconds
*/