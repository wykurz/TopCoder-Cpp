import glob
import os.path as path
import time

class Checker(object):
    def __init__(self, fname):
        self._fname = fname
        self._mtime = path.getmtime(self._fname)

    def run(self):
        mtime = path.getmtime(self._fname)
        if self._mtime < mtime:
            self._mtime = mtime
            return True
        return False

files = glob.glob('*.cpp')
assert len(files) == 1
checker = Checker(files[0])

def main():
    while True:
        if checker.run():
            return
        time.sleep(0.1)

try:
    main()
except KeyboardInterrupt:
    exit(1)
