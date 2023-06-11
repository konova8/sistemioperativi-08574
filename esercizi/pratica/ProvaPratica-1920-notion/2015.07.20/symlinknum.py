import os,sys

symLink = {}

def scan(path):
    for entry in os.scandir(path):
        if entry.is_dir():
            scan(entry.path)
        elif entry.is_symlink():
            if entry.path not in symLink:
                symLink[entry.path] = 0
            symLink[entry.path]+=1

def main():
    if(not sys.argv[1:]):
        return
    scan(sys.argv[1])
    max = -1
    name = ""
    for entry in sorted(symLink):
        if symLink[entry] > max:
            max = symLink[entry]
            name = entry
    if max != -1: 
        print(f'{name} has {max} symlink')
    else:
        print("No symlink found")
if __name__ == '__main__':
    main()