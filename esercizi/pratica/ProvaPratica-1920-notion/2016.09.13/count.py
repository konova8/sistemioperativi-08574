import os
import sys

def scanCount(path):
    countDir = 0
    countFile = 0
    for entry in os.scandir(path):
        if entry.is_dir() and entry.name != "." and entry.name !="..":
            recCount = scanCount(entry.name)
            countDir += recCount[0]
            countFile += recCount[1]
        elif not entry.is_symlink():
            countFile+=1
    return [countDir,countFile]
def main():
    totDir, totFile = scanCount(sys.argv[1])
    print(f'Tot Directory: {totDir}\nTot File: {totFile}')
            

if __name__ == '__main__':
    main()