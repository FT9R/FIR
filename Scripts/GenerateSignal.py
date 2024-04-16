import numpy as np
import matplotlib.pyplot as plt
from scipy import signal

# Input parameters
sample_rate = 48000
samples = 320
triangle_amp = 1
triangle_freq = 1e+3
triangle_periods = 3
noise_amp = 0.2
noise_freq = 15e+3

# Time domain
t = np.linspace(0, triangle_periods / triangle_freq, samples, endpoint = False)

# Generate signals
triangle = triangle_amp * signal.sawtooth(2 * np.pi * triangle_freq * t, width = 0.5)
noise = noise_amp * np.sin(2 * np.pi * noise_freq * t)

# Plot charts
fig = plt.figure(figsize = (12, 9))
fig.suptitle('Generated signals')

plt.subplot(3, 1, 1)
plt.plot(t, triangle, color = 'steelblue')
plt.legend(['triangle'], loc = 'upper right')
plt.grid()
plt.xlabel('Time')
plt.ylabel('Absolute amplitude')

plt.subplot(3, 1, 2)
plt.plot(t, noise, color = 'slateblue')
plt.legend(['noise'], loc = 'upper right')
plt.grid()
plt.xlabel('Time')
plt.ylabel('Absolute amplitude')

plt.subplot(3, 1, 3)
plt.plot(t, triangle + noise, color = 'orchid')
plt.legend(['combined'], loc = 'upper right')
plt.grid()
plt.xlabel('Time')
plt.ylabel('Absolute amplitude')

plt.tight_layout()
plt.show()

# Save signal data to the file
np.savetxt('PureSignal.csv', triangle, delimiter = ',')
np.savetxt('CombinedSignal.csv', triangle + noise, delimiter = ',')