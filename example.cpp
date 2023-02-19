#include <vector>
#include <random>
#include "cluster.h";
int main() {
    std::vector<std::vector<float>> inputs;
    std::random_device rnd;
    std::mt19937 gen(rnd());
    std::uniform_real_distribution<> dist(0.,1.);

    for(int i = 0; i < 200; i++) {
        auto temp = std::vector<float>(12);
        std::generate(temp.begin(), temp.end(), [&gen, &dist]() { return dist(gen); });
        inputs.emplace_back(temp);
    }
    auto clusters = cluster(inputs, 3, 50);
}