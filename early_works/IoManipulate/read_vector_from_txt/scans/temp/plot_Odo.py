import matplotlib.pyplot as plt
from mpl_toolkits.mplot3d import Axes3D

# Function to extract x, y, z values from the text file
def extract_positions(file_path):
    x_values = []
    y_values = []
    z_values = []

    with open(file_path, 'r') as file:
        lines = file.readlines()
        i = 0
        while i < len(lines):
            line = lines[i]
            if "position:" in line:
                i += 1  # Move to next line after "position:"
                while i < len(lines):
                    line = lines[i].strip()
                    if line.startswith('x:'):
                        x_values.append(float(line.split(":")[1].strip()))
                    elif line.startswith('y:'):
                        y_values.append(float(line.split(":")[1].strip()))
                    elif line.startswith('z:'):
                        z_values.append(float(line.split(":")[1].strip()))
                        break  # Exit loop after finding z value
                    i += 1
            i += 1

    return x_values, y_values, z_values

# Other parts of your code remain the same



# Extract positions from the text file
x, y, z = extract_positions('Odo_FastLIO_Fendt.txt')

# Create a 3D plot
fig = plt.figure()
ax = fig.add_subplot(111, projection='3d')
ax.scatter(x, y, z)

ax.set_xlabel('X')
ax.set_ylabel('Y')
ax.set_zlabel('Z')

plt.show()

