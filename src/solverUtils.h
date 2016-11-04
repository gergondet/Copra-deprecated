// This file is part of ModelPreviewController.

// ModelPreviewController is free software: you can redistribute it and/or
// modify
// it under the terms of the GNU Lesser General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// ModelPreviewController is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU Lesser General Public License for more details.
//
// You should have received a copy of the GNU Lesser General Public License
// along with ModelPreviewController.  If not, see
// <http://www.gnu.org/licenses/>.

#pragma once

#include "QLDSolver.h"
#include "QuadProgSolver.h"
#include "SolverInterface.h"
#ifdef LSSOL_SOLVER_FOUND
#include "LSSOLSolver.h"
#endif

#include <memory>
#include <utility>

namespace mpc {

/**
 * Enum class that handles flag for selecting a qp solver.
 */
enum class SolverFlag {
    DEFAULT, /**< Default solver (QuadProgDense solver) */
#ifdef LSSOL_SOLVER_FOUND
    LSSOL, /**< Standford LSSOL solver */
#endif
    QLD, /**< Scilab QLD solver */
    QuadProgDense, /**< DenseMatrix version of QuadProg solver */
    // QuadProgSparse
};

/**
 * Helper function to get an unique pointer to a desired solver.
 * @param flag Flag of the solver.
 * @return An unique pointer to the desired solver.
 */
std::unique_ptr<SolverInterface> solverFactory(SolverFlag flag)
{
    switch (flag) {
#ifdef LSSOL_SOLVER_FOUND
    case SolverFlag::LSSOL:
        return std::make_unique<LSSOLSolver>();
#endif
    case SolverFlag::QLD:
        return std::make_unique<QLDSolver>();
    // case SolverFlag::QuadProgSparse:
    //    return std::make_unique<QuadProgSparseSolver>();
    case SolverFlag::QuadProgDense:
    default:
        return std::make_unique<QuadProgDenseSolver>();
    }
}

/**
 * Helper function to get a desired solver.
 * This should only be used by python (unique_ptr are not yet bindable)
 * @param flag Flag of the solver.
 * @return The desired solver.
 */
SolverInterface* pythonSolverFactory(SolverFlag flag)
{
    switch (flag) {
#ifdef LSSOL_SOLVER_FOUND
    case SolverFlag::LSSOL:
        return new LSSOLSolver;
#endif
    case SolverFlag::QLD:
        return new QLDSolver;
    case SolverFlag::QuadProgDense:
    default:
        return new QuadProgDenseSolver;
    }
}

} // namespace pc