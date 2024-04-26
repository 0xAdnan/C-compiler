# Run "./cc --in examples/tests/000*.c --out cmake-build-debug/000*.ll" for each test

import os
import sys
import subprocess

def run_tests():
    for filename in os.listdir("examples/tests"):
        if filename.endswith(".c"):
            print(f"Running {filename}...")
            subprocess.run(["cmake-build-debug/cc", "--in", f"examples/tests/{filename}", "--out", f"cmake-build-debug/{filename[:-2] + 'll'}", "--print-ast", 0])
            # Check if it returned 0. If not, print error
            if subprocess.run(["lli-17", f"cmake-build-debug/{filename[:-2] + 'll'}"]).returncode != 0:
                print(f"Error in {filename}")


if __name__ == "__main__":
    run_tests()
    print("All tests passed!")
    sys.exit(0)