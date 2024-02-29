import numpy as np

def read_matrix(size, filename):
    f = open(filename, 'r')
    A = np.zeros((size, size))
    
    f.close()
    return A

def check_matrix(size, filename):
    res = open(filename, 'r')
    A = read_matrix(size, 'matrix_A'+ str(size) + '.txt')
    B = read_matrix(size, 'matrix_B'+ str(size) + '.txt')
    C1 = read_matrix(size, 'matrix_C'+ str(size) + '.txt')
    C = np.matmul(A, B)
    res.write('Результат сравнения матриц размера: ' + str(size) + ' ' + str(np.array_equal(C, C1)))
    res.close()
    
if __name__ == "__main__":
    list_of_size = [10, 20, 50, 100, 200, 500, 750, 1000]
    list_of_filenames = ['matrix_A', 'matrix_B']
    for i in list_of_size:
        for j in list_of_filenames:
            check_matrix(i, j + str(i) + '.txt')