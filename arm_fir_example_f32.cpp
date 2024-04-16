#include "arm_fir_filter.h"
#include <filesystem>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <vector>
#include <windows.h>

#define TEST_LENGTH_SAMPLES 320
#define BLOCK_SIZE          32
#define NUM_TAPS            255

static arm_fir_filter::float32_t testOutput[TEST_LENGTH_SAMPLES];
static arm_fir_filter::float32_t firStateF32[BLOCK_SIZE + NUM_TAPS - 1];

const arm_fir_filter::float32_t firCoeffs32[NUM_TAPS] = {
    -0.00000000f, -0.00000508f, -0.00000765f, 0.00000000f,  0.00001726f,  0.00003227f,  0.00002890f,  -0.00000000f,
    -0.00004268f, -0.00007128f, -0.00005869f, -0.00000000f, 0.00007702f,  0.00012316f,  0.00009778f,  -0.00000000f,
    -0.00012105f, -0.00018904f, -0.00014696f, 0.00000000f,  0.00017560f,  0.00027010f,  0.00020710f,  0.00000000f,
    -0.00024155f, -0.00036759f, -0.00027909f, -0.00000000f, 0.00031984f,  0.00048290f,  0.00036394f,  -0.00000000f,
    -0.00041151f, -0.00061752f, -0.00046272f, 0.00000000f,  0.00051771f,  0.00077312f,  0.00057666f,  -0.00000000f,
    -0.00063974f, -0.00095160f, -0.00070714f, -0.00000000f, 0.00077907f,  0.00115513f,  0.00085575f,  -0.00000000f,
    -0.00093743f, -0.00138624f, -0.00102437f, 0.00000000f,  0.00111686f,  0.00164796f,  0.00121522f,  -0.00000000f,
    -0.00131982f, -0.00194394f, -0.00143104f, -0.00000000f, 0.00154932f,  0.00227867f,  0.00167516f,  -0.00000000f,
    -0.00180911f, -0.00265777f, -0.00195181f, 0.00000000f,  0.00210396f,  0.00308840f,  0.00226638f,  -0.00000000f,
    -0.00244000f, -0.00357985f, -0.00262589f, -0.00000000f, 0.00282532f,  0.00414442f,  0.00303972f,  -0.00000000f,
    -0.00327080f, -0.00479873f, -0.00352057f, 0.00000000f,  0.00379143f,  0.00556583f,  0.00408623f,  -0.00000000f,
    -0.00440842f, -0.00647861f, -0.00476222f, 0.00000000f,  0.00515280f,  0.00758561f,  0.00558661f,  -0.00000000f,
    -0.00607176f, -0.00896148f, -0.00661863f, 0.00000000f,  0.00724066f,  0.01072710f,  0.00795563f,  -0.00000000f,
    -0.00878753f, -0.01309166f, -0.00976947f, 0.00000000f,  0.01094856f,  0.01645081f,  0.01239408f,  -0.00000000f,
    -0.01421233f, -0.02165309f, -0.01657501f, 0.00000000f,  0.01977877f,  0.03090573f,  0.02438398f,  -0.00000000f,
    -0.03159154f, -0.05230374f, -0.04452386f, 0.00000000f,  0.07462993f,  0.15870778f,  0.22495125f,  0.25036025f,
    0.22495125f,  0.15870778f,  0.07462993f,  0.00000000f,  -0.04452386f, -0.05230374f, -0.03159154f, -0.00000000f,
    0.02438398f,  0.03090573f,  0.01977877f,  0.00000000f,  -0.01657501f, -0.02165309f, -0.01421233f, -0.00000000f,
    0.01239408f,  0.01645081f,  0.01094856f,  0.00000000f,  -0.00976947f, -0.01309166f, -0.00878753f, -0.00000000f,
    0.00795563f,  0.01072710f,  0.00724066f,  0.00000000f,  -0.00661863f, -0.00896148f, -0.00607176f, -0.00000000f,
    0.00558661f,  0.00758561f,  0.00515280f,  0.00000000f,  -0.00476222f, -0.00647861f, -0.00440842f, -0.00000000f,
    0.00408623f,  0.00556583f,  0.00379143f,  0.00000000f,  -0.00352057f, -0.00479873f, -0.00327080f, -0.00000000f,
    0.00303972f,  0.00414442f,  0.00282532f,  -0.00000000f, -0.00262589f, -0.00357985f, -0.00244000f, -0.00000000f,
    0.00226638f,  0.00308840f,  0.00210396f,  0.00000000f,  -0.00195181f, -0.00265777f, -0.00180911f, -0.00000000f,
    0.00167516f,  0.00227867f,  0.00154932f,  -0.00000000f, -0.00143104f, -0.00194394f, -0.00131982f, -0.00000000f,
    0.00121522f,  0.00164796f,  0.00111686f,  0.00000000f,  -0.00102437f, -0.00138624f, -0.00093743f, -0.00000000f,
    0.00085575f,  0.00115513f,  0.00077907f,  -0.00000000f, -0.00070714f, -0.00095160f, -0.00063974f, -0.00000000f,
    0.00057666f,  0.00077312f,  0.00051771f,  0.00000000f,  -0.00046272f, -0.00061752f, -0.00041151f, -0.00000000f,
    0.00036394f,  0.00048290f,  0.00031984f,  -0.00000000f, -0.00027909f, -0.00036759f, -0.00024155f, 0.00000000f,
    0.00020710f,  0.00027010f,  0.00017560f,  0.00000000f,  -0.00014696f, -0.00018904f, -0.00012105f, -0.00000000f,
    0.00009778f,  0.00012316f,  0.00007702f,  -0.00000000f, -0.00005869f, -0.00007128f, -0.00004268f, -0.00000000f,
    0.00002890f,  0.00003227f,  0.00001726f,  0.00000000f,  -0.00000765f, -0.00000508f, -0.00000000f};

