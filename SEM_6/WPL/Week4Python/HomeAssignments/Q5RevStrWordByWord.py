"""
5. Write a Python class to reverse a string word by word.
"""

inp = "Hi word by word i have to rev"

class s:
    def rev(inp):
        words = inp.split(" ")
        for i in range(len(words)):
            words[i] = words[i][::-1]
        out = " ".join(words)
        print(out)

s.rev(inp)