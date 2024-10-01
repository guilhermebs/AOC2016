import hashlib
import re

SALT = "abc"
SALT = "ihaygndm"


def solve_pt1():
    i = 0
    triplets = []
    triplets_regex = re.compile(r"(.)\1\1")
    keys = []
    while len(keys) < 64:
        hash = hashlib.md5(f"{SALT}{i}".encode())
        if t := re.search(triplets_regex, hash.hexdigest()):
            triplets.append((t[1] * 5, i))
        to_remove = []
        for tr, ti in triplets:
            if (ti + 1000 >= i > ti and tr in hash.hexdigest()):
                keys.append((ti, tr[0]))
                to_remove.append((tr, ti))
        
        for r in to_remove:
            triplets.remove(r)

        i += 1
    keys = sorted(keys)
    print(keys[-1][0])


def solve_pt2():
    i = 0
    triplets = []
    triplets_regex = re.compile(r"(.)\1\1")
    keys = []
    while len(keys) < 64:
        hash = hashlib.md5(f"{SALT}{i}".encode()).hexdigest()
        for _ in range(2016):
            hash = hashlib.md5(hash.encode()).hexdigest()
        if t := re.search(triplets_regex, hash):
            triplets.append((t[1] * 5, i))
        to_remove = []
        for tr, ti in triplets:
            if (i > ti + 1000):
                to_remove.append((tr, ti))
            elif (i > ti and len(keys) < 64 and tr in hash):
                keys.append((ti, tr[0]))
                to_remove.append((tr, ti))
                print(keys)
        for r in to_remove:
            triplets.remove(r)
        i += 1
    keys = sorted(keys)
    print(keys[-1][0])


if __name__ == "__main__":
    solve_pt1()
    solve_pt2()