import hashlib
import collections


PASSCODE = "hijkl"
PASSCODE = "ihgpwlah"
#PASSCODE = "kglvqrro"
#PASSCODE = "ulqzkmiv"
PASSCODE = "qljzarfv"


def open_doors(path: str) -> str:
    h = hashlib.md5(f"{PASSCODE}{path}".encode()).hexdigest()
    result = ""
    for c, d in zip(h, "UDLR"):
        if c in "bcdef":
            result += d
    return result


def path2coords(path: str) -> tuple[int, int]:
    y = path.count('D') - path.count('U')
    x = path.count('R') - path.count('L')
    return (x, y)


def solve_pt1():
    queue = collections.deque()
    queue.append("")
    while len(queue) > 0:
        path = queue.popleft()
        for p in open_doors(path):
            x, y = path2coords(path + p)
            if (x == 3 and y == 3):
                print(path + p)
                return
            if (0 <= x <= 3 and 0 <= y <= 3):
                queue.append(path + p)


def solve_pt2():
    queue = collections.deque()
    queue.append("")
    max_len = 0
    while len(queue) > 0:
        path = queue.popleft()
        for p in open_doors(path):
            x, y = path2coords(path + p)
            if (x == 3 and y == 3):
                max_len = len(path) + 1
                print(max_len)
            elif (0 <= x <= 3 and 0 <= y <= 3):
                queue.append(path + p)
    print(max_len)



if __name__ == "__main__":
    solve_pt1()
    solve_pt2()