import subprocess
import sys


def search(folder):
    counter = 0
    for line in sys.argv:
        if folder in line:
            searcherlist = line.split("/home/")
            searcher = folder + searcherlist[1].split(":")[0] + "/"
            search(searcher)
            counter += 1
    if counter > 0 :
        print(folder + " " + str(counter))
    

def main():
    search("/home/")

if __name__ == "__main__":
    main()