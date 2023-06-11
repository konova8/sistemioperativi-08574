import os
import subprocess

def shell():
    while True:
        try:
            cmd = input(">")
        except EOFError:
            break
        if cmd == "logout":
            break
        else:
            cmd = cmd.split(" ")
            subprocess.run(cmd, shell=False)
    return

if __name__ == '__main__':
    shell()