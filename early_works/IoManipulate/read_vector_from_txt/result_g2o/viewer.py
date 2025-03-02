import matplotlib.pyplot as plt

def read_data_from_file(file_path):
    data = []
    path = []
    with open(file_path, 'r') as file:
        for line in file:
            parts = line.strip().split()
            if parts[0] == 'VERTEX_XY':
                x = float(parts[2])
                y = float(parts[3])
                data.append((x, y))
            elif parts[0] == 'VERTEX_SE2':
                x = float(parts[2])
                y = float(parts[3])
                path.append((x, y))
    return data, path

# File paths (replace with your actual file paths)
file_path_1 = 'reference.txt'
file_path_2 = 'to_compare.txt'

# Read data from files
data_1, path_1 = read_data_from_file(file_path_1)
data_2, path_2 = read_data_from_file(file_path_2)

# Extracting x and y coordinates for data and path
x1, y1 = zip(*data_1)
x2, y2 = zip(*data_2)
path_x1, path_y1 = zip(*path_1) if path_1 else ([], [])
path_x2, path_y2 = zip(*path_2) if path_2 else ([], [])

# Plotting data and path
plt.figure(figsize=(10, 8))
plt.scatter(x1, y1, s=10, color='blue', label='Data ' + file_path_1)
plt.scatter(x2, y2, s=8, color='red', label='Data ' + file_path_2)
if path_1:
    plt.plot(path_x1, path_y1, color='cyan', label='Path ' + file_path_1)
if path_2:
    plt.plot(path_x2, path_y2, color='magenta', label='Path ' + file_path_2)
plt.title("XY Coordinates and Paths from Two Files")
plt.xlabel("X Coordinate")
plt.ylabel("Y Coordinate")
plt.legend()
plt.grid(True)
plt.show()

