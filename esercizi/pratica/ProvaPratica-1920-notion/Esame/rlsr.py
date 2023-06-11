import os, sys

filemap = {}

def scan(path):
	for entry in os.scandir(path):
		if entry.is_dir():
			scan(entry.path)
		else:
			if(entry.name not in filemap):
				filemap[entry.name] = []
			filemap[entry.name].append(path)

def main():
	os.chdir(sys.argv[1])
	scan(".")
	for entry in filemap:
		filemap[entry].sort()
	for entry in filemap:
		print(entry + " " + str(filemap[entry]))

if __name__ == '__main__':
	main()
