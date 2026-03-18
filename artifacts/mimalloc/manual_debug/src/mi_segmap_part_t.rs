use crate::*;
use std::sync::atomic::AtomicUsize;
pub struct MiSegmapPartS {
    pub memid: MiMemidS,
    pub map: [std::sync::atomic::AtomicUsize; 1008],
}

impl Clone for MiSegmapPartS {
    fn clone(&self) -> Self {
        Self {
            memid: self.memid.clone(),
            map: std::array::from_fn(|i| {
                let val = self.map[i].load(std::sync::atomic::Ordering::Relaxed);
                std::sync::atomic::AtomicUsize::new(val)
            }),
        }
    }
}

pub type MiSegmapPartT = MiSegmapPartS;

