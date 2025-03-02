import matplotlib.pyplot as plt

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

# Extract positions from the text file
x, y, z = extract_positions('Odo_FastLIO_Fendt.txt')

# Create a 2D XY plot
plt.figure()
plt.scatter(x, y)
plt.xlabel('X')
plt.ylabel('Y')
plt.title('XY Plot')
plt.axis('equal')
plt.grid(True)
plt.show()

# Create a 2D XZ plot
plt.figure()
plt.scatter(x, z)
plt.xlabel('X')
plt.ylabel('Z')
plt.title('XZ Plot')
plt.axis('equal')
plt.grid(True)
plt.show()

