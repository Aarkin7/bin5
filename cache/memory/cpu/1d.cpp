#include <iostream>
#include <queue>
#include <vector>
#include <stack>
#include <omp.h>

using namespace std;

#define MAXN 100000

vector<int> adj[MAXN]; // Adjacency list representation of graph

void dfs_parallel(int source) {

    bool visited[MAXN] = {false}; // Array to keep track of visited nodes
    stack<int> st; // Stack to store nodes to visit

    visited[source] = true;
    st.push(source);

    cout<<"Visited nodes: ";

    while (!st.empty()) {
        int u = st.top();
        st.pop();

        cout<<u<<" ";

        #pragma omp parallel for
        for (int i = 0; i < adj[u].size(); i++) {
            int v = adj[u][i];

            #pragma omp critical
            {
                if (!visited[v]) {
                    visited[v] = true;
                    st.push(v);
                }
            }
        }
    }

    cout<<endl;
}

void dfs_serial(int source) {

    bool visited[MAXN] = {false}; // Array to keep track of visited nodes
    stack<int> st; // Stack to store nodes to visit

    visited[source] = true;
    st.push(source);

    cout<<"Visited nodes: ";

    while (!st.empty()) {
        int u = st.top();
        st.pop();

        cout<<u<<" ";

        for (int i = 0; i < adj[u].size(); i++) {
            int v = adj[u][i];

            if (!visited[v]) {
                visited[v] = true;
                st.push(v);
            }
        }
    }

    cout<<endl;
}

int main() {
    int n, m;
    cin >> n >> m;

    for (int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    int source;
    cin >> source;

    double start_time = omp_get_wtime();
    dfs_serial(source);
    double mid_time = omp_get_wtime();

    cout << "Time taken for serial DFS: " << (mid_time - start_time) << " seconds" << endl;

    dfs_parallel(source);
    double end_time  = omp_get_wtime();

    cout << "Time taken for parallel DFS: " << (end_time - mid_time) << " seconds" << endl;


    return 0;
}

// The #pragma omp critical is a directive used in OpenMP to define a critical section in a parallel program. It ensures that a specific section of code is executed by only one thread at a time, preventing multiple threads from concurrently accessing or modifying shared resources and potentially causing data races.


// OpenMP (Open Multi-Processing) is an application programming interface (API) that supports shared-memory multiprocessing programming in C, C++, and Fortran. It provides a set of directives, runtime library routines, and environment variables that enable developers to parallelize their code and take advantage of multiple processors or processor cores within a single machine.

// The main goal of OpenMP is to simplify parallel programming by allowing developers to add parallelism to their code through the use of compiler directives. These directives are special annotations that indicate which parts of the code should be executed in parallel. By inserting these directives, developers can instruct the compiler to automatically generate and manage multiple threads to execute the parallel portions of the code.

// OpenMP supports a wide range of parallelization techniques, including loop parallelism, task parallelism, and data parallelism. It allows developers to express parallelism at different levels of granularity, from fine-grained parallelism within loops to coarse-grained parallelism across different sections of the code.

// In addition to directives, OpenMP also provides runtime library routines that allow developers to control and synchronize the execution of parallel code. These routines enable thread synchronization, data sharing, and other essential operations in parallel programs.

// OpenMP is widely supported by compilers and platforms, making it a portable and accessible choice for parallel programming. It is commonly used in scientific computing, numerical simulations, and other computationally intensive applications. By leveraging OpenMP, developers can take advantage of the available resources on multi-core machines and achieve performance improvements through parallel execution.