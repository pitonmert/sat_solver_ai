#include "dpll_solver.h"
#include <iostream>
#include <vector>
#include <set>

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


bool DPLL(CNFFormula& formula, std::set<int>& assigned, std::set<int>& solution) {
    CNFFormula original_formula_at_call_start = formula;
    std::set<int> original_assigned_at_call_start = assigned;

    std::set<int> newly_assigned_from_prop = unitPropagation(formula);

    for (int lit : newly_assigned_from_prop) {
        assigned.insert(lit);
    }

    if (formula.clauses.size() == 1 && formula.clauses[0].literals.empty()) {
        assigned = original_assigned_at_call_start;
        formula = original_formula_at_call_start;
        return false;
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
        assigned = original_assigned_at_call_start;
        formula = original_formula_at_call_start;
        return false;
    }

    CNFFormula formula_for_true_branch = formula;
    std::set<int> assigned_for_true_branch = assigned;

    int decision_literal_true = chosen_var;
    formula_for_true_branch.clauses.push_back(Clause{std::vector<int>{decision_literal_true}});
    assigned_for_true_branch.insert(decision_literal_true);

    bool sat_in_true_branch = DPLL(formula_for_true_branch, assigned_for_true_branch, solution);

    if (sat_in_true_branch) {
        assigned = assigned_for_true_branch;
        return true;
    }

    CNFFormula formula_for_false_branch = original_formula_at_call_start;
    std::set<int> assigned_for_false_branch = original_assigned_at_call_start;

    std::set<int> newly_assigned_from_prop_for_false = unitPropagation(formula_for_false_branch);
    for (int lit : newly_assigned_from_prop_for_false) {
        assigned_for_false_branch.insert(lit);
    }

    if (formula_for_false_branch.clauses.size() == 1 && formula_for_false_branch.clauses[0].literals.empty()) {
         assigned = original_assigned_at_call_start;
         formula = original_formula_at_call_start;
         return false;
    }

    int chosen_var_for_false_branch = 0;
    for (int v = 1; v <= formula_for_false_branch.numVars; ++v) {
        if (assigned_for_false_branch.count(v) == 0 && assigned_for_false_branch.count(-v) == 0) {
            chosen_var_for_false_branch = v;
            break;
        }
    }
    if (chosen_var_for_false_branch == 0 && !formula_for_false_branch.clauses.empty()) {
        assigned = original_assigned_at_call_start;
        formula = original_formula_at_call_start;
        return false;
    }


    int decision_literal_false = -chosen_var;
    formula_for_false_branch.clauses.push_back(Clause{std::vector<int>{decision_literal_false}});
    assigned_for_false_branch.insert(decision_literal_false);

    bool sat_in_false_branch = DPLL(formula_for_false_branch, assigned_for_false_branch, solution);

    if (sat_in_false_branch) {
        assigned = assigned_for_false_branch;
        return true;
    }

    assigned = original_assigned_at_call_start;
    formula = original_formula_at_call_start;
    return false;
}
