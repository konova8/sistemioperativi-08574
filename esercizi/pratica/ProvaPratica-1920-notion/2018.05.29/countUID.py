import os
import sys

id_map = {}

def main():
    for direntry in os.scandir("/proc"):
        if direntry.is_dir():
            for dirdirentry in os.scandir(direntry.path):
                if dirdirentry.name == "status":
                    fd = open(dirdirentry.path, "r")
                    lines = fd.readlines()
                    b = False
                    for line in lines:
                        if line.startswith("State"):
                            try:
                                line.index("(running)")
                                b=True
                            except:
                                b = False
                        if b == True and line.startswith("UID"):
                            id = line.split("\t")
                            for i in range(1, 5):
                                if id[i].endswith("\n"):
                                    id[i] = id[i].replace("\n", "")
                                if id[i] not in id_map:
                                    id_map[id[i]] = [0, 0, 0, 0]
                                id_map.get(id[i])[i - 1] += 1
    return

if __name__ == '__main__':
    main()