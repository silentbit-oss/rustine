use crate::*;

#[derive(Debug, Clone, Copy, PartialEq, Eq)]
pub enum MiOptionE {
    MiOptionShowErrors,
    MiOptionShowStats,
    MiOptionVerbose,
    MiOptionEagerCommit,
    MiOptionArenaEagerCommit,
    MiOptionPurgeDecommits,
    MiOptionAllowLargeOsPages,
    MiOptionReserveHugeOsPages,
    MiOptionReserveHugeOsPagesAt,
    MiOptionReserveOsMemory,
    MiOptionDeprecatedSegmentCache,
    MiOptionDeprecatedPageReset,
    MiOptionAbandonedPagePurge,
    MiOptionDeprecatedSegmentReset,
    MiOptionEagerCommitDelay,
    MiOptionPurgeDelay,
    MiOptionUseNumaNodes,
    MiOptionDisallowOsAlloc,
    MiOptionOsTag,
    MiOptionMaxErrors,
    MiOptionMaxWarnings,
    MiOptionMaxSegmentReclaim,
    MiOptionDestroyOnExit,
    MiOptionArenaReserve,
    MiOptionArenaPurgeMult,
    MiOptionPurgeExtendDelay,
    MiOptionAbandonedReclaimOnFree,
    MiOptionDisallowArenaAlloc,
    MiOptionRetryOnOom,
    MiOptionVisitAbandoned,
    MiOptionGuardedMin,
    MiOptionGuardedMax,
    MiOptionGuardedPrecise,
    MiOptionGuardedSampleRate,
    MiOptionGuardedSampleSeed,
    MiOptionTargetSegmentsPerThread,
    MiOptionGenericCollect,
    _MiOptionLast,
}

pub type MiOptionT = MiOptionE;

pub struct MiOptionAliases;

impl MiOptionAliases {
    pub const MI_OPTION_LARGE_OS_PAGES: MiOptionE = MiOptionE::MiOptionAllowLargeOsPages;
    pub const MI_OPTION_EAGER_REGION_COMMIT: MiOptionE = MiOptionE::MiOptionArenaEagerCommit;
    pub const MI_OPTION_RESET_DECOMMITS: MiOptionE = MiOptionE::MiOptionPurgeDecommits;
    pub const MI_OPTION_RESET_DELAY: MiOptionE = MiOptionE::MiOptionPurgeDelay;
    pub const MI_OPTION_ABANDONED_PAGE_RESET: MiOptionE = MiOptionE::MiOptionAbandonedPagePurge;
    pub const MI_OPTION_LIMIT_OS_ALLOC: MiOptionE = MiOptionE::MiOptionDisallowOsAlloc;
}

