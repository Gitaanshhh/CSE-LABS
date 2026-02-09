PRIMES = [3, 13, 23, 43, 53]
cells = [10, -100, 100, -2]

def max_score_bt(cells):
    n = len(cells)

    def rec(i):
        if i >= n:
            return 0
        score = rec(i + 1)
        for p in PRIMES:
            if i + p < n:
                t = dfs(i + p)
                if t > score:
                    score = t
                    i = i + p
        return cells[i] + score

    return rec(0)
