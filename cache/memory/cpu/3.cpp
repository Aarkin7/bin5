#include <iostream>
#include <vector>
#include <omp.h>

int main() {
    std::vector<int> numbers = {10, 5, 7, 15, 3, 9, 12, 8, 23, 25, 67, 1, 890, 23, 73, 25};

    // Serial Operations
    int min_val_serial = numbers[0];
    int max_val_serial = numbers[0];
    int sum_serial = 0;

    //auto start_serial = std::chrono::high_resolution_clock::now();
    double start_serial = omp_get_wtime();

    for (int i = 0; i < numbers.size(); i++) {
        min_val_serial = std::min(min_val_serial, numbers[i]);
        max_val_serial = std::max(max_val_serial, numbers[i]);
        sum_serial += numbers[i];
    }

    double average_serial = static_cast<double>(sum_serial) / numbers.size();

    // auto end_serial = std::chrono::high_resolution_clock::now();
    double end_serial = omp_get_wtime();
    double duration_serial = end_serial - start_serial;

    std::cout << "Serial Results:" << std::endl;
    std::cout << "Minimum value: " << min_val_serial << std::endl;
    std::cout << "Maximum value: " << max_val_serial << std::endl;
    std::cout << "Sum: " << sum_serial << std::endl;
    std::cout << "Average: " << average_serial << std::endl;
    std::cout << "Serial Execution Time: " << duration_serial << " seconds" << std::endl;

    // Parallel Operations
    int min_val_parallel = numbers[0];
    int max_val_parallel = numbers[0];
    int sum_parallel = 0;

    double start_parallel = omp_get_wtime();

    #pragma omp parallel for reduction(min:min_val_parallel) reduction(max:max_val_parallel) reduction(+:sum_parallel)
    for (int i = 0; i < numbers.size(); i++) {
        min_val_parallel = std::min(min_val_parallel, numbers[i]);
        max_val_parallel = std::max(max_val_parallel, numbers[i]);
        sum_parallel += numbers[i];
    }

    double average_parallel = static_cast<double>(sum_parallel) / numbers.size();

    double end_parallel = omp_get_wtime();
    double duration_parallel = (end_parallel - start_parallel);

    std::cout << "\nParallel Results:" << std::endl;
    std::cout << "Minimum value: " << min_val_parallel << std::endl;
    std::cout << "Maximum value: " << max_val_parallel << std::endl;
    std::cout << "Sum: " << sum_parallel << std::endl;
    std::cout << "Average: " << average_parallel << std::endl;
    std::cout << "Parallel Execution Time: " << duration_parallel << " seconds" << std::endl;

    return 0;
}


// By using the reduction clauses, the directive instructs the OpenMP runtime to perform the specified reduction operations on the variables (min_val_parallel, max_val_parallel, and sum_parallel) during the parallel execution of the loop. Each thread works on its assigned portion of the loop, and the results are combined using the specified reduction operations.

// In this example, the loop is parallelized, and the variables min_val_parallel, max_val_parallel, and sum_parallel are modified within the loop. The reduction operations ensure that the final values of these variables, after the loop, reflect the combined results from all the threads executing their respective iterations.

// The reduction clause in OpenMP simplifies the process of performing reduction operations, such as finding the minimum, maximum, or sum of values, across multiple threads in a parallel loop. It automatically handles the synchronization and combination of values, providing a convenient way to parallelize loops with reduction computations.