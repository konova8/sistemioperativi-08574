import os
import sys

#quasi
def main():
    filesNum = {}
    for entry in os.listdir(sys.argv[1]):
        suffix = entry.split(".")[-1]
        if(suffix.isnumeric()):
            if suffix not in filesNum:
                filesNum[suffix] = []
            print("Inserisco "+entry+ " nel suffisso " + suffix)
            filesNum[suffix].append(entry)

    for file in sorted(filesNum):
        print(str(filesNum[file]))

if __name__ == '__main__':
    main()