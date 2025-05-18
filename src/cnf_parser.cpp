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

std::set<int> unitPropagation(CNFFormula& formula) {
    std::set<int> assigned_literals;
    bool changed = true;

    while (changed) {
        changed = false;
        int unit_literal = 0;

        for (const auto& clause : formula.clauses) {
            if (clause.literals.empty()) {
                formula.clauses.assign(1, Clause{});
                formula.numClauses = 1;
                return assigned_literals;
            }
            if (clause.literals.size() == 1) {
                int lit = clause.literals[0];
                if (assigned_literals.count(lit)) {
                    continue;
                }
                if (assigned_literals.count(-lit)) {
                    formula.clauses.assign(1, Clause{});
                    formula.numClauses = 1;
                    return assigned_literals;
                }
                unit_literal = lit;
                break;
            }
        }

        if (unit_literal == 0) {
            break;
        }
        
        assigned_literals.insert(unit_literal);
        changed = true;

        std::vector<Clause> new_clauses;

        for (const auto& clause : formula.clauses) {
            bool satisfied = false;
            Clause new_clause;
            for (int lit : clause.literals) {
                if (lit == unit_literal) {
                    satisfied = true;
                    break;
                }
                if (lit == -unit_literal) {
                    continue;
                }
                new_clause.literals.push_back(lit);
            }

            if (satisfied) {
                continue;
            }

            if (new_clause.literals.empty() && !clause.literals.empty()) {
                formula.clauses.assign(1, Clause{});
                formula.numClauses = 1;
                return assigned_literals;
            }
            
            new_clauses.push_back(new_clause);
        }
        
        formula.clauses = new_clauses;
        formula.numClauses = formula.clauses.size();

    }

    return assigned_literals;
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