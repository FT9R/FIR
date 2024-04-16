import numpy as np
import matplotlib.pyplot as plt

# Get raw data
pure_signal = np.loadtxt('Signals/PureSignal.csv')
combined_signal = np.loadtxt('Signals/CombinedSignal.csv')
filtered_signal = np.loadtxt('Signals/FilteredSignal.csv')

# Plot charts
fig = plt.figure(figsize = (12, 6))
fig.suptitle('I/O signal comparison')

plt.subplot(2, 1, 1)
plt.plot(combined_signal, color = 'steelblue')
plt.plot(filtered_signal, color = 'orchid')
plt.legend(['combined', 'filtered'], loc = 'upper right')
plt.grid()
plt.xlabel('Sample number')
plt.ylabel('Absolute amplitude')

plt.subplot(2, 1, 2)
plt.plot(pure_signal, color = 'slateblue')
plt.plot(filtered_signal, color = 'orchid')
plt.legend(['pure', 'filtered'], loc = 'upper right')
plt.grid()
plt.xlabel('Sample number')
plt.ylabel('Absolute amplitude')

plt.tight_layout()
plt.show()