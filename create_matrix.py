import random

def create_matrix(size, filename):
    random.seed
    f = open(filename, 'w')
    for i in range(size*size):
        f.write(str(random.randint(-10, 10))+'\n')
        if(i == size*size-1):
            f.write(str(random.randint(-10, 10)))
    f.close()
    
if __name__ == "__main__":
    list_of_size = [10, 20, 50, 100, 200, 500, 750, 1000]
    list_of_filenames = ['matrix_A', 'matrix_B']
    for i in list_of_size:
        for j in list_of_filenames:
            create_matrix(i, j + str(i) + '.txt')