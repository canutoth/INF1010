import matplotlib.pyplot as plt
import numpy as np
import pandas as pd
import math

# Load collision data from file
data = pd.read_csv('colisoes_por_cpf.txt', sep="\t", header=None)
data.columns = ["CPF_Index", "Collisions"]


# Generate dynamic AVL values using log2 values from 1 to 1000
avl_dynamic_access_counts = [math.log2(i) if i > 0 else 0 for i in range(1, 1001)]

# Re-plotting with a line representing log growth from 1 to 1000
plt.figure(figsize=(12, 6))

# Scatter plot for each CPF index with the number of collisions with updated color and size
plt.scatter(data["CPF_Index"], data["Collisions"], color="#38b6ff", label="Número de Colisões", s=10, alpha=0.7)

# Plot the dynamic AVL line for log base 2 from 1 to 1000
plt.plot(range(1, 1001), avl_dynamic_access_counts, color="#050a30", linestyle="--", label="Complexidade AVL (O(log n))")

# Adding horizontal grid lines and setting ticks
plt.grid(axis='y', linestyle=':', color='gray')
plt.yticks(np.arange(0, 25, 1))
plt.xticks(np.arange(0, 1001, 100))

# Labels and title
plt.title("Colisões na Tabela Hash vs. Complexidade na AVL")
plt.xlabel("CPFs lidos")
plt.ylabel("Número de Colisões / Complexidade")

# Adjusting legend position to avoid overlap with the graph
plt.legend(loc="upper left")

# Display plot
plt.show()
