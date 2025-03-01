import pandas as pd
import matplotlib.pyplot as plt

def plot_comparison(input_csv='/home/nessy/Desktop/testOpCore/data/real.csv', output_csv='/home/nessy/Desktop/testOpCore/data/result.csv'):
    # Read input and output CSV files
    input_df = pd.read_csv(input_csv, header=None)
    output_df = pd.read_csv(output_csv, header=None)

    # Assigning column names for better clarity
    input_df.columns = ['p_x', 'p_y', 'p_z', 'dp_x', 'dp_y', 'dp_z', 'ddp_x', 'ddp_y', 'ddp_z']
    output_df.columns = ['p_x', 'p_y', 'p_z', 'dp_x', 'dp_y', 'dp_z', 'ddp_x', 'ddp_y', 'ddp_z']

    # Plot position comparison
    plt.figure(figsize=(14, 8))
    plt.suptitle('Kalman Filter Comparison', fontsize=16)

    plt.subplot(3, 1, 1)
    plt.plot(input_df['p_x'], label='Real p_x', linestyle='--')
    plt.plot(output_df['p_x'], label='Filtered p_x')
    plt.title('Position (X)')
    plt.legend()
    plt.grid(True)

    plt.subplot(3, 1, 2)
    plt.plot(input_df['p_y'], label='Real p_y', linestyle='--')
    plt.plot(output_df['p_y'], label='Filtered p_y')
    plt.title('Position (Y)')
    plt.legend()
    plt.grid(True)

    plt.subplot(3, 1, 3)
    plt.plot(input_df['p_z'], label='Real p_z', linestyle='--')
    plt.plot(output_df['p_z'], label='Filtered p_z')
    plt.title('Position (Z)')
    plt.legend()
    plt.grid(True)

    # Plot velocity comparison
    plt.figure(figsize=(14, 8))
    plt.suptitle('Velocity Comparison', fontsize=16)

    plt.subplot(3, 1, 1)
    plt.plot(input_df['dp_x'], label='Real dp_x', linestyle='--')
    plt.plot(output_df['dp_x'], label='Filtered dp_x')
    plt.title('Velocity (X)')
    plt.legend()
    plt.grid(True)

    plt.subplot(3, 1, 2)
    plt.plot(input_df['dp_y'], label='Real dp_y', linestyle='--')
    plt.plot(output_df['dp_y'], label='Filtered dp_y')
    plt.title('Velocity (Y)')
    plt.legend()
    plt.grid(True)

    plt.subplot(3, 1, 3)
    plt.plot(input_df['dp_z'], label='Real dp_z', linestyle='--')
    plt.plot(output_df['dp_z'], label='Filtered dp_z')
    plt.title('Velocity (Z)')
    plt.legend()
    plt.grid(True)

    # Plot acceleration comparison
    plt.figure(figsize=(14, 8))
    plt.suptitle('Acceleration Comparison', fontsize=16)

    plt.subplot(3, 1, 1)
    plt.plot(input_df['ddp_x'], label='Real ddp_x', linestyle='--')
    plt.plot(output_df['ddp_x'], label='Filtered ddp_x')
    plt.title('Acceleration (X)')
    plt.legend()
    plt.grid(True)

    plt.subplot(3, 1, 2)
    plt.plot(input_df['ddp_y'], label='Real ddp_y', linestyle='--')
    plt.plot(output_df['ddp_y'], label='Filtered ddp_y')
    plt.title('Acceleration (Y)')
    plt.legend()
    plt.grid(True)

    plt.subplot(3, 1, 3)
    plt.plot(input_df['ddp_z'], label='Real ddp_z', linestyle='--')
    plt.plot(output_df['ddp_z'], label='Filtered ddp_z')
    plt.title('Acceleration (Z)')
    plt.legend()
    plt.grid(True)

    plt.tight_layout()
    plt.show()

if __name__ == '__main__':
    plot_comparison()
