#include "dpll_solver.h"
#include "visualizer.h"
#include <iostream>

int main(int argc, char* argv[]) {
    if (argc < 2) {
        std::cerr << "Kullanım: " << argv[0] << " <cnf dosya yolu>" << std::endl;
        return 1;
    }
    std::string dosya = argv[1];

    try {
        std::cout << "Dosya okunuyor: " << dosya << std::endl;
        CNFFormula f = parseCNF(dosya);

        std::cout << "---- CNF Okundu ----" << std::endl;

        std::set<int> solution;
        std::set<int> initial_assigned;

        bool result = DPLL(f, initial_assigned, solution);

        if (result) {
            std::cout << "Çözüm bulundu!" << std::endl;
            printSolution(f, solution);
        } else {
            std::cout << "Çözüm yok (UNSAT)." << std::endl;
        }

        std::cout << "Program sorunsuz sona erdi (main'den çıkıyor)." << std::endl;
        std::cout << std::flush;

    } catch (const std::exception& ex) {
        std::cerr << "Hata: " << ex.what() << std::endl;
    }
    return 0;
}
