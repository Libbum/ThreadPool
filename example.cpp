#include <iostream>
#include <vector>
#include <chrono>

#include "ThreadPool.hpp"

int main()
{

    ThreadPool<PRIORITY> pool(2);
    std::vector< std::future<int> > results;

    for(int i = 0; i < 11; ++i) {
        results.push_back(
            pool.enqueue(i, [i] {
                std::cout << "hello " << i << std::endl;
                std::this_thread::sleep_for(std::chrono::seconds(1));
                std::cout << "world " << i << std::endl;
                return i*i;
            })
        );
    }

    for(auto && result: results)
        std::cout << result.get() << ' ';
    std::cout << std::endl;

    return 0;
}
