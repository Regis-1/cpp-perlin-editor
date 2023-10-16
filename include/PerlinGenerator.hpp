#pragma once

#include <random>

class PerlinGenerator {
public:
    PerlinGenerator() = delete;
    PerlinGenerator(int w, int h, unsigned int seed = 0, int repeat = -1);
    ~PerlinGenerator(){}

    double Noise(double x, double y, double z);
    double OctaveNoise(double x, double y, double z, int octaves, double persistence);
    void Generate2D(double* pixels, int octaves, double persistence);
    void Seed(unsigned int seed);

private:
    static double Fade(double t) {
        return  t * t * t * (t * (t * 6 - 15) + 10);
    }
    static double Lerp(double a, double b, double x) {
        return a + x * (b - a);
    }
    int Increase(int num) {
        num++;
        if (_repeat > 0) num %= _repeat;

        return num;
    }
    static double Grad(int hash, double x, double y, double z) {
        //float u = (h < 8) ? x : y;
        //float v = (h < 4) ? y : ((h == 12 || h == 14) ? x : z);
        //return ((h & 1) == 0 ? u : -u) + ((h & 2) == 0 ? v : -v);

        switch(hash & 0xF) {
            case 0x0: return  x + y;
            case 0x1: return -x + y;
            case 0x2: return  x - y;
            case 0x3: return -x - y;
            case 0x4: return  x + z;
            case 0x5: return -x + z;
            case 0x6: return  x - z;
            case 0x7: return -x - z;
            case 0x8: return  y + z;
            case 0x9: return -y + z;
            case 0xA: return  y - z;
            case 0xB: return -y - z;
            case 0xC: return  y + x;
            case 0xD: return -y + z;
            case 0xE: return  y - x;
            case 0xF: return -y - z;
            default: return 0; // never happens
        }
    }
    double MapRange(double value, double fromMin, double fromMax, double toMin, double toMax) {
        // First, normalize the value to a range from 0 to 1 within the original range.
        double normalizedValue = (value - fromMin) / (fromMax - fromMin);
        // Then, scale the normalized value to the new range.
        double mappedValue = normalizedValue * (toMax - toMin) + toMin;
        return mappedValue;
    }
    void GeneratePermutation();

    int _width;
    int _height;
    int _repeat;

    int _p[512];
    std::vector<int> _permutation;

    std::mt19937_64 _mt_rand;
};
