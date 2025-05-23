#include "dpll_solver.h" // DPLL çözücü ve unitPropagation için
#include "visualizer.h"  // Çözümü ekrana yazdırmak için
#include "cnf_parser.h"  // parseCNF ve parseCNFFromStream için
#include <iostream>      // Giriş/çıkış işlemleri için
#include <string>        // std::string için
#include <set>           // std::set için
#include <limits>        // std::numeric_limits için

int main(int argc, char* argv[]) {
    CNFFormula f;
    std::string input_choice;
    bool valid_choice = false;

    // Kullanıcıdan giriş yöntemini seçmesini iste
    while (!valid_choice) {
        std::cout << "Giriş yöntemini seçin (dosya/terminal): ";
        std::cin >> input_choice;

        if (input_choice == "dosya" || input_choice == "terminal") {
            valid_choice = true;
        } else {
            std::cerr << "Geçersiz seçim. Lütfen 'dosya' veya 'terminal' yazın." << std::endl;
        }
        // Giriş tamponunu temizle (özellikle terminal girişi sonrası oluşabilecek sorunlar için)
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }

    try {
        if (input_choice == "dosya") {
            if (argc < 2) {
                std::cerr << "Kullanım: " << argv[0] << " dosya" << std::endl;
                std::cerr << "Dosya girişi seçildi ancak dosya yolu belirtilmedi." << std::endl;
                return 1;
            }
            std::string filename = argv[1];
            std::cout << "Dosya okunuyor: " << filename << std::endl;
            f = parseCNF(filename); // Dosyadan oku
        } else { // input_choice == "terminal"
            std::cout << "CNF problemini terminalden girin (örnek: p cnf 3 2\\n1 2 0\\n-1 3 0):" << std::endl;
            std::cout << "Girişi bitirmek için Ctrl+D (Linux/macOS) veya Ctrl+Z (Windows) tuşlarına basın." << std::endl;
            f = parseCNFFromStream(std::cin); // Terminalden oku
        }

        std::cout << "---- CNF Okundu ----" << std::endl;
        // İsterseniz okunan formülü görmek için printCNF(f); çağırabilirsiniz.

        std::set<int> solution;
        std::set<int> initial_assigned;

        bool result = DPLL(f, initial_assigned, solution);

        if (result) {
            std::cout << "Çözüm bulundu!" << std::endl;
            printSolution(f, solution); // Çözüm atamalarını ekrana yaz
        } else {
            std::cout << "Çözüm yok (UNSAT)." << std::endl;
        }

        std::cout << "Program sorunsuz sona erdi (main'den çıkıyor)." << std::endl;
        std::cout << std::flush; // Çıktı tamponunu temizle ve tüm çıktıları bas

    } catch (const std::exception& ex) {
        std::cerr << "Hata: " << ex.what() << std::endl;
        return 1; // Hata durumunda programdan çık
    }
    return 0; // Başarılı çıkış
}
