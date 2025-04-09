import pandas as pd
import matplotlib.pyplot as plt

# Load CSV file
df = pd.read_csv("data.csv")

# Just to check everything is loaded correctly
print("Available columns:", df.columns)
print(df.head())

# Use correct column names from your CSV
temp_col = 'Temperature'
dielectric_col = 'Epsilon'

# Plot
plt.figure(figsize=(8, 5))
plt.plot(df[temp_col], df[dielectric_col], marker='o', linestyle='-', label='Dielectric Constant')

# Optional: Estimate Curie Temperature as the peak in Epsilon
curie_temp = df[temp_col][df[dielectric_col].idxmax()]
plt.axvline(curie_temp, color='red', linestyle='--', label=f'Curie Temp ≈ {curie_temp}°C')

# Labels & Styling
plt.xlabel("Temperature (°C)")
plt.ylabel("Dielectric Constant (εr)")
plt.title("Variation of Dielectric Constant with Temperature")
plt.legend()
plt.grid(True)
plt.tight_layout()

# Save the plot as image
plt.savefig("dielectric_vs_temp.png")

# Show the plot
plt.show()
