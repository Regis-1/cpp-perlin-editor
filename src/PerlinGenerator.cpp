#include "PerlinGenerator.hpp"

#include <iostream>
#include <cmath>

PerlinGenerator::PerlinGenerator(int w, int h, unsigned int seed, int repeat)
    : _width(w), _height(h), _repeat(repeat), _permutation(256,0)
{
    Seed(seed);
    for (auto i : _permutation)
        std::cout << i << ", ";
    for (int i = 0; i < 512; i++) {
        _p[i] = _permutation[i%256];
    }
}

double PerlinGenerator::Noise(double x, double y, double z) {
    if (_repeat > 0) {
        x = std::fmod(x, _repeat);
        y = std::fmod(y, _repeat);
        z = std::fmod(z, _repeat);
    }

    int xi = (int)x & 255;
    int yi = (int)y & 255;
    int zi = (int)z & 255;
    double xf = x - (int)x;
    double yf = y - (int)y;
    double zf = z - (int)z;
    double u = Fade(xf);
    double v = Fade(yf);
    double w = Fade(zf);

    int aaa, aba, aab, abb, baa, bba, bab, bbb;
    aaa = _p[_p[_p[xi]+yi]+zi];
    aba = _p[_p[_p[xi]+Increase(yi)]+zi];
    aab = _p[_p[_p[xi]+yi]+Increase(zi)];
    abb = _p[_p[_p[xi]+Increase(yi)]+Increase(zi)];
    baa = _p[_p[_p[Increase(xi)]+yi]+zi];
    bba = _p[_p[_p[Increase(xi)]+Increase(yi)]+zi];
    bab = _p[_p[_p[Increase(xi)]+yi]+Increase(zi)];
    bbb = _p[_p[_p[Increase(xi)]+Increase(yi)]+Increase(zi)];

    double x1, x2, y1, y2;
    x1 = Lerp(Grad(aaa, xf, yf, zf), Grad(baa, xf-1, yf, zf), u);
    x2 = Lerp(Grad(aba, xf, yf-1, zf), Grad(bba, xf-1, yf-1, zf), u);
    y1 = Lerp(x1, x2, v);
    x1 = Lerp(Grad(aab, xf, yf, zf-1), Grad(bab, xf-1, yf, zf-1), u);
    x2 = Lerp(Grad(abb, xf, yf-1, zf-1), Grad(bbb, xf-1, yf-1, zf-1), u);
    y2 = Lerp(x1, x2, v);

    return (Lerp(y1, y2, w)/2);
}

double PerlinGenerator::OctaveNoise(double x, double y, double z, int octaves,
        double persistence)
{
    double total = 0;
    double frequency = 1;
    double amplitude = 1;
    double maxValue = 0;

    for (int i = 0; i < octaves; i++) {
        total += Noise(x*frequency, y*frequency, z*frequency) * amplitude;
        maxValue += amplitude;

        amplitude *= persistence;
        frequency *= 2;
    }

    return total/maxValue;
}

void PerlinGenerator::Seed(unsigned int seed) {
    seed == 0 ? _mt_rand.seed(std::random_device()()) : _mt_rand.seed(seed);
    GeneratePermutation();
}

// Fisher-Yates shuffle
void PerlinGenerator::GeneratePermutation() {
    for (std::size_t i = 0; i != 256; ++i) {
        std::uniform_int_distribution<> dis(0, i);
        std::size_t j = dis(_mt_rand);
        if (j < _permutation.size()) {
            if (i < _permutation.size()) {
                _permutation[i] = _permutation[j];
            }
            _permutation[j] = i;
        }
    }
}
