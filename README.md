# Description
The current repository contains some Python scripts for:
- Generating a noisy signal
- Calculating the coefficients of a finite impulse response (FIR) filter
- Applying the filter to noisy signal
- Comparing signals on charts
- Performing a fast Fourier transform (FFT) to evaluate filtering efficiency

## Notes
Despite the fact that CMSIS DSP software library is designed to work alongside with Cortex-based MCUs,  
this time windows machine is used because of its extended debug capability.  
So CMSIS `arm_fir_f32` and `arm_fir_init_f32` functions are implemented in form of DLL with minor changes  
to be used by a console application.

## Sequence of application
1. Run `GenerateSignal.py`

![Generated Signals](Images/Signal/Generated.png)

2. Use `GetCoefficients.ipynb` to interract with notebook and calculate filter coefficients   
3. In `arm_fir_example_f32.cpp` replace definitions and coefficients with new values 
4. Run `fir.exe` to get filtered signal values
5. Run `CompareSignal.py`
   
![Signals comparison](Images/Signal/Comparison.png)

6. Run `PerformFFT.py`
   
![Signals FFT](Images/Signal/FFT.png)
