// Some imperative scripts for algorithms in COMP4121.
// By including "C4121", one may call these functions directly
#include <random>
#include <vector>

std::mt19937 mt_rng_global;

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

// implementation of skip list
typedef struct _node{
    int val;
    size_t n_levels;

    // nodes in the same level
    SKIP_NODE** levels;
    SKIP_NODE* next;
    SKIP_NODE* prev;
} SKIP_NODE;

typedef struct _skip_list{
    size_t max_level; // n-1..0

    // TODO: actually points to first the node at the highest level
    SKIP_NODE* head;
    size_t N;
    // SKIP_NODE* median; pointer to the median node
} SKIP_LIST;

SKIP_LIST* initialize_skip_list(){
    SKIP_LIST* sklist = new SKIP_LIST;

    sklist->head = NULL;
    sklist->N = 0;

    return sklist;
}

// adds an element to the skip list, in order
// allow duplicates, which are added after the current version
void add_elem(SKIP_LIST* sklist, int elem){
    SKIP_NODE* node = new SKIP_NODE;

    ///////////////////
    // GENERATE LEVELS
    ///////////////////

    size_t n_levels = 0;
    while(true){
        int gen = mt_rng_global() % 2;
        if(gen != 0) break;

        n_levels++;
    }

    node->val = elem;
    node->n_levels = n_levels;
    node->levels = new SKIP_NODE*[n_levels];

    //////////
    // INSERT
    //////////

    // first element
    if(!sklist->head){
        sklist->head = node;
        node->next = NULL;
        node->prev = NULL;
        sklist->max_level = n_levels;

        for(int i=0; i<n_levels; i++) node->levels[i] = NULL;

    }
    // not first element
    else{
        // start from max level, go furthest right until you can't go anymore
        int cur_level = sklist->max_level - 1;
        SKIP_NODE* cur = sklist->head->levels[cur_level];
        
        while(cur_level != 0){
            if(cur->val < elem){
                cur = cur->next;
            }
            // we would overshoot, so go down a level
            else{
                cur = cur->levels[--cur_level];
            }
        }
        // arrived at level 0, where the element to be inserted is at cur_node

    }

}