uint32_t blockSize = BLOCK_SIZE;
uint32_t numBlocks = TEST_LENGTH_SAMPLES / BLOCK_SIZE;

int32_t main(void)
{
    // Get the directory of the executable
    char buffer[MAX_PATH];
    GetModuleFileNameA(NULL, buffer, MAX_PATH); // Note the 'A' suffix for ANSI version
    std::string executablePath(buffer);
    std::string executableDir = executablePath.substr(0, executablePath.find_last_of("\\/"));

    // Set cwd to the directory containing the executable
    SetCurrentDirectoryA(executableDir.c_str());
    std::cout << "Current working directory: " << std::filesystem::current_path() << std::endl << std::endl;

    /* Set file paths */
    std::string CombinedDataPath = "../../Scripts/CombinedSignal.csv";
    std::string FilteredDataPath =
        CombinedDataPath.substr(0, CombinedDataPath.find_last_of("\\/")).append("/FilteredSignal.csv");

    arm_fir_filter::arm_fir_instance_f32 firInstance;
    arm_fir_filter::float32_t *inputF32, *outputF32;

    /* Read original signal data */
    /* Open input stream */
    std::ifstream istream(CombinedDataPath);

    /* Check if its opened successfully */
    if (!istream.is_open())
    {
        std::cerr << "Error opening the file for read!" << std::endl;

        return 1;
    }

    std::string line;
    std::vector<arm_fir_filter::float32_t> samples;
    while (std::getline(istream, line))
    {
        /* Convert each line to float32_t and add it to the vector */
        arm_fir_filter::float32_t number;
        std::istringstream iss(line);
        if (!(iss >> number))
        {
            std::cerr << "Error converting line to float32_t: " << line << std::endl;

            continue;
        }
        samples.push_back(number);
    }

    /* Close input stream */
    istream.close();

    /* Initialize input and output buffer pointers */
    inputF32 = samples.data();
    outputF32 = &testOutput[0];

    /* Call FIR init function to initialize the instance structure. */
    arm_fir_filter filter;
    filter.Init(&firInstance, NUM_TAPS, (arm_fir_filter::float32_t *) &firCoeffs32[0], &firStateF32[0], blockSize);

    /* Print original data */
    std::cout << "Input signal" << std::endl;
    for (size_t i = 0; i < samples.size(); i++)
    {
        std::cout << std::fixed << std::setprecision(10) << inputF32[i] << std::endl;
    }

    /* Perform the convolution */
    for (size_t i = 0; i < numBlocks; i++)
    {
        filter.Process(&firInstance, inputF32 + (i * blockSize), outputF32 + (i * blockSize), blockSize);
    }

    /* Print filtered data */
    std::cout << std::endl << "Output signal" << std::endl;
    for (size_t i = 0; i < sizeof(testOutput) / sizeof(*testOutput); i++)
    {
        std::cout << std::fixed << std::setprecision(8) << outputF32[i] << std::endl;
    }

    /* Save filtered signal data to the file */
    /* Open output stream */
    std::ofstream ostream(FilteredDataPath);

    /* Check if its opened successfully */
    if (!ostream.is_open())
    {
        std::cerr << "Error opening the file for write!" << std::endl;

        return 1;
    }

    /* Write data */
    for (arm_fir_filter::float32_t sample : testOutput)
    {
        ostream << std::fixed << std::setprecision(8) << sample << std::endl;
    }

    /* Close output stream */
    ostream.close();
}