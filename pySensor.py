import sys
import time


if __name__ == "__main__":
    n = 0
    while True:
        sys.stdout.write(f"|{n}")
        n += 1
        sys.stdout.flush()
        time.sleep(1)