#pragma once
#include "cnf_parser.h"
#include <set>
#include <vector>

bool DPLL(CNFFormula& formula, std::set<int>& assigned, std::set<int>& solution);

std::set<int> unitPropagation(CNFFormula& formula);
