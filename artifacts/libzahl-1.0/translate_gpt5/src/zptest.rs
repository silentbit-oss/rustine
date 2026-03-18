// Module: zptest
// Implements Miller-Rabin primality testing

use crate::z_t;
use crate::zcmpu::zcmpu;
use crate::zsub::zsub_unsigned;
use crate::zlsb::zlsb;
use crate::zrsh::zrsh;
use crate::zrand::{zrand, zranddev, zranddist};
use crate::zadd::zadd_unsigned;
use crate::zmodpow::zmodpow;
use crate::zcmp::zcmp;
use crate::zsqr::zsqr;
use crate::zmod::zmod;
use crate::zswap::zswap;
use num_traits::Zero;
use num_integer::Integer;
use num_bigint::BigInt;

/// zprimality test result
#[derive(Debug, Clone, Copy, PartialEq, Eq)]
pub enum zprimality {
    /// The number is definitely composite (not prime)
    NONPRIME = 0,
    /// The number is probably prime (with high confidence)
    PROBABLY_PRIME = 1,
    /// The number is definitely prime (for small numbers)
    PRIME = 2,
}

/// Test the primality of a BigInt using Miller-Rabin primality test.
///
/// This function implements the Miller-Rabin probabilistic primality test.
/// It performs `t` rounds of testing to determine if `n` is prime.
///
/// # Arguments
/// * `witness` - Optional output parameter. If `NONPRIME` is returned, this will
///               contain a witness to n's compositeness (a value that proves n is composite)
/// * `n` - The number to test for primality
/// * `t` - The number of test rounds (higher values give more confidence)
///
/// # Returns
/// * `zprimality::PRIME` - n is definitely prime (for small values 2 or 3)
/// * `zprimality::PROBABLY_PRIME` - n is probably prime with confidence (1 - 4^(-t))
/// * `zprimality::NONPRIME` - n is definitely composite, witness contains proof
///
/// # Examples
/// ```
/// use libzahl::{z_t, zptest::{zptest, zprimality}};
///
/// let mut witness = z_t::from(0);
/// let n = z_t::from(17);
/// let result = zptest(Some(&mut witness), &n, 10);
/// assert_eq!(result, zprimality::PROBABLY_PRIME);
///
/// let n = z_t::from(15);
/// let result = zptest(Some(&mut witness), &n, 10);
/// assert_eq!(result, zprimality::NONPRIME);
/// ```
pub fn zptest(witness: Option<&mut z_t>, n: &z_t, t: i32) -> zprimality {
    // Handle small values: n <= 3
    if zcmpu(n, 3) <= 0 {
        if zcmpu(n, 1) <= 0 {
            // n <= 1: not prime
            if let Some(w) = witness {
                *w = n.clone();
            }
            return zprimality::NONPRIME;
        } else {
            // n == 2 or n == 3: definitely prime
            return zprimality::PRIME;
        }
    }

    // Check if n is even
    if n.is_even() {
        if let Some(w) = witness {
            *w = n.clone();
        }
        return zprimality::NONPRIME;
    }

    // Miller-Rabin test:
    // Write n-1 as 2^r * d where d is odd
    let mut n1 = BigInt::zero();
    let mut n4 = BigInt::zero();
    let one = BigInt::from(1u64);
    let two = BigInt::from(2u64);
    let four = BigInt::from(4u64);

    // n1 = n - 1
    zsub_unsigned(&mut n1, n, &one);
    // n4 = n - 4
    zsub_unsigned(&mut n4, n, &four);

    // Find r: the number of times 2 divides n-1
    let r = zlsb(&n1);

    // d = (n-1) / 2^r
    let mut d = BigInt::zero();
    zrsh(&mut d, &n1, r);

    // Perform t rounds of testing
    for _ in 0..t {
        // Pick random a in [2, n-2]
        // First generate random in [0, n-4], then add 2
        let mut a = match zrand(zranddev::FAST_RANDOM, zranddist::UNIFORM, &n4) {
            Ok(val) => val,
            Err(_) => return zprimality::NONPRIME,
        };
        let a_clone = a.clone();
        zadd_unsigned(&mut a, &a_clone, &two);

        // x = a^d mod n
        let mut x = BigInt::zero();
        if zmodpow(&mut x, &a, &d, n).is_err() {
            return zprimality::NONPRIME;
        }

        // If x == 1 or x == n-1, continue to next round
        if zcmp(&x, &one) == 0 || zcmp(&x, &n1) == 0 {
            continue;
        }

        // Square x repeatedly r-1 times
        let mut composite = true;
        for _ in 1..r {
            // x = x^2 mod n
            let x_clone = x.clone();
            zsqr(&mut x, &x_clone);
            let x_clone = x.clone();
            if zmod(&mut x, &x_clone, n).is_err() {
                return zprimality::NONPRIME;
            }

            // If x == 1, we found a nontrivial square root of 1
            if zcmp(&x, &one) == 0 {
                if let Some(w) = witness {
                    zswap(w, &mut a);
                }
                return zprimality::NONPRIME;
            }

            // If x == n-1, this round passes
            if zcmp(&x, &n1) == 0 {
                composite = false;
                break;
            }
        }

        // If we didn't find x == n-1, n is composite
        if composite {
            if let Some(w) = witness {
                zswap(w, &mut a);
            }
            return zprimality::NONPRIME;
        }
    }

    // All rounds passed: probably prime
    zprimality::PROBABLY_PRIME
}

