"""
This is a py script to do quick comparison between piso and opt_piso
"""

import pandas as pd

fast_piso_bench = pd.read_csv("../results_opt/fast_piso_benchmark_512_7680_100_b.csv").drop('algorithm', axis=1)

piso_opt_bench = pd.read_csv("../results_opt/fast_piso_benchmark_512_7680_100.csv").drop('algorithm', axis=1)
piso_bench = pd.read_csv("../results/piso_benchmark_512_7680_100_old.csv").drop('algorithm', axis=1)

print(fast_piso_bench.groupby('size').mean())
print(piso_bench.groupby('size').mean())
print(piso_opt_bench.groupby('size').mean())
def improvement_percentage(old, new):
    return 100 * (old - new) / old
def compare_benchmarks(bench1, bench2):
    first = bench1.groupby('size').mean().reset_index()
    second = bench2.groupby('size').mean().reset_index()

    # Merge the two dataframes on the 'size' column
    merged = pd.merge(first, second, on='size', suffixes=('_bench1', '_bench2'))
    merged['improvement (%)'] = improvement_percentage(merged['tot_bench1'], merged['tot_bench2'])
    return merged

compare = compare_benchmarks(piso_bench, piso_opt_bench)
print(compare)
print(compare['improvement (%)'].mean())
