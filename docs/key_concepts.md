## How random numbers work
- A random number engine is an object that generates a sequence of integer values, uniformly.
- Distributions are objects that generates a sequence of values according to some mathematical formula from some inputs.

## Static Libaries
What we're basically doing here is creating a static library of source (.cpp) files and headers (.h) that our app interfaces with.

## 'Discrete' Verlet Algorithm
This is used to compute positions and velocities. It is based on the taylor expansion, which we don't have to implement directly.
Note, we require the position of r_i at the next timestep to predict the velocity, which we can then use again to make a
better prediction of the position of r_i at the next timestep.

r_i(t + 1) = 2r_i(t) - r_i(t - 1) + a_i(t)*1^2
v_i(t + 1) = (r_i(t + 1) - r_i(t - 1)) / 2*(1^2)

The verlet algorithm:
    a_i(t) = derivative of r_i respect to t
    r_i(t + 1) = 2*r_i(t) - r_i(t - 1) + a_i(t)
    v_i(t + 1) = (r_i(t + 1) - r_i(t + 1)) / 2*(1^2)

What if we don't want to store r_i(t-1)? If we have N=1000000000 particles, that is going to take a lot of extra space.
We can reformulate the equations to use only the current timestep values.

r_i(t + 1) = r_i(t) + v_i(t) + 1/2*a_i(t)
v_i(t + 1) = v_i(t) + (a_i(t) + a_i(t + 1))/2
