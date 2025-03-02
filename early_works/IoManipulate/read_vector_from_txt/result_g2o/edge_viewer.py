

import matplotlib.pyplot as plt

def read_vertex_se2(file_path, vertex_se2_id):
    with open(file_path, 'r') as file:
        for line in file:
            parts = line.strip().split()
            if parts[0] == 'VERTEX_SE2' and int(parts[1]) == vertex_se2_id:
                x = float(parts[2])
                y = float(parts[3])
                return x, y
    return None, None

def read_edge_data(file_path, vertex_se2_id):
    connected_vertices = []
    with open(file_path, 'r') as file:
        for line in file:
            parts = line.strip().split()
            if parts[0] == 'EDGE_SE2_XY' and int(parts[1]) == vertex_se2_id:
                x = float(parts[3])
                y = float(parts[4])
                connected_vertices.append((x, y))
    return connected_vertices

# File paths and SE2 vertex ID
file_path_1 = 'Fend.g2o'#'result_2d.g2o'#  # Replace with the first actual file path
file_path_2 = 'result_2d.g2o'  # Replace with the second actual file path
vertex_se2_id = 450

# Read data from files
vertex_se2_x1, vertex_se2_y1 = read_vertex_se2(file_path_1, vertex_se2_id)
connected_vertices1 = read_edge_data(file_path_1, vertex_se2_id)

vertex_se2_x2, vertex_se2_y2 = read_vertex_se2(file_path_2, vertex_se2_id)
connected_vertices2 = read_edge_data(file_path_2, vertex_se2_id)

# Plotting
plt.figure(figsize=(10, 8))

# Plot for the first file
plt.scatter(vertex_se2_x1, vertex_se2_y1, color='pink', label= file_path_1+f'   Reference: VERTEX_SE2 ID {vertex_se2_id}')
for x, y in connected_vertices1:
    plt.scatter(x, y, color='lightblue')
    plt.plot([vertex_se2_x1, x], [vertex_se2_y1, y], 'b-', linewidth=1)

# Plot for the second file
plt.scatter(vertex_se2_x2, vertex_se2_y2, color='green', label=file_path_2+f'    TO be analysed : VERTEX_SE2 ID {vertex_se2_id}')
for x, y in connected_vertices2:
    plt.scatter(x, y, color='lightgreen')
    plt.plot([vertex_se2_x2, x], [vertex_se2_y2, y], 'g-', linewidth=1)

plt.title(f"VERTEX_SE2 ID {vertex_se2_id} Connections in Two Files")
plt.xlabel("X Coordinate")
plt.ylabel("Y Coordinate")
plt.grid(True)
plt.legend()
plt.show()


