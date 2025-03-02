import matplotlib.pyplot as plt

def read_data_from_file(file_path):
    data, path = [], []
    with open(file_path, 'r') as file:
        for line in file:
            parts = line.strip().split()
            if parts[0] == 'VERTEX_XY':
                x, y = float(parts[2]), float(parts[3])
                data.append((x, y))
            elif parts[0] == 'VERTEX_SE2':
                x, y = float(parts[2]), float(parts[3])
                path.append((x, y))
    return data, path

def read_vertex_se2_and_edges(file_path, vertex_se2_id):
    vertex_se2, connected_vertices = None, []
    with open(file_path, 'r') as file:
        for line in file:
            parts = line.strip().split()
            if parts[0] == 'VERTEX_SE2' and int(parts[1]) == vertex_se2_id:
                vertex_se2 = (float(parts[2]), float(parts[3]))
            elif parts[0] == 'EDGE_SE2_XY' and int(parts[1]) == vertex_se2_id:
                connected_vertices.append((float(parts[3]), float(parts[4])))
    return vertex_se2, connected_vertices

# File paths and SE2 vertex ID
file_path_1, file_path_2 = 'reference.txt', 'to_compare.txt'
vertex_se2_id = 184#210

# Read VERTEX_XY and VERTEX_SE2 data
data_1, path_1 = read_data_from_file(file_path_1)
data_2, path_2 = read_data_from_file(file_path_2)

# Read VERTEX_SE2 positions and their connections
vertex_se2_1, edges_1 = read_vertex_se2_and_edges(file_path_1, vertex_se2_id)
vertex_se2_2, edges_2 = read_vertex_se2_and_edges(file_path_2, vertex_se2_id)

# Plotting
plt.figure(figsize=(12, 10))

# Plot VERTEX_XY data
plt.scatter(*zip(*data_1), s=10, color='blue', label='Data ' + file_path_1)
plt.scatter(*zip(*data_2), s=8, color='red', label='Data ' + file_path_2)

# Plot VERTEX_SE2 positions and connections
if vertex_se2_1:
    plt.scatter(*vertex_se2_1, color='cyan', label=file_path_1 + f' VERTEX_SE2 ID {vertex_se2_id}')
    for edge in edges_1:
        plt.plot([vertex_se2_1[0], edge[0]], [vertex_se2_1[1], edge[1]], 'c-', linewidth=1)
if vertex_se2_2:
    plt.scatter(*vertex_se2_2, color='green', label=file_path_2 + f' VERTEX_SE2 ID {vertex_se2_id}')
    for edge in edges_2:
        plt.plot([vertex_se2_2[0], edge[0]], [vertex_se2_2[1], edge[1]], 'g-', linewidth=1)

plt.title(f"VERTEX_SE2 ID {vertex_se2_id} Connections in Two Files")
plt.xlabel("X Coordinate")
plt.ylabel("Y Coordinate")
plt.grid(True)
plt.legend()
plt.show()

