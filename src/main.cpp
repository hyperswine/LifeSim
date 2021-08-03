#include <iostream>
#include <vector>
#include <random>
#include <chrono>
#include <cmath>
#include <algorithm>
#include <cstdarg>

using std::vector;

// float get_velocities(vector<vector<float>>& vel){
// for each speed, rand() % 2 == 0

// }

#define END_CHAR -100000000

class Vec
{
    vector<float> vec;
    int size = 0;

public:
    Vec();
    Vec(const float vals...)
    {
        // add all values to users
        va_list args;
        va_start(args, vals);
        while (vals != END_CHAR)
        {
            // add val to values
            vec.push_back(va_arg(args, float));
        }
    }
    ~Vec();
    Vec(const Vec &to_copy)
    {
        for (auto &t : to_copy.vec)
        {
            vec.push_back(t);
        }
    }
    Vec(vector<float> &v)
    {
        vec = v;
    }

    /**
     * Only adds according to the first vector's size, truncates the end of the second vector
     */
    Vec operator+(const Vec &m)
    {
        vector<float> res;
        for (int i = 0; i < size; i++)
        {
            res.push_back(m.vec[i] + vec[i]);
        }

        return Vec(res);
    }
    Vec operator-(const Vec &m)
    {
        vector<float> res;
        for (int i = 0; i < size; i++)
        {
            res.push_back(m.vec[i] - vec[i]);
        }

        return Vec(res);
    }
    Vec operator*(const Vec &m)
    {
        vector<float> res;
        for (int i = 0; i < size; i++)
        {
            res.push_back(m.vec[i] * vec[i]);
        }

        return Vec(res);
    }
    Vec operator/(const Vec &m)
    {
        vector<float> res;
        for (int i = 0; i < size; i++)
        {
            res.push_back(m.vec[i] / vec[i]);
        }

        return Vec(res);
    }

    // negative and over indexing allowed
    float &operator[](int index)
    {
        index = index % size;
        return vec[index];
    }
};

class Matrix
{
    vector<Vec> values;
    vector<int> size{0, 0};

public:
    Matrix();
    // varags of vectors(rows)
    Matrix(const vector<float> &vals...)
    {
        va_list args;
        va_start(args, vals);
        while (1)
        {
            if (vals[0] == END_CHAR)
                break;
            // add val to values
            values.push_back(va_arg(args, float));
        }
    }
    ~Matrix();

    // arithmetic
    Matrix operator+(const Matrix &m)
    {
        // check if n x m is the same
        if (m.size[0] != size[0] || m.size[1] != size[1])
            return Matrix();

        // elementwise addition of each row
    }
    Matrix operator-(const Matrix &m);
    Matrix operator*(const Matrix &m);
    Matrix operator/(const Matrix &m);
};

int main()
{
    // 100 particles
    int n_particles = 100;

    // initial positions and velocities
    vector<vector<float>> positions;
    vector<vector<float>> velocities;
    vector<float> masses;
    vector<vector<float>> forces;

    // generate random positions and velocities
    auto curr_time = std::chrono::system_clock::now();
    // get current time
    // std::mt19937 engine(curr_time);

    for (int i = 0; i < 100; i++)
    {
        // generate random value for position in 3D [0,0,0] is the origin
        // all values >= 0 and < 100 mm
        float pos_x = rand() / (RAND_MAX / 100);
        float pos_y = rand() / (RAND_MAX / 100);
        float pos_z = rand() / (RAND_MAX / 100);

        std::cout << "pushing positions" << std::endl;
        vector<float> pos{pos_x, pos_x, pos_z};
        positions.push_back(pos);

        // generate values for velocity
        float speed_x = rand() / (RAND_MAX / 10);
        float speed_y = rand() / (RAND_MAX / 10);
        float speed_z = rand() / (RAND_MAX / 10);

        // make some of them negative if possible
        if (rand() % 2 == 0)
            speed_x = -speed_x;
        if (rand() % 2 == 0)
            speed_y = -speed_y;
        if (rand() % 2 == 0)
            speed_z = -speed_z;

        std::cout << "pushing velocities" << std::endl;
        vector<float> vel{speed_x, speed_y, speed_z};
        velocities.push_back(vel);
    }

    // f_i = m_i*a_i

    std::cout << "printing positions" << std::endl;
    for (auto &p : positions)
    {
        for (auto &p_ : p)
            std::cout << p_ << std::endl;
    }

    std::cout << "printing velocities" << std::endl;
    for (auto &v : velocities)
    {
        for (auto &v_ : v)
            std::cout << v_ << std::endl;
    }

    // test

    // collision when particles reach 1mm radius
    // all particles around 1mm diameter
    // collision when particles reach 1mm within boundary or surpass boundary position next step

    // 100 timesteps
    // for (int i = 0; i < 100; i++)
    // {
    //     vector<vector<float>> prev_forces;
    //     // velocity verlet
    //     for (int j = 0; j < 100; j++)
    //     {
    //         // at each timestep, compute each force on each particle NON BONDING energy functions for the current
    //         // columb potential energy
    //         // U_i = 1/(4 pi eps)*q_iq_j/r_ij
    //         // van der vaals
    //         // U_i = eps ((R/r_ij)^{12} - 2(R/r_ij)^6)
    //         // F_i = U_i
    //         // auto potential = 1(4*PI)

    //         // calculate force on x -> r_ij(x)
    //         // calculate force on y -> r_ij(x)
    //         // calculate force on z -> r_ij(x)

    //         // QUESTIONS : what the hell is epsilon?
    //         //

    //         vector<float> forces{0, 0, 0};
    //         vector<float> mass_k{masses[j], masses[j], masses[j]};
    //         auto accel = std::transform(forces.begin(), forces.end(), mass_k.begin(), mass_k.end());

    //         // Extension: only compute forces for particles within neighbor list

    //         // v(t+1) = v(t) + h/(2m(t))*(f(t)+f(t+1))
    //         auto next_velocity = velocities[j] + 1 / (2 * masses[j]) * (prev_forces[j] + forces)

    //         // x(t+1) = x(t) + h v(t) + h^2/(2m)f(t)
    //     }
    // }

    // no complex inter particle forces

    return 0;
}