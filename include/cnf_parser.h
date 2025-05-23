#pragma once
#include <vector>
#include <set>
#include <string>
#include <stdexcept>
#include <istream> // std::istream için gerekli

struct Clause {
    std::vector<int> literals;
};

struct CNFFormula {
    int numVars;
    int numClauses;
    std::vector<Clause> clauses;
};

// Dosyadan CNF formülü okuyan fonksiyon
CNFFormula parseCNF(const std::string& filename);

// Bir input stream'den (örneğin dosya veya terminal) CNF formülü okuyan yeni fonksiyon
CNFFormula parseCNFFromStream(std::istream& input_stream);

// Unit Propagation fonksiyonu (dpll_solver.cpp'ye taşınacak, burada sadece bildirim)
std::set<int> unitPropagation(CNFFormula& formula);

// CNF formülünü ekrana yazdıran yardımcı fonksiyon
void printCNF(const CNFFormula& formula);
