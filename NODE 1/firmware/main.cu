//main.cu
// Include Files
#include "myAdd.h"
#include "main.h"
#include "myAdd_terminate.h"
#include "myAdd_initialize.h"
#include <stdio.h>

// Function Declarations
static void argInit_1x100_real_T(real_T result[100]);
static void main_myAdd();

// Function Definitions
static void argInit_1x100_real_T(real_T result[100])
{
  int32_T idx1;

  // Initialize each element.
  for (idx1 = 0; idx1 < 100; idx1++) {
    result[idx1] = (real_T) idx1;
  }
}

void writeToFile(real_T result[100])
{
    FILE *fid = NULL;
    fid = fopen("myAdd.bin", "wb");
    fwrite(result, sizeof(real_T), 100, fid);
    fclose(fid);
}

static void main_myAdd()
{
  real_T out[100];
  real_T b[100];
  real_T c[100];

  argInit_1x100_real_T(b);
  argInit_1x100_real_T(c);
  
  myAdd(b, c, out);
  writeToFile(out);  // Write the output to a binary file
}

// Main routine
int32_T main(int32_T, const char * const [])
{
  // Initialize the application.
  myAdd_initialize();

  // Invoke the entry-point functions.
  main_myAdd();

  // Terminate the application.
  myAdd_terminate();
  return 0;
}