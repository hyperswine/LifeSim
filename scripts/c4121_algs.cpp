// Some imperative scripts for algorithms in COMP4121.
// By including "C4121", one may call these functions directly
#include <random>
#include <vector>

inline static int roll_p(int p){
    std::mt19937 mt_rng;
    std::uniform_int_distribution<> dist(0, p);
    int val = dist(mt_rng);

    return val;
}

/**
 * database access algorithm
 * In - N, number of processes
 *    - T, number of timesteps
 * Out - number of distinct processes that accessed the database
 */
int acc_contention(const int N, const int T){
    using namespace std;
    int n_succeeded = 0;
    vector<bool> proc;
    for(int i = 0; i < N; i++) proc.push_back(false);

    for (int i = 0; i < T; i++){
        int P = proc.size();
        // for all processes, roll a N-sided dice and if only one of them succeeds, then fine
        int n_access = 0;
        int prev_proc_access = -1; // set to the process that previously accessed database
        for (int j = 0; j < P; j++){
            // roll for current process
            if(roll_p(P) == j){
                n_access++;
                prev_proc_access = j;
            }
        }
        // check off and remove from the list
        if(n_access == 1){
            n_succeeded++;
            proc.erase(proc.begin() - 1 + prev_proc_access);
        }
    }
    return n_succeeded;
}

