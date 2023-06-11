import os

count = []

def main():
    for direntry in os.scandir("/proc"):
        if direntry.is_dir() and direntry.name.isnumeric():
            for dirdirentry in os.scandir(direntry.path):
                if(dirdirentry.name == "fd"):
                    try:
                        c = 0
                        for fild in os.listdir(dirdirentry.path):
                            c += 1
                        count.append([c,direntry.name])
                    except:
                        continue
    count.sort()
    counOrdered = count[::-1]
    for pcs in counOrdered:
        print("Process: " + str(pcs[1]) + " is using " + str(pcs[0]) + " fd")
    
if __name__ == '__main__':
    main()