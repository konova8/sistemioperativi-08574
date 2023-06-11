import os
import sys

filemap = {".c": [], ".h": [], "makefile": []}

def scan(path, match):
    for entry in os.scandir(path):
        if entry.is_dir():
            scan(entry.path, match)
        elif entry.name.endswith(match):
            num_line = sum(1 for line in open(path+"/"+entry.name))
            entry = [path + "/" + entry.name , num_line]
            filemap[match].append(entry)
def main():
    scan(sys.argv[1], ".c")
    scan(sys.argv[1], ".h")
    scan(sys.argv[1], "makefile")

    totalc=0
    for entry in filemap[".c"]:
        print(entry[0] + ": "+ str(entry[1]))
        totalc+=entry[1]
    print("Total .c : " + str(totalc))

    totalh=0
    for entry in filemap[".h"]:
        print(entry[0] + ": "+ str(entry[1]))
        totalh+=entry[1]
    print("Total .h : " + str(totalh))

    totalm=0
    for entry in filemap["makefile"]:
        print(entry[0] + ": "+ str(entry[1]))
        totalm+=entry[1]
    print("Total .h : " + str(totalm))

    print("Total source: "+ str(totalc+totalh+totalm))


if __name__ == "__main__":
    main()