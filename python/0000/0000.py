import matplotlib.pyplot as plt
from matplotlib.transforms import Bbox
import numpy as np

def run_simulation_and_save_frames(num_frames):
    for i in range(num_frames):
        # Run one step of your simulation (algorithmic logic here)
        data = np.random.rand(10, 10) # Placeholder for actual simulation data

        # Generate the visualization
        plt.imshow(data, cmap='viridis')
        plt.axis('off')

        # Save the frame with sequential naming
        filename = f'frame_{i:04d}.png'
        plt.savefig(filename, dpi=100, bbox_inches=Bbox([[0,0],[10.24, 7.68]]), pad_inches=0)
        plt.close()

    print(f"Generated {num_frames} frames.")

# Example usage:
run_simulation_and_save_frames(100)
