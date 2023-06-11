import os
import sys

filemap = {}

def scan(path):
    for entry in os.scandir(path):
        if entry.is_dir():
            scan(entry.path)
        else:
            file = open(entry.path, "r", encoding='cp437')
            str = file.read()
            if str.startswith("#!"):
                list = str.split("/n")
                if list[0] in filemap:
                    filemap[list[0]].append(entry.path)
                else:
                    filemap[list[0]] = [entry.path]
def main():
    scan(sys.argv[1])
    for name in filemap:
        n = ""
        for i in filemap[name]:
            n = n + " " + i
        print(name + n)

if __name__ == '__main__':
    main()