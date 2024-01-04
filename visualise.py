import pandas as pd
import matplotlib.pyplot as plt

# Read the data
data = pd.read_csv('output.csv', header=None, names=['x', 'y', 'class', 'type'])

# Create a scatter plot for the grid points (decision boundary)
# 'cmap' determines the color map for different classes
plt.scatter(data['x'], data['y'], c=data['class'], alpha=0.5, cmap='coolwarm')

# Overlay the original dataset points
# You can choose a different color and marker for better visibility
for index, row in data.iterrows():
    if row['type'] == 'dataset':
        plt.scatter(row['x'], row['y'], c='green', marker='o', edgecolors='w')  # Green color with white edge

plt.xlabel('X-axis')
plt.ylabel('Y-axis')
plt.title('Neural Network Decision Boundary')
plt.show()
