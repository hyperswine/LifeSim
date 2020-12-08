import numpy as np
import matplotlib.pyplot as plt

# p = [0.1, 0.2, 0.1, 0.3, 0.3]
# x = ['lamo', 'ayy_lamo', 'lmAo', 'Ayy Lmao', 'LAMO']

def metropolis(N=1000):
    # initialize: choose random x and choose another y for which Q(x|y) is gotten.

    for t in range(N):
        # get another x' from the sample
        x_prime = np.random.normal(0, 1, 1)
        # calculate acceptance ratio alpha = f(x')/f(x_t) = P(x')/P(x_t).

        # generate some u in [0, 1]
        # if u <= alpha, accept
        # else reject
        pass


def graph_normal_dist():
    # x = [float(i/1000) for i in range(1000)]
    x = np.random.normal(0, 1, size=100)
    # y = norm.pdf(x, 0, 1)
    plt.figure('Normal Distribution')
    # plots against the index of the list
    plt.scatter(x, x)
    plt.show()


# graph_normal_dist()

states = [i for i in range(100)]
p = [float(1/100)] * 100
def markov_chain(epochs=1000):
    
    for i in range(epochs):
        x = np.random.sample(states)
        print(x)
        

values = np.random.randn(100)
plt.hist(values, bins=20)
plt.show()
