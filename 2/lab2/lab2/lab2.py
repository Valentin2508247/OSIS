
RESULT_FILE_NAME = 'result.txt'

file_name = input('Please, enter file name ')

try:
    with open(file_name, 'r') as file:
        value = file.read()
        with open(RESULT_FILE_NAME, 'w') as file:
            file.write(value)
            print('File "{}" copy to "{}"'.format(file_name, RESULT_FILE_NAME))
except FileNotFoundError:
    print('File "{}" not found'.format(file_name))
