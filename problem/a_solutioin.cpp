#include <algorithm>
#include <iostream>
#include <vector>

struct library_t {
  unsigned long long id;
  unsigned long long n_books;
  unsigned long long signup_time;
  unsigned long long ships_per_day;
  unsigned long long score;
  std::vector<int> books;
};

struct output_v {
  unsigned long long id;
  unsigned long long n_books;
  std::vector<int> b_ids;
};

unsigned long long n_books;
unsigned long long n_libraries;
unsigned long long n_days;
std::vector<int> book_value;
std::vector<library_t> libraries;

bool compare(unsigned long long a, unsigned long long b) {
  if (book_value[a] > book_value[b])
    return true;
  if (book_value[a] == book_value[b] && a > b)
    return true;
  return false;
}

unsigned long long library_score(unsigned long long a, unsigned long long b,
                                 unsigned long long c, int d, int e) {
  return (a - b) * c * (d + e);
}

bool compare_lib(library_t &l1, library_t &l2) { return l1.score > l2.score; }

void write_output(std::vector<output_v> &v) {
  std::cout << v.size() << std::endl;
  for (auto l : v) {
    std::cout << l.id << " " << l.n_books << std::endl;
    for (auto j : l.b_ids) {
      std::cout << j << " ";
    }
    std::cout << l.b_ids[v.size() - 1] << std::endl;
  }
}

int main() {

  // Input data

  // Read input
  std::cin >> n_books;
  std::cin >> n_libraries;
  std::cin >> n_days;

  unsigned long long aux, signup, ships, aux4;

  for (unsigned long long i = 0; i < n_books; i++) {
    std::cin >> aux;
    book_value.push_back(aux);
  }

  for (unsigned long long i = 0; i < n_libraries; i++) {
    std::cin >> aux;
    std::cin >> signup;
    std::cin >> ships;
    std::vector<int> aux5;
    for (unsigned long long j = 0; j < aux; j++) {
      std::cin >> aux4;
      aux5.push_back(aux4);
    }

    std::sort(aux5.begin(), aux5.end(), compare);
    libraries.push_back(
        {i, aux, signup, ships,
         library_score(n_days, signup, ships, book_value[aux5[0]],
                       book_value[aux5.back()]),
         aux5});
  }

    

}