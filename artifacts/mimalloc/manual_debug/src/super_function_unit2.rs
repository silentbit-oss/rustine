use crate::*;
use lazy_static::lazy_static;
use std::ffi::CStr;
use std::os::raw::c_char;
use std::sync::Mutex;
use std::sync::atomic::AtomicUsize;
use std::sync::atomic::Ordering;

pub fn mi_option_init(desc: &mut MiOptionDescT) {
    let mut s = [0u8; 64 + 1];
    let mut buf = [0u8; 64 + 1];
    
    let buf_len = buf.len();
    let s_len = s.len();
    
    _mi_strlcpy(&mut buf, b"mimalloc_");
    _mi_strlcat(&mut buf, desc.name.as_ref().unwrap().as_bytes(), buf_len);
    
    let mut found = _mi_getenv(
        Some(unsafe { CStr::from_bytes_until_nul(&buf).unwrap().to_str().unwrap() }),
        &mut s,
        s_len
    );
    
    if !found && desc.legacy_name.is_some() {
        _mi_strlcpy(&mut buf, b"mimalloc_");
        _mi_strlcat(&mut buf, desc.legacy_name.as_ref().unwrap().as_bytes(), buf_len);
        
        found = _mi_getenv(
            Some(unsafe { CStr::from_bytes_until_nul(&buf).unwrap().to_str().unwrap() }),
            &mut s,
            s_len
        );
        
        if found {
            let msg = format!(
                "environment option \"mimalloc_{}\" is deprecated -- use \"mimalloc_{}\" instead.\n",
                desc.legacy_name.as_ref().unwrap(),
                desc.name.as_ref().unwrap()
            );
            let c_msg = std::ffi::CString::new(msg).unwrap();
            _mi_warning_message(&c_msg);
        }
    }
    
    if found {
        helper_mi_option_init_1(desc, &s, &mut buf);
    } else if !_mi_preloading() {
        desc.init = MiInitT::DEFAULTED;
    }
}


pub fn _mi_warning_message(msg: &CStr) {
    if !mi_option_is_enabled(MiOptionT::MiOptionVerbose) {
        if !mi_option_is_enabled(MiOptionT::MiOptionShowErrors) {
            return;
        }
        if (MI_MAX_WARNING_COUNT.load(Ordering::Acquire) >= 0) && 
           ((WARNING_COUNT.fetch_add(1, Ordering::AcqRel) as i64) > MI_MAX_WARNING_COUNT.load(Ordering::Acquire)) {
            return;
        }
    }
    
    mi_vfprintf_thread(None, std::ptr::null_mut(), Some("mimalloc: warning: "), msg, std::ptr::null_mut());
}