#[cfg(test)]
mod tests {
    use super::*;
    use num_bigint::BigInt;

    #[test]
    fn test_zptest_small_primes() {
        let mut witness = BigInt::zero();

        // 2 is prime
        let n = BigInt::from(2);
        assert_eq!(zptest(Some(&mut witness), &n, 5), zprimality::PRIME);

        // 3 is prime
        let n = BigInt::from(3);
        assert_eq!(zptest(Some(&mut witness), &n, 5), zprimality::PRIME);
    }

    #[test]
    fn test_zptest_small_composites() {
        let mut witness = BigInt::zero();

        // 0 is not prime
        let n = BigInt::from(0);
        assert_eq!(zptest(Some(&mut witness), &n, 5), zprimality::NONPRIME);

        // 1 is not prime
        let n = BigInt::from(1);
        assert_eq!(zptest(Some(&mut witness), &n, 5), zprimality::NONPRIME);

        // 4 is not prime (even)
        let n = BigInt::from(4);
        assert_eq!(zptest(Some(&mut witness), &n, 5), zprimality::NONPRIME);
    }

    #[test]
    fn test_zptest_larger_primes() {
        let mut witness = BigInt::zero();

        // 17 is prime
        let n = BigInt::from(17);
        assert_eq!(zptest(Some(&mut witness), &n, 10), zprimality::PROBABLY_PRIME);

        // 97 is prime
        let n = BigInt::from(97);
        assert_eq!(zptest(Some(&mut witness), &n, 10), zprimality::PROBABLY_PRIME);
    }

    #[test]
    fn test_zptest_larger_composites() {
        let mut witness = BigInt::zero();

        // 15 is not prime (3 * 5)
        let n = BigInt::from(15);
        assert_eq!(zptest(Some(&mut witness), &n, 10), zprimality::NONPRIME);

        // 91 is not prime (7 * 13)
        let n = BigInt::from(91);
        assert_eq!(zptest(Some(&mut witness), &n, 10), zprimality::NONPRIME);
    }

    #[test]
    fn test_zptest_no_witness() {
        // Test without witness parameter
        let n = BigInt::from(17);
        assert_eq!(zptest(None, &n, 10), zprimality::PROBABLY_PRIME);

        let n = BigInt::from(15);
        assert_eq!(zptest(None, &n, 10), zprimality::NONPRIME);
    }

    #[test]
    fn test_zptest_large_prime() {
        let mut witness = BigInt::zero();

        // 1000000007 is prime
        let n = BigInt::from(1000000007u64);
        assert_eq!(zptest(Some(&mut witness), &n, 20), zprimality::PROBABLY_PRIME);
    }

    #[test]
    fn test_zptest_large_composite() {
        let mut witness = BigInt::zero();

        // 1000000008 is even, so composite
        let n = BigInt::from(1000000008u64);
        assert_eq!(zptest(Some(&mut witness), &n, 20), zprimality::NONPRIME);
    }
}
