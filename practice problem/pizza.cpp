#include <iostream>
#include <vector>
#include <algorithm>
#include <iterator>

using namespace std;

vector<int> choosePizza(int maxSlides, vector<int>& sortSlides, vector<int>& res) {

    // greedy
    // keep maxSlides always >= 0
    // if element in sortSlides is visited, we mark it as -1
    for (int i = 0; i < sortSlides.size(); i++) {
        if (maxSlides - sortSlides[i] >= 0 && sortSlides[i] != -1) {
            maxSlides -= sortSlides[i];
            res.push_back(sortSlides[i]);
            sortSlides[i] = -1;
        }
    }
    return res;

}

int main() {

    // read and write from files
    freopen("input", "r", stdin);
    freopen("output", "w", stdout);
    int maxSlides = 0;
    int pizzaTypes = 0;
    vector<int> originSlides;
    cin >> maxSlides >> pizzaTypes;
    for (int i = 0; i < pizzaTypes; i++) {
        int size;
        cin >> size;
        originSlides.push_back(size);
    }


    // init
    // int maxSlides = 17;
    // int pizzaTypes = 4;
    // vector<int> originSlides;
    // originSlides.push_back(2);
    // originSlides.push_back(5);
    // originSlides.push_back(6);
    // originSlides.push_back(8);

    // sort the origin slides from big to small
    vector<int> sortSlides(originSlides);
    sort(sortSlides.rbegin(), sortSlides.rend());

    // use the greedy algorithm, choose the largest scale 
    vector<int> res;
    res = choosePizza(maxSlides, sortSlides, res);

    // find the chosen pizza index in origin slides
    sort(res.begin(), res.end());

    // output
    cout << res.size() << endl;
    for (auto i : res) {
        auto iter = find(originSlides.begin(), originSlides.end(), i);
        cout << distance(originSlides.begin(), iter) << " ";
    }

    return 0;
}