// libzahl Rust translation
// Main library file

// Re-export BigInt as z_t and as BigInt
pub use num_bigint::BigInt as z_t;
pub use num_bigint::BigInt;

// Re-export error types and functions from zerror module
// Note: zerror enum and zerror() function are accessed via zerror::zerror and zerror::zerror()
pub use zerror::{ZahlError, Result, set_error, clear_error};

// Re-export random number generation types from zrand module
pub use zrand::{zranddev, zranddist};

// Re-export primality test result from zptest module
pub use zptest::zprimality;

// Module declarations
pub mod allocator;
pub mod zabs;
pub mod zadd;
pub mod zand;
pub mod zbits;
pub mod zbset;
pub mod zbtest;
pub mod zcmp;
pub mod zcmpi;
pub mod zcmpmag;
pub mod zcmpu;
pub mod zdiv;
pub mod zdivmod;
pub mod zerror;
pub mod zfree;
pub mod zgcd;
pub mod zload;
pub mod zlsb;
pub mod zlsh;
pub mod zmod;
pub mod zmodmul;
pub mod zmodpow;
pub mod zmodpowu;
pub mod zmodsqr;
pub mod zmul;
pub mod zneg;
pub mod znot;
pub mod zor;
pub mod zperror;
pub mod zpow;
pub mod zpowu;
pub mod zptest;
pub mod zrand;
pub mod zrsh;
pub mod zsave;
pub mod zset;
pub mod zseti;
pub mod zsets;
pub mod zsetu;
pub mod zsetup;
pub mod zsplit;
pub mod zsqr;
pub mod zstr;
pub mod zstr_length;
pub mod zsub;
pub mod zswap;
pub mod ztrunc;
pub mod zunsetup;
pub mod zxor;
