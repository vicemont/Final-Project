
#include <stdio.h>
#include <pigpio.h>

#define PIN 17

int main(int argc, char* argv[])
{
    float memory;
    float storage;
    float threshold;
    const char *status;
    const char *ledStatus;

    printf("- Welcome to Raspberry Pi Equipment Health Monitor -\n");

    printf("Enter memory usage: ");
    scanf("%f", &memory);

    printf("Enter storage usage: ");
    scanf("%f", &storage);

    printf("Enter warning threshold: ");
    scanf("%f", &threshold);

    if (memory > threshold || storage > threshold)
    {
        status = "WARNING";
        ledStatus = "ON";
    }
    else
    {
        status = "HEALTHY";
        ledStatus = "OFF";
    }

    // Display the results
    printf("\nMemory: %.1f%% | Storage: %.1f%% | Threshold: %.1f%% | Status: %s | Warning LED: %s\n",
       memory, storage, threshold, status, ledStatus);

    // Save results to a file
    FILE *file = fopen("health_log.txt", "a");

    if (file != NULL)
    {
        fprintf(file, "Memory: %.1f%% | Storage: %.1f%% | Threshold: %.1f%% | Status: %s | Warning LED: %s\n",
        memory, storage, threshold, status, ledStatus);
        fclose(file);
    }
    else
    {
        printf("Error opening file\n");
    }

    gpioInitialise();
    gpioSetMode(PIN, PI_OUTPUT);

    if (memory > threshold || storage > threshold)
    {
        gpioWrite(PIN, 1);
        printf("LED: ON\n");
    }
    else
    {
        gpioWrite(PIN, 0);
        printf("LED: OFF\n");
    }

    printf("Press Enter to exit\n");
    getchar();
    getchar();

    gpioWrite(PIN, 0);
    gpioTerminate();

    return 0;
}