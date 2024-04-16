import numpy as np
import matplotlib.pyplot as plt

# Get raw data
pure_signal = np.loadtxt('PureSignal.csv')
combined_signal = np.loadtxt('CombinedSignal.csv')
filtered_signal = np.loadtxt('FilteredSignal.csv')

# Parameters
samples = pure_signal.__len__()
sample_periods = 3
sample_freq = 1000
sample_rate = sample_freq / sample_periods * samples

# Perform FFT
freqs = np.fft.fftfreq(samples) * sample_rate
pure_amps = np.fft.fft(pure_signal) * 2 / samples
combined_amps = np.fft.fft(combined_signal) * 2 / samples
filtered_amps = np.fft.fft(filtered_signal) * 2 / samples

# Plot the FFT results
plt.figure(figsize = (12, 9))

plt.subplot(3, 1, 1, title='FFT pure signal')
plt.plot(freqs[range(samples//2)], abs(pure_amps[range(samples//2)]))
plt.xlabel('Frequency [Hz]')
plt.xlim([0, 20000])
plt.ylabel('Absolute amplitude')
plt.grid()

plt.subplot(3, 1, 2, title='FFT combined signal')
plt.plot(freqs[range(samples//2)], abs(combined_amps[range(samples//2)]))
plt.xlabel('Frequency [Hz]')
plt.xlim([0, 20000])
plt.ylabel('Absolute amplitude')
plt.grid()

plt.subplot(3, 1, 3, title='FFT filtered signal')
plt.plot(freqs[range(samples//2)], abs(filtered_amps[range(samples//2)]))
plt.xlabel('Frequency [Hz]')
plt.xlim([0, 20000])
plt.ylabel('Absolute amplitude')
plt.grid()

plt.tight_layout()
plt.show()