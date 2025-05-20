#pragma once
#include <vector>
#include <set>
#include <string>
#include <stdexcept>

struct Clause {
    std::vector<int> literals;
};

struct CNFFormula {
    int numVars;
    int numClauses;
    std::vector<Clause> clauses;
};

CNFFormula parseCNF(const std::string& filename);

std::set<int> unitPropagation(CNFFormula& formula);

void printCNF(const CNFFormula& formula);
