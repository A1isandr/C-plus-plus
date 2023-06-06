#include <iostream>
#include <tuple>

std::tuple<int, int, int> find_lcm(int n1, int n2) {
    // вычисление LCM, c1 и c2
    int lcm = 1, c1 = 2, c2 = 3;
    return std::make_tuple(lcm, c1, c2);
}

int main() {
    int n1 = 12, n2 = 18;
    auto [lcm, c1, c2] = find_lcm(n1, n2);

    std::cout << "LCM: " << lcm << std::endl;
    std::cout << "c1: " << c1 << std::endl;
    std::cout << "c2: " << c2 << std::endl;

    return 0;
}