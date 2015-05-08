#ifndef RNG_H
#define RNG_H
class RNG
{
public:
        static bool Chance(int percentualSuccess);      // Returns true if random value is less than given value
        static int Random(int max);                     // Value between zero and given value
        static int RandomNotZero(int max);              // Value between one and given value
        static int Between(int min, int max);           // Value between two given values
};

#endif