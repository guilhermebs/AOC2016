import hashlib

DOOR_ID = "wtnhxymk"
#DOOR_ID = "abc"


def solve_pt1():
    i = 0
    password = ""
    while len(password) < 8:
        hash = hashlib.md5(f"{DOOR_ID}{i}".encode())
        if hash.hexdigest().startswith("00000"):
            password += hash.hexdigest()[5]
        i += 1
    print(password)


def solve_pt2():
    i = 0
    password = 8*["_",]
    while "_" in password:
        hash = hashlib.md5(f"{DOOR_ID}{i}".encode()).hexdigest()
        target = int(hash[5], base=16)
        #print(i, hash, target)
        if hash.startswith("00000") and target < 8 and password[target] == "_":
            password[target] = hash[6]
            print(password)
        i += 1
    print(''.join(password))


if __name__ == "__main__":
    #solve_pt1()
    solve_pt2()