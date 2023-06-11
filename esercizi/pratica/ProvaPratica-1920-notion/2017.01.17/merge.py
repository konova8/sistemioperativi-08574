import os
import sys
import shutil

def main():
	for fileA in os.listdir(sys.argv[1]):
		if fileA not in os.listdir(sys.argv[2]):
			pathA = sys.argv[1] + "/" + fileA
			shutil.move(pathA, sys.argv[3])
		else:
			lastmodA = os.stat(sys.argv[1] + "/" + fileA).st_mtime
			lastmodB = os.stat(sys.argv[2] + "/" + fileA).st_mtime			
			if lastmodA > lastmodB:
				pathA = sys.argv[1] + "/" + fileA
				shutil.move(pathA, sys.argv[3])
			else:
				pathB = sys.argv[2] + "/" + fileA
				shutil.move(pathB, sys.argv[3])
	for fileB in os.listdir(sys.argv[2]):
		if fileB not in os.listdir(sys.argv[3]):
			pathB = sys.argv[2] + "/" + fileB
			shutil.move(pathB, sys.argv[3])
if __name__ == '__main__':
    main()
