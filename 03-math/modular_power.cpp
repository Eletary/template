// @title Modular Power and Inverse
// @brief Binary exponentiation and multiplicative inverse modulo a prime.
// @complexity O(log exponent)
// @author Team Template

using i64 = long long;

i64 modular_power(i64 base, i64 exponent, i64 modulus) {
    base %= modulus;
    i64 result = 1 % modulus;
    while (exponent > 0) {
        if (exponent & 1) result = static_cast<__int128>(result) * base % modulus;
        base = static_cast<__int128>(base) * base % modulus;
        exponent >>= 1;
    }
    return result;
}

i64 modular_inverse_prime(i64 value, i64 prime_modulus) {
    return modular_power(value, prime_modulus - 2, prime_modulus);
}
