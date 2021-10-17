from sklearn.datasets import make_regression
from matplotlib import pyplot as plt
import numpy as np
from sklearn.linear_model import LinearRegression

# Functions
def gram_schmidt(a):
    q = []
    for i in range(len(a)):
        #orthogonalization
        q_tilde = a[i]
        for j in range(len(q)):
            q_tilde = q_tilde - (q[j] @ a[i])*q[j]
        #Test for dependennce
        if np.sqrt(sum(q_tilde**2)) <= 1e-10:
            print('Vectors are linearly dependent.')
            print('GS algorithm terminates at iteration ', i+1)
            return q
        #Normalization
        else:
            q_tilde = q_tilde / np.sqrt(sum(q_tilde**2))
            q.append(q_tilde)
    print('Vectors are linearly independent.')
    return q

def QR_factorization(A):
    Q_transpose = np.array(gram_schmidt(A.T))
    R = Q_transpose @ A
    Q = Q_transpose.T
    return Q, R

def back_subst(R,b_tilde):
    n = R.shape[0]
    x = np.zeros(n)
    for i in reversed(range(n)):
        x[i] = b_tilde[i]
        for j in range(i+1,n):
            x[i] = x[i] - R[i,j]*x[j]
        x[i] = x[i]/R[i,i]
    return x

def solve_via_backsub(A,b):
    Q,R = QR_factorization(A)
    b_tilde = Q.T @ b
    x = back_subst(R,b_tilde)
    return x

#########

# # Least squares problem
# A = np.array([[2,0],[-1,1],[0,2]])
# b = np.array([1,0,-1])
# x_hat = np.array([1/3, -1/3])
# r_hat = A @ x_hat - b
# print(np.linalg.norm(r_hat))
# x = np.array([1/2, -1/2]) #other value of x
# r = A @ x - b
# print(np.linalg.norm(r))
# print(np.linalg.inv(A.T @ A) @ A.T @ b)
# print(np.linalg.pinv(A) @ b)
# print((A.T @ A) @ x_hat - A.T @ b) #Check that normal equations hold
# # Principio da ortogonalidade
# z = np.array([-1.1,2.3])
# print(A @ z).T @ r_hat)
# z = np.array([5.3, -1.2])
# print((A @ z).T @ r_hat)

# # Resolvendo problemas de quadrados mínimos
# A = np.random.normal(size = (100,20))
# b = np.random.normal(size = 100)
# x1 = solve_via_backsub(A,b)
# x2 = np.linalg.inv(A.T @ A) @ (A.T @ b)
# x3 = np.linalg.pinv(A) @ b
# print(np.linalg.norm(x1-x2))
# print(np.linalg.norm(x2-x3))
# print(np.linalg.norm(x3-x1))

# Exemplo página 234
n = 10 # número de lâmpadas
# posições (x,y) das lâmpadas e altura acima do chão
lamps = np.array([[4.1 ,20.4, 4],
    [14.1, 21.3, 3.5],
    [22.6, 17.1,6], 
    [5.5 ,12.3, 4.0], 
    [12.2, 9.7, 4.0], 
    [15.3, 13.8, 6],
    [21.3, 10.5, 5.5], 
    [3.9 ,3.3, 5.0], 
    [13.1, 4.3, 5.0], 
    [20.3,4.2, 4.5]]) 

N = 25 # grid size
m = N*N # Número de pixels
# construct m x 2 matrix with coordinates of pixel centers
pixels = np.hstack([np.outer(np.arange(0.5,N,1),np.ones(N)).reshape(m,1), np.outer(np.ones(N),np.arange(0.5,N,1)).reshape(m,1)])
# The m x n matrix A maps lamp powers to pixel intensities.
# A[i,j] is inversely proportional to the squared distance of
# lamp j to pixel i.
A = np.zeros((m,n))
for i in range(m):
    for j in range(n):
        A[i,j] = 1.0 / (np.linalg.norm(np.hstack([pixels[i,:], 0]) - lamps[j,:])**2)

A = (m / np.sum(A)) * A # scale elements of A
# Least squares solution
x = solve_via_backsub(A, np.ones(m))
rms_ls = (sum((A @ x - 1)**2)/m)**0.5
print(rms_ls)
import matplotlib.pyplot as plt
plt.ion()
plt.hist(A @ x, bins = 25)
plt.show()
plt.pause(10)
# Intensity if all lamp powers are one
rms_uniform = (sum((A @ np.ones(n) - 1)**2)/m)**0.5
print(rms_uniform)
plt.hist(A @ np.ones(n), bins = 25)
plt.show()
plt.pause(10)
