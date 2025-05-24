#include "dpll_solver.h"
#include "visualizer.h"
#include "cnf_parser.h"
#include <iostream>
#include <string>
#include <set>
#include <limits>

int main(int argc, char* argv[]) {
    CNFFormula f;
    std::string input_choice;
    bool valid_choice = false;

    if (argc > 1) { // Eğer komut satırı argümanı varsa (dosya yolu gibi)
        std::string filename = argv[1];
        try {
            std::cout << "Dosya okunuyor: " << filename << std::endl;
            f = parseCNF(filename);
        } catch (const std::exception& ex) {
            std::cerr << "Hata: " << ex.what() << std::endl;
            return 1;
        }
    } else { // Komut satırı argümanı yoksa, kullanıcıya sor
        while (!valid_choice) {
            std::cout << "Giriş yöntemini seçin (dosya/terminal): ";
            std::cin >> input_choice;

            if (input_choice == "dosya" || input_choice == "terminal") {
                valid_choice = true;
            } else {
                std::cerr << "Geçersiz seçim. Lütfen 'dosya' veya 'terminal' yazın." << std::endl;
            }
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }

        try {
            if (input_choice == "dosya") {
                std::cerr << "Dosya girişi seçildi ancak dosya yolu belirtilmedi." << std::endl;
                std::cerr << "Kullanım: " << argv[0] << " <cnf dosya yolu>" << std::endl;
                return 1;
            } else { // input_choice == "terminal"
                std::cout << "CNF problemini terminalden girin (örnek: p cnf 3 2\\n1 2 0\\n-1 3 0):" << std::endl;
                std::cout << "Girişi bitirmek için Ctrl+D (Linux/macOS) veya Ctrl+Z (Windows) tuşlarına basın." << std::endl;
                f = parseCNFFromStream(std::cin);
            }
        } catch (const std::exception& ex) {
            std::cerr << "Hata: " << ex.what() << std::endl;
            return 1;
        }
    }

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

    return 0;
}