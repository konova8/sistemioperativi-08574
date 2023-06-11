import os
import sys

def main():
    list = []
    for (root,dirs,files) in os.walk(sys.argv[1], topdown = True):
        for file in files:
            stat = os.lstat(root+"/"+file)
            entry = [stat.st_ino, root+"/"+file]
            list.append(entry)
    while(len(list) > 0):
        found = False
        toPrint = ""
        entry = list.pop(0)
        inode = entry[0]
        todelete = []
        for elem in list:
            if elem[0] == inode:
                found = True
                toPrint += " " + elem[1]
                todelete.append(elem)
        if found:
            print(entry[1] + toPrint)
            for item in todelete:
                list.remove(item)

if __name__ == "__main__":
    main()