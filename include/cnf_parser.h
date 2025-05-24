#pragma once
#include <vector>
#include <set>
#include <string>
#include <stdexcept>
#include <istream>

struct Clause
{
    std::vector<int> literals;
};

struct CNFFormula
{
    int numVars;
    int numClauses;
    std::vector<Clause> clauses;
};

CNFFormula parseCNF(const std::string &filename);
CNFFormula parseCNFFromStream(std::istream &input_stream);
std::set<int> unitPropagation(CNFFormula &formula);
void printCNF(const CNFFormula &formula);