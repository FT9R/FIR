# Description
The current repository contains some Python scripts for:
- Generating a noisy signal
- Calculating the coefficients of a finite impulse response (FIR) filter
- Applying the filter to noisy signal
- Comparing signals on charts
- Performing a fast Fourier transform (FFT) to evaluate filtering efficiency

## Notes
This time it is aimed primarily for use alongside with Cortex-based MCUs and the CMSIS DSP software library.  
But windows machine is used because of its extended debug capability.  
So CMSIS `arm_fir_f32` and `arm_fir_init_f32` functions are implemented in form of DLL with minor changes  
to be used by a console application.

## Sequence of application
1. Run `GenerateSignal.py`

![Generated Signals](Images/Signal/Generated.png)

3. Use `GetCoefficients.ipynb` to interract with notebook and calculate filter coefficients   
4. In `arm_fir_example_f32.cpp` replace definitions and coefficients with new values 
5. Run `fir.exe` to get filtered signal values
6. Run `CompareSignal.py`
   
![Signals comparison](Images/Signal/Comparison.png)

8. Run `PerformFFT.py`
   
![Signals FFT](Images/Signal/FFT.png)
