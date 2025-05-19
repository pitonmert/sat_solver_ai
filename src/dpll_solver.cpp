#include "dpll_solver.h"
#include <iostream>


bool DPLL(CNFFormula& formula, std::set<int>& assigned, std::set<int>& solution) {
    std::set<int> newly_assigned_from_prop = unitPropagation(formula);

    for (int lit : newly_assigned_from_prop) assigned.insert(lit);

    for (const auto& clause : formula.clauses) {
        if (clause.literals.empty()) {
            for (int lit : newly_assigned_from_prop) assigned.erase(lit);
            return false;
        }
    }

    if (formula.clauses.empty()) {
        solution = assigned;
        return true;
    }

    int chosen_var = 0;
    for (int v = 1; v <= formula.numVars; ++v) {
        if (assigned.count(v) == 0 && assigned.count(-v) == 0) {
            chosen_var = v;
            break;
        }
    }
    if (chosen_var == 0) {
        for (int lit : newly_assigned_from_prop) assigned.erase(lit);
        return false;
    }

    int decision_literal_true = chosen_var;
    formula.clauses.push_back(Clause{std::vector<int>{decision_literal_true}});
    assigned.insert(decision_literal_true);

    bool sat_in_true_branch = DPLL(formula, assigned, solution);

    assigned.erase(decision_literal_true);
    formula.clauses.pop_back();

    if (sat_in_true_branch) {
        return true;
    }

    for (int lit : newly_assigned_from_prop) assigned.erase(lit);

    int decision_literal_false = -chosen_var;
    formula.clauses.push_back(Clause{std::vector<int>{decision_literal_false}});
    assigned.insert(decision_literal_false);

    bool sat_in_false_branch = DPLL(formula, assigned, solution);

    assigned.erase(decision_literal_false);
    formula.clauses.pop_back();

    if (sat_in_false_branch) {
        return true;
    }

    for (int lit : newly_assigned_from_prop) assigned.erase(lit);

    return false;
}