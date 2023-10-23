import numpy as np
import matplotlib.pyplot as plt
from mpl_toolkits.mplot3d import Axes3D  # Importing this for 3D plotting

def plotResultScantoScanMatching_R_as_Z(folder_name):
    # Load data from the text file
    data = np.loadtxt( folder_name + "/global_map.txt")
    
    # Extract x, y, and radius columns
    x = data[:, 0]
    y = data[:, 1]
    radius = data[:, 2]
    
    # Create a 3D scatter plot
    fig = plt.figure(figsize=(12, 10))
    ax = fig.add_subplot(111, projection='3d')  # Creating a subplot with 3D projection
    
    # Scatter plot with x, y, and radius as z
    ax.scatter(x, y, radius, c='b')  # c='b' makes the points blue
    
    path_data = np.loadtxt( folder_name + "/state_cloud_2d.txt")
    
    # 3D轨迹 (3D trajectory)
    ax.scatter(path_data[:, 1], path_data[:, 2], path_data[:, 0], c='r', marker='+')  # Using radius as z, and making the points red with marker '+'
    
    # Set axis labels and title
    ax.set_xlabel("X")
    ax.set_ylabel("Y")
    ax.set_zlabel("Radius")
    ax.set_title("Global Map--scan by scan matching in 3D")
    
    # Show the plot
    plt.show()

# You may call the function like this:
plotResultScantoScanMatching_R_as_Z('Fend')
