import numpy as np
import matplotlib.pyplot as plt

# Load data from the text file
data = np.loadtxt("global_map.txt")

# Extract x, y, and radius columns
x = data[:, 0]
y = data[:, 1]
radius = data[:, 2]

# Create a scatter plot with circles
fig, ax = plt.subplots()
for i in range(len(x)):
    circle = plt.Circle((x[i], y[i]), radius[i], fill=False, edgecolor='b')
    ax.add_patch(circle)

# Set axis limits based on the data range
x_min, x_max = min(x), max(x)
y_min, y_max = min(y), max(y)
ax.set_xlim(x_min - 1, x_max + 1)
ax.set_ylim(y_min - 1, y_max + 1)

# Set axis labels and title
ax.set_xlabel("X")
ax.set_ylabel("Y")
ax.set_title("Circle Plot")

# Show the plot
plt.gca().set_aspect('equal', adjustable='box')  # Equal aspect ratio
plt.grid(True)
plt.show()

