import os

def delete_files():
    test_directory = "examples/tests"
    extensions = [".c.expected", ".c.tags", ".c.otags"]

    for filename in os.listdir(test_directory):
        if any(filename.endswith(ext) for ext in extensions):
            file_path = os.path.join(test_directory, filename)
            os.remove(file_path)
            print(f"Deleted {filename}")

if __name__ == "__main__":
    delete_files()
    print("Deletion complete.")