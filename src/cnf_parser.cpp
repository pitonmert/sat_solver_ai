#include "cnf_parser.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <set>
#include <algorithm>
#include <cctype>
#include <stdexcept>


CNFFormula parseCNF(const std::string& filename) {
    std::ifstream infile(filename);
    if (!infile) {
        throw std::runtime_error("Dosya açılamadı: " + filename);
    }

    std::string line;
    CNFFormula formula;
    formula.numVars = 0;
    formula.numClauses = 0;

    int actualClauseCount = 0;

    while (std::getline(infile, line)) {
        if (line.empty() || line[0] == 'c') {
            continue;
        }
        if (line[0] == 'p') {
            std::istringstream iss(line);
            std::string dummy1, dummy2;
            iss >> dummy1 >> dummy2 >> formula.numVars >> formula.numClauses;
            continue;
        }

        std::istringstream iss(line);
        int literal;
        Clause clause;
        std::string token;
        while (iss >> token) {
            bool valid = true;
            size_t start = 0;
            if (token[0] == '-' || token[0] == '+') start = 1;
            for (size_t i = start; i < token.size(); ++i) {
                if (!std::isdigit(token[i])) {
                    valid = false;
                    break;
                }
            }
            if (!valid) {
                throw std::runtime_error("Geçersiz karakter klauz satırında: " + token);
            }

            literal = std::stoi(token);

            if (literal == 0) {
                break;
            }
            clause.literals.push_back(literal);
        }

        if (!clause.literals.empty()) {
            formula.clauses.push_back(clause);
            actualClauseCount++;
        }
    }

    if (actualClauseCount != formula.numClauses) {
        throw std::runtime_error("Dosyadaki klauz sayısı (" + std::to_string(actualClauseCount) +
                                 ") p satırındaki sayı ile eşleşmiyor (" + std::to_string(formula.numClauses) + ").");
    }

    infile.close();

    return formula;
}

void printCNF(const CNFFormula& formula) {
    std::cout << "Değişken sayısı: " << formula.numVars << std::endl;
    std::cout << "Klauz sayısı: " << formula.clauses.size() << std::endl;
    for (const auto& clause : formula.clauses) {
        for (int lit : clause.literals) {
            std::cout << lit << " ";
        }
        std::cout << "0" << std::endl;
    }
}
