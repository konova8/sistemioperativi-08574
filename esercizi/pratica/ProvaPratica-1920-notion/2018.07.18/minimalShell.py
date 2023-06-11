import os
import subprocess
import sys

def main():
    while True:
        try:
            cmd = (input("> "))
        except EOFError:
            #se riceve ^D termina
            print("\n")
            break 
        if cmd=="logout":
            break
        argv = cmd.split(" ")
        try:
            subprocess.run(argv, shell=False)
        except:
            print("Not permitted")
if __name__ == '__main__':
    main()