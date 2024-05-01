import os

deleted = 0
def delete_file_if_contains_hello(file_path):
    try:
        with open(file_path, 'r') as file:
            file_content = file.read()
            if "do" in file_content:
                os.remove(file_path)
                print(f"File '{file_path}' deleted because it contains 'Hello'.")
                # deleted += 1
            else:
                pass
                # print(f"File '{file_path}' does not contain 'Hello'.")
    except FileNotFoundError:
        print(f"File '{file_path}' not found.")
    except Exception as e:
        print(f"An error occurred: {e}")

def delete_files_with_hello_in_directory(directory):
    try:
        for file_name in os.listdir(directory):
            file_path = os.path.join(directory, file_name)
            if os.path.isfile(file_path):
                delete_file_if_contains_hello(file_path)
    except Exception as e:
        print(f"An error occurred while processing files in directory '{directory}': {e}")

# Example usage:
directory_path = "examples/tests/"
delete_files_with_hello_in_directory(directory_path)
print(deleted)
