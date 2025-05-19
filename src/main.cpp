#include "dpll_solver.h"
#include <iostream>

int main() {
    std::string dosya = "test/example.cnf";

    try {
        std::cout << "Dosya okunuyor: " << dosya << std::endl;
        CNFFormula f = parseCNF(dosya);

        std::cout << "---- CNF Okundu ----" << std::endl;

        std::set<int> solution;
        std::set<int> initial_assigned;

        bool result = DPLL(f, initial_assigned, solution);

        if (result) {
            std::cout << "Çözüm bulundu! Atamalar: ";
            for (int lit : solution) std::cout << lit << " ";
            std::cout << std::endl;
        } else {
            std::cout << "Çözüm yok (UNSAT)." << std::endl;
        }

    } catch (const std::exception& ex) {
        std::cerr << "Hata: " << ex.what() << std::endl;
    }
    return 0;
}