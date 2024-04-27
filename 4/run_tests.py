import os
import sys
import subprocess

def modify_file_for_testing(file_path):
    with open(file_path, 'r') as file:
        lines = file.readlines()

    has_print = any('print' in line for line in lines)
    has_include = any(line.strip().startswith('#include') for line in lines)

    includes = [line for line in lines if line.strip().startswith('#include')]
    lines = [line for line in lines if not line.strip().startswith('#include')]

    if has_print:
        lines.insert(0, "int printf(const char *format, ...);\n")

    with open(file_path, 'w') as file:
        file.writelines(lines)

    return includes, has_print

def restore_file(file_path, includes, had_print):
    with open(file_path, 'r') as file:
        lines = file.readlines()

    if had_print:
        lines.pop(0)

    lines = includes + lines

    with open(file_path, 'w') as file:
        file.writelines(lines)

def run_tests():
    cc_path = "/home/adnan/Documents/col728lab/compiler_assignment/4/build/cc"
    test_directory = "examples/tests"
    timeout_duration = 10  
    results_file_path = os.path.join(os.path.dirname(__file__), "test_results.txt")

    if not os.path.exists(cc_path):
        print(f"Executable not found: {cc_path}")
        sys.exit(1)

    with open(results_file_path, "w") as file:
        file.write(f"|{'Filename'.center(20)}|{'Result'.center(15)}|{'Optimized Result'.center(20)}|\n")
        file.write(f"|{'-'*20}|{'-'*15}|{'-'*20}|\n")

        files = [f for f in os.listdir(test_directory) if f.endswith(".c")]
        sorted_files = sorted(files)

        results = {}

        for filename in sorted_files:
            file_path = os.path.join(test_directory, filename)
            includes, had_print = modify_file_for_testing(file_path)
            output_path = os.path.join(test_directory, f"{filename[:-2]}.c.ll")
            print(f"Running {filename}...", flush=True)

            try:
                subprocess.check_call([cc_path, "--in", file_path, output_path], timeout=timeout_duration)
                result = "Passed"
            except (subprocess.TimeoutExpired, subprocess.CalledProcessError):
                result = "Error"

            try:
                subprocess.check_call([cc_path, "--in", file_path, "--opt-const-prop", "--opt-deadcode", "--opt-al-sim", output_path], timeout=timeout_duration)
                optimized_result = "Passed"
            except (subprocess.TimeoutExpired, subprocess.CalledProcessError):
                optimized_result = "Error"

            results[filename] = (result, optimized_result)

            file.write(f"|{filename.center(20)}|{result.center(15)}|{optimized_result.center(20)}|\n")
            restore_file(file_path, includes, had_print)

        file.write(f"|{'-'*20}|{'-'*15}|{'-'*20}|\n")

        regressions = {k: v for k, v in results.items() if v[0] == "Passed" and v[1] == "Error"}
        if regressions:
            file.write("\nRegressions detected in the following tests:\n")
            for test, result in regressions.items():
                file.write(f"{test}: Passed -> Error\n")

if __name__ == "__main__":
    run_tests()
    with open(os.path.join(os.path.dirname(__file__), "test_results.txt"), "a") as file:
        file.write("\nAll tests processed!\n")
    sys.exit(0)