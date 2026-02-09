"""
MS OT q on balancing chem eqs
"""

from sympy import Matrix, lcm
import re

def parse_compound(compound):
    counts = {}
    parts = re.findall(r'([A-Z][a-z]*)(\d*)', compound)
    for elem, num in parts:
        counts[elem] = counts.get(elem, 0) + (int(num) if num else 1)
    return counts

def balanceEquation(chemicalEquation):
    left, right = chemicalEquation.split(" - ")
    left_compounds = left.split(" + ")
    right_compounds = right.split(" + ")
    
    compounds = left_compounds + right_compounds
    
    element_set = []
    compound_maps = []
    
    for comp in compounds:
        m = parse_compound(comp)
        compound_maps.append(m)
        for e in m:
            if e not in element_set:
                element_set.append(e)
    print("ele set ", element_set)
    print("comp maps ", compound_maps)

    matrix = []
    for elem in element_set:
        row = []
        for i, comp in enumerate(compound_maps):
            val = comp.get(elem, 0)
            if i >= len(left_compounds):
                val = -val
            row.append(val)
        matrix.append(row)
    
    mat = Matrix(matrix)
    nullspace = mat.nullspace()[0]
    
    lcm_val = lcm([term.q for term in nullspace])
    result = [int(term * lcm_val) for term in nullspace]
    
    return result

inp = "NH4ClO4 + Al - Al2O3 + HCl + H2O + N2"
print(balanceEquation(inp))