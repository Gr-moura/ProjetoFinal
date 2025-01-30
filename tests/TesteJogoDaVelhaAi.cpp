#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "../include/JogoDaVelha.hpp"
#include "../include/JogoDaVelhaAi.hpp"
#include "doctest.h"

#include <iostream>
using namespace std;

int fatorial(int n)
{
    if (n == 0)
        return 1;
    return n * fatorial(n - 1);
};

TEST_CASE("Testando a classe JogoDaVelhaAi") {}