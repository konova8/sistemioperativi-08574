import os
import sys

def list_to_string(argv):
    str = []
    command = ""
    for i in argv:
        if(i!="//"):
            command = command + i + " "
        else:
            str.append(command[:-1])
            command = ""
    str.append(command[:-1])
    return str

def main():
    commands = list_to_string(sys.argv[1:])
    for i in commands:
        command = "" + i
        command = command.split(" ")
        pid = os.fork()
        if pid == 0:
            if(len(command) == 1):
                os.execlp(command[0], command[0])
            else:
                os.execlp(command[0], command[0], command[1])                
    for i in commands:
        os.wait()

if __name__ == "__main__":
    main()