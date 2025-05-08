"""
This is a py script to do quick comparison between piso and opt_piso
"""

import pandas as pd

piso_bench = pd.read_csv("../results/piso_benchmark_512_7680_100.csv").drop('algorithm', axis=1)

piso_opt_bench = pd.read_csv("../results_opt/piso_benchmark_512_7680_100.csv").drop('algorithm', axis=1)
max_size = piso_opt_bench['size'].max()
piso_bench = piso_bench[piso_bench['size'] <= max_size]

print(piso_bench.groupby('size').mean())
print(piso_opt_bench.groupby('size').mean())