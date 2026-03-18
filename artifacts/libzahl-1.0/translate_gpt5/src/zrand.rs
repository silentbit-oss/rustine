// Module: zrand
// Implements random number generation with different devices and distributions

use crate::z_t;
use crate::Result;
use crate::ZahlError;
use num_traits::Zero;
use num_traits::One;
use num_bigint::RandBigInt;
use rand::rngs::OsRng;
use rand::thread_rng;

/// Random device type
#[derive(Debug, Clone, Copy, PartialEq, Eq)]
pub enum zranddev {
    /// Fast random number generator (using ThreadRng)
    FAST_RANDOM = 0,
    /// Secure random number generator (using OsRng)
    SECURE_RANDOM = 1,
}

/// Random distribution type
#[derive(Debug, Clone, Copy, PartialEq, Eq)]
pub enum zranddist {
    /// QUASIUNIFORM distribution: faster but slightly biased
    /// Uses formula: random(bits) * n / 2^bits
    QUASIUNIFORM = 0,
    /// UNIFORM distribution: unbiased using rejection sampling
    /// Generates random numbers until one is <= n
    UNIFORM = 1,
}

/// Generate a random BigInt with exactly the specified number of bits.
/// The result will be in the range [0, 2^bits).
///
/// This is a helper function used internally by zrand.
///
/// # Arguments
/// * `bits` - The number of random bits to generate
/// * `dev` - The random device to use (FAST_RANDOM or SECURE_RANDOM)
///
/// # Returns
/// * `z_t` - A BigInt with the specified number of random bits
///
/// # Examples
/// ```
/// use zahl::zrand::{zrand_get_random_bits, zranddev};
///
/// let result = zrand_get_random_bits(128, zranddev::FAST_RANDOM);
/// assert!(result.bits() <= 128);
/// ```
pub fn zrand_get_random_bits(bits: usize, dev: zranddev) -> z_t {
    // Handle zero bits case
    if bits == 0 {
        return z_t::zero();
    }

    // Generate random bits based on device type
    match dev {
        zranddev::FAST_RANDOM => {
            let mut rng = thread_rng();
            rng.gen_biguint(bits as u64).into()
        }
        zranddev::SECURE_RANDOM => {
            let mut rng = OsRng;
            rng.gen_biguint(bits as u64).into()
        }
    }
}

/// Generate a random BigInt in the range [0, n] using the specified device and distribution.
///
/// # Arguments
/// * `dev` - The random device to use (FAST_RANDOM or SECURE_RANDOM)
/// * `dist` - The distribution type (QUASIUNIFORM or UNIFORM)
/// * `n` - The upper bound (inclusive) for the random number
///
/// # Returns
/// * `Result<z_t>` - A random BigInt in [0, n], or an error if n is negative
///
/// # Errors
/// * `ZahlError::InvalidDomain` - if n is negative
///
/// # Examples
/// ```
/// use zahl::z_t;
/// use zahl::zrand::{zrand, zranddev, zranddist};
///
/// let n = z_t::from(100);
/// let result = zrand(zranddev::FAST_RANDOM, zranddist::UNIFORM, &n).unwrap();
/// assert!(result >= z_t::from(0) && result <= n);
/// ```
pub fn zrand(dev: zranddev, dist: zranddist, n: &z_t) -> Result<z_t> {
    use crate::zbits::zbits;
    use crate::zcmpmag::zcmpmag;
    use crate::zadd::zadd;
    use crate::zmul::zmul;
    use crate::zrsh::zrsh;

    // If n is zero, return zero
    if n.is_zero() {
        return Ok(z_t::zero());
    }

    // Check that n is non-negative
    if n < &z_t::zero() {
        return Err(ZahlError::InvalidDomain);
    }

    match dist {
        zranddist::QUASIUNIFORM => {
            // QUASIUNIFORM distribution:
            // 1. Get number of bits in n
            // 2. Generate random number with that many bits
            // 3. Compute (random + 1) * n / 2^bits

            let bits = zbits(n);
            let mut r = zrand_get_random_bits(bits, dev);

            // r = r + 1
            let one = z_t::one();
            let mut temp = z_t::zero();
            zadd(&mut temp, &r, &one);
            r = temp;

            // r = r * n
            let mut temp = z_t::zero();
            zmul(&mut temp, &r, n);
            r = temp;

            // r = r >> bits
            let mut result = z_t::zero();
            zrsh(&mut result, &r, bits);

            Ok(result)
        }
        zranddist::UNIFORM => {
            // UNIFORM distribution with rejection sampling:
            // Generate random numbers with same bit length as n
            // until we get one that is <= n

            let bits = zbits(n);
            let mut r;

            loop {
                r = zrand_get_random_bits(bits, dev);

                // Compare magnitude: if r <= n, accept it
                if zcmpmag(&r, n) <= 0 {
                    break;
                }
                // Otherwise, reject and try again
            }

            Ok(r)
        }
    }
}

#[cfg(test)]
mod tests {
    use super::*;
    use num_bigint::BigInt;

    #[test]
    fn test_zrand_get_random_bits_zero() {
        let result = zrand_get_random_bits(0, zranddev::FAST_RANDOM);
        assert_eq!(result, BigInt::from(0));
    }

    #[test]
    fn test_zrand_get_random_bits_small() {
        let result = zrand_get_random_bits(8, zranddev::FAST_RANDOM);
        // Result should fit in 8 bits: 0 <= result < 256
        assert!(result >= BigInt::from(0));
        assert!(result < BigInt::from(256));
    }

    #[test]
    fn test_zrand_get_random_bits_secure() {
        let result = zrand_get_random_bits(16, zranddev::SECURE_RANDOM);
        // Result should fit in 16 bits: 0 <= result < 65536
        assert!(result >= BigInt::from(0));
        assert!(result < BigInt::from(65536));
    }

    #[test]
    fn test_zrand_zero_bound() {
        let n = BigInt::from(0);
        let result = zrand(zranddev::FAST_RANDOM, zranddist::UNIFORM, &n).unwrap();
        assert_eq!(result, BigInt::from(0));
    }

    #[test]
    fn test_zrand_negative_bound() {
        let n = BigInt::from(-10);
        let result = zrand(zranddev::FAST_RANDOM, zranddist::UNIFORM, &n);
        assert!(result.is_err());
        assert!(matches!(result.unwrap_err(), ZahlError::InvalidDomain));
    }

    #[test]
    fn test_zrand_uniform_range() {
        let n = BigInt::from(100);
        for _ in 0..10 {
            let result = zrand(zranddev::FAST_RANDOM, zranddist::UNIFORM, &n).unwrap();
            assert!(result >= BigInt::from(0));
            assert!(result <= n);
        }
    }

    #[test]
    fn test_zrand_quasiuniform_range() {
        let n = BigInt::from(100);
        for _ in 0..10 {
            let result = zrand(zranddev::FAST_RANDOM, zranddist::QUASIUNIFORM, &n).unwrap();
            assert!(result >= BigInt::from(0));
            assert!(result <= n);
        }
    }

    #[test]
    fn test_zrand_large_number() {
        // Test with a large number
        let n = BigInt::from(1u64 << 32);
        let result = zrand(zranddev::FAST_RANDOM, zranddist::UNIFORM, &n).unwrap();
        assert!(result >= BigInt::from(0));
        assert!(result <= n);
    }

    #[test]
    fn test_zrand_secure_random() {
        let n = BigInt::from(1000);
        let result = zrand(zranddev::SECURE_RANDOM, zranddist::UNIFORM, &n).unwrap();
        assert!(result >= BigInt::from(0));
        assert!(result <= n);
    }
}
