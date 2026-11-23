#!/usr/bin/env python3
"""Checks that every GroupMin regex selects exactly the tests TPS assigned to that subtask.
usage: verify_score_type.py <tests.zip> <score_type.txt> <tests/mapping> [subtasks.json]"""
import sys, json, re, zipfile
zf, st, mp = sys.argv[1:4]
sj = sys.argv[4] if len(sys.argv) > 4 else None
names = zipfile.ZipFile(zf).namelist()
ins = sorted(n[:-3] for n in names if n.endswith('.in'))
outs = sorted(n[:-4] for n in names if n.endswith('.out'))
ok = True
if ins != outs or len(names) != 2 * len(ins) or any('/' in n for n in names):
    print("ZIP: .in/.out mismatch, extra files or folders"); ok = False
params = json.load(open(st))
order, want = [], {}
for line in open(mp):
    s, t = line.split()
    if s not in want: order.append(s); want[s] = set()
    want[s].add(t)
if len(order) != len(params):
    print("number of groups != number of subtasks"); ok = False
if sj:
    sub = json.load(open(sj))['subtasks']
    order = sorted(sub, key=lambda k: sub[k]['index'])
    tot = 0
    for s, (sc, _) in zip(order, params):
        tot += sc
        if sub[s]['score'] != sc: print(f"score mismatch for {s}: {sub[s]['score']} vs {sc}"); ok = False
    if tot != 100: print("total score", tot, "!= 100"); ok = False
for s, (sc, rx) in zip(order, params):
    r = re.compile(rx)
    got_match = {t for t in ins if r.match(t)}          # CMS uses re.match
    got_full = {t for t in ins if r.fullmatch(t)}
    good = got_match == want[s] == got_full
    ok &= good
    print(f"{s:10s} score={sc:3d} regex={rx:28s} tests={len(got_match):3d} expected={len(want[s]):3d} {'OK' if good else 'MISMATCH'}")
    if not good:
        print("   extra:", sorted(got_match - want[s]), "missing:", sorted(want[s] - got_match))
print("ALL OK" if ok else "FAILED"); sys.exit(0 if ok else 1)