lazy_static! {
    pub static ref OPTIONS: Mutex<[MiOptionDescT; 40]> = Mutex::new([
        MiOptionDescS { value: 1, init: MiInitT::UNINIT, option: MiOptionT::MiOptionShowErrors, name: Some("show_errors".to_string()), legacy_name: Some("0".to_string()) },
        MiOptionDescS { value: 0, init: MiInitT::UNINIT, option: MiOptionT::MiOptionShowStats, name: Some("show_stats".to_string()), legacy_name: Some("0".to_string()) },
        MiOptionDescS { value: 0, init: MiInitT::UNINIT, option: MiOptionT::MiOptionVerbose, name: Some("verbose".to_string()), legacy_name: Some("0".to_string()) },
        MiOptionDescS { value: 1, init: MiInitT::UNINIT, option: MiOptionT::MiOptionEagerCommit, name: Some("eager_commit".to_string()), legacy_name: Some("0".to_string()) },
        MiOptionDescS { value: 2, init: MiInitT::UNINIT, option: MiOptionT::MiOptionArenaEagerCommit, name: Some("arena_eager_commit".to_string()), legacy_name: Some("eager_region_commit".to_string()) },
        MiOptionDescS { value: 1, init: MiInitT::UNINIT, option: MiOptionT::MiOptionPurgeDecommits, name: Some("purge_decommits".to_string()), legacy_name: Some("reset_decommits".to_string()) },
        MiOptionDescS { value: 2, init: MiInitT::UNINIT, option: MiOptionT::MiOptionAllowLargeOsPages, name: Some("allow_large_os_pages".to_string()), legacy_name: Some("large_os_pages".to_string()) },
        MiOptionDescS { value: 0, init: MiInitT::UNINIT, option: MiOptionT::MiOptionReserveHugeOsPages, name: Some("reserve_huge_os_pages".to_string()), legacy_name: Some("0".to_string()) },
        MiOptionDescS { value: -1, init: MiInitT::UNINIT, option: MiOptionT::MiOptionReserveHugeOsPagesAt, name: Some("reserve_huge_os_pages_at".to_string()), legacy_name: Some("0".to_string()) },
        MiOptionDescS { value: 0, init: MiInitT::UNINIT, option: MiOptionT::MiOptionReserveOsMemory, name: Some("reserve_os_memory".to_string()), legacy_name: Some("0".to_string()) },
        MiOptionDescS { value: 0, init: MiInitT::UNINIT, option: MiOptionT::MiOptionDeprecatedSegmentCache, name: Some("deprecated_segment_cache".to_string()), legacy_name: Some("0".to_string()) },
        MiOptionDescS { value: 0, init: MiInitT::UNINIT, option: MiOptionT::MiOptionDeprecatedPageReset, name: Some("deprecated_page_reset".to_string()), legacy_name: Some("0".to_string()) },
        MiOptionDescS { value: 0, init: MiInitT::UNINIT, option: MiOptionT::MiOptionAbandonedPagePurge, name: Some("abandoned_page_purge".to_string()), legacy_name: Some("abandoned_page_reset".to_string()) },
        MiOptionDescS { value: 0, init: MiInitT::UNINIT, option: MiOptionT::MiOptionDeprecatedSegmentReset, name: Some("deprecated_segment_reset".to_string()), legacy_name: Some("0".to_string()) },
        MiOptionDescS { value: 1, init: MiInitT::UNINIT, option: MiOptionT::MiOptionEagerCommitDelay, name: Some("eager_commit_delay".to_string()), legacy_name: Some("0".to_string()) },
        MiOptionDescS { value: 10, init: MiInitT::UNINIT, option: MiOptionT::MiOptionPurgeDelay, name: Some("purge_delay".to_string()), legacy_name: Some("reset_delay".to_string()) },
        MiOptionDescS { value: 0, init: MiInitT::UNINIT, option: MiOptionT::MiOptionUseNumaNodes, name: Some("use_numa_nodes".to_string()), legacy_name: Some("0".to_string()) },
        MiOptionDescS { value: 0, init: MiInitT::UNINIT, option: MiOptionT::MiOptionDisallowOsAlloc, name: Some("disallow_os_alloc".to_string()), legacy_name: Some("limit_os_alloc".to_string()) },
        MiOptionDescS { value: 100, init: MiInitT::UNINIT, option: MiOptionT::MiOptionOsTag, name: Some("os_tag".to_string()), legacy_name: Some("0".to_string()) },
        MiOptionDescS { value: 32, init: MiInitT::UNINIT, option: MiOptionT::MiOptionMaxErrors, name: Some("max_errors".to_string()), legacy_name: Some("0".to_string()) },
        MiOptionDescS { value: 32, init: MiInitT::UNINIT, option: MiOptionT::MiOptionMaxWarnings, name: Some("max_warnings".to_string()), legacy_name: Some("0".to_string()) },
        MiOptionDescS { value: 10, init: MiInitT::UNINIT, option: MiOptionT::MiOptionMaxSegmentReclaim, name: Some("max_segment_reclaim".to_string()), legacy_name: Some("0".to_string()) },
        MiOptionDescS { value: 0, init: MiInitT::UNINIT, option: MiOptionT::MiOptionDestroyOnExit, name: Some("destroy_on_exit".to_string()), legacy_name: Some("0".to_string()) },
        MiOptionDescS { value: 1024 * 1024, init: MiInitT::UNINIT, option: MiOptionT::MiOptionArenaReserve, name: Some("arena_reserve".to_string()), legacy_name: Some("0".to_string()) },
        MiOptionDescS { value: 10, init: MiInitT::UNINIT, option: MiOptionT::MiOptionArenaPurgeMult, name: Some("arena_purge_mult".to_string()), legacy_name: Some("0".to_string()) },
        MiOptionDescS { value: 1, init: MiInitT::UNINIT, option: MiOptionT::MiOptionPurgeExtendDelay, name: Some("purge_extend_delay".to_string()), legacy_name: Some("decommit_extend_delay".to_string()) },
        MiOptionDescS { value: 0, init: MiInitT::UNINIT, option: MiOptionT::MiOptionAbandonedReclaimOnFree, name: Some("abandoned_reclaim_on_free".to_string()), legacy_name: Some("0".to_string()) },
        MiOptionDescS { value: 0, init: MiInitT::UNINIT, option: MiOptionT::MiOptionDisallowArenaAlloc, name: Some("disallow_arena_alloc".to_string()), legacy_name: Some("0".to_string()) },
        MiOptionDescS { value: 400, init: MiInitT::UNINIT, option: MiOptionT::MiOptionRetryOnOom, name: Some("retry_on_oom".to_string()), legacy_name: Some("0".to_string()) },
        MiOptionDescS { value: 0, init: MiInitT::UNINIT, option: MiOptionT::MiOptionVisitAbandoned, name: Some("visit_abandoned".to_string()), legacy_name: Some("0".to_string()) },
        MiOptionDescS { value: 0, init: MiInitT::UNINIT, option: MiOptionT::MiOptionGuardedMin, name: Some("guarded_min".to_string()), legacy_name: Some("0".to_string()) },
        MiOptionDescS { value: (1024 * 1024 * 1024) as i64, init: MiInitT::UNINIT, option: MiOptionT::MiOptionGuardedMax, name: Some("guarded_max".to_string()), legacy_name: Some("0".to_string()) },
        MiOptionDescS { value: 0, init: MiInitT::UNINIT, option: MiOptionT::MiOptionGuardedPrecise, name: Some("guarded_precise".to_string()), legacy_name: Some("0".to_string()) },
        MiOptionDescS { value: 0, init: MiInitT::UNINIT, option: MiOptionT::MiOptionGuardedSampleRate, name: Some("guarded_sample_rate".to_string()), legacy_name: Some("0".to_string()) },
        MiOptionDescS { value: 0, init: MiInitT::UNINIT, option: MiOptionT::MiOptionGuardedSampleSeed, name: Some("guarded_sample_seed".to_string()), legacy_name: Some("0".to_string()) },
        MiOptionDescS { value: 0, init: MiInitT::UNINIT, option: MiOptionT::MiOptionTargetSegmentsPerThread, name: Some("target_segments_per_thread".to_string()), legacy_name: Some("0".to_string()) },
        MiOptionDescS { value: 10000, init: MiInitT::UNINIT, option: MiOptionT::MiOptionGenericCollect, name: Some("generic_collect".to_string()), legacy_name: Some("0".to_string()) },
        MiOptionDescS { value: 0, init: MiInitT::UNINIT, option: MiOptionT::_MiOptionLast, name: None, legacy_name: None },
        MiOptionDescS { value: 0, init: MiInitT::UNINIT, option: MiOptionT::_MiOptionLast, name: None, legacy_name: None },
        MiOptionDescS { value: 0, init: MiInitT::UNINIT, option: MiOptionT::_MiOptionLast, name: None, legacy_name: None },
    ]);
}

pub fn mi_option_get(option: MiOptionT) -> i64 {
    // Check bounds - equivalent to the C ternary assertion
    if (option as usize) < (MiOptionT::MiOptionShowErrors as usize) || (option as usize) >= (MiOptionT::_MiOptionLast as usize) {
        return 0;
    }
    
    let options_guard = OPTIONS.lock().unwrap();
    let desc = &options_guard[option as usize];
    
    // Verify the option field matches - equivalent to the C ternary assertion
    if desc.option != option {
        return 0;
    }
    
    // Check if initialization is needed
    if desc.init == MiInitT::UNINIT {
        // We need to initialize, but we have an immutable reference
        // Drop the guard and get a mutable one
        drop(options_guard);
        let mut options_guard_mut = OPTIONS.lock().unwrap();
        let desc_mut = &mut options_guard_mut[option as usize];
        mi_option_init(desc_mut);
        return desc_mut.value;
    }
    
    desc.value
}

pub fn mi_option_is_enabled(option: MiOptionT) -> bool {
    mi_option_get(option) != 0
}
