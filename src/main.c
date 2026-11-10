#include <stdio.h>
#include <unistd.h>
//#include <pigpio.h>
#include <sys/statvfs.h>
#define PIN 17

int main(int argc, char* argv[])
{
    float memory;
    float storage;
    float threshold;
    const char *status;

    printf("- Welcome to Raspberry Pi Equipment Health Monitor -\n");
    printf("Enter memory usage: ");
    scanf("%f", &memory);

    printf("Enter storage usage: ");
    scanf("%f", &storage);

    printf("Enter warning threshold: ");
    scanf("%f", &threshold);

    if(memory > threshold || storage > threshold)
    {
        status = "WARNING";
    } else {
        status = "HEALTHY";
    }

    printf("System Status: %s\n", status);

    FILE *file = fopen("health_log.txt", "a");
    if (file != NULL)
    {
        fprintf(file, "Memory: %.1f\n", memory);
        fprintf(file, "Storage: %.1f\n", storage);
        fprintf(file, "Threshold: %.1f\n", threshold);
        fprintf(file, "Status: %s\n", status);
        fclose(file);
    }

    return 0;

}