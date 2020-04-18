import os, sys


def main():
    print("Enter result file:", end = " ")
    result_file = input()
    print("Enter file extension:", end = " ")
    extension = input()
    if extension[0] == '.':
        extension = extension[1::]

    files = get_filse_by_extend(extension)
    write_in_file(result_file, files)




def get_filse_by_extend(extension):
    path = os.getcwd()
    files = []
    if (extension == '*'):
        return os.listdir(path)
    for file in os.listdir(path):
        if file.endswith(extension):
            files.append(file)
    return files


def write_in_file(file_name, value):
    path = os.getcwd()
    path_for_file = os.path.join(path, file_name)
    if os.path.exists(path_for_file):
        with open(path_for_file, 'r') as file:
            old_file = file.read() + ' \n'
        with open(path_for_file, 'w') as file:
            file.write(old_file)
            file.write(' '.join(value))
    else:
        with open(path_for_file, 'w') as file:
            file.write(' '.join(value))



if __name__ == '__main__':
    main()

