import os, sys

symInutili = []

def scan(path):
    for entry in os.scandir(path):
        if entry.is_dir():
            scan(entry.path)
        elif entry.is_symlink():
            if not os.path.exists(entry.path):
                symInutili.append(entry.path)

def main():
    scan(sys.argv[1])
    for entry in symInutili:
        print(entry)

if __name__ == '__main__':
    main()