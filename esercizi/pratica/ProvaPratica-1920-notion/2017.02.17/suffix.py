import os

dictionary = {}
no_suffix = []

def main():
    for entry in os.scandir():
        if entry.is_file():
            if "." in entry.name:
                point = entry.name.index(".")
                suffix = entry.name[point:]
                if suffix not in dictionary:
                    dictionary[suffix] = []
                dictionary[suffix].append(entry.name)
            else:
                no_suffix.append(entry.name)

    for key in sorted(dictionary):
        print(key + "\t" + str(dictionary[key]))
    print(no_suffix)

if __name__ == '__main__':
    main()