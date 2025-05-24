#include "visualizer.h"
#include <iostream>

// Çözümü ekrana yazdıran fonksiyon
void printSolution(const CNFFormula &formula, const std::set<int> &solution)
{
    std::cout << "Cozum (degisken atamalari):" << std::endl;
    // Tüm değişkenler için atama durumunu yazdır
    for (int v = 1; v <= formula.numVars; ++v)
    {
        if (solution.count(v))
        {
            std::cout << "x" << v << " = 1" << std::endl;
        }
        else if (solution.count(-v))
        {
            std::cout << "x" << v << " = 0" << std::endl;
        }
        else
        {
            std::cout << "x" << v << " = (atanmamis)" << std::endl;
        }
    }
}