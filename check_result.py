import numpy as np

def read_matrix(size, filename):
    A = np.zeros((size, size))
    with open(filename) as file:
        lines = [int(line.rstrip()) for line in file]
    k = 0    
    for i in range(size):
        for j in range(size):
            A[i][j] = int(lines[k])
            k +=1
    file.close()
    return A

def check_matrix(size):
    res = open('check_result', 'a')
    A = read_matrix(size, 'matrix_A'+ str(size) + '.txt')
    B = read_matrix(size, 'matrix_B'+ str(size) + '.txt')
    C1 = read_matrix(size, 'matrix_C'+ str(size) + '.txt')
    C = np.matmul(A, B)
    res.write('Результат сравнения матриц размера: ' + str(size) + ' ' + str(np.array_equal(C, C1)) + '\n')
    res.close()
    
if __name__ == "__main__":
    list_of_size = [10, 20, 50, 100, 200, 500, 750, 1000]
    for i in list_of_size:
        check_matrix(i)