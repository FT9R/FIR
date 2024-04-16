#pragma once

#include <stdint.h>
#include <string.h>

#define DllImport __declspec(dllimport)
#define DllExport __declspec(dllexport)

class DllExport arm_fir_filter
{
public:
    /**
     * @brief 32-bit floating-point type definition.
     */
    typedef float float32_t;

    /**
     * @brief Instance structure for the floating-point FIR filter.
     */
    typedef struct
    {
        uint16_t numTaps; // Number of filter coefficients in the filter.
        float32_t *pState; // Points to the state variable array. The array is of length numTaps + blockSize - 1.
        float32_t *pCoeffs; // Points to the coefficient array. The array is of length numTaps.
    } arm_fir_instance_f32;

    /**
     * @brief  Initialization function for the floating-point FIR filter.
     * @param[in,out] *S points to an instance of the floating-point FIR filter structure.
     * @param[in] 	numTaps  Number of filter coefficients in the filter.
     * @param[in] 	*pCoeffs points to the filter coefficients.
     * @param[in] 	*pState points to the state buffer.
     * @param[in] 	blockSize number of samples that are processed at a time.
     * @return    	none.
     */
    void Init(arm_fir_instance_f32 *S, uint16_t numTaps, float32_t *pCoeffs, float32_t *pState, uint32_t blockSize);

    /**
     * @brief Processing function for the floating-point FIR filter.
     * @param[in] *S points to an instance of the floating-point FIR structure.
     * @param[in] *pSrc points to the block of input data.
     * @param[out] *pDst points to the block of output data.
     * @param[in] blockSize number of samples to process.
     * @return none.
     */
    void Process(const arm_fir_instance_f32 *S, float32_t *pSrc, float32_t *pDst, uint32_t blockSize);

private:
};