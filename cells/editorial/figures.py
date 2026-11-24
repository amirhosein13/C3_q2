#!/usr/bin/env python3
"""Generates the SVG figures of the editorial from a small example grid."""
import os
G = [".......*.",
     "**..*.**.",
     "......***",
     ".*.**..*.",
     "...*.....",
     "........."]
n, m = len(G), len(G[0])
fr = [[0]*m for _ in range(n)]; to = [[0]*m for _ in range(n)]
for i in range(n):
    for j in range(m):
        if G[i][j] == '.':
            fr[i][j] = (i == 0 and j == 0) or (i and fr[i-1][j]) or (j and fr[i][j-1])
for i in range(n-1, -1, -1):
    for j in range(m-1, -1, -1):
        if G[i][j] == '.':
            to[i][j] = (i == n-1 and j == m-1) or (i+1 < n and to[i+1][j]) or (j+1 < m and to[i][j+1])
U = [[bool(fr[i][j] and to[i][j]) for j in range(m)] for i in range(n)]
cnt = {}
for i in range(n):
    for j in range(m):
        if U[i][j]: cnt[i+j] = cnt.get(i+j, 0)+1
def walk(i, j, down_first, ti, tj):
    p = [(i, j)]
    while (i, j) != (ti, tj):
        if down_first:
            if i+1 < n and U[i+1][j]: i += 1
            else: j += 1
        else:
            if j+1 < m and U[i][j+1]: j += 1
            else: i += 1
        p.append((i, j))
    return p
def back(i, j):
    p = [(i, j)]
    while (i, j) != (0, 0):
        if j and U[i][j-1]: j -= 1
        else: i -= 1
        p.append((i, j))
    return p[::-1]
L = walk(0, 0, True, n-1, m-1); R = walk(0, 0, False, n-1, m-1)
single = {(i, j) for i in range(n) for j in range(m) if U[i][j] and cnt[i+j] == 1}
single0 = set(single)

C = 44; PAD = 30
def svg(name, paths=(), marks=(), labels=(), diag=None, cross=()):
    W, H = m*C+2*PAD, n*C+2*PAD
    o = [f'<svg xmlns="http://www.w3.org/2000/svg" viewBox="0 0 {W} {H}" width="{W}" height="{H}" font-family="DejaVu Sans, sans-serif">']
    o.append('<defs><pattern id="h" width="6" height="6" patternUnits="userSpaceOnUse" patternTransform="rotate(45)"><line x1="0" y1="0" x2="0" y2="6" stroke="#c9c9c9" stroke-width="3"/></pattern></defs>')
    for i in range(n):
        for j in range(m):
            x, y = PAD+j*C, PAD+i*C
            if G[i][j] == '*': f = '#3b3f46'
            elif not U[i][j]: f = 'url(#h)'
            else: f = '#ffffff'
            if (i, j) in single: f = '#ffd54a'
            if diag is not None and i+j == diag and U[i][j]: f = '#d8ecff' if (i, j) not in single else f
            o.append(f'<rect x="{x}" y="{y}" width="{C}" height="{C}" fill="{f}" stroke="#9aa0a6" stroke-width="1"/>')
    for pts, col, off, dash in paths:
        d = ' '.join(f'{PAD+j*C+C/2+off},{PAD+i*C+C/2+off}' for i, j in pts)
        o.append(f'<polyline points="{d}" fill="none" stroke="{col}" stroke-width="5" stroke-linejoin="round" stroke-linecap="round" opacity="0.9" {dash}/>')
    for (i, j), col in marks:
        o.append(f'<circle cx="{PAD+j*C+C/2}" cy="{PAD+i*C+C/2}" r="{C*0.3}" fill="none" stroke="{col}" stroke-width="4"/>')
    for (i, j) in cross:
        x, y = PAD+j*C, PAD+i*C
        o.append(f'<path d="M{x+8},{y+8} L{x+C-8},{y+C-8} M{x+C-8},{y+8} L{x+8},{y+C-8}" stroke="#d32f2f" stroke-width="5"/>')
    for (i, j), t in labels:
        o.append(f'<text x="{PAD+j*C+C-6}" y="{PAD+i*C+14}" font-size="13" font-weight="bold" text-anchor="end" fill="#111">{t}</text>')
    o.append('</svg>')
    open(name, 'w').write('\n'.join(o))

# fig1: grid, useful cells, single blockers
svg('fig1.svg', labels=[((0, 0), 's'), ((n-1, m-1), 't')])
# fig2: leftmost (blue) and rightmost (red) paths
svg('fig2.svg', paths=[(L, '#1e66d0', 3, ''), (R, '#d93025', -3, '')], labels=[((0, 0), 's'), ((n-1, m-1), 't')])
# fig3: block a on L, new leftmost path through c, partners = L' ∩ R (non single)
Rs = set(R)
a = (3, 2)  # the cell of L we block in figure 3
assert a in L and a not in single
d = a[0]+a[1]; r, c = a[0]-1, a[1]+1
while not U[r][c]: r -= 1; c += 1
Lp = back(r, c)[:-1] + walk(r, c, True, n-1, m-1)
part = [p for p in Lp if p in Rs and p not in single]
best = (a, (r, c), Lp, part, d)
a, c, Lp, part, d = best
svg('fig3.svg', paths=[(R, '#d93025', -3, ''), (Lp, '#188038', 3, '')], marks=[(p, '#8e24aa') for p in part],
    cross=[a], labels=[(a, 'a'), (c, 'c'), ((0, 0), 's'), ((n-1, m-1), 't')], diag=d)
# fig4: 2 x 6 empty grid, cross-diagonal cut
G2 = ["......", "......"]
G, n, m = G2, 2, 6
U = [[True]*m for _ in range(n)]; single = {(0, 0), (1, 5)}
svg('fig4.svg', cross=[(0, 3), (1, 3)], labels=[((0, 0), 's'), ((1, 5), 't')])
print("single blockers:", sorted(single0))
print("a", a, "c", c, "partners", part, "diag", d)
print("L", L); print("R", R)
