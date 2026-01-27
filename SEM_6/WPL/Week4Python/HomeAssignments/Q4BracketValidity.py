"""
4. Write a Python class to find validity of a string of parentheses, '(', ')', '{', '}', '['
and ']. These brackets must be close in the correct order, for example "()" and
"()[]{}" are valid but "[)", "({[)]" and "{{{" are invalid.
"""

inp = "()()()"

d = {"(":")", "[":']', "{":"}"}
stack = []

for i in inp:
    if i in d.keys():
        stack.append(i)
    else :
        top = stack.pop()
        if i != d[top]:
            print("Invalid")
            exit()

print("Valid")