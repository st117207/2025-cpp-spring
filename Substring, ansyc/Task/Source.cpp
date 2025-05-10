#include <iostream>
#include <string>
#include <vector>
#include <future>
#include <algorithm>
#include <chrono>
using namespace std::chrono;

int Find(const std::string& what, const std::string& s, int a, int b) {
    int count = 0;
    int what_len = what.length();
    int s_len = s.length();


    for (int i = a; i <= b - what_len; ++i) {
        if (s.substr(i, what_len) == what) {
            ++count;
        }
    }

    return count;
}

int Find_thread(const std::string& what, const std::string& s, int threads, int first_index) {
    int s_len = s.length();
    int what_len = what.length();

    int size = s_len / threads;
    int a = first_index * size;
    int b = (first_index == threads - 1) ? s_len : (first_index + 1) * size;

    b = std::min(b + what_len - 1, s_len);

    return Find(what, s, a, b);
}

int MultiThreadFind(const std::string& what, const std::string& s, int threads) {

    std::vector<std::future<int>> futures;

    for (int i = 0; i < threads; ++i) {
        futures.push_back(async(Find_thread, what, s, threads, i));

    }

    int total_count = 0;
    for (auto& fut : futures) {
        total_count += fut.get();
    }

    return total_count;
}


int main() {
    setlocale(LC_ALL, "ru");
    std::string what = "abc";
    std::string s = "abcabcabcabceeeabc!!abc??abcab";
    int threads = 12;

    auto t1 = steady_clock::now();
    int count = MultiThreadFind(what, s, threads);
    auto t2 = steady_clock::now();

    std::cout << "Число вхождений " << count << std::endl;
    std::cout << duration_cast<milliseconds> (t2 - t1).count() << " ms " << std::endl;
    return 0;
}