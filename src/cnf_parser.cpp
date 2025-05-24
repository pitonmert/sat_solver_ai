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

CNFFormula parseCNFFromStream(std::istream &input_stream)
{
    std::string line;
    CNFFormula formula;
    formula.numVars = 0;
    formula.numClauses = 0;

    int actualClauseCount = 0;
    bool p_line_found = false;

    while (std::getline(input_stream, line))
    {
        if (line.empty() || line[0] == 'c')
        {
            continue;
        }
        if (line[0] == 'p')
        {
            if (p_line_found)
            {
                throw std::runtime_error("Birden fazla 'p' satiri bulundu. CNF formati gecersiz.");
            }
            std::istringstream iss(line);
            std::string dummy1, dummy2;
            iss >> dummy1 >> dummy2 >> formula.numVars >> formula.numClauses;
            if (iss.fail() || dummy1 != "p" || dummy2 != "cnf" || formula.numVars <= 0 || formula.numClauses < 0)
            {
                throw std::runtime_error("Gecersiz 'p' satiri formati. Beklenen: p cnf <degisken_sayisi> <klauz_sayisi>");
            }
            p_line_found = true;
            continue;
        }

        if (!p_line_found)
        {
            throw std::runtime_error("Klauzlar 'p' satirindan once geldi. CNF formati gecersiz.");
        }

        std::istringstream iss(line);
        int literal;
        Clause clause;
        std::string token;
        while (iss >> token)
        {
            bool valid = true;
            size_t start = 0;
            if (token[0] == '-' || token[0] == '+')
                start = 1;
            for (size_t i = start; i < token.size(); ++i)
            {
                if (!std::isdigit(token[i]))
                {
                    valid = false;
                    break;
                }
            }
            if (!valid)
            {
                throw std::runtime_error("Gecersiz karakter klauz satirinda: " + token + " (Sadece sayilar ve 0 beklenir)");
            }

            literal = std::stoi(token);

            if (literal == 0)
            {
                break;
            }
            if (std::abs(literal) > formula.numVars)
            {
                throw std::runtime_error("Klauzda tanimlanmamis degisken kullanildi: " + std::to_string(literal) + ". Maksimum degisken: " + std::to_string(formula.numVars));
            }
            clause.literals.push_back(literal);
        }

        if (!clause.literals.empty() || (literal == 0 && line.find_first_not_of(" \t\r\n") != std::string::npos))
        {
            formula.clauses.push_back(clause);
            actualClauseCount++;
        }
    }

    if (p_line_found && actualClauseCount != formula.numClauses)
    {
        throw std::runtime_error("Dosyadaki klauz sayisi (" + std::to_string(actualClauseCount) +
                                 ") p satirindaki sayi ile eslesmiyor (" + std::to_string(formula.numClauses) + ").");
    }
    if (!p_line_found)
    {
        throw std::runtime_error("CNF formatinda 'p' satiri bulunamadi.");
    }

    return formula;
}

CNFFormula parseCNF(const std::string &filename)
{
    std::ifstream infile(filename);
    if (!infile)
    {
        throw std::runtime_error("Dosya acilamadi: " + filename);
    }
    return parseCNFFromStream(infile);
}

void printCNF(const CNFFormula &formula)
{
    std::cout << "Degisken sayisi: " << formula.numVars << std::endl;
    std::cout << "Klauz sayisi: " << formula.clauses.size() << std::endl;
    for (const auto &clause : formula.clauses)
    {
        for (int lit : clause.literals)
        {
            std::cout << lit << " ";
        }
        std::cout << "0" << std::endl;
    }
}