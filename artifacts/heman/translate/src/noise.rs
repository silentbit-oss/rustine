use crate::*;
use rand::Rng;

#[inline]
pub fn fastFloor(x: f64) -> i32 {
    let xi = x as i32;
    if x < xi as f64 {
        xi - 1
    } else {
        xi
    }
}
pub fn helper_open_simplex_noise2_1(
    dx_ext_ref: &mut f64,
    dy_ext_ref: &mut f64,
    xsv_ext_ref: &mut i32,
    ysv_ext_ref: &mut i32,
    xsb: i32,
    ysb: i32,
    xins: f64,
    yins: f64,
    inSum: f64,
    dx0: f64,
    dy0: f64,
) {
    let mut dx_ext = *dx_ext_ref;
    let mut dy_ext = *dy_ext_ref;
    let mut xsv_ext = *xsv_ext_ref;
    let mut ysv_ext = *ysv_ext_ref;
    let zins = 1.0 - inSum;

    if zins > xins || zins > yins {
        if xins > yins {
            xsv_ext = xsb + 1;
            ysv_ext = ysb - 1;
            dx_ext = dx0 - 1.0;
            dy_ext = dy0 + 1.0;
        } else {
            xsv_ext = xsb - 1;
            ysv_ext = ysb + 1;
            dx_ext = dx0 + 1.0;
            dy_ext = dy0 - 1.0;
        }
    } else {
        xsv_ext = xsb + 1;
        ysv_ext = ysb + 1;
        dx_ext = (dx0 - 1.0) - (2.0 * 0.366025403784439);
        dy_ext = (dy0 - 1.0) - (2.0 * 0.366025403784439);
    }

    *dx_ext_ref = dx_ext;
    *dy_ext_ref = dy_ext;
    *xsv_ext_ref = xsv_ext;
    *ysv_ext_ref = ysv_ext;
}
pub fn helper_open_simplex_noise2_2(
    xsb_ref: &mut i32,
    ysb_ref: &mut i32,
    dx0_ref: &mut f64,
    dy0_ref: &mut f64,
    dx_ext_ref: &mut f64,
    dy_ext_ref: &mut f64,
    xsv_ext_ref: &mut i32,
    ysv_ext_ref: &mut i32,
    xins: f64,
    yins: f64,
    inSum: f64,
) {
    let mut xsb = *xsb_ref;
    let mut ysb = *ysb_ref;
    let mut dx0 = *dx0_ref;
    let mut dy0 = *dy0_ref;
    let mut dx_ext = *dx_ext_ref;
    let mut dy_ext = *dy_ext_ref;
    let mut xsv_ext = *xsv_ext_ref;
    let mut ysv_ext = *ysv_ext_ref;
    
    let zins = 2.0 - inSum;
    
    if zins < xins || zins < yins {
        if xins > yins {
            xsv_ext = xsb + 2;
            ysv_ext = ysb + 0;
            dx_ext = (dx0 - 2.0) - (2.0 * 0.366025403784439);
            dy_ext = (dy0 + 0.0) - (2.0 * 0.366025403784439);
        } else {
            xsv_ext = xsb + 0;
            ysv_ext = ysb + 2;
            dx_ext = (dx0 + 0.0) - (2.0 * 0.366025403784439);
            dy_ext = (dy0 - 2.0) - (2.0 * 0.366025403784439);
        }
    } else {
        dx_ext = dx0;
        dy_ext = dy0;
        xsv_ext = xsb;
        ysv_ext = ysb;
    }
    
    xsb += 1;
    ysb += 1;
    dx0 = (dx0 - 1.0) - (2.0 * 0.366025403784439);
    dy0 = (dy0 - 1.0) - (2.0 * 0.366025403784439);
    
    *xsb_ref = xsb;
    *ysb_ref = ysb;
    *dx0_ref = dx0;
    *dy0_ref = dy0;
    *dx_ext_ref = dx_ext;
    *dy_ext_ref = dy_ext;
    *xsv_ext_ref = xsv_ext;
    *ysv_ext_ref = ysv_ext;
}
pub fn helper_helper_open_simplex_noise3_1_1(
    dx_ext0_ref: &mut f64,
    dy_ext0_ref: &mut f64,
    dz_ext0_ref: &mut f64,
    dx_ext1_ref: &mut f64,
    dy_ext1_ref: &mut f64,
    dz_ext1_ref: &mut f64,
    xsv_ext0_ref: &mut i32,
    ysv_ext0_ref: &mut i32,
    zsv_ext0_ref: &mut i32,
    xsv_ext1_ref: &mut i32,
    ysv_ext1_ref: &mut i32,
    zsv_ext1_ref: &mut i32,
    xsb: i32,
    ysb: i32,
    zsb: i32,
    dx0: f64,
    dy0: f64,
    dz0: f64,
    aPoint: i8,
    aScore: f64,
    bPoint: i8,
    bScore: f64,
) {
    let mut dx_ext0 = *dx_ext0_ref;
    let mut dy_ext0 = *dy_ext0_ref;
    let mut dz_ext0 = *dz_ext0_ref;
    let mut dx_ext1 = *dx_ext1_ref;
    let mut dy_ext1 = *dy_ext1_ref;
    let mut dz_ext1 = *dz_ext1_ref;
    let mut xsv_ext0 = *xsv_ext0_ref;
    let mut ysv_ext0 = *ysv_ext0_ref;
    let mut zsv_ext0 = *zsv_ext0_ref;
    let mut xsv_ext1 = *xsv_ext1_ref;
    let mut ysv_ext1 = *ysv_ext1_ref;
    let mut zsv_ext1 = *zsv_ext1_ref;

    let c = if bScore > aScore { bPoint } else { aPoint };

    if (c & 0x01) == 0 {
        xsv_ext0 = xsb - 1;
        xsv_ext1 = xsb;
        dx_ext0 = dx0 + 1.0;
        dx_ext1 = dx0;
    } else {
        xsv_ext0 = xsb + 1;
        xsv_ext1 = xsb + 1;
        dx_ext0 = dx0 - 1.0;
        dx_ext1 = dx0 - 1.0;
    }

    if (c & 0x02) == 0 {
        ysv_ext0 = ysb;
        ysv_ext1 = ysb;
        dy_ext0 = dy0;
        dy_ext1 = dy0;
        if (c & 0x01) == 0 {
            ysv_ext1 -= 1;
            dy_ext1 += 1.0;
        } else {
            ysv_ext0 -= 1;
            dy_ext0 += 1.0;
        }
    } else {
        ysv_ext0 = ysb + 1;
        ysv_ext1 = ysb + 1;
        dy_ext0 = dy0 - 1.0;
        dy_ext1 = dy0 - 1.0;
    }

    if (c & 0x04) == 0 {
        zsv_ext0 = zsb;
        zsv_ext1 = zsb - 1;
        dz_ext0 = dz0;
        dz_ext1 = dz0 + 1.0;
    } else {
        zsv_ext0 = zsb + 1;
        zsv_ext1 = zsb + 1;
        dz_ext0 = dz0 - 1.0;
        dz_ext1 = dz0 - 1.0;
    }

    *dx_ext0_ref = dx_ext0;
    *dy_ext0_ref = dy_ext0;
    *dz_ext0_ref = dz_ext0;
    *dx_ext1_ref = dx_ext1;
    *dy_ext1_ref = dy_ext1;
    *dz_ext1_ref = dz_ext1;
    *xsv_ext0_ref = xsv_ext0;
    *ysv_ext0_ref = ysv_ext0;
    *zsv_ext0_ref = zsv_ext0;
    *xsv_ext1_ref = xsv_ext1;
    *ysv_ext1_ref = ysv_ext1;
    *zsv_ext1_ref = zsv_ext1;
}
pub fn helper_helper_open_simplex_noise3_1_2(
    dx_ext0_ref: &mut f64,
    dy_ext0_ref: &mut f64,
    dz_ext0_ref: &mut f64,
    dx_ext1_ref: &mut f64,
    dy_ext1_ref: &mut f64,
    dz_ext1_ref: &mut f64,
    xsv_ext0_ref: &mut i32,
    ysv_ext0_ref: &mut i32,
    zsv_ext0_ref: &mut i32,
    xsv_ext1_ref: &mut i32,
    ysv_ext1_ref: &mut i32,
    zsv_ext1_ref: &mut i32,
    xsb: i32,
    ysb: i32,
    zsb: i32,
    dx0: f64,
    dy0: f64,
    dz0: f64,
    aPoint: i8,
    bPoint: i8,
) {
    let mut dx_ext0 = *dx_ext0_ref;
    let mut dy_ext0 = *dy_ext0_ref;
    let mut dz_ext0 = *dz_ext0_ref;
    let mut dx_ext1 = *dx_ext1_ref;
    let mut dy_ext1 = *dy_ext1_ref;
    let mut dz_ext1 = *dz_ext1_ref;
    let mut xsv_ext0 = *xsv_ext0_ref;
    let mut ysv_ext0 = *ysv_ext0_ref;
    let mut zsv_ext0 = *zsv_ext0_ref;
    let mut xsv_ext1 = *xsv_ext1_ref;
    let mut ysv_ext1 = *ysv_ext1_ref;
    let mut zsv_ext1 = *zsv_ext1_ref;

    let c = aPoint | bPoint;

    if (c & 0x01) == 0 {
        xsv_ext0 = xsb;
        xsv_ext1 = xsb - 1;
        dx_ext0 = dx0 - (2.0 * (1.0 / 3.0));
        dx_ext1 = (dx0 + 1.0) - (1.0 / 3.0);
    } else {
        xsv_ext0 = xsb + 1;
        xsv_ext1 = xsb + 1;
        dx_ext0 = (dx0 - 1.0) - (2.0 * (1.0 / 3.0));
        dx_ext1 = (dx0 - 1.0) - (1.0 / 3.0);
    }

    if (c & 0x02) == 0 {
        ysv_ext0 = ysb;
        ysv_ext1 = ysb - 1;
        dy_ext0 = dy0 - (2.0 * (1.0 / 3.0));
        dy_ext1 = (dy0 + 1.0) - (1.0 / 3.0);
    } else {
        ysv_ext0 = ysb + 1;
        ysv_ext1 = ysb + 1;
        dy_ext0 = (dy0 - 1.0) - (2.0 * (1.0 / 3.0));
        dy_ext1 = (dy0 - 1.0) - (1.0 / 3.0);
    }

    if (c & 0x04) == 0 {
        zsv_ext0 = zsb;
        zsv_ext1 = zsb - 1;
        dz_ext0 = dz0 - (2.0 * (1.0 / 3.0));
        dz_ext1 = (dz0 + 1.0) - (1.0 / 3.0);
    } else {
        zsv_ext0 = zsb + 1;
        zsv_ext1 = zsb + 1;
        dz_ext0 = (dz0 - 1.0) - (2.0 * (1.0 / 3.0));
        dz_ext1 = (dz0 - 1.0) - (1.0 / 3.0);
    }

    *dx_ext0_ref = dx_ext0;
    *dy_ext0_ref = dy_ext0;
    *dz_ext0_ref = dz_ext0;
    *dx_ext1_ref = dx_ext1;
    *dy_ext1_ref = dy_ext1;
    *dz_ext1_ref = dz_ext1;
    *xsv_ext0_ref = xsv_ext0;
    *ysv_ext0_ref = ysv_ext0;
    *zsv_ext0_ref = zsv_ext0;
    *xsv_ext1_ref = xsv_ext1;
    *ysv_ext1_ref = ysv_ext1;
    *zsv_ext1_ref = zsv_ext1;
}
pub fn helper_helper_open_simplex_noise3_2_1(
    dx_ext0_ref: &mut f64,
    dy_ext0_ref: &mut f64,
    dz_ext0_ref: &mut f64,
    dx_ext1_ref: &mut f64,
    dy_ext1_ref: &mut f64,
    dz_ext1_ref: &mut f64,
    xsv_ext0_ref: &mut i32,
    ysv_ext0_ref: &mut i32,
    zsv_ext0_ref: &mut i32,
    xsv_ext1_ref: &mut i32,
    ysv_ext1_ref: &mut i32,
    zsv_ext1_ref: &mut i32,
    xsb: i32,
    ysb: i32,
    zsb: i32,
    dx0: f64,
    dy0: f64,
    dz0: f64,
    aPoint: i8,
    aScore: f64,
    bPoint: i8,
    bScore: f64,
) {
    let mut dx_ext0 = *dx_ext0_ref;
    let mut dy_ext0 = *dy_ext0_ref;
    let mut dz_ext0 = *dz_ext0_ref;
    let mut dx_ext1 = *dx_ext1_ref;
    let mut dy_ext1 = *dy_ext1_ref;
    let mut dz_ext1 = *dz_ext1_ref;
    let mut xsv_ext0 = *xsv_ext0_ref;
    let mut ysv_ext0 = *ysv_ext0_ref;
    let mut zsv_ext0 = *zsv_ext0_ref;
    let mut xsv_ext1 = *xsv_ext1_ref;
    let mut ysv_ext1 = *ysv_ext1_ref;
    let mut zsv_ext1 = *zsv_ext1_ref;

    let c = if bScore < aScore { bPoint } else { aPoint };

    if (c & 0x01) != 0 {
        xsv_ext0 = xsb + 2;
        xsv_ext1 = xsb + 1;
        dx_ext0 = (dx0 - 2.0) - (3.0 * (1.0 / 3.0));
        dx_ext1 = (dx0 - 1.0) - (3.0 * (1.0 / 3.0));
    } else {
        xsv_ext0 = xsb;
        xsv_ext1 = xsb;
        dx_ext0 = dx0 - (3.0 * (1.0 / 3.0));
        dx_ext1 = dx0 - (3.0 * (1.0 / 3.0));
    }

    if (c & 0x02) != 0 {
        ysv_ext0 = ysb + 1;
        ysv_ext1 = ysb + 1;
        dy_ext0 = (dy0 - 1.0) - (3.0 * (1.0 / 3.0));
        dy_ext1 = (dy0 - 1.0) - (3.0 * (1.0 / 3.0));
        if (c & 0x01) != 0 {
            ysv_ext1 += 1;
            dy_ext1 -= 1.0;
        } else {
            ysv_ext0 += 1;
            dy_ext0 -= 1.0;
        }
    } else {
        ysv_ext0 = ysb;
        ysv_ext1 = ysb;
        dy_ext0 = dy0 - (3.0 * (1.0 / 3.0));
        dy_ext1 = dy0 - (3.0 * (1.0 / 3.0));
    }

    if (c & 0x04) != 0 {
        zsv_ext0 = zsb + 1;
        zsv_ext1 = zsb + 2;
        dz_ext0 = (dz0 - 1.0) - (3.0 * (1.0 / 3.0));
        dz_ext1 = (dz0 - 2.0) - (3.0 * (1.0 / 3.0));
    } else {
        zsv_ext0 = zsb;
        zsv_ext1 = zsb;
        dz_ext0 = dz0 - (3.0 * (1.0 / 3.0));
        dz_ext1 = dz0 - (3.0 * (1.0 / 3.0));
    }

    *dx_ext0_ref = dx_ext0;
    *dy_ext0_ref = dy_ext0;
    *dz_ext0_ref = dz_ext0;
    *dx_ext1_ref = dx_ext1;
    *dy_ext1_ref = dy_ext1;
    *dz_ext1_ref = dz_ext1;
    *xsv_ext0_ref = xsv_ext0;
    *ysv_ext0_ref = ysv_ext0;
    *zsv_ext0_ref = zsv_ext0;
    *xsv_ext1_ref = xsv_ext1;
    *ysv_ext1_ref = ysv_ext1;
    *zsv_ext1_ref = zsv_ext1;
}
pub fn helper_helper_open_simplex_noise3_2_2(
    dx_ext0_ref: &mut f64,
    dy_ext0_ref: &mut f64,
    dz_ext0_ref: &mut f64,
    dx_ext1_ref: &mut f64,
    dy_ext1_ref: &mut f64,
    dz_ext1_ref: &mut f64,
    xsv_ext0_ref: &mut i32,
    ysv_ext0_ref: &mut i32,
    zsv_ext0_ref: &mut i32,
    xsv_ext1_ref: &mut i32,
    ysv_ext1_ref: &mut i32,
    zsv_ext1_ref: &mut i32,
    xsb: i32,
    ysb: i32,
    zsb: i32,
    dx0: f64,
    dy0: f64,
    dz0: f64,
    aPoint: i8,
    bPoint: i8,
) {
    let mut dx_ext0 = *dx_ext0_ref;
    let mut dy_ext0 = *dy_ext0_ref;
    let mut dz_ext0 = *dz_ext0_ref;
    let mut dx_ext1 = *dx_ext1_ref;
    let mut dy_ext1 = *dy_ext1_ref;
    let mut dz_ext1 = *dz_ext1_ref;
    let mut xsv_ext0 = *xsv_ext0_ref;
    let mut ysv_ext0 = *ysv_ext0_ref;
    let mut zsv_ext0 = *zsv_ext0_ref;
    let mut xsv_ext1 = *xsv_ext1_ref;
    let mut ysv_ext1 = *ysv_ext1_ref;
    let mut zsv_ext1 = *zsv_ext1_ref;

    let c = aPoint & bPoint;

    if (c & 0x01) != 0 {
        xsv_ext0 = xsb + 1;
        xsv_ext1 = xsb + 2;
        dx_ext0 = (dx0 - 1.0) - (1.0 / 3.0);
        dx_ext1 = (dx0 - 2.0) - (2.0 * (1.0 / 3.0));
    } else {
        xsv_ext0 = xsb;
        xsv_ext1 = xsb;
        dx_ext0 = dx0 - (1.0 / 3.0);
        dx_ext1 = dx0 - (2.0 * (1.0 / 3.0));
    }

    if (c & 0x02) != 0 {
        ysv_ext0 = ysb + 1;
        ysv_ext1 = ysb + 2;
        dy_ext0 = (dy0 - 1.0) - (1.0 / 3.0);
        dy_ext1 = (dy0 - 2.0) - (2.0 * (1.0 / 3.0));
    } else {
        ysv_ext0 = ysb;
        ysv_ext1 = ysb;
        dy_ext0 = dy0 - (1.0 / 3.0);
        dy_ext1 = dy0 - (2.0 * (1.0 / 3.0));
    }

    if (c & 0x04) != 0 {
        zsv_ext0 = zsb + 1;
        zsv_ext1 = zsb + 2;
        dz_ext0 = (dz0 - 1.0) - (1.0 / 3.0);
        dz_ext1 = (dz0 - 2.0) - (2.0 * (1.0 / 3.0));
    } else {
        zsv_ext0 = zsb;
        zsv_ext1 = zsb;
        dz_ext0 = dz0 - (1.0 / 3.0);
        dz_ext1 = dz0 - (2.0 * (1.0 / 3.0));
    }

    *dx_ext0_ref = dx_ext0;
    *dy_ext0_ref = dy_ext0;
    *dz_ext0_ref = dz_ext0;
    *dx_ext1_ref = dx_ext1;
    *dy_ext1_ref = dy_ext1;
    *dz_ext1_ref = dz_ext1;
    *xsv_ext0_ref = xsv_ext0;
    *ysv_ext0_ref = ysv_ext0;
    *zsv_ext0_ref = zsv_ext0;
    *xsv_ext1_ref = xsv_ext1;
    *ysv_ext1_ref = ysv_ext1;
    *zsv_ext1_ref = zsv_ext1;
}
pub fn helper_helper_open_simplex_noise3_3_1(
    dx_ext0_ref: &mut f64,
    dy_ext0_ref: &mut f64,
    dz_ext0_ref: &mut f64,
    dx_ext1_ref: &mut f64,
    dy_ext1_ref: &mut f64,
    dz_ext1_ref: &mut f64,
    xsv_ext0_ref: &mut i32,
    ysv_ext0_ref: &mut i32,
    zsv_ext0_ref: &mut i32,
    xsv_ext1_ref: &mut i32,
    ysv_ext1_ref: &mut i32,
    zsv_ext1_ref: &mut i32,
    xsb: i32,
    ysb: i32,
    zsb: i32,
    dx0: f64,
    dy0: f64,
    dz0: f64,
    aPoint: i8,
    aIsFurtherSide: i32,
    bPoint: i8,
) {
    let mut dx_ext0 = *dx_ext0_ref;
    let mut dy_ext0 = *dy_ext0_ref;
    let mut dz_ext0 = *dz_ext0_ref;
    let mut dx_ext1 = *dx_ext1_ref;
    let mut dy_ext1 = *dy_ext1_ref;
    let mut dz_ext1 = *dz_ext1_ref;
    let mut xsv_ext0 = *xsv_ext0_ref;
    let mut ysv_ext0 = *ysv_ext0_ref;
    let mut zsv_ext0 = *zsv_ext0_ref;
    let mut xsv_ext1 = *xsv_ext1_ref;
    let mut ysv_ext1 = *ysv_ext1_ref;
    let mut zsv_ext1 = *zsv_ext1_ref;

    let (c1, c2) = if aIsFurtherSide != 0 {
        (aPoint, bPoint)
    } else {
        (bPoint, aPoint)
    };

    if (c1 & 0x01) == 0 {
        dx_ext0 = (dx0 + 1.0) - (1.0 / 3.0);
        dy_ext0 = (dy0 - 1.0) - (1.0 / 3.0);
        dz_ext0 = (dz0 - 1.0) - (1.0 / 3.0);
        xsv_ext0 = xsb - 1;
        ysv_ext0 = ysb + 1;
        zsv_ext0 = zsb + 1;
    } else if (c1 & 0x02) == 0 {
        dx_ext0 = (dx0 - 1.0) - (1.0 / 3.0);
        dy_ext0 = (dy0 + 1.0) - (1.0 / 3.0);
        dz_ext0 = (dz0 - 1.0) - (1.0 / 3.0);
        xsv_ext0 = xsb + 1;
        ysv_ext0 = ysb - 1;
        zsv_ext0 = zsb + 1;
    } else {
        dx_ext0 = (dx0 - 1.0) - (1.0 / 3.0);
        dy_ext0 = (dy0 - 1.0) - (1.0 / 3.0);
        dz_ext0 = (dz0 + 1.0) - (1.0 / 3.0);
        xsv_ext0 = xsb + 1;
        ysv_ext0 = ysb + 1;
        zsv_ext0 = zsb - 1;
    }

    dx_ext1 = dx0 - (2.0 * (1.0 / 3.0));
    dy_ext1 = dy0 - (2.0 * (1.0 / 3.0));
    dz_ext1 = dz0 - (2.0 * (1.0 / 3.0));
    xsv_ext1 = xsb;
    ysv_ext1 = ysb;
    zsv_ext1 = zsb;

    if (c2 & 0x01) != 0 {
        dx_ext1 -= 2.0;
        xsv_ext1 += 2;
    } else if (c2 & 0x02) != 0 {
        dy_ext1 -= 2.0;
        ysv_ext1 += 2;
    } else {
        dz_ext1 -= 2.0;
        zsv_ext1 += 2;
    }

    *dx_ext0_ref = dx_ext0;
    *dy_ext0_ref = dy_ext0;
    *dz_ext0_ref = dz_ext0;
    *dx_ext1_ref = dx_ext1;
    *dy_ext1_ref = dy_ext1;
    *dz_ext1_ref = dz_ext1;
    *xsv_ext0_ref = xsv_ext0;
    *ysv_ext0_ref = ysv_ext0;
    *zsv_ext0_ref = zsv_ext0;
    *xsv_ext1_ref = xsv_ext1;
    *ysv_ext1_ref = ysv_ext1;
    *zsv_ext1_ref = zsv_ext1;
}
pub fn helper_helper_open_simplex_noise4_1_1(
    dx_ext0_ref: &mut f64,
    dy_ext0_ref: &mut f64,
    dz_ext0_ref: &mut f64,
    dw_ext0_ref: &mut f64,
    dx_ext1_ref: &mut f64,
    dy_ext1_ref: &mut f64,
    dz_ext1_ref: &mut f64,
    dz_ext2_ref: &mut f64,
    dw_ext2_ref: &mut f64,
    xsv_ext0_ref: &mut i32,
    ysv_ext0_ref: &mut i32,
    zsv_ext0_ref: &mut i32,
    wsv_ext0_ref: &mut i32,
    xsv_ext1_ref: &mut i32,
    ysv_ext1_ref: &mut i32,
    zsv_ext1_ref: &mut i32,
    zsv_ext2_ref: &mut i32,
    wsv_ext2_ref: &mut i32,
    xsb: i32,
    ysb: i32,
    zsb: i32,
    wsb: i32,
    dx0: f64,
    dy0: f64,
    dz0: f64,
    dw0: f64,
    mut wsv_ext1: i32,
    mut xsv_ext2: i32,
    mut dw_ext1: f64,
    mut dx_ext2: f64,
    mut dy_ext2: f64,
    mut ysv_ext2: i32,
    aPoint: i8,
    aScore: f64,
    bPoint: i8,
    bScore: f64,
) {
    let mut dx_ext0 = *dx_ext0_ref;
    let mut dy_ext0 = *dy_ext0_ref;
    let mut dz_ext0 = *dz_ext0_ref;
    let mut dw_ext0 = *dw_ext0_ref;
    let mut dx_ext1 = *dx_ext1_ref;
    let mut dy_ext1 = *dy_ext1_ref;
    let mut dz_ext1 = *dz_ext1_ref;
    let mut dz_ext2 = *dz_ext2_ref;
    let mut dw_ext2 = *dw_ext2_ref;
    let mut xsv_ext0 = *xsv_ext0_ref;
    let mut ysv_ext0 = *ysv_ext0_ref;
    let mut zsv_ext0 = *zsv_ext0_ref;
    let mut wsv_ext0 = *wsv_ext0_ref;
    let mut xsv_ext1 = *xsv_ext1_ref;
    let mut ysv_ext1 = *ysv_ext1_ref;
    let mut zsv_ext1 = *zsv_ext1_ref;
    let mut zsv_ext2 = *zsv_ext2_ref;
    let mut wsv_ext2 = *wsv_ext2_ref;

    let c = if bScore > aScore { bPoint } else { aPoint };

    if (c & 0x01) == 0 {
        xsv_ext0 = xsb - 1;
        xsv_ext1 = xsb;
        xsv_ext2 = xsb;
        dx_ext0 = dx0 + 1.0;
        dx_ext1 = dx0;
        dx_ext2 = dx0;
    } else {
        xsv_ext0 = xsb + 1;
        xsv_ext1 = xsb + 1;
        xsv_ext2 = xsb + 1;
        dx_ext0 = dx0 - 1.0;
        dx_ext1 = dx0 - 1.0;
        dx_ext2 = dx0 - 1.0;
    }

    if (c & 0x02) == 0 {
        ysv_ext0 = ysb;
        ysv_ext1 = ysb;
        ysv_ext2 = ysb;
        dy_ext0 = dy0;
        dy_ext1 = dy0;
        dy_ext2 = dy0;
        if (c & 0x01) == 0x01 {
            ysv_ext0 -= 1;
            dy_ext0 += 1.0;
        } else {
            ysv_ext1 -= 1;
            dy_ext1 += 1.0;
        }
    } else {
        ysv_ext0 = ysb + 1;
        ysv_ext1 = ysb + 1;
        ysv_ext2 = ysb + 1;
        dy_ext0 = dy0 - 1.0;
        dy_ext1 = dy0 - 1.0;
        dy_ext2 = dy0 - 1.0;
    }

    if (c & 0x04) == 0 {
        zsv_ext0 = zsb;
        zsv_ext1 = zsb;
        zsv_ext2 = zsb;
        dz_ext0 = dz0;
        dz_ext1 = dz0;
        dz_ext2 = dz0;
        if (c & 0x03) != 0 {
            if (c & 0x03) == 0x03 {
                zsv_ext0 -= 1;
                dz_ext0 += 1.0;
            } else {
                zsv_ext1 -= 1;
                dz_ext1 += 1.0;
            }
        } else {
            zsv_ext2 -= 1;
            dz_ext2 += 1.0;
        }
    } else {
        zsv_ext0 = zsb + 1;
        zsv_ext1 = zsb + 1;
        zsv_ext2 = zsb + 1;
        dz_ext0 = dz0 - 1.0;
        dz_ext1 = dz0 - 1.0;
        dz_ext2 = dz0 - 1.0;
    }

    if (c & 0x08) == 0 {
        wsv_ext0 = wsb;
        wsv_ext1 = wsb;
        wsv_ext2 = wsb - 1;
        dw_ext0 = dw0;
        dw_ext1 = dw0;
        dw_ext2 = dw0 + 1.0;
    } else {
        wsv_ext0 = wsb + 1;
        wsv_ext1 = wsb + 1;
        wsv_ext2 = wsb + 1;
        dw_ext0 = dw0 - 1.0;
        dw_ext1 = dw0 - 1.0;
        dw_ext2 = dw0 - 1.0;
    }

    *dx_ext0_ref = dx_ext0;
    *dy_ext0_ref = dy_ext0;
    *dz_ext0_ref = dz_ext0;
    *dw_ext0_ref = dw_ext0;
    *dx_ext1_ref = dx_ext1;
    *dy_ext1_ref = dy_ext1;
    *dz_ext1_ref = dz_ext1;
    *dz_ext2_ref = dz_ext2;
    *dw_ext2_ref = dw_ext2;
    *xsv_ext0_ref = xsv_ext0;
    *ysv_ext0_ref = ysv_ext0;
    *zsv_ext0_ref = zsv_ext0;
    *wsv_ext0_ref = wsv_ext0;
    *xsv_ext1_ref = xsv_ext1;
    *ysv_ext1_ref = ysv_ext1;
    *zsv_ext1_ref = zsv_ext1;
    *zsv_ext2_ref = zsv_ext2;
    *wsv_ext2_ref = wsv_ext2;
}
pub fn helper_helper_open_simplex_noise4_1_2(
    dx_ext0_ref: &mut f64,
    dy_ext0_ref: &mut f64,
    dz_ext0_ref: &mut f64,
    dw_ext0_ref: &mut f64,
    dx_ext1_ref: &mut f64,
    dy_ext1_ref: &mut f64,
    dz_ext1_ref: &mut f64,
    dw_ext1_ref: &mut f64,
    dx_ext2_ref: &mut f64,
    dy_ext2_ref: &mut f64,
    dz_ext2_ref: &mut f64,
    dw_ext2_ref: &mut f64,
    xsv_ext0_ref: &mut i32,
    ysv_ext0_ref: &mut i32,
    zsv_ext0_ref: &mut i32,
    wsv_ext0_ref: &mut i32,
    xsv_ext1_ref: &mut i32,
    ysv_ext1_ref: &mut i32,
    zsv_ext1_ref: &mut i32,
    ysv_ext2_ref: &mut i32,
    zsv_ext2_ref: &mut i32,
    wsv_ext2_ref: &mut i32,
    xsb: i32,
    ysb: i32,
    zsb: i32,
    wsb: i32,
    dx0: f64,
    dy0: f64,
    dz0: f64,
    dw0: f64,
    mut wsv_ext1: i32,
    mut xsv_ext2: i32,
    aPoint: i8,
    bPoint: i8,
) {
    // Initialize local variables by dereferencing the references
    let mut dx_ext0 = *dx_ext0_ref;
    let mut dy_ext0 = *dy_ext0_ref;
    let mut dz_ext0 = *dz_ext0_ref;
    let mut dw_ext0 = *dw_ext0_ref;
    let mut dx_ext1 = *dx_ext1_ref;
    let mut dy_ext1 = *dy_ext1_ref;
    let mut dz_ext1 = *dz_ext1_ref;
    let mut dw_ext1 = *dw_ext1_ref;
    let mut dx_ext2 = *dx_ext2_ref;
    let mut dy_ext2 = *dy_ext2_ref;
    let mut dz_ext2 = *dz_ext2_ref;
    let mut dw_ext2 = *dw_ext2_ref;
    let mut xsv_ext0 = *xsv_ext0_ref;
    let mut ysv_ext0 = *ysv_ext0_ref;
    let mut zsv_ext0 = *zsv_ext0_ref;
    let mut wsv_ext0 = *wsv_ext0_ref;
    let mut xsv_ext1 = *xsv_ext1_ref;
    let mut ysv_ext1 = *ysv_ext1_ref;
    let mut zsv_ext1 = *zsv_ext1_ref;
    let mut ysv_ext2 = *ysv_ext2_ref;
    let mut zsv_ext2 = *zsv_ext2_ref;
    let mut wsv_ext2 = *wsv_ext2_ref;

    let c = aPoint | bPoint;

    // Handle x-axis
    if (c & 0x01) == 0 {
        xsv_ext0 = xsb;
        xsv_ext2 = xsb;
        xsv_ext1 = xsb - 1;
        dx_ext0 = dx0 - (2.0 * 0.309016994374947);
        dx_ext1 = dx0 + 1.0 - 0.309016994374947;
        dx_ext2 = dx0 - 0.309016994374947;
    } else {
        xsv_ext0 = xsb + 1;
        xsv_ext1 = xsb + 1;
        xsv_ext2 = xsb + 1;
        dx_ext0 = (dx0 - 1.0) - (2.0 * 0.309016994374947);
        dx_ext1 = (dx0 - 1.0) - 0.309016994374947;
        dx_ext2 = (dx0 - 1.0) - 0.309016994374947;
    }

    // Handle y-axis
    if (c & 0x02) == 0 {
        ysv_ext0 = ysb;
        ysv_ext1 = ysb;
        ysv_ext2 = ysb;
        dy_ext0 = dy0 - (2.0 * 0.309016994374947);
        dy_ext1 = dy0 - 0.309016994374947;
        dy_ext2 = dy0 - 0.309016994374947;
        
        if (c & 0x01) == 0x01 {
            ysv_ext1 -= 1;
            dy_ext1 += 1.0;
        } else {
            ysv_ext2 -= 1;
            dy_ext2 += 1.0;
        }
    } else {
        ysv_ext0 = ysb + 1;
        ysv_ext1 = ysb + 1;
        ysv_ext2 = ysb + 1;
        dy_ext0 = (dy0 - 1.0) - (2.0 * 0.309016994374947);
        dy_ext1 = (dy0 - 1.0) - 0.309016994374947;
        dy_ext2 = (dy0 - 1.0) - 0.309016994374947;
    }

    // Handle z-axis
    if (c & 0x04) == 0 {
        zsv_ext0 = zsb;
        zsv_ext1 = zsb;
        zsv_ext2 = zsb;
        dz_ext0 = dz0 - (2.0 * 0.309016994374947);
        dz_ext1 = dz0 - 0.309016994374947;
        dz_ext2 = dz0 - 0.309016994374947;
        
        if (c & 0x03) == 0x03 {
            zsv_ext1 -= 1;
            dz_ext1 += 1.0;
        } else {
            zsv_ext2 -= 1;
            dz_ext2 += 1.0;
        }
    } else {
        zsv_ext0 = zsb + 1;
        zsv_ext1 = zsb + 1;
        zsv_ext2 = zsb + 1;
        dz_ext0 = (dz0 - 1.0) - (2.0 * 0.309016994374947);
        dz_ext1 = (dz0 - 1.0) - 0.309016994374947;
        dz_ext2 = (dz0 - 1.0) - 0.309016994374947;
    }

    // Handle w-axis
    if (c & 0x08) == 0 {
        wsv_ext0 = wsb;
        wsv_ext1 = wsb;
        wsv_ext2 = wsb - 1;
        dw_ext0 = dw0 - (2.0 * 0.309016994374947);
        dw_ext1 = dw0 - 0.309016994374947;
        dw_ext2 = (dw0 + 1.0) - 0.309016994374947;
    } else {
        wsv_ext0 = wsb + 1;
        wsv_ext1 = wsb + 1;
        wsv_ext2 = wsb + 1;
        dw_ext0 = (dw0 - 1.0) - (2.0 * 0.309016994374947);
        dw_ext1 = (dw0 - 1.0) - 0.309016994374947;
        dw_ext2 = (dw0 - 1.0) - 0.309016994374947;
    }

    // Update all the reference parameters
    *dx_ext0_ref = dx_ext0;
    *dy_ext0_ref = dy_ext0;
    *dz_ext0_ref = dz_ext0;
    *dw_ext0_ref = dw_ext0;
    *dx_ext1_ref = dx_ext1;
    *dy_ext1_ref = dy_ext1;
    *dz_ext1_ref = dz_ext1;
    *dw_ext1_ref = dw_ext1;
    *dx_ext2_ref = dx_ext2;
    *dy_ext2_ref = dy_ext2;
    *dz_ext2_ref = dz_ext2;
    *dw_ext2_ref = dw_ext2;
    *xsv_ext0_ref = xsv_ext0;
    *ysv_ext0_ref = ysv_ext0;
    *zsv_ext0_ref = zsv_ext0;
    *wsv_ext0_ref = wsv_ext0;
    *xsv_ext1_ref = xsv_ext1;
    *ysv_ext1_ref = ysv_ext1;
    *zsv_ext1_ref = zsv_ext1;
    *ysv_ext2_ref = ysv_ext2;
    *zsv_ext2_ref = zsv_ext2;
    *wsv_ext2_ref = wsv_ext2;
}
pub fn helper_helper_open_simplex_noise4_2_1(
    dx_ext0_ref: &mut f64,
    dy_ext0_ref: &mut f64,
    dz_ext0_ref: &mut f64,
    dw_ext0_ref: &mut f64,
    dx_ext1_ref: &mut f64,
    dy_ext1_ref: &mut f64,
    dz_ext1_ref: &mut f64,
    dz_ext2_ref: &mut f64,
    dw_ext2_ref: &mut f64,
    xsv_ext0_ref: &mut i32,
    ysv_ext0_ref: &mut i32,
    zsv_ext0_ref: &mut i32,
    wsv_ext0_ref: &mut i32,
    xsv_ext1_ref: &mut i32,
    ysv_ext1_ref: &mut i32,
    zsv_ext1_ref: &mut i32,
    zsv_ext2_ref: &mut i32,
    wsv_ext2_ref: &mut i32,
    xsb: i32,
    ysb: i32,
    zsb: i32,
    wsb: i32,
    mut wsv_ext1: i32,
    mut xsv_ext2: i32,
    dx0: f64,
    dy0: f64,
    dz0: f64,
    dw0: f64,
    mut dw_ext1: f64,
    mut dx_ext2: f64,
    mut dy_ext2: f64,
    mut ysv_ext2: i32,
    aPoint: i8,
    aScore: f64,
    bPoint: i8,
    bScore: f64,
) {
    let mut dx_ext0 = *dx_ext0_ref;
    let mut dy_ext0 = *dy_ext0_ref;
    let mut dz_ext0 = *dz_ext0_ref;
    let mut dw_ext0 = *dw_ext0_ref;
    let mut dx_ext1 = *dx_ext1_ref;
    let mut dy_ext1 = *dy_ext1_ref;
    let mut dz_ext1 = *dz_ext1_ref;
    let mut dz_ext2 = *dz_ext2_ref;
    let mut dw_ext2 = *dw_ext2_ref;
    let mut xsv_ext0 = *xsv_ext0_ref;
    let mut ysv_ext0 = *ysv_ext0_ref;
    let mut zsv_ext0 = *zsv_ext0_ref;
    let mut wsv_ext0 = *wsv_ext0_ref;
    let mut xsv_ext1 = *xsv_ext1_ref;
    let mut ysv_ext1 = *ysv_ext1_ref;
    let mut zsv_ext1 = *zsv_ext1_ref;
    let mut zsv_ext2 = *zsv_ext2_ref;
    let mut wsv_ext2 = *wsv_ext2_ref;

    let c = if bScore < aScore { bPoint } else { aPoint };

    if (c & 0x01) != 0 {
        xsv_ext0 = xsb + 2;
        xsv_ext1 = xsb + 1;
        xsv_ext2 = xsb + 1;
        dx_ext0 = dx0 - 2.0 - (4.0 * 0.309016994374947);
        dx_ext1 = dx0 - 1.0 - (4.0 * 0.309016994374947);
        dx_ext2 = dx0 - 1.0 - (4.0 * 0.309016994374947);
    } else {
        xsv_ext0 = xsb;
        xsv_ext1 = xsb;
        xsv_ext2 = xsb;
        dx_ext0 = dx0 - (4.0 * 0.309016994374947);
        dx_ext1 = dx0 - (4.0 * 0.309016994374947);
        dx_ext2 = dx0 - (4.0 * 0.309016994374947);
    }

    if (c & 0x02) != 0 {
        ysv_ext0 = ysb + 1;
        ysv_ext1 = ysb + 1;
        ysv_ext2 = ysb + 1;
        dy_ext0 = dy0 - 1.0 - (4.0 * 0.309016994374947);
        dy_ext1 = dy0 - 1.0 - (4.0 * 0.309016994374947);
        dy_ext2 = dy0 - 1.0 - (4.0 * 0.309016994374947);
        if (c & 0x01) != 0 {
            ysv_ext1 += 1;
            dy_ext1 -= 1.0;
        } else {
            ysv_ext0 += 1;
            dy_ext0 -= 1.0;
        }
    } else {
        ysv_ext0 = ysb;
        ysv_ext1 = ysb;
        ysv_ext2 = ysb;
        dy_ext0 = dy0 - (4.0 * 0.309016994374947);
        dy_ext1 = dy0 - (4.0 * 0.309016994374947);
        dy_ext2 = dy0 - (4.0 * 0.309016994374947);
    }

    if (c & 0x04) != 0 {
        zsv_ext0 = zsb + 1;
        zsv_ext1 = zsb + 1;
        zsv_ext2 = zsb + 1;
        dz_ext0 = dz0 - 1.0 - (4.0 * 0.309016994374947);
        dz_ext1 = dz0 - 1.0 - (4.0 * 0.309016994374947);
        dz_ext2 = dz0 - 1.0 - (4.0 * 0.309016994374947);
        if (c & 0x03) != 0x03 {
            if (c & 0x03) == 0 {
                zsv_ext0 += 1;
                dz_ext0 -= 1.0;
            } else {
                zsv_ext1 += 1;
                dz_ext1 -= 1.0;
            }
        } else {
            zsv_ext2 += 1;
            dz_ext2 -= 1.0;
        }
    } else {
        zsv_ext0 = zsb;
        zsv_ext1 = zsb;
        zsv_ext2 = zsb;
        dz_ext0 = dz0 - (4.0 * 0.309016994374947);
        dz_ext1 = dz0 - (4.0 * 0.309016994374947);
        dz_ext2 = dz0 - (4.0 * 0.309016994374947);
    }

    if (c & 0x08) != 0 {
        wsv_ext0 = wsb + 1;
        wsv_ext1 = wsb + 1;
        wsv_ext2 = wsb + 2;
        dw_ext0 = dw0 - 1.0 - (4.0 * 0.309016994374947);
        dw_ext1 = dw0 - 1.0 - (4.0 * 0.309016994374947);
        dw_ext2 = dw0 - 2.0 - (4.0 * 0.309016994374947);
    } else {
        wsv_ext0 = wsb;
        wsv_ext1 = wsb;
        wsv_ext2 = wsb;
        dw_ext0 = dw0 - (4.0 * 0.309016994374947);
        dw_ext1 = dw0 - (4.0 * 0.309016994374947);
        dw_ext2 = dw0 - (4.0 * 0.309016994374947);
    }

    *dx_ext0_ref = dx_ext0;
    *dy_ext0_ref = dy_ext0;
    *dz_ext0_ref = dz_ext0;
    *dw_ext0_ref = dw_ext0;
    *dx_ext1_ref = dx_ext1;
    *dy_ext1_ref = dy_ext1;
    *dz_ext1_ref = dz_ext1;
    *dz_ext2_ref = dz_ext2;
    *dw_ext2_ref = dw_ext2;
    *xsv_ext0_ref = xsv_ext0;
    *ysv_ext0_ref = ysv_ext0;
    *zsv_ext0_ref = zsv_ext0;
    *wsv_ext0_ref = wsv_ext0;
    *xsv_ext1_ref = xsv_ext1;
    *ysv_ext1_ref = ysv_ext1;
    *zsv_ext1_ref = zsv_ext1;
    *zsv_ext2_ref = zsv_ext2;
    *wsv_ext2_ref = wsv_ext2;
}
pub fn helper_helper_open_simplex_noise4_2_2(
    dx_ext0_ref: &mut f64,
    dy_ext0_ref: &mut f64,
    dz_ext0_ref: &mut f64,
    dw_ext0_ref: &mut f64,
    dx_ext1_ref: &mut f64,
    dy_ext1_ref: &mut f64,
    dz_ext1_ref: &mut f64,
    dw_ext1_ref: &mut f64,
    dx_ext2_ref: &mut f64,
    dy_ext2_ref: &mut f64,
    dz_ext2_ref: &mut f64,
    dw_ext2_ref: &mut f64,
    xsv_ext0_ref: &mut i32,
    ysv_ext0_ref: &mut i32,
    zsv_ext0_ref: &mut i32,
    wsv_ext0_ref: &mut i32,
    xsv_ext1_ref: &mut i32,
    ysv_ext1_ref: &mut i32,
    zsv_ext1_ref: &mut i32,
    ysv_ext2_ref: &mut i32,
    zsv_ext2_ref: &mut i32,
    wsv_ext2_ref: &mut i32,
    xsb: i32,
    ysb: i32,
    zsb: i32,
    wsb: i32,
    mut wsv_ext1: i32,
    mut xsv_ext2: i32,
    dx0: f64,
    dy0: f64,
    dz0: f64,
    dw0: f64,
    aPoint: i8,
    bPoint: i8,
) {
    let mut dx_ext0 = *dx_ext0_ref;
    let mut dy_ext0 = *dy_ext0_ref;
    let mut dz_ext0 = *dz_ext0_ref;
    let mut dw_ext0 = *dw_ext0_ref;
    let mut dx_ext1 = *dx_ext1_ref;
    let mut dy_ext1 = *dy_ext1_ref;
    let mut dz_ext1 = *dz_ext1_ref;
    let mut dw_ext1 = *dw_ext1_ref;
    let mut dx_ext2 = *dx_ext2_ref;
    let mut dy_ext2 = *dy_ext2_ref;
    let mut dz_ext2 = *dz_ext2_ref;
    let mut dw_ext2 = *dw_ext2_ref;
    let mut xsv_ext0 = *xsv_ext0_ref;
    let mut ysv_ext0 = *ysv_ext0_ref;
    let mut zsv_ext0 = *zsv_ext0_ref;
    let mut wsv_ext0 = *wsv_ext0_ref;
    let mut xsv_ext1 = *xsv_ext1_ref;
    let mut ysv_ext1 = *ysv_ext1_ref;
    let mut zsv_ext1 = *zsv_ext1_ref;
    let mut ysv_ext2 = *ysv_ext2_ref;
    let mut zsv_ext2 = *zsv_ext2_ref;
    let mut wsv_ext2 = *wsv_ext2_ref;

    let c = aPoint & bPoint;
    const K: f64 = 0.309016994374947;

    if (c & 0x01) != 0 {
        xsv_ext0 = xsb + 1;
        xsv_ext2 = xsb + 1;
        xsv_ext1 = xsb + 2;
        dx_ext0 = (dx0 - 1.0) - (2.0 * K);
        dx_ext1 = (dx0 - 2.0) - (3.0 * K);
        dx_ext2 = (dx0 - 1.0) - (3.0 * K);
    } else {
        xsv_ext0 = xsb;
        xsv_ext1 = xsb;
        xsv_ext2 = xsb;
        dx_ext0 = dx0 - (2.0 * K);
        dx_ext1 = dx0 - (3.0 * K);
        dx_ext2 = dx0 - (3.0 * K);
    }

    if (c & 0x02) != 0 {
        ysv_ext0 = ysb + 1;
        ysv_ext1 = ysb + 1;
        ysv_ext2 = ysb + 1;
        dy_ext0 = (dy0 - 1.0) - (2.0 * K);
        dy_ext1 = (dy0 - 1.0) - (3.0 * K);
        dy_ext2 = (dy0 - 1.0) - (3.0 * K);
        if (c & 0x01) != 0 {
            ysv_ext2 += 1;
            dy_ext2 -= 1.0;
        } else {
            ysv_ext1 += 1;
            dy_ext1 -= 1.0;
        }
    } else {
        ysv_ext0 = ysb;
        ysv_ext1 = ysb;
        ysv_ext2 = ysb;
        dy_ext0 = dy0 - (2.0 * K);
        dy_ext1 = dy0 - (3.0 * K);
        dy_ext2 = dy0 - (3.0 * K);
    }

    if (c & 0x04) != 0 {
        zsv_ext0 = zsb + 1;
        zsv_ext1 = zsb + 1;
        zsv_ext2 = zsb + 1;
        dz_ext0 = (dz0 - 1.0) - (2.0 * K);
        dz_ext1 = (dz0 - 1.0) - (3.0 * K);
        dz_ext2 = (dz0 - 1.0) - (3.0 * K);
        if (c & 0x03) != 0 {
            zsv_ext2 += 1;
            dz_ext2 -= 1.0;
        } else {
            zsv_ext1 += 1;
            dz_ext1 -= 1.0;
        }
    } else {
        zsv_ext0 = zsb;
        zsv_ext1 = zsb;
        zsv_ext2 = zsb;
        dz_ext0 = dz0 - (2.0 * K);
        dz_ext1 = dz0 - (3.0 * K);
        dz_ext2 = dz0 - (3.0 * K);
    }

    if (c & 0x08) != 0 {
        wsv_ext0 = wsb + 1;
        wsv_ext1 = wsb + 1;
        wsv_ext2 = wsb + 2;
        dw_ext0 = (dw0 - 1.0) - (2.0 * K);
        dw_ext1 = (dw0 - 1.0) - (3.0 * K);
        dw_ext2 = (dw0 - 2.0) - (3.0 * K);
    } else {
        wsv_ext0 = wsb;
        wsv_ext1 = wsb;
        wsv_ext2 = wsb;
        dw_ext0 = dw0 - (2.0 * K);
        dw_ext1 = dw0 - (3.0 * K);
        dw_ext2 = dw0 - (3.0 * K);
    }

    *dx_ext0_ref = dx_ext0;
    *dy_ext0_ref = dy_ext0;
    *dz_ext0_ref = dz_ext0;
    *dw_ext0_ref = dw_ext0;
    *dx_ext1_ref = dx_ext1;
    *dy_ext1_ref = dy_ext1;
    *dz_ext1_ref = dz_ext1;
    *dw_ext1_ref = dw_ext1;
    *dx_ext2_ref = dx_ext2;
    *dy_ext2_ref = dy_ext2;
    *dz_ext2_ref = dz_ext2;
    *dw_ext2_ref = dw_ext2;
    *xsv_ext0_ref = xsv_ext0;
    *ysv_ext0_ref = ysv_ext0;
    *zsv_ext0_ref = zsv_ext0;
    *wsv_ext0_ref = wsv_ext0;
    *xsv_ext1_ref = xsv_ext1;
    *ysv_ext1_ref = ysv_ext1;
    *zsv_ext1_ref = zsv_ext1;
    *ysv_ext2_ref = ysv_ext2;
    *zsv_ext2_ref = zsv_ext2;
    *wsv_ext2_ref = wsv_ext2;
}
pub fn helper_helper_open_simplex_noise4_3_1(
    dx_ext0_ref: &mut f64,
    dy_ext0_ref: &mut f64,
    dz_ext0_ref: &mut f64,
    dw_ext0_ref: &mut f64,
    dx_ext1_ref: &mut f64,
    dy_ext1_ref: &mut f64,
    dz_ext1_ref: &mut f64,
    dw_ext1_ref: &mut f64,
    dx_ext2_ref: &mut f64,
    dy_ext2_ref: &mut f64,
    dz_ext2_ref: &mut f64,
    dw_ext2_ref: &mut f64,
    xsv_ext0_ref: &mut i32,
    ysv_ext0_ref: &mut i32,
    zsv_ext0_ref: &mut i32,
    wsv_ext0_ref: &mut i32,
    xsv_ext1_ref: &mut i32,
    ysv_ext1_ref: &mut i32,
    zsv_ext1_ref: &mut i32,
    wsv_ext1_ref: &mut i32,
    xsv_ext2_ref: &mut i32,
    ysv_ext2_ref: &mut i32,
    zsv_ext2_ref: &mut i32,
    wsv_ext2_ref: &mut i32,
    xsb: i32,
    ysb: i32,
    zsb: i32,
    wsb: i32,
    dx0: f64,
    dy0: f64,
    dz0: f64,
    dw0: f64,
    aPoint: i8,
    aIsBiggerSide: i32,
    bPoint: i8,
) {
    let mut dx_ext0 = *dx_ext0_ref;
    let mut dy_ext0 = *dy_ext0_ref;
    let mut dz_ext0 = *dz_ext0_ref;
    let mut dw_ext0 = *dw_ext0_ref;
    let mut dx_ext1 = *dx_ext1_ref;
    let mut dy_ext1 = *dy_ext1_ref;
    let mut dz_ext1 = *dz_ext1_ref;
    let mut dw_ext1 = *dw_ext1_ref;
    let mut dx_ext2 = *dx_ext2_ref;
    let mut dy_ext2 = *dy_ext2_ref;
    let mut dz_ext2 = *dz_ext2_ref;
    let mut dw_ext2 = *dw_ext2_ref;
    let mut xsv_ext0 = *xsv_ext0_ref;
    let mut ysv_ext0 = *ysv_ext0_ref;
    let mut zsv_ext0 = *zsv_ext0_ref;
    let mut wsv_ext0 = *wsv_ext0_ref;
    let mut xsv_ext1 = *xsv_ext1_ref;
    let mut ysv_ext1 = *ysv_ext1_ref;
    let mut zsv_ext1 = *zsv_ext1_ref;
    let mut wsv_ext1 = *wsv_ext1_ref;
    let mut xsv_ext2 = *xsv_ext2_ref;
    let mut ysv_ext2 = *ysv_ext2_ref;
    let mut zsv_ext2 = *zsv_ext2_ref;
    let mut wsv_ext2 = *wsv_ext2_ref;

    let (c1, c2) = if aIsBiggerSide != 0 {
        (aPoint, bPoint)
    } else {
        (bPoint, aPoint)
    };

    if (c1 & 0x01) != 0 {
        xsv_ext0 = xsb + 2;
        xsv_ext1 = xsb + 1;
        dx_ext0 = (dx0 - 2.0) - (3.0 * 0.309016994374947);
        dx_ext1 = (dx0 - 1.0) - (3.0 * 0.309016994374947);
    } else {
        xsv_ext0 = xsb;
        xsv_ext1 = xsb;
        dx_ext0 = dx0 - (3.0 * 0.309016994374947);
        dx_ext1 = dx0 - (3.0 * 0.309016994374947);
    }

    if (c1 & 0x02) != 0 {
        ysv_ext0 = ysb + 1;
        ysv_ext1 = ysb + 1;
        dy_ext0 = (dy0 - 1.0) - (3.0 * 0.309016994374947);
        dy_ext1 = (dy0 - 1.0) - (3.0 * 0.309016994374947);
        if (c1 & 0x01) == 0 {
            ysv_ext0 += 1;
            dy_ext0 -= 1.0;
        } else {
            ysv_ext1 += 1;
            dy_ext1 -= 1.0;
        }
    } else {
        ysv_ext0 = ysb;
        ysv_ext1 = ysb;
        dy_ext0 = dy0 - (3.0 * 0.309016994374947);
        dy_ext1 = dy0 - (3.0 * 0.309016994374947);
    }

    if (c1 & 0x04) != 0 {
        zsv_ext0 = zsb + 1;
        zsv_ext1 = zsb + 1;
        dz_ext0 = (dz0 - 1.0) - (3.0 * 0.309016994374947);
        dz_ext1 = (dz0 - 1.0) - (3.0 * 0.309016994374947);
        if (c1 & 0x03) == 0 {
            zsv_ext0 += 1;
            dz_ext0 -= 1.0;
        } else {
            zsv_ext1 += 1;
            dz_ext1 -= 1.0;
        }
    } else {
        zsv_ext0 = zsb;
        zsv_ext1 = zsb;
        dz_ext0 = dz0 - (3.0 * 0.309016994374947);
        dz_ext1 = dz0 - (3.0 * 0.309016994374947);
    }

    if (c1 & 0x08) != 0 {
        wsv_ext0 = wsb + 1;
        wsv_ext1 = wsb + 2;
        dw_ext0 = (dw0 - 1.0) - (3.0 * 0.309016994374947);
        dw_ext1 = (dw0 - 2.0) - (3.0 * 0.309016994374947);
    } else {
        wsv_ext0 = wsb;
        wsv_ext1 = wsb;
        dw_ext0 = dw0 - (3.0 * 0.309016994374947);
        dw_ext1 = dw0 - (3.0 * 0.309016994374947);
    }

    xsv_ext2 = xsb + 1;
    ysv_ext2 = ysb + 1;
    zsv_ext2 = zsb + 1;
    wsv_ext2 = wsb + 1;
    dx_ext2 = (dx0 - 1.0) - (2.0 * 0.309016994374947);
    dy_ext2 = (dy0 - 1.0) - (2.0 * 0.309016994374947);
    dz_ext2 = (dz0 - 1.0) - (2.0 * 0.309016994374947);
    dw_ext2 = (dw0 - 1.0) - (2.0 * 0.309016994374947);

    if (c2 & 0x01) == 0 {
        xsv_ext2 -= 2;
        dx_ext2 += 2.0;
    } else if (c2 & 0x02) == 0 {
        ysv_ext2 -= 2;
        dy_ext2 += 2.0;
    } else if (c2 & 0x04) == 0 {
        zsv_ext2 -= 2;
        dz_ext2 += 2.0;
    } else {
        wsv_ext2 -= 2;
        dw_ext2 += 2.0;
    }

    *dx_ext0_ref = dx_ext0;
    *dy_ext0_ref = dy_ext0;
    *dz_ext0_ref = dz_ext0;
    *dw_ext0_ref = dw_ext0;
    *dx_ext1_ref = dx_ext1;
    *dy_ext1_ref = dy_ext1;
    *dz_ext1_ref = dz_ext1;
    *dw_ext1_ref = dw_ext1;
    *dx_ext2_ref = dx_ext2;
    *dy_ext2_ref = dy_ext2;
    *dz_ext2_ref = dz_ext2;
    *dw_ext2_ref = dw_ext2;
    *xsv_ext0_ref = xsv_ext0;
    *ysv_ext0_ref = ysv_ext0;
    *zsv_ext0_ref = zsv_ext0;
    *wsv_ext0_ref = wsv_ext0;
    *xsv_ext1_ref = xsv_ext1;
    *ysv_ext1_ref = ysv_ext1;
    *zsv_ext1_ref = zsv_ext1;
    *wsv_ext1_ref = wsv_ext1;
    *xsv_ext2_ref = xsv_ext2;
    *ysv_ext2_ref = ysv_ext2;
    *zsv_ext2_ref = zsv_ext2;
    *wsv_ext2_ref = wsv_ext2;
}
pub fn helper_helper_open_simplex_noise4_4_1(
    dx_ext0_ref: &mut f64,
    dy_ext0_ref: &mut f64,
    dz_ext0_ref: &mut f64,
    dw_ext0_ref: &mut f64,
    dx_ext1_ref: &mut f64,
    dy_ext1_ref: &mut f64,
    dz_ext1_ref: &mut f64,
    dw_ext1_ref: &mut f64,
    dx_ext2_ref: &mut f64,
    dy_ext2_ref: &mut f64,
    dz_ext2_ref: &mut f64,
    dw_ext2_ref: &mut f64,
    xsv_ext0_ref: &mut i32,
    ysv_ext0_ref: &mut i32,
    zsv_ext0_ref: &mut i32,
    wsv_ext0_ref: &mut i32,
    xsv_ext1_ref: &mut i32,
    ysv_ext1_ref: &mut i32,
    zsv_ext1_ref: &mut i32,
    wsv_ext1_ref: &mut i32,
    xsv_ext2_ref: &mut i32,
    ysv_ext2_ref: &mut i32,
    zsv_ext2_ref: &mut i32,
    wsv_ext2_ref: &mut i32,
    xsb: i32,
    ysb: i32,
    zsb: i32,
    wsb: i32,
    dx0: f64,
    dy0: f64,
    dz0: f64,
    dw0: f64,
    aPoint: i8,
    aIsBiggerSide: i32,
    bPoint: i8,
) {
    let mut dx_ext0 = *dx_ext0_ref;
    let mut dy_ext0 = *dy_ext0_ref;
    let mut dz_ext0 = *dz_ext0_ref;
    let mut dw_ext0 = *dw_ext0_ref;
    let mut dx_ext1 = *dx_ext1_ref;
    let mut dy_ext1 = *dy_ext1_ref;
    let mut dz_ext1 = *dz_ext1_ref;
    let mut dw_ext1 = *dw_ext1_ref;
    let mut dx_ext2 = *dx_ext2_ref;
    let mut dy_ext2 = *dy_ext2_ref;
    let mut dz_ext2 = *dz_ext2_ref;
    let mut dw_ext2 = *dw_ext2_ref;
    let mut xsv_ext0 = *xsv_ext0_ref;
    let mut ysv_ext0 = *ysv_ext0_ref;
    let mut zsv_ext0 = *zsv_ext0_ref;
    let mut wsv_ext0 = *wsv_ext0_ref;
    let mut xsv_ext1 = *xsv_ext1_ref;
    let mut ysv_ext1 = *ysv_ext1_ref;
    let mut zsv_ext1 = *zsv_ext1_ref;
    let mut wsv_ext1 = *wsv_ext1_ref;
    let mut xsv_ext2 = *xsv_ext2_ref;
    let mut ysv_ext2 = *ysv_ext2_ref;
    let mut zsv_ext2 = *zsv_ext2_ref;
    let mut wsv_ext2 = *wsv_ext2_ref;

    let (c1, c2) = if aIsBiggerSide != 0 {
        (aPoint, bPoint)
    } else {
        (bPoint, aPoint)
    };

    if (c1 & 0x01) == 0 {
        xsv_ext0 = xsb - 1;
        xsv_ext1 = xsb;
        dx_ext0 = (dx0 + 1.0) - 0.309016994374947;
        dx_ext1 = dx0 - 0.309016994374947;
    } else {
        xsv_ext0 = xsb + 1;
        xsv_ext1 = xsb + 1;
        dx_ext0 = (dx0 - 1.0) - 0.309016994374947;
        dx_ext1 = (dx0 - 1.0) - 0.309016994374947;
    }

    if (c1 & 0x02) == 0 {
        ysv_ext0 = ysb;
        ysv_ext1 = ysb;
        dy_ext0 = dy0 - 0.309016994374947;
        dy_ext1 = dy0 - 0.309016994374947;
        if (c1 & 0x01) == 0x01 {
            ysv_ext0 -= 1;
            dy_ext0 += 1.0;
        } else {
            ysv_ext1 -= 1;
            dy_ext1 += 1.0;
        }
    } else {
        ysv_ext0 = ysb + 1;
        ysv_ext1 = ysb + 1;
        dy_ext0 = (dy0 - 1.0) - 0.309016994374947;
        dy_ext1 = (dy0 - 1.0) - 0.309016994374947;
    }

    if (c1 & 0x04) == 0 {
        zsv_ext0 = zsb;
        zsv_ext1 = zsb;
        dz_ext0 = dz0 - 0.309016994374947;
        dz_ext1 = dz0 - 0.309016994374947;
        if (c1 & 0x03) == 0x03 {
            zsv_ext0 -= 1;
            dz_ext0 += 1.0;
        } else {
            zsv_ext1 -= 1;
            dz_ext1 += 1.0;
        }
    } else {
        zsv_ext0 = zsb + 1;
        zsv_ext1 = zsb + 1;
        dz_ext0 = (dz0 - 1.0) - 0.309016994374947;
        dz_ext1 = (dz0 - 1.0) - 0.309016994374947;
    }

    if (c1 & 0x08) == 0 {
        wsv_ext0 = wsb;
        wsv_ext1 = wsb - 1;
        dw_ext0 = dw0 - 0.309016994374947;
        dw_ext1 = (dw0 + 1.0) - 0.309016994374947;
    } else {
        wsv_ext0 = wsb + 1;
        wsv_ext1 = wsb + 1;
        dw_ext0 = (dw0 - 1.0) - 0.309016994374947;
        dw_ext1 = (dw0 - 1.0) - 0.309016994374947;
    }

    xsv_ext2 = xsb;
    ysv_ext2 = ysb;
    zsv_ext2 = zsb;
    wsv_ext2 = wsb;
    dx_ext2 = dx0 - (2.0 * 0.309016994374947);
    dy_ext2 = dy0 - (2.0 * 0.309016994374947);
    dz_ext2 = dz0 - (2.0 * 0.309016994374947);
    dw_ext2 = dw0 - (2.0 * 0.309016994374947);

    if (c2 & 0x01) != 0 {
        xsv_ext2 += 2;
        dx_ext2 -= 2.0;
    } else if (c2 & 0x02) != 0 {
        ysv_ext2 += 2;
        dy_ext2 -= 2.0;
    } else if (c2 & 0x04) != 0 {
        zsv_ext2 += 2;
        dz_ext2 -= 2.0;
    } else {
        wsv_ext2 += 2;
        dw_ext2 -= 2.0;
    }

    *dx_ext0_ref = dx_ext0;
    *dy_ext0_ref = dy_ext0;
    *dz_ext0_ref = dz_ext0;
    *dw_ext0_ref = dw_ext0;
    *dx_ext1_ref = dx_ext1;
    *dy_ext1_ref = dy_ext1;
    *dz_ext1_ref = dz_ext1;
    *dw_ext1_ref = dw_ext1;
    *dx_ext2_ref = dx_ext2;
    *dy_ext2_ref = dy_ext2;
    *dz_ext2_ref = dz_ext2;
    *dw_ext2_ref = dw_ext2;
    *xsv_ext0_ref = xsv_ext0;
    *ysv_ext0_ref = ysv_ext0;
    *zsv_ext0_ref = zsv_ext0;
    *wsv_ext0_ref = wsv_ext0;
    *xsv_ext1_ref = xsv_ext1;
    *ysv_ext1_ref = ysv_ext1;
    *zsv_ext1_ref = zsv_ext1;
    *wsv_ext1_ref = wsv_ext1;
    *xsv_ext2_ref = xsv_ext2;
    *ysv_ext2_ref = ysv_ext2;
    *zsv_ext2_ref = zsv_ext2;
    *wsv_ext2_ref = wsv_ext2;
}
pub fn helper_helper_helper_open_simplex_noise3_3_2_1(
    dx_ext0_ref: &mut f64,
    dy_ext0_ref: &mut f64,
    dz_ext0_ref: &mut f64,
    dx_ext1_ref: &mut f64,
    dy_ext1_ref: &mut f64,
    dz_ext1_ref: &mut f64,
    xsv_ext0_ref: &mut i32,
    ysv_ext0_ref: &mut i32,
    zsv_ext0_ref: &mut i32,
    xsv_ext1_ref: &mut i32,
    ysv_ext1_ref: &mut i32,
    zsv_ext1_ref: &mut i32,
    xsb: i32,
    ysb: i32,
    zsb: i32,
    dx0: f64,
    dy0: f64,
    dz0: f64,
    aPoint: i8,
    bPoint: i8,
) {
    let mut dx_ext0 = *dx_ext0_ref;
    let mut dy_ext0 = *dy_ext0_ref;
    let mut dz_ext0 = *dz_ext0_ref;
    let mut dx_ext1 = *dx_ext1_ref;
    let mut dy_ext1 = *dy_ext1_ref;
    let mut dz_ext1 = *dz_ext1_ref;
    let mut xsv_ext0 = *xsv_ext0_ref;
    let mut ysv_ext0 = *ysv_ext0_ref;
    let mut zsv_ext0 = *zsv_ext0_ref;
    let mut xsv_ext1 = *xsv_ext1_ref;
    let mut ysv_ext1 = *ysv_ext1_ref;
    let mut zsv_ext1 = *zsv_ext1_ref;

    dx_ext0 = (dx0 - 1.0) - (3.0 * (1.0 / 3.0));
    dy_ext0 = (dy0 - 1.0) - (3.0 * (1.0 / 3.0));
    dz_ext0 = (dz0 - 1.0) - (3.0 * (1.0 / 3.0));
    xsv_ext0 = xsb + 1;
    ysv_ext0 = ysb + 1;
    zsv_ext0 = zsb + 1;

    let c = aPoint & bPoint;
    if (c & 0x01) != 0 {
        dx_ext1 = (dx0 - 2.0) - (2.0 * (1.0 / 3.0));
        dy_ext1 = dy0 - (2.0 * (1.0 / 3.0));
        dz_ext1 = dz0 - (2.0 * (1.0 / 3.0));
        xsv_ext1 = xsb + 2;
        ysv_ext1 = ysb;
        zsv_ext1 = zsb;
    } else if (c & 0x02) != 0 {
        dx_ext1 = dx0 - (2.0 * (1.0 / 3.0));
        dy_ext1 = (dy0 - 2.0) - (2.0 * (1.0 / 3.0));
        dz_ext1 = dz0 - (2.0 * (1.0 / 3.0));
        xsv_ext1 = xsb;
        ysv_ext1 = ysb + 2;
        zsv_ext1 = zsb;
    } else {
        dx_ext1 = dx0 - (2.0 * (1.0 / 3.0));
        dy_ext1 = dy0 - (2.0 * (1.0 / 3.0));
        dz_ext1 = (dz0 - 2.0) - (2.0 * (1.0 / 3.0));
        xsv_ext1 = xsb;
        ysv_ext1 = ysb;
        zsv_ext1 = zsb + 2;
    }

    *dx_ext0_ref = dx_ext0;
    *dy_ext0_ref = dy_ext0;
    *dz_ext0_ref = dz_ext0;
    *dx_ext1_ref = dx_ext1;
    *dy_ext1_ref = dy_ext1;
    *dz_ext1_ref = dz_ext1;
    *xsv_ext0_ref = xsv_ext0;
    *ysv_ext0_ref = ysv_ext0;
    *zsv_ext0_ref = zsv_ext0;
    *xsv_ext1_ref = xsv_ext1;
    *ysv_ext1_ref = ysv_ext1;
    *zsv_ext1_ref = zsv_ext1;
}
pub fn helper_helper_helper_open_simplex_noise3_3_2_2(
    dx_ext0_ref: &mut f64,
    dy_ext0_ref: &mut f64,
    dz_ext0_ref: &mut f64,
    dx_ext1_ref: &mut f64,
    dy_ext1_ref: &mut f64,
    dz_ext1_ref: &mut f64,
    xsv_ext0_ref: &mut i32,
    ysv_ext0_ref: &mut i32,
    zsv_ext0_ref: &mut i32,
    xsv_ext1_ref: &mut i32,
    ysv_ext1_ref: &mut i32,
    zsv_ext1_ref: &mut i32,
    xsb: i32,
    ysb: i32,
    zsb: i32,
    dx0: f64,
    dy0: f64,
    dz0: f64,
    aPoint: i8,
    bPoint: i8,
) {
    // Initialize local variables by dereferencing the input references
    let mut dx_ext0 = *dx_ext0_ref;
    let mut dy_ext0 = *dy_ext0_ref;
    let mut dz_ext0 = *dz_ext0_ref;
    let mut dx_ext1 = *dx_ext1_ref;
    let mut dy_ext1 = *dy_ext1_ref;
    let mut dz_ext1 = *dz_ext1_ref;
    let mut xsv_ext0 = *xsv_ext0_ref;
    let mut ysv_ext0 = *ysv_ext0_ref;
    let mut zsv_ext0 = *zsv_ext0_ref;
    let mut xsv_ext1 = *xsv_ext1_ref;
    let mut ysv_ext1 = *ysv_ext1_ref;
    let mut zsv_ext1 = *zsv_ext1_ref;

    // Update values
    dx_ext0 = dx0;
    dy_ext0 = dy0;
    dz_ext0 = dz0;
    xsv_ext0 = xsb;
    ysv_ext0 = ysb;
    zsv_ext0 = zsb;

    let c = aPoint | bPoint;

    if (c & 0x01) == 0 {
        dx_ext1 = (dx0 + 1.0) - (1.0 / 3.0);
        dy_ext1 = (dy0 - 1.0) - (1.0 / 3.0);
        dz_ext1 = (dz0 - 1.0) - (1.0 / 3.0);
        xsv_ext1 = xsb - 1;
        ysv_ext1 = ysb + 1;
        zsv_ext1 = zsb + 1;
    } else if (c & 0x02) == 0 {
        dx_ext1 = (dx0 - 1.0) - (1.0 / 3.0);
        dy_ext1 = (dy0 + 1.0) - (1.0 / 3.0);
        dz_ext1 = (dz0 - 1.0) - (1.0 / 3.0);
        xsv_ext1 = xsb + 1;
        ysv_ext1 = ysb - 1;
        zsv_ext1 = zsb + 1;
    } else {
        dx_ext1 = (dx0 - 1.0) - (1.0 / 3.0);
        dy_ext1 = (dy0 - 1.0) - (1.0 / 3.0);
        dz_ext1 = (dz0 + 1.0) - (1.0 / 3.0);
        xsv_ext1 = xsb + 1;
        ysv_ext1 = ysb + 1;
        zsv_ext1 = zsb - 1;
    }

    // Update the referenced values
    *dx_ext0_ref = dx_ext0;
    *dy_ext0_ref = dy_ext0;
    *dz_ext0_ref = dz_ext0;
    *dx_ext1_ref = dx_ext1;
    *dy_ext1_ref = dy_ext1;
    *dz_ext1_ref = dz_ext1;
    *xsv_ext0_ref = xsv_ext0;
    *ysv_ext0_ref = ysv_ext0;
    *zsv_ext0_ref = zsv_ext0;
    *xsv_ext1_ref = xsv_ext1;
    *ysv_ext1_ref = ysv_ext1;
    *zsv_ext1_ref = zsv_ext1;
}
pub fn helper_helper_helper_open_simplex_noise4_3_2_1(
    dx_ext0_ref: &mut f64,
    dy_ext0_ref: &mut f64,
    dz_ext0_ref: &mut f64,
    dw_ext0_ref: &mut f64,
    dx_ext1_ref: &mut f64,
    dy_ext1_ref: &mut f64,
    dz_ext1_ref: &mut f64,
    dw_ext1_ref: &mut f64,
    dx_ext2_ref: &mut f64,
    dy_ext2_ref: &mut f64,
    dz_ext2_ref: &mut f64,
    dw_ext2_ref: &mut f64,
    xsv_ext0_ref: &mut i32,
    ysv_ext0_ref: &mut i32,
    zsv_ext0_ref: &mut i32,
    wsv_ext0_ref: &mut i32,
    xsv_ext1_ref: &mut i32,
    ysv_ext1_ref: &mut i32,
    zsv_ext1_ref: &mut i32,
    wsv_ext1_ref: &mut i32,
    xsv_ext2_ref: &mut i32,
    ysv_ext2_ref: &mut i32,
    zsv_ext2_ref: &mut i32,
    wsv_ext2_ref: &mut i32,
    xsb: i32,
    ysb: i32,
    zsb: i32,
    wsb: i32,
    dx0: f64,
    dy0: f64,
    dz0: f64,
    dw0: f64,
    aPoint: i8,
    bPoint: i8,
) {
    // Initialize local variables by dereferencing the input references
    let mut dx_ext0 = *dx_ext0_ref;
    let mut dy_ext0 = *dy_ext0_ref;
    let mut dz_ext0 = *dz_ext0_ref;
    let mut dw_ext0 = *dw_ext0_ref;
    let mut dx_ext1 = *dx_ext1_ref;
    let mut dy_ext1 = *dy_ext1_ref;
    let mut dz_ext1 = *dz_ext1_ref;
    let mut dw_ext1 = *dw_ext1_ref;
    let mut dx_ext2 = *dx_ext2_ref;
    let mut dy_ext2 = *dy_ext2_ref;
    let mut dz_ext2 = *dz_ext2_ref;
    let mut dw_ext2 = *dw_ext2_ref;
    let mut xsv_ext0 = *xsv_ext0_ref;
    let mut ysv_ext0 = *ysv_ext0_ref;
    let mut zsv_ext0 = *zsv_ext0_ref;
    let mut wsv_ext0 = *wsv_ext0_ref;
    let mut xsv_ext1 = *xsv_ext1_ref;
    let mut ysv_ext1 = *ysv_ext1_ref;
    let mut zsv_ext1 = *zsv_ext1_ref;
    let mut wsv_ext1 = *wsv_ext1_ref;
    let mut xsv_ext2 = *xsv_ext2_ref;
    let mut ysv_ext2 = *ysv_ext2_ref;
    let mut zsv_ext2 = *zsv_ext2_ref;
    let mut wsv_ext2 = *wsv_ext2_ref;

    // Set ext2 values
    xsv_ext2 = xsb + 1;
    ysv_ext2 = ysb + 1;
    zsv_ext2 = zsb + 1;
    wsv_ext2 = wsb + 1;
    dx_ext2 = (dx0 - 1.0) - (4.0 * 0.309016994374947);
    dy_ext2 = (dy0 - 1.0) - (4.0 * 0.309016994374947);
    dz_ext2 = (dz0 - 1.0) - (4.0 * 0.309016994374947);
    dw_ext2 = (dw0 - 1.0) - (4.0 * 0.309016994374947);

    let c = aPoint & bPoint;

    // Handle x-axis
    if (c & 0x01) != 0 {
        xsv_ext0 = xsb + 2;
        xsv_ext1 = xsb + 1;
        dx_ext0 = (dx0 - 2.0) - (3.0 * 0.309016994374947);
        dx_ext1 = (dx0 - 1.0) - (3.0 * 0.309016994374947);
    } else {
        xsv_ext0 = xsb;
        xsv_ext1 = xsb;
        dx_ext0 = dx0 - (3.0 * 0.309016994374947);
        dx_ext1 = dx0 - (3.0 * 0.309016994374947);
    }

    // Handle y-axis
    if (c & 0x02) != 0 {
        ysv_ext0 = ysb + 1;
        ysv_ext1 = ysb + 1;
        dy_ext0 = (dy0 - 1.0) - (3.0 * 0.309016994374947);
        dy_ext1 = (dy0 - 1.0) - (3.0 * 0.309016994374947);
        
        if (c & 0x01) == 0 {
            ysv_ext0 += 1;
            dy_ext0 -= 1.0;
        } else {
            ysv_ext1 += 1;
            dy_ext1 -= 1.0;
        }
    } else {
        ysv_ext0 = ysb;
        ysv_ext1 = ysb;
        dy_ext0 = dy0 - (3.0 * 0.309016994374947);
        dy_ext1 = dy0 - (3.0 * 0.309016994374947);
    }

    // Handle z-axis
    if (c & 0x04) != 0 {
        zsv_ext0 = zsb + 1;
        zsv_ext1 = zsb + 1;
        dz_ext0 = (dz0 - 1.0) - (3.0 * 0.309016994374947);
        dz_ext1 = (dz0 - 1.0) - (3.0 * 0.309016994374947);
        
        if (c & 0x03) == 0 {
            zsv_ext0 += 1;
            dz_ext0 -= 1.0;
        } else {
            zsv_ext1 += 1;
            dz_ext1 -= 1.0;
        }
    } else {
        zsv_ext0 = zsb;
        zsv_ext1 = zsb;
        dz_ext0 = dz0 - (3.0 * 0.309016994374947);
        dz_ext1 = dz0 - (3.0 * 0.309016994374947);
    }

    // Handle w-axis
    if (c & 0x08) != 0 {
        wsv_ext0 = wsb + 1;
        wsv_ext1 = wsb + 2;
        dw_ext0 = (dw0 - 1.0) - (3.0 * 0.309016994374947);
        dw_ext1 = (dw0 - 2.0) - (3.0 * 0.309016994374947);
    } else {
        wsv_ext0 = wsb;
        wsv_ext1 = wsb;
        dw_ext0 = dw0 - (3.0 * 0.309016994374947);
        dw_ext1 = dw0 - (3.0 * 0.309016994374947);
    }

    // Update all output references
    *dx_ext0_ref = dx_ext0;
    *dy_ext0_ref = dy_ext0;
    *dz_ext0_ref = dz_ext0;
    *dw_ext0_ref = dw_ext0;
    *dx_ext1_ref = dx_ext1;
    *dy_ext1_ref = dy_ext1;
    *dz_ext1_ref = dz_ext1;
    *dw_ext1_ref = dw_ext1;
    *dx_ext2_ref = dx_ext2;
    *dy_ext2_ref = dy_ext2;
    *dz_ext2_ref = dz_ext2;
    *dw_ext2_ref = dw_ext2;
    *xsv_ext0_ref = xsv_ext0;
    *ysv_ext0_ref = ysv_ext0;
    *zsv_ext0_ref = zsv_ext0;
    *wsv_ext0_ref = wsv_ext0;
    *xsv_ext1_ref = xsv_ext1;
    *ysv_ext1_ref = ysv_ext1;
    *zsv_ext1_ref = zsv_ext1;
    *wsv_ext1_ref = wsv_ext1;
    *xsv_ext2_ref = xsv_ext2;
    *ysv_ext2_ref = ysv_ext2;
    *zsv_ext2_ref = zsv_ext2;
    *wsv_ext2_ref = wsv_ext2;
}
pub fn helper_helper_helper_open_simplex_noise4_3_2_2(
    dx_ext0_ref: &mut f64,
    dy_ext0_ref: &mut f64,
    dz_ext0_ref: &mut f64,
    dw_ext0_ref: &mut f64,
    dx_ext1_ref: &mut f64,
    dy_ext1_ref: &mut f64,
    dz_ext1_ref: &mut f64,
    dw_ext1_ref: &mut f64,
    dx_ext2_ref: &mut f64,
    dy_ext2_ref: &mut f64,
    dz_ext2_ref: &mut f64,
    dw_ext2_ref: &mut f64,
    xsv_ext0_ref: &mut i32,
    ysv_ext0_ref: &mut i32,
    zsv_ext0_ref: &mut i32,
    wsv_ext0_ref: &mut i32,
    xsv_ext1_ref: &mut i32,
    ysv_ext1_ref: &mut i32,
    zsv_ext1_ref: &mut i32,
    wsv_ext1_ref: &mut i32,
    xsv_ext2_ref: &mut i32,
    ysv_ext2_ref: &mut i32,
    zsv_ext2_ref: &mut i32,
    wsv_ext2_ref: &mut i32,
    xsb: i32,
    ysb: i32,
    zsb: i32,
    wsb: i32,
    dx0: f64,
    dy0: f64,
    dz0: f64,
    dw0: f64,
    aPoint: i8,
    bPoint: i8,
) {
    let mut dx_ext0 = *dx_ext0_ref;
    let mut dy_ext0 = *dy_ext0_ref;
    let mut dz_ext0 = *dz_ext0_ref;
    let mut dw_ext0 = *dw_ext0_ref;
    let mut dx_ext1 = *dx_ext1_ref;
    let mut dy_ext1 = *dy_ext1_ref;
    let mut dz_ext1 = *dz_ext1_ref;
    let mut dw_ext1 = *dw_ext1_ref;
    let mut dx_ext2 = *dx_ext2_ref;
    let mut dy_ext2 = *dy_ext2_ref;
    let mut dz_ext2 = *dz_ext2_ref;
    let mut dw_ext2 = *dw_ext2_ref;
    let mut xsv_ext0 = *xsv_ext0_ref;
    let mut ysv_ext0 = *ysv_ext0_ref;
    let mut zsv_ext0 = *zsv_ext0_ref;
    let mut wsv_ext0 = *wsv_ext0_ref;
    let mut xsv_ext1 = *xsv_ext1_ref;
    let mut ysv_ext1 = *ysv_ext1_ref;
    let mut zsv_ext1 = *zsv_ext1_ref;
    let mut wsv_ext1 = *wsv_ext1_ref;
    let mut xsv_ext2 = *xsv_ext2_ref;
    let mut ysv_ext2 = *ysv_ext2_ref;
    let mut zsv_ext2 = *zsv_ext2_ref;
    let mut wsv_ext2 = *wsv_ext2_ref;

    let c1 = aPoint & bPoint;
    let c2 = aPoint | bPoint;

    xsv_ext0 = xsb;
    ysv_ext0 = ysb;
    zsv_ext0 = zsb;
    wsv_ext0 = wsb;
    xsv_ext1 = xsb;
    ysv_ext1 = ysb;
    zsv_ext1 = zsb;
    wsv_ext1 = wsb;

    dx_ext0 = dx0 - 0.309016994374947;
    dy_ext0 = dy0 - 0.309016994374947;
    dz_ext0 = dz0 - 0.309016994374947;
    dw_ext0 = dw0 - 0.309016994374947;
    dx_ext1 = dx0 - (2.0 * 0.309016994374947);
    dy_ext1 = dy0 - (2.0 * 0.309016994374947);
    dz_ext1 = dz0 - (2.0 * 0.309016994374947);
    dw_ext1 = dw0 - (2.0 * 0.309016994374947);

    if (c1 & 0x01) != 0 {
        xsv_ext0 += 1;
        dx_ext0 -= 1.0;
        xsv_ext1 += 2;
        dx_ext1 -= 2.0;
    } else if (c1 & 0x02) != 0 {
        ysv_ext0 += 1;
        dy_ext0 -= 1.0;
        ysv_ext1 += 2;
        dy_ext1 -= 2.0;
    } else if (c1 & 0x04) != 0 {
        zsv_ext0 += 1;
        dz_ext0 -= 1.0;
        zsv_ext1 += 2;
        dz_ext1 -= 2.0;
    } else {
        wsv_ext0 += 1;
        dw_ext0 -= 1.0;
        wsv_ext1 += 2;
        dw_ext1 -= 2.0;
    }

    xsv_ext2 = xsb + 1;
    ysv_ext2 = ysb + 1;
    zsv_ext2 = zsb + 1;
    wsv_ext2 = wsb + 1;
    dx_ext2 = (dx0 - 1.0) - (2.0 * 0.309016994374947);
    dy_ext2 = (dy0 - 1.0) - (2.0 * 0.309016994374947);
    dz_ext2 = (dz0 - 1.0) - (2.0 * 0.309016994374947);
    dw_ext2 = (dw0 - 1.0) - (2.0 * 0.309016994374947);

    if (c2 & 0x01) == 0 {
        xsv_ext2 -= 2;
        dx_ext2 += 2.0;
    } else if (c2 & 0x02) == 0 {
        ysv_ext2 -= 2;
        dy_ext2 += 2.0;
    } else if (c2 & 0x04) == 0 {
        zsv_ext2 -= 2;
        dz_ext2 += 2.0;
    } else {
        wsv_ext2 -= 2;
        dw_ext2 += 2.0;
    }

    *dx_ext0_ref = dx_ext0;
    *dy_ext0_ref = dy_ext0;
    *dz_ext0_ref = dz_ext0;
    *dw_ext0_ref = dw_ext0;
    *dx_ext1_ref = dx_ext1;
    *dy_ext1_ref = dy_ext1;
    *dz_ext1_ref = dz_ext1;
    *dw_ext1_ref = dw_ext1;
    *dx_ext2_ref = dx_ext2;
    *dy_ext2_ref = dy_ext2;
    *dz_ext2_ref = dz_ext2;
    *dw_ext2_ref = dw_ext2;
    *xsv_ext0_ref = xsv_ext0;
    *ysv_ext0_ref = ysv_ext0;
    *zsv_ext0_ref = zsv_ext0;
    *wsv_ext0_ref = wsv_ext0;
    *xsv_ext1_ref = xsv_ext1;
    *ysv_ext1_ref = ysv_ext1;
    *zsv_ext1_ref = zsv_ext1;
    *wsv_ext1_ref = wsv_ext1;
    *xsv_ext2_ref = xsv_ext2;
    *ysv_ext2_ref = ysv_ext2;
    *zsv_ext2_ref = zsv_ext2;
    *wsv_ext2_ref = wsv_ext2;
}
pub fn helper_helper_helper_open_simplex_noise4_4_2_1(
    dx_ext0_ref: &mut f64,
    dy_ext0_ref: &mut f64,
    dz_ext0_ref: &mut f64,
    dw_ext0_ref: &mut f64,
    dx_ext1_ref: &mut f64,
    dy_ext1_ref: &mut f64,
    dz_ext1_ref: &mut f64,
    dw_ext1_ref: &mut f64,
    dx_ext2_ref: &mut f64,
    dy_ext2_ref: &mut f64,
    dz_ext2_ref: &mut f64,
    dw_ext2_ref: &mut f64,
    xsv_ext0_ref: &mut i32,
    ysv_ext0_ref: &mut i32,
    zsv_ext0_ref: &mut i32,
    wsv_ext0_ref: &mut i32,
    xsv_ext1_ref: &mut i32,
    ysv_ext1_ref: &mut i32,
    zsv_ext1_ref: &mut i32,
    wsv_ext1_ref: &mut i32,
    xsv_ext2_ref: &mut i32,
    ysv_ext2_ref: &mut i32,
    zsv_ext2_ref: &mut i32,
    wsv_ext2_ref: &mut i32,
    xsb: i32,
    ysb: i32,
    zsb: i32,
    wsb: i32,
    dx0: f64,
    dy0: f64,
    dz0: f64,
    dw0: f64,
    aPoint: i8,
    bPoint: i8,
) {
    // Initialize local variables by dereferencing the input references
    let mut dx_ext0 = *dx_ext0_ref;
    let mut dy_ext0 = *dy_ext0_ref;
    let mut dz_ext0 = *dz_ext0_ref;
    let mut dw_ext0 = *dw_ext0_ref;
    let mut dx_ext1 = *dx_ext1_ref;
    let mut dy_ext1 = *dy_ext1_ref;
    let mut dz_ext1 = *dz_ext1_ref;
    let mut dw_ext1 = *dw_ext1_ref;
    let mut dx_ext2 = *dx_ext2_ref;
    let mut dy_ext2 = *dy_ext2_ref;
    let mut dz_ext2 = *dz_ext2_ref;
    let mut dw_ext2 = *dw_ext2_ref;
    let mut xsv_ext0 = *xsv_ext0_ref;
    let mut ysv_ext0 = *ysv_ext0_ref;
    let mut zsv_ext0 = *zsv_ext0_ref;
    let mut wsv_ext0 = *wsv_ext0_ref;
    let mut xsv_ext1 = *xsv_ext1_ref;
    let mut ysv_ext1 = *ysv_ext1_ref;
    let mut zsv_ext1 = *zsv_ext1_ref;
    let mut wsv_ext1 = *wsv_ext1_ref;
    let mut xsv_ext2 = *xsv_ext2_ref;
    let mut ysv_ext2 = *ysv_ext2_ref;
    let mut zsv_ext2 = *zsv_ext2_ref;
    let mut wsv_ext2 = *wsv_ext2_ref;

    // Set initial values for ext2
    xsv_ext2 = xsb;
    ysv_ext2 = ysb;
    zsv_ext2 = zsb;
    wsv_ext2 = wsb;
    dx_ext2 = dx0;
    dy_ext2 = dy0;
    dz_ext2 = dz0;
    dw_ext2 = dw0;

    let c = aPoint | bPoint;

    // Handle x coordinate
    if (c & 0x01) == 0 {
        xsv_ext0 = xsb - 1;
        xsv_ext1 = xsb;
        dx_ext0 = dx0 + 1.0 - 0.309016994374947;
        dx_ext1 = dx0 - 0.309016994374947;
    } else {
        xsv_ext0 = xsb + 1;
        xsv_ext1 = xsb + 1;
        dx_ext0 = (dx0 - 1.0) - 0.309016994374947;
        dx_ext1 = (dx0 - 1.0) - 0.309016994374947;
    }

    // Handle y coordinate
    if (c & 0x02) == 0 {
        ysv_ext0 = ysb;
        ysv_ext1 = ysb;
        dy_ext0 = dy0 - 0.309016994374947;
        dy_ext1 = dy0 - 0.309016994374947;
        if (c & 0x01) == 0x01 {
            ysv_ext0 -= 1;
            dy_ext0 += 1.0;
        } else {
            ysv_ext1 -= 1;
            dy_ext1 += 1.0;
        }
    } else {
        ysv_ext0 = ysb + 1;
        ysv_ext1 = ysb + 1;
        dy_ext0 = (dy0 - 1.0) - 0.309016994374947;
        dy_ext1 = (dy0 - 1.0) - 0.309016994374947;
    }

    // Handle z coordinate
    if (c & 0x04) == 0 {
        zsv_ext0 = zsb;
        zsv_ext1 = zsb;
        dz_ext0 = dz0 - 0.309016994374947;
        dz_ext1 = dz0 - 0.309016994374947;
        if (c & 0x03) == 0x03 {
            zsv_ext0 -= 1;
            dz_ext0 += 1.0;
        } else {
            zsv_ext1 -= 1;
            dz_ext1 += 1.0;
        }
    } else {
        zsv_ext0 = zsb + 1;
        zsv_ext1 = zsb + 1;
        dz_ext0 = (dz0 - 1.0) - 0.309016994374947;
        dz_ext1 = (dz0 - 1.0) - 0.309016994374947;
    }

    // Handle w coordinate
    if (c & 0x08) == 0 {
        wsv_ext0 = wsb;
        wsv_ext1 = wsb - 1;
        dw_ext0 = dw0 - 0.309016994374947;
        dw_ext1 = (dw0 + 1.0) - 0.309016994374947;
    } else {
        wsv_ext0 = wsb + 1;
        wsv_ext1 = wsb + 1;
        dw_ext0 = (dw0 - 1.0) - 0.309016994374947;
        dw_ext1 = (dw0 - 1.0) - 0.309016994374947;
    }

    // Update all output references
    *dx_ext0_ref = dx_ext0;
    *dy_ext0_ref = dy_ext0;
    *dz_ext0_ref = dz_ext0;
    *dw_ext0_ref = dw_ext0;
    *dx_ext1_ref = dx_ext1;
    *dy_ext1_ref = dy_ext1;
    *dz_ext1_ref = dz_ext1;
    *dw_ext1_ref = dw_ext1;
    *dx_ext2_ref = dx_ext2;
    *dy_ext2_ref = dy_ext2;
    *dz_ext2_ref = dz_ext2;
    *dw_ext2_ref = dw_ext2;
    *xsv_ext0_ref = xsv_ext0;
    *ysv_ext0_ref = ysv_ext0;
    *zsv_ext0_ref = zsv_ext0;
    *wsv_ext0_ref = wsv_ext0;
    *xsv_ext1_ref = xsv_ext1;
    *ysv_ext1_ref = ysv_ext1;
    *zsv_ext1_ref = zsv_ext1;
    *wsv_ext1_ref = wsv_ext1;
    *xsv_ext2_ref = xsv_ext2;
    *ysv_ext2_ref = ysv_ext2;
    *zsv_ext2_ref = zsv_ext2;
    *wsv_ext2_ref = wsv_ext2;
}
pub fn helper_helper_helper_open_simplex_noise4_4_2_2(
    dx_ext0_ref: &mut f64,
    dy_ext0_ref: &mut f64,
    dz_ext0_ref: &mut f64,
    dw_ext0_ref: &mut f64,
    dx_ext1_ref: &mut f64,
    dy_ext1_ref: &mut f64,
    dz_ext1_ref: &mut f64,
    dw_ext1_ref: &mut f64,
    dx_ext2_ref: &mut f64,
    dy_ext2_ref: &mut f64,
    dz_ext2_ref: &mut f64,
    dw_ext2_ref: &mut f64,
    xsv_ext0_ref: &mut i32,
    ysv_ext0_ref: &mut i32,
    zsv_ext0_ref: &mut i32,
    wsv_ext0_ref: &mut i32,
    xsv_ext1_ref: &mut i32,
    ysv_ext1_ref: &mut i32,
    zsv_ext1_ref: &mut i32,
    wsv_ext1_ref: &mut i32,
    xsv_ext2_ref: &mut i32,
    ysv_ext2_ref: &mut i32,
    zsv_ext2_ref: &mut i32,
    wsv_ext2_ref: &mut i32,
    xsb: i32,
    ysb: i32,
    zsb: i32,
    wsb: i32,
    dx0: f64,
    dy0: f64,
    dz0: f64,
    dw0: f64,
    aPoint: i8,
    bPoint: i8,
) {
    let mut dx_ext0 = *dx_ext0_ref;
    let mut dy_ext0 = *dy_ext0_ref;
    let mut dz_ext0 = *dz_ext0_ref;
    let mut dw_ext0 = *dw_ext0_ref;
    let mut dx_ext1 = *dx_ext1_ref;
    let mut dy_ext1 = *dy_ext1_ref;
    let mut dz_ext1 = *dz_ext1_ref;
    let mut dw_ext1 = *dw_ext1_ref;
    let mut dx_ext2 = *dx_ext2_ref;
    let mut dy_ext2 = *dy_ext2_ref;
    let mut dz_ext2 = *dz_ext2_ref;
    let mut dw_ext2 = *dw_ext2_ref;
    let mut xsv_ext0 = *xsv_ext0_ref;
    let mut ysv_ext0 = *ysv_ext0_ref;
    let mut zsv_ext0 = *zsv_ext0_ref;
    let mut wsv_ext0 = *wsv_ext0_ref;
    let mut xsv_ext1 = *xsv_ext1_ref;
    let mut ysv_ext1 = *ysv_ext1_ref;
    let mut zsv_ext1 = *zsv_ext1_ref;
    let mut wsv_ext1 = *wsv_ext1_ref;
    let mut xsv_ext2 = *xsv_ext2_ref;
    let mut ysv_ext2 = *ysv_ext2_ref;
    let mut zsv_ext2 = *zsv_ext2_ref;
    let mut wsv_ext2 = *wsv_ext2_ref;

    let c1 = aPoint | bPoint;
    let c2 = aPoint & bPoint;

    if (c1 & 0x01) == 0 {
        xsv_ext0 = xsb;
        xsv_ext1 = xsb - 1;
        dx_ext0 = dx0 - (3.0 * 0.309016994374947);
        dx_ext1 = (dx0 + 1.0) - (2.0 * 0.309016994374947);
    } else {
        xsv_ext0 = xsb + 1;
        xsv_ext1 = xsb + 1;
        dx_ext0 = (dx0 - 1.0) - (3.0 * 0.309016994374947);
        dx_ext1 = (dx0 - 1.0) - (2.0 * 0.309016994374947);
    }

    if (c1 & 0x02) == 0 {
        ysv_ext0 = ysb;
        ysv_ext1 = ysb - 1;
        dy_ext0 = dy0 - (3.0 * 0.309016994374947);
        dy_ext1 = (dy0 + 1.0) - (2.0 * 0.309016994374947);
    } else {
        ysv_ext0 = ysb + 1;
        ysv_ext1 = ysb + 1;
        dy_ext0 = (dy0 - 1.0) - (3.0 * 0.309016994374947);
        dy_ext1 = (dy0 - 1.0) - (2.0 * 0.309016994374947);
    }

    if (c1 & 0x04) == 0 {
        zsv_ext0 = zsb;
        zsv_ext1 = zsb - 1;
        dz_ext0 = dz0 - (3.0 * 0.309016994374947);
        dz_ext1 = (dz0 + 1.0) - (2.0 * 0.309016994374947);
    } else {
        zsv_ext0 = zsb + 1;
        zsv_ext1 = zsb + 1;
        dz_ext0 = (dz0 - 1.0) - (3.0 * 0.309016994374947);
        dz_ext1 = (dz0 - 1.0) - (2.0 * 0.309016994374947);
    }

    if (c1 & 0x08) == 0 {
        wsv_ext0 = wsb;
        wsv_ext1 = wsb - 1;
        dw_ext0 = dw0 - (3.0 * 0.309016994374947);
        dw_ext1 = (dw0 + 1.0) - (2.0 * 0.309016994374947);
    } else {
        wsv_ext0 = wsb + 1;
        wsv_ext1 = wsb + 1;
        dw_ext0 = (dw0 - 1.0) - (3.0 * 0.309016994374947);
        dw_ext1 = (dw0 - 1.0) - (2.0 * 0.309016994374947);
    }

    xsv_ext2 = xsb;
    ysv_ext2 = ysb;
    zsv_ext2 = zsb;
    wsv_ext2 = wsb;
    dx_ext2 = dx0 - (2.0 * 0.309016994374947);
    dy_ext2 = dy0 - (2.0 * 0.309016994374947);
    dz_ext2 = dz0 - (2.0 * 0.309016994374947);
    dw_ext2 = dw0 - (2.0 * 0.309016994374947);

    if (c2 & 0x01) != 0 {
        xsv_ext2 += 2;
        dx_ext2 -= 2.0;
    } else if (c2 & 0x02) != 0 {
        ysv_ext2 += 2;
        dy_ext2 -= 2.0;
    } else if (c2 & 0x04) != 0 {
        zsv_ext2 += 2;
        dz_ext2 -= 2.0;
    } else {
        wsv_ext2 += 2;
        dw_ext2 -= 2.0;
    }

    *dx_ext0_ref = dx_ext0;
    *dy_ext0_ref = dy_ext0;
    *dz_ext0_ref = dz_ext0;
    *dw_ext0_ref = dw_ext0;
    *dx_ext1_ref = dx_ext1;
    *dy_ext1_ref = dy_ext1;
    *dz_ext1_ref = dz_ext1;
    *dw_ext1_ref = dw_ext1;
    *dx_ext2_ref = dx_ext2;
    *dy_ext2_ref = dy_ext2;
    *dz_ext2_ref = dz_ext2;
    *dw_ext2_ref = dw_ext2;
    *xsv_ext0_ref = xsv_ext0;
    *ysv_ext0_ref = ysv_ext0;
    *zsv_ext0_ref = zsv_ext0;
    *wsv_ext0_ref = wsv_ext0;
    *xsv_ext1_ref = xsv_ext1;
    *ysv_ext1_ref = ysv_ext1;
    *zsv_ext1_ref = zsv_ext1;
    *wsv_ext1_ref = wsv_ext1;
    *xsv_ext2_ref = xsv_ext2;
    *ysv_ext2_ref = ysv_ext2;
    *zsv_ext2_ref = zsv_ext2;
    *wsv_ext2_ref = wsv_ext2;
}
pub fn open_simplex_noise_free(ctx: Option<Box<OsnContext>>) {
    // Rust's ownership system handles memory deallocation automatically
    // When the Box goes out of scope, its contents will be dropped
    // The Option wrapper allows for NULL check equivalent
    if let Some(ctx) = ctx {
        // The Vec fields will be automatically dropped when the struct is dropped
        // No explicit free needed in Rust
    }
    // If ctx is None, nothing happens (equivalent to NULL check in C)
}
pub fn allocate_perm(ctx: &mut OsnContext, nperm: usize, ngrad: usize) -> Result<(), i32> {
    // Free existing allocations if they exist
    ctx.perm = None;
    ctx.perm_grad_index3_d = None;

    // Allocate new vectors
    ctx.perm = Some(vec![0; nperm]);
    ctx.perm_grad_index3_d = Some(vec![0; ngrad]);

    // Check if allocations succeeded
    if ctx.perm.is_none() || ctx.perm_grad_index3_d.is_none() {
        ctx.perm = None;
        ctx.perm_grad_index3_d = None;
        return Err(-12); // ENOMEM is typically -12
    }

    Ok(())
}
pub fn extrapolate2(ctx: &OsnContext, xsb: i32, ysb: i32, dx: f64, dy: f64) -> f64 {
    // Safely access the perm field, returning 0.0 if it's None (similar to NULL check in C)
    let perm = match &ctx.perm {
        Some(p) => p,
        None => return 0.0,
    };

    // Calculate index using the same logic as C code
    // Cast ysb to i16 to match perm's element type
    let index = (perm[(perm[(xsb & 0xFF) as usize] + ysb as i16) as usize & 0xFF] & 0x0E) as usize;

    // Perform the calculation using GRADIENTS2D
    (GRADIENTS2D[index] as f64 * dx) + (GRADIENTS2D[index + 1] as f64 * dy)
}
pub fn extrapolate3(ctx: &OsnContext, xsb: i32, ysb: i32, zsb: i32, dx: f64, dy: f64, dz: f64) -> f64 {
    // Safely access the perm and perm_grad_index3_d vectors
    let perm = ctx.perm.as_ref().expect("perm must be initialized");
    let perm_grad_index3_d = ctx.perm_grad_index3_d.as_ref().expect("perm_grad_index3_d must be initialized");

    // Calculate the index using safe array access with proper type casting
    let index = perm_grad_index3_d[
        (perm[
            (perm[(xsb & 0xFF) as usize] + (ysb & 0xFF) as i16) as usize
        ] as usize + (zsb & 0xFF) as usize) & 0xFF
    ] as usize;

    // Perform the calculation with safe array access
    (GRADIENTS_3D[index] as f64 * dx) + 
    (GRADIENTS_3D[index + 1] as f64 * dy) + 
    (GRADIENTS_3D[index + 2] as f64 * dz)
}
pub fn extrapolate4(ctx: &OsnContext, xsb: i32, ysb: i32, zsb: i32, wsb: i32, dx: f64, dy: f64, dz: f64, dw: f64) -> f64 {
    // Safe access to perm with proper bounds checking
    let perm = match &ctx.perm {
        Some(p) => p,
        None => return 0.0, // Handle missing perm array (could also panic or return Option)
    };

    // Calculate index with proper bounds checking
    let index = perm.get((xsb & 0xFF) as usize)
        .and_then(|&x| perm.get((x as usize + ysb as usize) & 0xFF))
        .and_then(|&y| perm.get((y as usize + zsb as usize) & 0xFF))
        .and_then(|&z| perm.get((z as usize + wsb as usize) & 0xFF))
        .map(|&w| w & 0xFC)
        .unwrap_or(0) as usize;

    // Safe access to gradients4D with bounds checking
    let g0 = GRADIENTS4D.get(index).unwrap_or(&0);
    let g1 = GRADIENTS4D.get(index + 1).unwrap_or(&0);
    let g2 = GRADIENTS4D.get(index + 2).unwrap_or(&0);
    let g3 = GRADIENTS4D.get(index + 3).unwrap_or(&0);

    (*g0 as f64 * dx) + (*g1 as f64 * dy) + (*g2 as f64 * dz) + (*g3 as f64 * dw)
}
pub fn helper_helper_open_simplex_noise3_3_2(
    dx_ext0_ref: &mut f64,
    dy_ext0_ref: &mut f64,
    dz_ext0_ref: &mut f64,
    dx_ext1_ref: &mut f64,
    dy_ext1_ref: &mut f64,
    dz_ext1_ref: &mut f64,
    xsv_ext0_ref: &mut i32,
    ysv_ext0_ref: &mut i32,
    zsv_ext0_ref: &mut i32,
    xsv_ext1_ref: &mut i32,
    ysv_ext1_ref: &mut i32,
    zsv_ext1_ref: &mut i32,
    xsb: i32,
    ysb: i32,
    zsb: i32,
    dx0: f64,
    dy0: f64,
    dz0: f64,
    aPoint: i8,
    aIsFurtherSide: i32,
    bPoint: i8,
) {
    let mut dx_ext0 = *dx_ext0_ref;
    let mut dy_ext0 = *dy_ext0_ref;
    let mut dz_ext0 = *dz_ext0_ref;
    let mut dx_ext1 = *dx_ext1_ref;
    let mut dy_ext1 = *dy_ext1_ref;
    let mut dz_ext1 = *dz_ext1_ref;
    let mut xsv_ext0 = *xsv_ext0_ref;
    let mut ysv_ext0 = *ysv_ext0_ref;
    let mut zsv_ext0 = *zsv_ext0_ref;
    let mut xsv_ext1 = *xsv_ext1_ref;
    let mut ysv_ext1 = *ysv_ext1_ref;
    let mut zsv_ext1 = *zsv_ext1_ref;

    if aIsFurtherSide != 0 {
        helper_helper_helper_open_simplex_noise3_3_2_1(
            &mut dx_ext0,
            &mut dy_ext0,
            &mut dz_ext0,
            &mut dx_ext1,
            &mut dy_ext1,
            &mut dz_ext1,
            &mut xsv_ext0,
            &mut ysv_ext0,
            &mut zsv_ext0,
            &mut xsv_ext1,
            &mut ysv_ext1,
            &mut zsv_ext1,
            xsb,
            ysb,
            zsb,
            dx0,
            dy0,
            dz0,
            aPoint,
            bPoint,
        );
    } else {
        helper_helper_helper_open_simplex_noise3_3_2_2(
            &mut dx_ext0,
            &mut dy_ext0,
            &mut dz_ext0,
            &mut dx_ext1,
            &mut dy_ext1,
            &mut dz_ext1,
            &mut xsv_ext0,
            &mut ysv_ext0,
            &mut zsv_ext0,
            &mut xsv_ext1,
            &mut ysv_ext1,
            &mut zsv_ext1,
            xsb,
            ysb,
            zsb,
            dx0,
            dy0,
            dz0,
            aPoint,
            bPoint,
        );
    }

    *dx_ext0_ref = dx_ext0;
    *dy_ext0_ref = dy_ext0;
    *dz_ext0_ref = dz_ext0;
    *dx_ext1_ref = dx_ext1;
    *dy_ext1_ref = dy_ext1;
    *dz_ext1_ref = dz_ext1;
    *xsv_ext0_ref = xsv_ext0;
    *ysv_ext0_ref = ysv_ext0;
    *zsv_ext0_ref = zsv_ext0;
    *xsv_ext1_ref = xsv_ext1;
    *ysv_ext1_ref = ysv_ext1;
    *zsv_ext1_ref = zsv_ext1;
}
pub fn helper_helper_open_simplex_noise4_3_2(
    dx_ext0_ref: &mut f64,
    dy_ext0_ref: &mut f64,
    dz_ext0_ref: &mut f64,
    dw_ext0_ref: &mut f64,
    dx_ext1_ref: &mut f64,
    dy_ext1_ref: &mut f64,
    dz_ext1_ref: &mut f64,
    dw_ext1_ref: &mut f64,
    dx_ext2_ref: &mut f64,
    dy_ext2_ref: &mut f64,
    dz_ext2_ref: &mut f64,
    dw_ext2_ref: &mut f64,
    xsv_ext0_ref: &mut i32,
    ysv_ext0_ref: &mut i32,
    zsv_ext0_ref: &mut i32,
    wsv_ext0_ref: &mut i32,
    xsv_ext1_ref: &mut i32,
    ysv_ext1_ref: &mut i32,
    zsv_ext1_ref: &mut i32,
    wsv_ext1_ref: &mut i32,
    xsv_ext2_ref: &mut i32,
    ysv_ext2_ref: &mut i32,
    zsv_ext2_ref: &mut i32,
    wsv_ext2_ref: &mut i32,
    xsb: i32,
    ysb: i32,
    zsb: i32,
    wsb: i32,
    dx0: f64,
    dy0: f64,
    dz0: f64,
    dw0: f64,
    aPoint: i8,
    aIsBiggerSide: i32,
    bPoint: i8,
) {
    // Dereference all input references to local variables
    let mut dx_ext0 = *dx_ext0_ref;
    let mut dy_ext0 = *dy_ext0_ref;
    let mut dz_ext0 = *dz_ext0_ref;
    let mut dw_ext0 = *dw_ext0_ref;
    let mut dx_ext1 = *dx_ext1_ref;
    let mut dy_ext1 = *dy_ext1_ref;
    let mut dz_ext1 = *dz_ext1_ref;
    let mut dw_ext1 = *dw_ext1_ref;
    let mut dx_ext2 = *dx_ext2_ref;
    let mut dy_ext2 = *dy_ext2_ref;
    let mut dz_ext2 = *dz_ext2_ref;
    let mut dw_ext2 = *dw_ext2_ref;
    let mut xsv_ext0 = *xsv_ext0_ref;
    let mut ysv_ext0 = *ysv_ext0_ref;
    let mut zsv_ext0 = *zsv_ext0_ref;
    let mut wsv_ext0 = *wsv_ext0_ref;
    let mut xsv_ext1 = *xsv_ext1_ref;
    let mut ysv_ext1 = *ysv_ext1_ref;
    let mut zsv_ext1 = *zsv_ext1_ref;
    let mut wsv_ext1 = *wsv_ext1_ref;
    let mut xsv_ext2 = *xsv_ext2_ref;
    let mut ysv_ext2 = *ysv_ext2_ref;
    let mut zsv_ext2 = *zsv_ext2_ref;
    let mut wsv_ext2 = *wsv_ext2_ref;

    if aIsBiggerSide != 0 {
        helper_helper_helper_open_simplex_noise4_3_2_2(
            &mut dx_ext0, &mut dy_ext0, &mut dz_ext0, &mut dw_ext0,
            &mut dx_ext1, &mut dy_ext1, &mut dz_ext1, &mut dw_ext1,
            &mut dx_ext2, &mut dy_ext2, &mut dz_ext2, &mut dw_ext2,
            &mut xsv_ext0, &mut ysv_ext0, &mut zsv_ext0, &mut wsv_ext0,
            &mut xsv_ext1, &mut ysv_ext1, &mut zsv_ext1, &mut wsv_ext1,
            &mut xsv_ext2, &mut ysv_ext2, &mut zsv_ext2, &mut wsv_ext2,
            xsb, ysb, zsb, wsb,
            dx0, dy0, dz0, dw0,
            aPoint, bPoint,
        );
    } else {
        helper_helper_helper_open_simplex_noise4_3_2_1(
            &mut dx_ext0, &mut dy_ext0, &mut dz_ext0, &mut dw_ext0,
            &mut dx_ext1, &mut dy_ext1, &mut dz_ext1, &mut dw_ext1,
            &mut dx_ext2, &mut dy_ext2, &mut dz_ext2, &mut dw_ext2,
            &mut xsv_ext0, &mut ysv_ext0, &mut zsv_ext0, &mut wsv_ext0,
            &mut xsv_ext1, &mut ysv_ext1, &mut zsv_ext1, &mut wsv_ext1,
            &mut xsv_ext2, &mut ysv_ext2, &mut zsv_ext2, &mut wsv_ext2,
            xsb, ysb, zsb, wsb,
            dx0, dy0, dz0, dw0,
            aPoint, bPoint,
        );
    }

    // Update all output references
    *dx_ext0_ref = dx_ext0;
    *dy_ext0_ref = dy_ext0;
    *dz_ext0_ref = dz_ext0;
    *dw_ext0_ref = dw_ext0;
    *dx_ext1_ref = dx_ext1;
    *dy_ext1_ref = dy_ext1;
    *dz_ext1_ref = dz_ext1;
    *dw_ext1_ref = dw_ext1;
    *dx_ext2_ref = dx_ext2;
    *dy_ext2_ref = dy_ext2;
    *dz_ext2_ref = dz_ext2;
    *dw_ext2_ref = dw_ext2;
    *xsv_ext0_ref = xsv_ext0;
    *ysv_ext0_ref = ysv_ext0;
    *zsv_ext0_ref = zsv_ext0;
    *wsv_ext0_ref = wsv_ext0;
    *xsv_ext1_ref = xsv_ext1;
    *ysv_ext1_ref = ysv_ext1;
    *zsv_ext1_ref = zsv_ext1;
    *wsv_ext1_ref = wsv_ext1;
    *xsv_ext2_ref = xsv_ext2;
    *ysv_ext2_ref = ysv_ext2;
    *zsv_ext2_ref = zsv_ext2;
    *wsv_ext2_ref = wsv_ext2;
}
pub fn helper_helper_open_simplex_noise4_4_2(
    dx_ext0_ref: &mut f64,
    dy_ext0_ref: &mut f64,
    dz_ext0_ref: &mut f64,
    dw_ext0_ref: &mut f64,
    dx_ext1_ref: &mut f64,
    dy_ext1_ref: &mut f64,
    dz_ext1_ref: &mut f64,
    dw_ext1_ref: &mut f64,
    dx_ext2_ref: &mut f64,
    dy_ext2_ref: &mut f64,
    dz_ext2_ref: &mut f64,
    dw_ext2_ref: &mut f64,
    xsv_ext0_ref: &mut i32,
    ysv_ext0_ref: &mut i32,
    zsv_ext0_ref: &mut i32,
    wsv_ext0_ref: &mut i32,
    xsv_ext1_ref: &mut i32,
    ysv_ext1_ref: &mut i32,
    zsv_ext1_ref: &mut i32,
    wsv_ext1_ref: &mut i32,
    xsv_ext2_ref: &mut i32,
    ysv_ext2_ref: &mut i32,
    zsv_ext2_ref: &mut i32,
    wsv_ext2_ref: &mut i32,
    xsb: i32,
    ysb: i32,
    zsb: i32,
    wsb: i32,
    dx0: f64,
    dy0: f64,
    dz0: f64,
    dw0: f64,
    aPoint: i8,
    aIsBiggerSide: i32,
    bPoint: i8,
) {
    let mut dx_ext0 = *dx_ext0_ref;
    let mut dy_ext0 = *dy_ext0_ref;
    let mut dz_ext0 = *dz_ext0_ref;
    let mut dw_ext0 = *dw_ext0_ref;
    let mut dx_ext1 = *dx_ext1_ref;
    let mut dy_ext1 = *dy_ext1_ref;
    let mut dz_ext1 = *dz_ext1_ref;
    let mut dw_ext1 = *dw_ext1_ref;
    let mut dx_ext2 = *dx_ext2_ref;
    let mut dy_ext2 = *dy_ext2_ref;
    let mut dz_ext2 = *dz_ext2_ref;
    let mut dw_ext2 = *dw_ext2_ref;
    let mut xsv_ext0 = *xsv_ext0_ref;
    let mut ysv_ext0 = *ysv_ext0_ref;
    let mut zsv_ext0 = *zsv_ext0_ref;
    let mut wsv_ext0 = *wsv_ext0_ref;
    let mut xsv_ext1 = *xsv_ext1_ref;
    let mut ysv_ext1 = *ysv_ext1_ref;
    let mut zsv_ext1 = *zsv_ext1_ref;
    let mut wsv_ext1 = *wsv_ext1_ref;
    let mut xsv_ext2 = *xsv_ext2_ref;
    let mut ysv_ext2 = *ysv_ext2_ref;
    let mut zsv_ext2 = *zsv_ext2_ref;
    let mut wsv_ext2 = *wsv_ext2_ref;

    if aIsBiggerSide != 0 {
        helper_helper_helper_open_simplex_noise4_4_2_2(
            &mut dx_ext0, &mut dy_ext0, &mut dz_ext0, &mut dw_ext0,
            &mut dx_ext1, &mut dy_ext1, &mut dz_ext1, &mut dw_ext1,
            &mut dx_ext2, &mut dy_ext2, &mut dz_ext2, &mut dw_ext2,
            &mut xsv_ext0, &mut ysv_ext0, &mut zsv_ext0, &mut wsv_ext0,
            &mut xsv_ext1, &mut ysv_ext1, &mut zsv_ext1, &mut wsv_ext1,
            &mut xsv_ext2, &mut ysv_ext2, &mut zsv_ext2, &mut wsv_ext2,
            xsb, ysb, zsb, wsb,
            dx0, dy0, dz0, dw0,
            aPoint, bPoint,
        );
    } else {
        helper_helper_helper_open_simplex_noise4_4_2_1(
            &mut dx_ext0, &mut dy_ext0, &mut dz_ext0, &mut dw_ext0,
            &mut dx_ext1, &mut dy_ext1, &mut dz_ext1, &mut dw_ext1,
            &mut dx_ext2, &mut dy_ext2, &mut dz_ext2, &mut dw_ext2,
            &mut xsv_ext0, &mut ysv_ext0, &mut zsv_ext0, &mut wsv_ext0,
            &mut xsv_ext1, &mut ysv_ext1, &mut zsv_ext1, &mut wsv_ext1,
            &mut xsv_ext2, &mut ysv_ext2, &mut zsv_ext2, &mut wsv_ext2,
            xsb, ysb, zsb, wsb,
            dx0, dy0, dz0, dw0,
            aPoint, bPoint,
        );
    }

    *dx_ext0_ref = dx_ext0;
    *dy_ext0_ref = dy_ext0;
    *dz_ext0_ref = dz_ext0;
    *dw_ext0_ref = dw_ext0;
    *dx_ext1_ref = dx_ext1;
    *dy_ext1_ref = dy_ext1;
    *dz_ext1_ref = dz_ext1;
    *dw_ext1_ref = dw_ext1;
    *dx_ext2_ref = dx_ext2;
    *dy_ext2_ref = dy_ext2;
    *dz_ext2_ref = dz_ext2;
    *dw_ext2_ref = dw_ext2;
    *xsv_ext0_ref = xsv_ext0;
    *ysv_ext0_ref = ysv_ext0;
    *zsv_ext0_ref = zsv_ext0;
    *wsv_ext0_ref = wsv_ext0;
    *xsv_ext1_ref = xsv_ext1;
    *ysv_ext1_ref = ysv_ext1;
    *zsv_ext1_ref = zsv_ext1;
    *wsv_ext1_ref = wsv_ext1;
    *xsv_ext2_ref = xsv_ext2;
    *ysv_ext2_ref = ysv_ext2;
    *zsv_ext2_ref = zsv_ext2;
    *wsv_ext2_ref = wsv_ext2;
}

pub fn open_simplex_noise(seed: i64, ctx: &mut Option<Box<OsnContext>>) -> Result<(), i32> {
    let mut source = [0i16; 256];
    let mut rng = rand::thread_rng();
    
    // Initialize context
    *ctx = Some(Box::new(OsnContext {
        perm: None,
        perm_grad_index3_d: None,
    }));
    
    let ctx_inner = ctx.as_mut().unwrap();
    
    // Allocate permutation tables
    allocate_perm(ctx_inner, 256, 256)?;
    
    // Initialize source array
    for i in 0..256 {
        source[i] = i as i16;
    }
    
    // Process seed
    let mut current_seed = seed;
    current_seed = current_seed.wrapping_mul(6364136223846793005) + 1442695040888963407;
    current_seed = current_seed.wrapping_mul(6364136223846793005) + 1442695040888963407;
    current_seed = current_seed.wrapping_mul(6364136223846793005) + 1442695040888963407;
    
    // Get mutable references to the permutation tables
    let perm = ctx_inner.perm.as_mut().unwrap();
    let perm_grad_index3_d = ctx_inner.perm_grad_index3_d.as_mut().unwrap();
    
    // Fisher-Yates shuffle
    for i in (0..256).rev() {
        current_seed = current_seed.wrapping_mul(6364136223846793005) + 1442695040888963407;
        let mut r = ((current_seed as i64 + 31) % (i as i64 + 1)) as i32;
        if r < 0 {
            r += (i + 1) as i32;
        }
        let r = r as usize;
        
        perm[i] = source[r];
        perm_grad_index3_d[i] = (perm[i] % (GRADIENTS_3D.len() as i16 / 3)) * 3;
        source[r] = source[i];
    }
    
    Ok(())
}
pub fn open_simplex_noise2(ctx: &OsnContext, x: f64, y: f64) -> f64 {
    let stretch_offset = (x + y) * (-0.211324865405187);
    let xs = x + stretch_offset;
    let ys = y + stretch_offset;
    let xsb = fastFloor(xs);
    let ysb = fastFloor(ys);
    let squish_offset = (xsb + ysb) as f64 * 0.366025403784439;
    let xb = xsb as f64 + squish_offset;
    let yb = ysb as f64 + squish_offset;
    let xins = xs - xsb as f64;
    let yins = ys - ysb as f64;
    let in_sum = xins + yins;
    let dx0 = x - xb;
    let dy0 = y - yb;
    
    let mut dx_ext = 0.0;
    let mut dy_ext = 0.0;
    let mut xsv_ext = 0;
    let mut ysv_ext = 0;
    let mut value = 0.0;
    
    let dx1 = (dx0 - 1.0) - 0.366025403784439;
    let dy1 = (dy0 - 0.0) - 0.366025403784439;
    let attn1 = 2.0 - (dx1 * dx1) - (dy1 * dy1);
    if attn1 > 0.0 {
        let attn1_sq = attn1 * attn1;
        value += attn1_sq * attn1_sq * extrapolate2(ctx, xsb + 1, ysb + 0, dx1, dy1);
    }
    
    let dx2 = (dx0 - 0.0) - 0.366025403784439;
    let dy2 = (dy0 - 1.0) - 0.366025403784439;
    let attn2 = 2.0 - (dx2 * dx2) - (dy2 * dy2);
    if attn2 > 0.0 {
        let attn2_sq = attn2 * attn2;
        value += attn2_sq * attn2_sq * extrapolate2(ctx, xsb + 0, ysb + 1, dx2, dy2);
    }
    
    if in_sum <= 1.0 {
        helper_open_simplex_noise2_1(
            &mut dx_ext,
            &mut dy_ext,
            &mut xsv_ext,
            &mut ysv_ext,
            xsb,
            ysb,
            xins,
            yins,
            in_sum,
            dx0,
            dy0,
        );
    } else {
        let mut xsb_mut = xsb;
        let mut ysb_mut = ysb;
        let mut dx0_mut = dx0;
        let mut dy0_mut = dy0;
        helper_open_simplex_noise2_2(
            &mut xsb_mut,
            &mut ysb_mut,
            &mut dx0_mut,
            &mut dy0_mut,
            &mut dx_ext,
            &mut dy_ext,
            &mut xsv_ext,
            &mut ysv_ext,
            xins,
            yins,
            in_sum,
        );
    }
    
    let attn0 = 2.0 - (dx0 * dx0) - (dy0 * dy0);
    if attn0 > 0.0 {
        let attn0_sq = attn0 * attn0;
        value += attn0_sq * attn0_sq * extrapolate2(ctx, xsb, ysb, dx0, dy0);
    }
    
    let attn_ext = 2.0 - (dx_ext * dx_ext) - (dy_ext * dy_ext);
    if attn_ext > 0.0 {
        let attn_ext_sq = attn_ext * attn_ext;
        value += attn_ext_sq * attn_ext_sq * extrapolate2(ctx, xsv_ext, ysv_ext, dx_ext, dy_ext);
    }
    
    value / 47.0
}
pub fn open_simplex_noise_init_perm(ctx: &mut OsnContext, p: &[i16], nelements: usize) -> Result<(), i32> {
    // Call allocate_perm and handle potential error
    allocate_perm(ctx, nelements, 256)?;

    // Copy p into ctx.perm (which is now allocated)
    if let Some(perm) = &mut ctx.perm {
        perm.copy_from_slice(p);
    }

    // Calculate permGradIndex3D values
    if let (Some(perm), Some(perm_grad_index3_d)) = (&ctx.perm, &mut ctx.perm_grad_index3_d) {
        for i in 0..256 {
            let gradient_count = GRADIENTS_3D.len() / 3;
            perm_grad_index3_d[i] = (perm[i] % (gradient_count as i16)) * 3;
        }
    }

    Ok(())
}
pub fn helper_open_simplex_noise3_1(
    dx_ext0_ref: &mut f64,
    dy_ext0_ref: &mut f64,
    dz_ext0_ref: &mut f64,
    dx_ext1_ref: &mut f64,
    dy_ext1_ref: &mut f64,
    dz_ext1_ref: &mut f64,
    xsv_ext0_ref: &mut i32,
    ysv_ext0_ref: &mut i32,
    zsv_ext0_ref: &mut i32,
    xsv_ext1_ref: &mut i32,
    ysv_ext1_ref: &mut i32,
    zsv_ext1_ref: &mut i32,
    value_ref: &mut f64,
    ctx: &OsnContext,
    xsb: i32,
    ysb: i32,
    zsb: i32,
    xins: f64,
    yins: f64,
    zins: f64,
    inSum: f64,
    dx0: f64,
    dy0: f64,
    dz0: f64,
) {
    let mut dx_ext0 = *dx_ext0_ref;
    let mut dy_ext0 = *dy_ext0_ref;
    let mut dz_ext0 = *dz_ext0_ref;
    let mut dx_ext1 = *dx_ext1_ref;
    let mut dy_ext1 = *dy_ext1_ref;
    let mut dz_ext1 = *dz_ext1_ref;
    let mut xsv_ext0 = *xsv_ext0_ref;
    let mut ysv_ext0 = *ysv_ext0_ref;
    let mut zsv_ext0 = *zsv_ext0_ref;
    let mut xsv_ext1 = *xsv_ext1_ref;
    let mut ysv_ext1 = *ysv_ext1_ref;
    let mut zsv_ext1 = *zsv_ext1_ref;
    let mut value = *value_ref;
    
    let mut aPoint = 0x01;
    let mut aScore = xins;
    let mut bPoint = 0x02;
    let mut bScore = yins;
    
    if (aScore >= bScore) && (zins > bScore) {
        bScore = zins;
        bPoint = 0x04;
    } else if (aScore < bScore) && (zins > aScore) {
        aScore = zins;
        aPoint = 0x04;
    }
    
    let wins = 1.0 - inSum;
    if (wins > aScore) || (wins > bScore) {
        helper_helper_open_simplex_noise3_1_1(
            &mut dx_ext0, &mut dy_ext0, &mut dz_ext0,
            &mut dx_ext1, &mut dy_ext1, &mut dz_ext1,
            &mut xsv_ext0, &mut ysv_ext0, &mut zsv_ext0,
            &mut xsv_ext1, &mut ysv_ext1, &mut zsv_ext1,
            xsb, ysb, zsb,
            dx0, dy0, dz0,
            aPoint, aScore, bPoint, bScore,
        );
    } else {
        helper_helper_open_simplex_noise3_1_2(
            &mut dx_ext0, &mut dy_ext0, &mut dz_ext0,
            &mut dx_ext1, &mut dy_ext1, &mut dz_ext1,
            &mut xsv_ext0, &mut ysv_ext0, &mut zsv_ext0,
            &mut xsv_ext1, &mut ysv_ext1, &mut zsv_ext1,
            xsb, ysb, zsb,
            dx0, dy0, dz0,
            aPoint, bPoint,
        );
    }
    
    let attn0 = 2.0 - (dx0 * dx0) - (dy0 * dy0) - (dz0 * dz0);
    if attn0 > 0.0 {
        let attn0 = attn0 * attn0;
        value += (attn0 * attn0) * extrapolate3(ctx, xsb + 0, ysb + 0, zsb + 0, dx0, dy0, dz0);
    }
    
    let dx1 = (dx0 - 1.0) - (1.0 / 3.0);
    let dy1 = (dy0 - 0.0) - (1.0 / 3.0);
    let dz1 = (dz0 - 0.0) - (1.0 / 3.0);
    let attn1 = 2.0 - (dx1 * dx1) - (dy1 * dy1) - (dz1 * dz1);
    if attn1 > 0.0 {
        let attn1 = attn1 * attn1;
        value += (attn1 * attn1) * extrapolate3(ctx, xsb + 1, ysb + 0, zsb + 0, dx1, dy1, dz1);
    }
    
    let dx2 = (dx0 - 0.0) - (1.0 / 3.0);
    let dy2 = (dy0 - 1.0) - (1.0 / 3.0);
    let dz2 = dz1;
    let attn2 = 2.0 - (dx2 * dx2) - (dy2 * dy2) - (dz2 * dz2);
    if attn2 > 0.0 {
        let attn2 = attn2 * attn2;
        value += (attn2 * attn2) * extrapolate3(ctx, xsb + 0, ysb + 1, zsb + 0, dx2, dy2, dz2);
    }
    
    let dx3 = dx2;
    let dy3 = dy1;
    let dz3 = (dz0 - 1.0) - (1.0 / 3.0);
    let attn3 = 2.0 - (dx3 * dx3) - (dy3 * dy3) - (dz3 * dz3);
    if attn3 > 0.0 {
        let attn3 = attn3 * attn3;
        value += (attn3 * attn3) * extrapolate3(ctx, xsb + 0, ysb + 0, zsb + 1, dx3, dy3, dz3);
    }
    
    *dx_ext0_ref = dx_ext0;
    *dy_ext0_ref = dy_ext0;
    *dz_ext0_ref = dz_ext0;
    *dx_ext1_ref = dx_ext1;
    *dy_ext1_ref = dy_ext1;
    *dz_ext1_ref = dz_ext1;
    *xsv_ext0_ref = xsv_ext0;
    *ysv_ext0_ref = ysv_ext0;
    *zsv_ext0_ref = zsv_ext0;
    *xsv_ext1_ref = xsv_ext1;
    *ysv_ext1_ref = ysv_ext1;
    *zsv_ext1_ref = zsv_ext1;
    *value_ref = value;
}
pub fn helper_open_simplex_noise3_2(
    dx0_ref: &mut f64,
    dy0_ref: &mut f64,
    dz0_ref: &mut f64,
    dx_ext0_ref: &mut f64,
    dy_ext0_ref: &mut f64,
    dz_ext0_ref: &mut f64,
    dx_ext1_ref: &mut f64,
    dy_ext1_ref: &mut f64,
    dz_ext1_ref: &mut f64,
    xsv_ext0_ref: &mut i32,
    ysv_ext0_ref: &mut i32,
    zsv_ext0_ref: &mut i32,
    xsv_ext1_ref: &mut i32,
    ysv_ext1_ref: &mut i32,
    zsv_ext1_ref: &mut i32,
    value_ref: &mut f64,
    ctx: &OsnContext,
    xsb: i32,
    ysb: i32,
    zsb: i32,
    xins: f64,
    yins: f64,
    zins: f64,
    inSum: f64,
) {
    let mut dx0 = *dx0_ref;
    let mut dy0 = *dy0_ref;
    let mut dz0 = *dz0_ref;
    let mut dx_ext0 = *dx_ext0_ref;
    let mut dy_ext0 = *dy_ext0_ref;
    let mut dz_ext0 = *dz_ext0_ref;
    let mut dx_ext1 = *dx_ext1_ref;
    let mut dy_ext1 = *dy_ext1_ref;
    let mut dz_ext1 = *dz_ext1_ref;
    let mut xsv_ext0 = *xsv_ext0_ref;
    let mut ysv_ext0 = *ysv_ext0_ref;
    let mut zsv_ext0 = *zsv_ext0_ref;
    let mut xsv_ext1 = *xsv_ext1_ref;
    let mut ysv_ext1 = *ysv_ext1_ref;
    let mut zsv_ext1 = *zsv_ext1_ref;
    let mut value = *value_ref;

    let mut aPoint = 0x06;
    let mut aScore = xins;
    let mut bPoint = 0x05;
    let mut bScore = yins;

    if (aScore <= bScore) && (zins < bScore) {
        bScore = zins;
        bPoint = 0x03;
    } else if (aScore > bScore) && (zins < aScore) {
        aScore = zins;
        aPoint = 0x03;
    }

    let wins = 3.0 - inSum;
    if (wins < aScore) || (wins < bScore) {
        helper_helper_open_simplex_noise3_2_1(
            &mut dx_ext0,
            &mut dy_ext0,
            &mut dz_ext0,
            &mut dx_ext1,
            &mut dy_ext1,
            &mut dz_ext1,
            &mut xsv_ext0,
            &mut ysv_ext0,
            &mut zsv_ext0,
            &mut xsv_ext1,
            &mut ysv_ext1,
            &mut zsv_ext1,
            xsb,
            ysb,
            zsb,
            dx0,
            dy0,
            dz0,
            aPoint,
            aScore,
            bPoint,
            bScore,
        );
    } else {
        helper_helper_open_simplex_noise3_2_2(
            &mut dx_ext0,
            &mut dy_ext0,
            &mut dz_ext0,
            &mut dx_ext1,
            &mut dy_ext1,
            &mut dz_ext1,
            &mut xsv_ext0,
            &mut ysv_ext0,
            &mut zsv_ext0,
            &mut xsv_ext1,
            &mut ysv_ext1,
            &mut zsv_ext1,
            xsb,
            ysb,
            zsb,
            dx0,
            dy0,
            dz0,
            aPoint,
            bPoint,
        );
    }

    let dx3 = (dx0 - 1.0) - (2.0 * (1.0 / 3.0));
    let dy3 = (dy0 - 1.0) - (2.0 * (1.0 / 3.0));
    let dz3 = (dz0 - 0.0) - (2.0 * (1.0 / 3.0));
    let attn3 = ((2.0 - (dx3 * dx3)) - (dy3 * dy3)) - (dz3 * dz3);
    if attn3 > 0.0 {
        let attn3 = attn3 * attn3;
        value += (attn3 * attn3) * extrapolate3(ctx, xsb + 1, ysb + 1, zsb + 0, dx3, dy3, dz3);
    }

    let dx2 = dx3;
    let dy2 = (dy0 - 0.0) - (2.0 * (1.0 / 3.0));
    let dz2 = (dz0 - 1.0) - (2.0 * (1.0 / 3.0));
    let attn2 = ((2.0 - (dx2 * dx2)) - (dy2 * dy2)) - (dz2 * dz2);
    if attn2 > 0.0 {
        let attn2 = attn2 * attn2;
        value += (attn2 * attn2) * extrapolate3(ctx, xsb + 1, ysb + 0, zsb + 1, dx2, dy2, dz2);
    }

    let dx1 = (dx0 - 0.0) - (2.0 * (1.0 / 3.0));
    let dy1 = dy3;
    let dz1 = dz2;
    let attn1 = ((2.0 - (dx1 * dx1)) - (dy1 * dy1)) - (dz1 * dz1);
    if attn1 > 0.0 {
        let attn1 = attn1 * attn1;
        value += (attn1 * attn1) * extrapolate3(ctx, xsb + 0, ysb + 1, zsb + 1, dx1, dy1, dz1);
    }

    dx0 = (dx0 - 1.0) - (3.0 * (1.0 / 3.0));
    dy0 = (dy0 - 1.0) - (3.0 * (1.0 / 3.0));
    dz0 = (dz0 - 1.0) - (3.0 * (1.0 / 3.0));
    let attn0 = ((2.0 - (dx0 * dx0)) - (dy0 * dy0)) - (dz0 * dz0);
    if attn0 > 0.0 {
        let attn0 = attn0 * attn0;
        value += (attn0 * attn0) * extrapolate3(ctx, xsb + 1, ysb + 1, zsb + 1, dx0, dy0, dz0);
    }

    *dx0_ref = dx0;
    *dy0_ref = dy0;
    *dz0_ref = dz0;
    *dx_ext0_ref = dx_ext0;
    *dy_ext0_ref = dy_ext0;
    *dz_ext0_ref = dz_ext0;
    *dx_ext1_ref = dx_ext1;
    *dy_ext1_ref = dy_ext1;
    *dz_ext1_ref = dz_ext1;
    *xsv_ext0_ref = xsv_ext0;
    *ysv_ext0_ref = ysv_ext0;
    *zsv_ext0_ref = zsv_ext0;
    *xsv_ext1_ref = xsv_ext1;
    *ysv_ext1_ref = ysv_ext1;
    *zsv_ext1_ref = zsv_ext1;
    *value_ref = value;
}
pub fn helper_open_simplex_noise3_3(
    dx_ext0_ref: &mut f64,
    dy_ext0_ref: &mut f64,
    dz_ext0_ref: &mut f64,
    dx_ext1_ref: &mut f64,
    dy_ext1_ref: &mut f64,
    dz_ext1_ref: &mut f64,
    xsv_ext0_ref: &mut i32,
    ysv_ext0_ref: &mut i32,
    zsv_ext0_ref: &mut i32,
    xsv_ext1_ref: &mut i32,
    ysv_ext1_ref: &mut i32,
    zsv_ext1_ref: &mut i32,
    value_ref: &mut f64,
    ctx: &OsnContext,
    xsb: i32,
    ysb: i32,
    zsb: i32,
    xins: f64,
    yins: f64,
    zins: f64,
    dx0: f64,
    dy0: f64,
    dz0: f64,
) {
    let mut dx_ext0 = *dx_ext0_ref;
    let mut dy_ext0 = *dy_ext0_ref;
    let mut dz_ext0 = *dz_ext0_ref;
    let mut dx_ext1 = *dx_ext1_ref;
    let mut dy_ext1 = *dy_ext1_ref;
    let mut dz_ext1 = *dz_ext1_ref;
    let mut xsv_ext0 = *xsv_ext0_ref;
    let mut ysv_ext0 = *ysv_ext0_ref;
    let mut zsv_ext0 = *zsv_ext0_ref;
    let mut xsv_ext1 = *xsv_ext1_ref;
    let mut ysv_ext1 = *ysv_ext1_ref;
    let mut zsv_ext1 = *zsv_ext1_ref;
    let mut value = *value_ref;

    let p1 = xins + yins;
    let (aScore, aPoint, aIsFurtherSide) = if p1 > 1.0 {
        (p1 - 1.0, 0x03, 1)
    } else {
        (1.0 - p1, 0x04, 0)
    };

    let p2 = xins + zins;
    let (bScore, bPoint, bIsFurtherSide) = if p2 > 1.0 {
        (p2 - 1.0, 0x05, 1)
    } else {
        (1.0 - p2, 0x02, 0)
    };

    let p3 = yins + zins;
    let (aScore, aPoint, aIsFurtherSide, bScore, bPoint, bIsFurtherSide) = if p3 > 1.0 {
        let score = p3 - 1.0;
        if aScore <= bScore && aScore < score {
            (score, 0x06, 1, bScore, bPoint, bIsFurtherSide)
        } else if aScore > bScore && bScore < score {
            (aScore, aPoint, aIsFurtherSide, score, 0x06, 1)
        } else {
            (aScore, aPoint, aIsFurtherSide, bScore, bPoint, bIsFurtherSide)
        }
    } else {
        let score = 1.0 - p3;
        if aScore <= bScore && aScore < score {
            (score, 0x01, 0, bScore, bPoint, bIsFurtherSide)
        } else if aScore > bScore && bScore < score {
            (aScore, aPoint, aIsFurtherSide, score, 0x01, 0)
        } else {
            (aScore, aPoint, aIsFurtherSide, bScore, bPoint, bIsFurtherSide)
        }
    };

    if aIsFurtherSide == bIsFurtherSide {
        helper_helper_open_simplex_noise3_3_2(
            &mut dx_ext0,
            &mut dy_ext0,
            &mut dz_ext0,
            &mut dx_ext1,
            &mut dy_ext1,
            &mut dz_ext1,
            &mut xsv_ext0,
            &mut ysv_ext0,
            &mut zsv_ext0,
            &mut xsv_ext1,
            &mut ysv_ext1,
            &mut zsv_ext1,
            xsb,
            ysb,
            zsb,
            dx0,
            dy0,
            dz0,
            aPoint,
            aIsFurtherSide,
            bPoint,
        );
    } else {
        helper_helper_open_simplex_noise3_3_1(
            &mut dx_ext0,
            &mut dy_ext0,
            &mut dz_ext0,
            &mut dx_ext1,
            &mut dy_ext1,
            &mut dz_ext1,
            &mut xsv_ext0,
            &mut ysv_ext0,
            &mut zsv_ext0,
            &mut xsv_ext1,
            &mut ysv_ext1,
            &mut zsv_ext1,
            xsb,
            ysb,
            zsb,
            dx0,
            dy0,
            dz0,
            aPoint,
            aIsFurtherSide,
            bPoint,
        );
    }

    let dx1 = (dx0 - 1.0) - (1.0 / 3.0);
    let dy1 = (dy0 - 0.0) - (1.0 / 3.0);
    let dz1 = (dz0 - 0.0) - (1.0 / 3.0);
    let attn1 = ((2.0 - (dx1 * dx1)) - (dy1 * dy1)) - (dz1 * dz1);
    if attn1 > 0.0 {
        let attn1 = attn1 * attn1;
        value += (attn1 * attn1) * extrapolate3(ctx, xsb + 1, ysb + 0, zsb + 0, dx1, dy1, dz1);
    }

    let dx2 = (dx0 - 0.0) - (1.0 / 3.0);
    let dy2 = (dy0 - 1.0) - (1.0 / 3.0);
    let dz2 = dz1;
    let attn2 = ((2.0 - (dx2 * dx2)) - (dy2 * dy2)) - (dz2 * dz2);
    if attn2 > 0.0 {
        let attn2 = attn2 * attn2;
        value += (attn2 * attn2) * extrapolate3(ctx, xsb + 0, ysb + 1, zsb + 0, dx2, dy2, dz2);
    }

    let dx3 = dx2;
    let dy3 = dy1;
    let dz3 = (dz0 - 1.0) - (1.0 / 3.0);
    let attn3 = ((2.0 - (dx3 * dx3)) - (dy3 * dy3)) - (dz3 * dz3);
    if attn3 > 0.0 {
        let attn3 = attn3 * attn3;
        value += (attn3 * attn3) * extrapolate3(ctx, xsb + 0, ysb + 0, zsb + 1, dx3, dy3, dz3);
    }

    let dx4 = (dx0 - 1.0) - (2.0 * (1.0 / 3.0));
    let dy4 = (dy0 - 1.0) - (2.0 * (1.0 / 3.0));
    let dz4 = (dz0 - 0.0) - (2.0 * (1.0 / 3.0));
    let attn4 = ((2.0 - (dx4 * dx4)) - (dy4 * dy4)) - (dz4 * dz4);
    if attn4 > 0.0 {
        let attn4 = attn4 * attn4;
        value += (attn4 * attn4) * extrapolate3(ctx, xsb + 1, ysb + 1, zsb + 0, dx4, dy4, dz4);
    }

    let dx5 = dx4;
    let dy5 = (dy0 - 0.0) - (2.0 * (1.0 / 3.0));
    let dz5 = (dz0 - 1.0) - (2.0 * (1.0 / 3.0));
    let attn5 = ((2.0 - (dx5 * dx5)) - (dy5 * dy5)) - (dz5 * dz5);
    if attn5 > 0.0 {
        let attn5 = attn5 * attn5;
        value += (attn5 * attn5) * extrapolate3(ctx, xsb + 1, ysb + 0, zsb + 1, dx5, dy5, dz5);
    }

    let dx6 = (dx0 - 0.0) - (2.0 * (1.0 / 3.0));
    let dy6 = dy4;
    let dz6 = dz5;
    let attn6 = ((2.0 - (dx6 * dx6)) - (dy6 * dy6)) - (dz6 * dz6);
    if attn6 > 0.0 {
        let attn6 = attn6 * attn6;
        value += (attn6 * attn6) * extrapolate3(ctx, xsb + 0, ysb + 1, zsb + 1, dx6, dy6, dz6);
    }

    *dx_ext0_ref = dx_ext0;
    *dy_ext0_ref = dy_ext0;
    *dz_ext0_ref = dz_ext0;
    *dx_ext1_ref = dx_ext1;
    *dy_ext1_ref = dy_ext1;
    *dz_ext1_ref = dz_ext1;
    *xsv_ext0_ref = xsv_ext0;
    *ysv_ext0_ref = ysv_ext0;
    *zsv_ext0_ref = zsv_ext0;
    *xsv_ext1_ref = xsv_ext1;
    *ysv_ext1_ref = ysv_ext1;
    *zsv_ext1_ref = zsv_ext1;
    *value_ref = value;
}
pub fn helper_open_simplex_noise4_1(
    dx_ext0_ref: &mut f64,
    dy_ext0_ref: &mut f64,
    dz_ext0_ref: &mut f64,
    dw_ext0_ref: &mut f64,
    dx_ext1_ref: &mut f64,
    dy_ext1_ref: &mut f64,
    dz_ext1_ref: &mut f64,
    dw_ext1_ref: &mut f64,
    dx_ext2_ref: &mut f64,
    dy_ext2_ref: &mut f64,
    dz_ext2_ref: &mut f64,
    dw_ext2_ref: &mut f64,
    xsv_ext0_ref: &mut i32,
    ysv_ext0_ref: &mut i32,
    zsv_ext0_ref: &mut i32,
    wsv_ext0_ref: &mut i32,
    xsv_ext1_ref: &mut i32,
    ysv_ext1_ref: &mut i32,
    zsv_ext1_ref: &mut i32,
    ysv_ext2_ref: &mut i32,
    zsv_ext2_ref: &mut i32,
    wsv_ext2_ref: &mut i32,
    value_ref: &mut f64,
    ctx: &OsnContext,
    xsb: i32,
    ysb: i32,
    zsb: i32,
    wsb: i32,
    xins: f64,
    yins: f64,
    zins: f64,
    wins: f64,
    in_sum: f64,
    dx0: f64,
    dy0: f64,
    dz0: f64,
    dw0: f64,
    wsv_ext1: i32,
    xsv_ext2: i32,
) {
    let mut dx_ext0 = *dx_ext0_ref;
    let mut dy_ext0 = *dy_ext0_ref;
    let mut dz_ext0 = *dz_ext0_ref;
    let mut dw_ext0 = *dw_ext0_ref;
    let mut dx_ext1 = *dx_ext1_ref;
    let mut dy_ext1 = *dy_ext1_ref;
    let mut dz_ext1 = *dz_ext1_ref;
    let mut dw_ext1 = *dw_ext1_ref;
    let mut dx_ext2 = *dx_ext2_ref;
    let mut dy_ext2 = *dy_ext2_ref;
    let mut dz_ext2 = *dz_ext2_ref;
    let mut dw_ext2 = *dw_ext2_ref;
    let mut xsv_ext0 = *xsv_ext0_ref;
    let mut ysv_ext0 = *ysv_ext0_ref;
    let mut zsv_ext0 = *zsv_ext0_ref;
    let mut wsv_ext0 = *wsv_ext0_ref;
    let mut xsv_ext1 = *xsv_ext1_ref;
    let mut ysv_ext1 = *ysv_ext1_ref;
    let mut zsv_ext1 = *zsv_ext1_ref;
    let mut ysv_ext2 = *ysv_ext2_ref;
    let mut zsv_ext2 = *zsv_ext2_ref;
    let mut wsv_ext2 = *wsv_ext2_ref;
    let mut value = *value_ref;
    
    let mut a_point = 0x01;
    let mut a_score = xins;
    let mut b_point = 0x02;
    let mut b_score = yins;

    if (a_score >= b_score) && (zins > b_score) {
        b_score = zins;
        b_point = 0x04;
    } else if (a_score < b_score) && (zins > a_score) {
        a_score = zins;
        a_point = 0x04;
    }

    if (a_score >= b_score) && (wins > b_score) {
        b_score = wins;
        b_point = 0x08;
    } else if (a_score < b_score) && (wins > a_score) {
        a_score = wins;
        a_point = 0x08;
    }

    let uins = 1.0 - in_sum;
    if (uins > a_score) || (uins > b_score) {
        helper_helper_open_simplex_noise4_1_1(
            &mut dx_ext0, &mut dy_ext0, &mut dz_ext0, &mut dw_ext0,
            &mut dx_ext1, &mut dy_ext1, &mut dz_ext1, &mut dz_ext2, &mut dw_ext2,
            &mut xsv_ext0, &mut ysv_ext0, &mut zsv_ext0, &mut wsv_ext0,
            &mut xsv_ext1, &mut ysv_ext1, &mut zsv_ext1, &mut zsv_ext2, &mut wsv_ext2,
            xsb, ysb, zsb, wsb, dx0, dy0, dz0, dw0,
            wsv_ext1, xsv_ext2, dw_ext1, dx_ext2, dy_ext2, ysv_ext2,
            a_point, a_score, b_point, b_score,
        );
    } else {
        helper_helper_open_simplex_noise4_1_2(
            &mut dx_ext0, &mut dy_ext0, &mut dz_ext0, &mut dw_ext0,
            &mut dx_ext1, &mut dy_ext1, &mut dz_ext1, &mut dw_ext1,
            &mut dx_ext2, &mut dy_ext2, &mut dz_ext2, &mut dw_ext2,
            &mut xsv_ext0, &mut ysv_ext0, &mut zsv_ext0, &mut wsv_ext0,
            &mut xsv_ext1, &mut ysv_ext1, &mut zsv_ext1,
            &mut ysv_ext2, &mut zsv_ext2, &mut wsv_ext2,
            xsb, ysb, zsb, wsb, dx0, dy0, dz0, dw0,
            wsv_ext1, xsv_ext2, a_point, b_point,
        );
    }

    let attn0 = (2.0 - (dx0 * dx0) - (dy0 * dy0) - (dz0 * dz0) - (dw0 * dw0));
    if attn0 > 0.0 {
        let attn0 = attn0 * attn0;
        value += (attn0 * attn0) * extrapolate4(ctx, xsb + 0, ysb + 0, zsb + 0, wsb + 0, dx0, dy0, dz0, dw0);
    }

    let dx1 = (dx0 - 1.0) - 0.309016994374947;
    let dy1 = (dy0 - 0.0) - 0.309016994374947;
    let dz1 = (dz0 - 0.0) - 0.309016994374947;
    let dw1 = (dw0 - 0.0) - 0.309016994374947;
    let attn1 = (2.0 - (dx1 * dx1) - (dy1 * dy1) - (dz1 * dz1) - (dw1 * dw1));
    if attn1 > 0.0 {
        let attn1 = attn1 * attn1;
        value += (attn1 * attn1) * extrapolate4(ctx, xsb + 1, ysb + 0, zsb + 0, wsb + 0, dx1, dy1, dz1, dw1);
    }

    let dx2 = (dx0 - 0.0) - 0.309016994374947;
    let dy2 = (dy0 - 1.0) - 0.309016994374947;
    let dz2 = dz1;
    let dw2 = dw1;
    let attn2 = (2.0 - (dx2 * dx2) - (dy2 * dy2) - (dz2 * dz2) - (dw2 * dw2));
    if attn2 > 0.0 {
        let attn2 = attn2 * attn2;
        value += (attn2 * attn2) * extrapolate4(ctx, xsb + 0, ysb + 1, zsb + 0, wsb + 0, dx2, dy2, dz2, dw2);
    }

    let dx3 = dx2;
    let dy3 = dy1;
    let dz3 = (dz0 - 1.0) - 0.309016994374947;
    let dw3 = dw1;
    let attn3 = (2.0 - (dx3 * dx3) - (dy3 * dy3) - (dz3 * dz3) - (dw3 * dw3));
    if attn3 > 0.0 {
        let attn3 = attn3 * attn3;
        value += (attn3 * attn3) * extrapolate4(ctx, xsb + 0, ysb + 0, zsb + 1, wsb + 0, dx3, dy3, dz3, dw3);
    }

    let dx4 = dx2;
    let dy4 = dy1;
    let dz4 = dz1;
    let dw4 = (dw0 - 1.0) - 0.309016994374947;
    let attn4 = (2.0 - (dx4 * dx4) - (dy4 * dy4) - (dz4 * dz4) - (dw4 * dw4));
    if attn4 > 0.0 {
        let attn4 = attn4 * attn4;
        value += (attn4 * attn4) * extrapolate4(ctx, xsb + 0, ysb + 0, zsb + 0, wsb + 1, dx4, dy4, dz4, dw4);
    }

    *dx_ext0_ref = dx_ext0;
    *dy_ext0_ref = dy_ext0;
    *dz_ext0_ref = dz_ext0;
    *dw_ext0_ref = dw_ext0;
    *dx_ext1_ref = dx_ext1;
    *dy_ext1_ref = dy_ext1;
    *dz_ext1_ref = dz_ext1;
    *dw_ext1_ref = dw_ext1;
    *dx_ext2_ref = dx_ext2;
    *dy_ext2_ref = dy_ext2;
    *dz_ext2_ref = dz_ext2;
    *dw_ext2_ref = dw_ext2;
    *xsv_ext0_ref = xsv_ext0;
    *ysv_ext0_ref = ysv_ext0;
    *zsv_ext0_ref = zsv_ext0;
    *wsv_ext0_ref = wsv_ext0;
    *xsv_ext1_ref = xsv_ext1;
    *ysv_ext1_ref = ysv_ext1;
    *zsv_ext1_ref = zsv_ext1;
    *ysv_ext2_ref = ysv_ext2;
    *zsv_ext2_ref = zsv_ext2;
    *wsv_ext2_ref = wsv_ext2;
    *value_ref = value;
}
pub fn helper_open_simplex_noise4_2(
    dx0_ref: &mut f64,
    dy0_ref: &mut f64,
    dz0_ref: &mut f64,
    dw0_ref: &mut f64,
    dx_ext0_ref: &mut f64,
    dy_ext0_ref: &mut f64,
    dz_ext0_ref: &mut f64,
    dw_ext0_ref: &mut f64,
    dx_ext1_ref: &mut f64,
    dy_ext1_ref: &mut f64,
    dz_ext1_ref: &mut f64,
    dw_ext1_ref: &mut f64,
    dx_ext2_ref: &mut f64,
    dy_ext2_ref: &mut f64,
    dz_ext2_ref: &mut f64,
    dw_ext2_ref: &mut f64,
    xsv_ext0_ref: &mut i32,
    ysv_ext0_ref: &mut i32,
    zsv_ext0_ref: &mut i32,
    wsv_ext0_ref: &mut i32,
    xsv_ext1_ref: &mut i32,
    ysv_ext1_ref: &mut i32,
    zsv_ext1_ref: &mut i32,
    ysv_ext2_ref: &mut i32,
    zsv_ext2_ref: &mut i32,
    wsv_ext2_ref: &mut i32,
    value_ref: &mut f64,
    ctx: &OsnContext,
    xsb: i32,
    ysb: i32,
    zsb: i32,
    wsb: i32,
    xins: f64,
    yins: f64,
    zins: f64,
    wins: f64,
    in_sum: f64,
    wsv_ext1: i32,
    xsv_ext2: i32,
) {
    let mut dx0 = *dx0_ref;
    let mut dy0 = *dy0_ref;
    let mut dz0 = *dz0_ref;
    let mut dw0 = *dw0_ref;
    let mut dx_ext0 = *dx_ext0_ref;
    let mut dy_ext0 = *dy_ext0_ref;
    let mut dz_ext0 = *dz_ext0_ref;
    let mut dw_ext0 = *dw_ext0_ref;
    let mut dx_ext1 = *dx_ext1_ref;
    let mut dy_ext1 = *dy_ext1_ref;
    let mut dz_ext1 = *dz_ext1_ref;
    let mut dw_ext1 = *dw_ext1_ref;
    let mut dx_ext2 = *dx_ext2_ref;
    let mut dy_ext2 = *dy_ext2_ref;
    let mut dz_ext2 = *dz_ext2_ref;
    let mut dw_ext2 = *dw_ext2_ref;
    let mut xsv_ext0 = *xsv_ext0_ref;
    let mut ysv_ext0 = *ysv_ext0_ref;
    let mut zsv_ext0 = *zsv_ext0_ref;
    let mut wsv_ext0 = *wsv_ext0_ref;
    let mut xsv_ext1 = *xsv_ext1_ref;
    let mut ysv_ext1 = *ysv_ext1_ref;
    let mut zsv_ext1 = *zsv_ext1_ref;
    let mut ysv_ext2 = *ysv_ext2_ref;
    let mut zsv_ext2 = *zsv_ext2_ref;
    let mut wsv_ext2 = *wsv_ext2_ref;
    let mut value = *value_ref;

    let mut a_point = 0x0E;
    let mut a_score = xins;
    let mut b_point = 0x0D;
    let mut b_score = yins;

    if (a_score <= b_score) && (zins < b_score) {
        b_score = zins;
        b_point = 0x0B;
    } else if (a_score > b_score) && (zins < a_score) {
        a_score = zins;
        a_point = 0x0B;
    }

    if (a_score <= b_score) && (wins < b_score) {
        b_score = wins;
        b_point = 0x07;
    } else if (a_score > b_score) && (wins < a_score) {
        a_score = wins;
        a_point = 0x07;
    }

    let uins = 4.0 - in_sum;
    if (uins < a_score) || (uins < b_score) {
        helper_helper_open_simplex_noise4_2_1(
            &mut dx_ext0,
            &mut dy_ext0,
            &mut dz_ext0,
            &mut dw_ext0,
            &mut dx_ext1,
            &mut dy_ext1,
            &mut dz_ext1,
            &mut dz_ext2,
            &mut dw_ext2,
            &mut xsv_ext0,
            &mut ysv_ext0,
            &mut zsv_ext0,
            &mut wsv_ext0,
            &mut xsv_ext1,
            &mut ysv_ext1,
            &mut zsv_ext1,
            &mut zsv_ext2,
            &mut wsv_ext2,
            xsb,
            ysb,
            zsb,
            wsb,
            wsv_ext1,
            xsv_ext2,
            dx0,
            dy0,
            dz0,
            dw0,
            dw_ext1,
            dx_ext2,
            dy_ext2,
            ysv_ext2,
            a_point,
            a_score,
            b_point,
            b_score,
        );
    } else {
        helper_helper_open_simplex_noise4_2_2(
            &mut dx_ext0,
            &mut dy_ext0,
            &mut dz_ext0,
            &mut dw_ext0,
            &mut dx_ext1,
            &mut dy_ext1,
            &mut dz_ext1,
            &mut dw_ext1,
            &mut dx_ext2,
            &mut dy_ext2,
            &mut dz_ext2,
            &mut dw_ext2,
            &mut xsv_ext0,
            &mut ysv_ext0,
            &mut zsv_ext0,
            &mut wsv_ext0,
            &mut xsv_ext1,
            &mut ysv_ext1,
            &mut zsv_ext1,
            &mut ysv_ext2,
            &mut zsv_ext2,
            &mut wsv_ext2,
            xsb,
            ysb,
            zsb,
            wsb,
            wsv_ext1,
            xsv_ext2,
            dx0,
            dy0,
            dz0,
            dw0,
            a_point,
            b_point,
        );
    }

    let dx4 = (dx0 - 1.0) - (3.0 * 0.309016994374947);
    let dy4 = (dy0 - 1.0) - (3.0 * 0.309016994374947);
    let dz4 = (dz0 - 1.0) - (3.0 * 0.309016994374947);
    let dw4 = dw0 - (3.0 * 0.309016994374947);
    let attn4 = (2.0 - (dx4 * dx4) - (dy4 * dy4) - (dz4 * dz4)) - (dw4 * dw4);
    if attn4 > 0.0 {
        let attn4_squared = attn4 * attn4;
        value += attn4_squared * attn4_squared * extrapolate4(
            ctx,
            xsb + 1,
            ysb + 1,
            zsb + 1,
            wsb + 0,
            dx4,
            dy4,
            dz4,
            dw4,
        );
    }

    let dx3 = dx4;
    let dy3 = dy4;
    let dz3 = dz0 - (3.0 * 0.309016994374947);
    let dw3 = (dw0 - 1.0) - (3.0 * 0.309016994374947);
    let attn3 = (2.0 - (dx3 * dx3) - (dy3 * dy3) - (dz3 * dz3)) - (dw3 * dw3);
    if attn3 > 0.0 {
        let attn3_squared = attn3 * attn3;
        value += attn3_squared * attn3_squared * extrapolate4(
            ctx,
            xsb + 1,
            ysb + 1,
            zsb + 0,
            wsb + 1,
            dx3,
            dy3,
            dz3,
            dw3,
        );
    }

    let dx2 = dx4;
    let dy2 = dy0 - (3.0 * 0.309016994374947);
    let dz2 = dz4;
    let dw2 = dw3;
    let attn2 = (2.0 - (dx2 * dx2) - (dy2 * dy2) - (dz2 * dz2)) - (dw2 * dw2);
    if attn2 > 0.0 {
        let attn2_squared = attn2 * attn2;
        value += attn2_squared * attn2_squared * extrapolate4(
            ctx,
            xsb + 1,
            ysb + 0,
            zsb + 1,
            wsb + 1,
            dx2,
            dy2,
            dz2,
            dw2,
        );
    }

    let dx1 = dx0 - (3.0 * 0.309016994374947);
    let dz1 = dz4;
    let dy1 = dy4;
    let dw1 = dw3;
    let attn1 = (2.0 - (dx1 * dx1) - (dy1 * dy1) - (dz1 * dz1)) - (dw1 * dw1);
    if attn1 > 0.0 {
        let attn1_squared = attn1 * attn1;
        value += attn1_squared * attn1_squared * extrapolate4(
            ctx,
            xsb + 0,
            ysb + 1,
            zsb + 1,
            wsb + 1,
            dx1,
            dy1,
            dz1,
            dw1,
        );
    }

    dx0 = (dx0 - 1.0) - (4.0 * 0.309016994374947);
    dy0 = (dy0 - 1.0) - (4.0 * 0.309016994374947);
    dz0 = (dz0 - 1.0) - (4.0 * 0.309016994374947);
    dw0 = (dw0 - 1.0) - (4.0 * 0.309016994374947);
    let attn0 = (2.0 - (dx0 * dx0) - (dy0 * dy0) - (dz0 * dz0)) - (dw0 * dw0);
    if attn0 > 0.0 {
        let attn0_squared = attn0 * attn0;
        value += attn0_squared * attn0_squared * extrapolate4(
            ctx,
            xsb + 1,
            ysb + 1,
            zsb + 1,
            wsb + 1,
            dx0,
            dy0,
            dz0,
            dw0,
        );
    }

    *dx0_ref = dx0;
    *dy0_ref = dy0;
    *dz0_ref = dz0;
    *dw0_ref = dw0;
    *dx_ext0_ref = dx_ext0;
    *dy_ext0_ref = dy_ext0;
    *dz_ext0_ref = dz_ext0;
    *dw_ext0_ref = dw_ext0;
    *dx_ext1_ref = dx_ext1;
    *dy_ext1_ref = dy_ext1;
    *dz_ext1_ref = dz_ext1;
    *dw_ext1_ref = dw_ext1;
    *dx_ext2_ref = dx_ext2;
    *dy_ext2_ref = dy_ext2;
    *dz_ext2_ref = dz_ext2;
    *dw_ext2_ref = dw_ext2;
    *xsv_ext0_ref = xsv_ext0;
    *ysv_ext0_ref = ysv_ext0;
    *zsv_ext0_ref = zsv_ext0;
    *wsv_ext0_ref = wsv_ext0;
    *xsv_ext1_ref = xsv_ext1;
    *ysv_ext1_ref = ysv_ext1;
    *zsv_ext1_ref = zsv_ext1;
    *ysv_ext2_ref = ysv_ext2;
    *zsv_ext2_ref = zsv_ext2;
    *wsv_ext2_ref = wsv_ext2;
    *value_ref = value;
}
pub fn helper_open_simplex_noise4_3(
    dx_ext0_ref: &mut f64,
    dy_ext0_ref: &mut f64,
    dz_ext0_ref: &mut f64,
    dw_ext0_ref: &mut f64,
    dx_ext1_ref: &mut f64,
    dy_ext1_ref: &mut f64,
    dz_ext1_ref: &mut f64,
    dw_ext1_ref: &mut f64,
    dx_ext2_ref: &mut f64,
    dy_ext2_ref: &mut f64,
    dz_ext2_ref: &mut f64,
    dw_ext2_ref: &mut f64,
    xsv_ext0_ref: &mut i32,
    ysv_ext0_ref: &mut i32,
    zsv_ext0_ref: &mut i32,
    wsv_ext0_ref: &mut i32,
    xsv_ext1_ref: &mut i32,
    ysv_ext1_ref: &mut i32,
    zsv_ext1_ref: &mut i32,
    wsv_ext1_ref: &mut i32,
    xsv_ext2_ref: &mut i32,
    ysv_ext2_ref: &mut i32,
    zsv_ext2_ref: &mut i32,
    wsv_ext2_ref: &mut i32,
    value_ref: &mut f64,
    ctx: &OsnContext,
    xsb: i32,
    ysb: i32,
    zsb: i32,
    wsb: i32,
    xins: f64,
    yins: f64,
    zins: f64,
    wins: f64,
    in_sum: f64,
    dx0: f64,
    dy0: f64,
    dz0: f64,
    dw0: f64,
) {
    let mut dx_ext0 = *dx_ext0_ref;
    let mut dy_ext0 = *dy_ext0_ref;
    let mut dz_ext0 = *dz_ext0_ref;
    let mut dw_ext0 = *dw_ext0_ref;
    let mut dx_ext1 = *dx_ext1_ref;
    let mut dy_ext1 = *dy_ext1_ref;
    let mut dz_ext1 = *dz_ext1_ref;
    let mut dw_ext1 = *dw_ext1_ref;
    let mut dx_ext2 = *dx_ext2_ref;
    let mut dy_ext2 = *dy_ext2_ref;
    let mut dz_ext2 = *dz_ext2_ref;
    let mut dw_ext2 = *dw_ext2_ref;
    let mut xsv_ext0 = *xsv_ext0_ref;
    let mut ysv_ext0 = *ysv_ext0_ref;
    let mut zsv_ext0 = *zsv_ext0_ref;
    let mut wsv_ext0 = *wsv_ext0_ref;
    let mut xsv_ext1 = *xsv_ext1_ref;
    let mut ysv_ext1 = *ysv_ext1_ref;
    let mut zsv_ext1 = *zsv_ext1_ref;
    let mut wsv_ext1 = *wsv_ext1_ref;
    let mut xsv_ext2 = *xsv_ext2_ref;
    let mut ysv_ext2 = *ysv_ext2_ref;
    let mut zsv_ext2 = *zsv_ext2_ref;
    let mut wsv_ext2 = *wsv_ext2_ref;
    let mut value = *value_ref;

    let mut a_score;
    let mut a_point;
    let mut a_is_bigger_side = 1;
    let mut b_score;
    let mut b_point;
    let mut b_is_bigger_side = 1;

    if (xins + yins) < (zins + wins) {
        a_score = xins + yins;
        a_point = 0x0C;
    } else {
        a_score = zins + wins;
        a_point = 0x03;
    }

    if (xins + zins) < (yins + wins) {
        b_score = xins + zins;
        b_point = 0x0A;
    } else {
        b_score = yins + wins;
        b_point = 0x05;
    }

    if (xins + wins) < (yins + zins) {
        let score = xins + wins;
        if (a_score <= b_score) && (score < b_score) {
            b_score = score;
            b_point = 0x06;
        } else if (a_score > b_score) && (score < a_score) {
            a_score = score;
            a_point = 0x06;
        }
    } else {
        let score = yins + zins;
        if (a_score <= b_score) && (score < b_score) {
            b_score = score;
            b_point = 0x09;
        } else if (a_score > b_score) && (score < a_score) {
            a_score = score;
            a_point = 0x09;
        }
    }

    let p1 = (3.0 - in_sum) + xins;
    if (a_score <= b_score) && (p1 < b_score) {
        b_score = p1;
        b_point = 0x0E;
        b_is_bigger_side = 0;
    } else if (a_score > b_score) && (p1 < a_score) {
        a_score = p1;
        a_point = 0x0E;
        a_is_bigger_side = 0;
    }

    let p2 = (3.0 - in_sum) + yins;
    if (a_score <= b_score) && (p2 < b_score) {
        b_score = p2;
        b_point = 0x0D;
        b_is_bigger_side = 0;
    } else if (a_score > b_score) && (p2 < a_score) {
        a_score = p2;
        a_point = 0x0D;
        a_is_bigger_side = 0;
    }

    let p3 = (3.0 - in_sum) + zins;
    if (a_score <= b_score) && (p3 < b_score) {
        b_score = p3;
        b_point = 0x0B;
        b_is_bigger_side = 0;
    } else if (a_score > b_score) && (p3 < a_score) {
        a_score = p3;
        a_point = 0x0B;
        a_is_bigger_side = 0;
    }

    let p4 = (3.0 - in_sum) + wins;
    if (a_score <= b_score) && (p4 < b_score) {
        b_score = p4;
        b_point = 0x07;
        b_is_bigger_side = 0;
    } else if (a_score > b_score) && (p4 < a_score) {
        a_score = p4;
        a_point = 0x07;
        a_is_bigger_side = 0;
    }

    if a_is_bigger_side == b_is_bigger_side {
        helper_helper_open_simplex_noise4_3_2(
            &mut dx_ext0, &mut dy_ext0, &mut dz_ext0, &mut dw_ext0,
            &mut dx_ext1, &mut dy_ext1, &mut dz_ext1, &mut dw_ext1,
            &mut dx_ext2, &mut dy_ext2, &mut dz_ext2, &mut dw_ext2,
            &mut xsv_ext0, &mut ysv_ext0, &mut zsv_ext0, &mut wsv_ext0,
            &mut xsv_ext1, &mut ysv_ext1, &mut zsv_ext1, &mut wsv_ext1,
            &mut xsv_ext2, &mut ysv_ext2, &mut zsv_ext2, &mut wsv_ext2,
            xsb, ysb, zsb, wsb,
            dx0, dy0, dz0, dw0,
            a_point as i8, a_is_bigger_side, b_point as i8,
        );
    } else {
        helper_helper_open_simplex_noise4_3_1(
            &mut dx_ext0, &mut dy_ext0, &mut dz_ext0, &mut dw_ext0,
            &mut dx_ext1, &mut dy_ext1, &mut dz_ext1, &mut dw_ext1,
            &mut dx_ext2, &mut dy_ext2, &mut dz_ext2, &mut dw_ext2,
            &mut xsv_ext0, &mut ysv_ext0, &mut zsv_ext0, &mut wsv_ext0,
            &mut xsv_ext1, &mut ysv_ext1, &mut zsv_ext1, &mut wsv_ext1,
            &mut xsv_ext2, &mut ysv_ext2, &mut zsv_ext2, &mut wsv_ext2,
            xsb, ysb, zsb, wsb,
            dx0, dy0, dz0, dw0,
            a_point as i8, a_is_bigger_side, b_point as i8,
        );
    }

    let dx4 = (dx0 - 1.0) - (3.0 * 0.309016994374947);
    let dy4 = (dy0 - 1.0) - (3.0 * 0.309016994374947);
    let dz4 = (dz0 - 1.0) - (3.0 * 0.309016994374947);
    let dw4 = dw0 - (3.0 * 0.309016994374947);
    let attn4 = (2.0 - (dx4 * dx4) - (dy4 * dy4) - (dz4 * dz4) - (dw4 * dw4));
    if attn4 > 0.0 {
        let attn4 = attn4 * attn4;
        value += (attn4 * attn4) * extrapolate4(ctx, xsb + 1, ysb + 1, zsb + 1, wsb + 0, dx4, dy4, dz4, dw4);
    }

    let dx3 = dx4;
    let dy3 = dy4;
    let dz3 = dz0 - (3.0 * 0.309016994374947);
    let dw3 = (dw0 - 1.0) - (3.0 * 0.309016994374947);
    let attn3 = (2.0 - (dx3 * dx3) - (dy3 * dy3) - (dz3 * dz3) - (dw3 * dw3));
    if attn3 > 0.0 {
        let attn3 = attn3 * attn3;
        value += (attn3 * attn3) * extrapolate4(ctx, xsb + 1, ysb + 1, zsb + 0, wsb + 1, dx3, dy3, dz3, dw3);
    }

    let dx2 = dx4;
    let dy2 = dy0 - (3.0 * 0.309016994374947);
    let dz2 = dz4;
    let dw2 = dw3;
    let attn2 = (2.0 - (dx2 * dx2) - (dy2 * dy2) - (dz2 * dz2) - (dw2 * dw2));
    if attn2 > 0.0 {
        let attn2 = attn2 * attn2;
        value += (attn2 * attn2) * extrapolate4(ctx, xsb + 1, ysb + 0, zsb + 1, wsb + 1, dx2, dy2, dz2, dw2);
    }

    let dx1 = dx0 - (3.0 * 0.309016994374947);
    let dz1 = dz4;
    let dy1 = dy4;
    let dw1 = dw3;
    let attn1 = (2.0 - (dx1 * dx1) - (dy1 * dy1) - (dz1 * dz1) - (dw1 * dw1));
    if attn1 > 0.0 {
        let attn1 = attn1 * attn1;
        value += (attn1 * attn1) * extrapolate4(ctx, xsb + 0, ysb + 1, zsb + 1, wsb + 1, dx1, dy1, dz1, dw1);
    }

    let dx5 = (dx0 - 1.0) - (2.0 * 0.309016994374947);
    let dy5 = (dy0 - 1.0) - (2.0 * 0.309016994374947);
    let dz5 = (dz0 - 0.0) - (2.0 * 0.309016994374947);
    let dw5 = (dw0 - 0.0) - (2.0 * 0.309016994374947);
    let attn5 = (2.0 - (dx5 * dx5) - (dy5 * dy5) - (dz5 * dz5) - (dw5 * dw5));
    if attn5 > 0.0 {
        let attn5 = attn5 * attn5;
        value += (attn5 * attn5) * extrapolate4(ctx, xsb + 1, ysb + 1, zsb + 0, wsb + 0, dx5, dy5, dz5, dw5);
    }

    let dx6 = (dx0 - 1.0) - (2.0 * 0.309016994374947);
    let dy6 = (dy0 - 0.0) - (2.0 * 0.309016994374947);
    let dz6 = (dz0 - 1.0) - (2.0 * 0.309016994374947);
    let dw6 = (dw0 - 0.0) - (2.0 * 0.309016994374947);
    let attn6 = (2.0 - (dx6 * dx6) - (dy6 * dy6) - (dz6 * dz6) - (dw6 * dw6));
    if attn6 > 0.0 {
        let attn6 = attn6 * attn6;
        value += (attn6 * attn6) * extrapolate4(ctx, xsb + 1, ysb + 0, zsb + 1, wsb + 0, dx6, dy6, dz6, dw6);
    }

    let dx7 = (dx0 - 1.0) - (2.0 * 0.309016994374947);
    let dy7 = (dy0 - 0.0) - (2.0 * 0.309016994374947);
    let dz7 = (dz0 - 0.0) - (2.0 * 0.309016994374947);
    let dw7 = (dw0 - 1.0) - (2.0 * 0.309016994374947);
    let attn7 = (2.0 - (dx7 * dx7) - (dy7 * dy7) - (dz7 * dz7) - (dw7 * dw7));
    if attn7 > 0.0 {
        let attn7 = attn7 * attn7;
        value += (attn7 * attn7) * extrapolate4(ctx, xsb + 1, ysb + 0, zsb + 0, wsb + 1, dx7, dy7, dz7, dw7);
    }

    let dx8 = (dx0 - 0.0) - (2.0 * 0.309016994374947);
    let dy8 = (dy0 - 1.0) - (2.0 * 0.309016994374947);
    let dz8 = (dz0 - 1.0) - (2.0 * 0.309016994374947);
    let dw8 = (dw0 - 0.0) - (2.0 * 0.309016994374947);
    let attn8 = (2.0 - (dx8 * dx8) - (dy8 * dy8) - (dz8 * dz8) - (dw8 * dw8));
    if attn8 > 0.0 {
        let attn8 = attn8 * attn8;
        value += (attn8 * attn8) * extrapolate4(ctx, xsb + 0, ysb + 1, zsb + 1, wsb + 0, dx8, dy8, dz8, dw8);
    }

    let dx9 = (dx0 - 0.0) - (2.0 * 0.309016994374947);
    let dy9 = (dy0 - 1.0) - (2.0 * 0.309016994374947);
    let dz9 = (dz0 - 0.0) - (2.0 * 0.309016994374947);
    let dw9 = (dw0 - 1.0) - (2.0 * 0.309016994374947);
    let attn9 = (2.0 - (dx9 * dx9) - (dy9 * dy9) - (dz9 * dz9) - (dw9 * dw9));
    if attn9 > 0.0 {
        let attn9 = attn9 * attn9;
        value += (attn9 * attn9) * extrapolate4(ctx, xsb + 0, ysb + 1, zsb + 0, wsb + 1, dx9, dy9, dz9, dw9);
    }

    let dx10 = (dx0 - 0.0) - (2.0 * 0.309016994374947);
    let dy10 = (dy0 - 0.0) - (2.0 * 0.309016994374947);
    let dz10 = (dz0 - 1.0) - (2.0 * 0.309016994374947);
    let dw10 = (dw0 - 1.0) - (2.0 * 0.309016994374947);
    let attn10 = (2.0 - (dx10 * dx10) - (dy10 * dy10) - (dz10 * dz10) - (dw10 * dw10));
    if attn10 > 0.0 {
        let attn10 = attn10 * attn10;
        value += (attn10 * attn10) * extrapolate4(ctx, xsb + 0, ysb + 0, zsb + 1, wsb + 1, dx10, dy10, dz10, dw10);
    }

    *dx_ext0_ref = dx_ext0;
    *dy_ext0_ref = dy_ext0;
    *dz_ext0_ref = dz_ext0;
    *dw_ext0_ref = dw_ext0;
    *dx_ext1_ref = dx_ext1;
    *dy_ext1_ref = dy_ext1;
    *dz_ext1_ref = dz_ext1;
    *dw_ext1_ref = dw_ext1;
    *dx_ext2_ref = dx_ext2;
    *dy_ext2_ref = dy_ext2;
    *dz_ext2_ref = dz_ext2;
    *dw_ext2_ref = dw_ext2;
    *xsv_ext0_ref = xsv_ext0;
    *ysv_ext0_ref = ysv_ext0;
    *zsv_ext0_ref = zsv_ext0;
    *wsv_ext0_ref = wsv_ext0;
    *xsv_ext1_ref = xsv_ext1;
    *ysv_ext1_ref = ysv_ext1;
    *zsv_ext1_ref = zsv_ext1;
    *wsv_ext1_ref = wsv_ext1;
    *xsv_ext2_ref = xsv_ext2;
    *ysv_ext2_ref = ysv_ext2;
    *zsv_ext2_ref = zsv_ext2;
    *wsv_ext2_ref = wsv_ext2;
    *value_ref = value;
}
pub fn helper_open_simplex_noise4_4(
    dx_ext0_ref: &mut f64,
    dy_ext0_ref: &mut f64,
    dz_ext0_ref: &mut f64,
    dw_ext0_ref: &mut f64,
    dx_ext1_ref: &mut f64,
    dy_ext1_ref: &mut f64,
    dz_ext1_ref: &mut f64,
    dw_ext1_ref: &mut f64,
    dx_ext2_ref: &mut f64,
    dy_ext2_ref: &mut f64,
    dz_ext2_ref: &mut f64,
    dw_ext2_ref: &mut f64,
    xsv_ext0_ref: &mut i32,
    ysv_ext0_ref: &mut i32,
    zsv_ext0_ref: &mut i32,
    wsv_ext0_ref: &mut i32,
    xsv_ext1_ref: &mut i32,
    ysv_ext1_ref: &mut i32,
    zsv_ext1_ref: &mut i32,
    wsv_ext1_ref: &mut i32,
    xsv_ext2_ref: &mut i32,
    ysv_ext2_ref: &mut i32,
    zsv_ext2_ref: &mut i32,
    wsv_ext2_ref: &mut i32,
    value_ref: &mut f64,
    ctx: &OsnContext,
    xsb: i32,
    ysb: i32,
    zsb: i32,
    wsb: i32,
    xins: f64,
    yins: f64,
    zins: f64,
    wins: f64,
    in_sum: f64,
    dx0: f64,
    dy0: f64,
    dz0: f64,
    dw0: f64,
) {
    let mut dx_ext0 = *dx_ext0_ref;
    let mut dy_ext0 = *dy_ext0_ref;
    let mut dz_ext0 = *dz_ext0_ref;
    let mut dw_ext0 = *dw_ext0_ref;
    let mut dx_ext1 = *dx_ext1_ref;
    let mut dy_ext1 = *dy_ext1_ref;
    let mut dz_ext1 = *dz_ext1_ref;
    let mut dw_ext1 = *dw_ext1_ref;
    let mut dx_ext2 = *dx_ext2_ref;
    let mut dy_ext2 = *dy_ext2_ref;
    let mut dz_ext2 = *dz_ext2_ref;
    let mut dw_ext2 = *dw_ext2_ref;
    let mut xsv_ext0 = *xsv_ext0_ref;
    let mut ysv_ext0 = *ysv_ext0_ref;
    let mut zsv_ext0 = *zsv_ext0_ref;
    let mut wsv_ext0 = *wsv_ext0_ref;
    let mut xsv_ext1 = *xsv_ext1_ref;
    let mut ysv_ext1 = *ysv_ext1_ref;
    let mut zsv_ext1 = *zsv_ext1_ref;
    let mut wsv_ext1 = *wsv_ext1_ref;
    let mut xsv_ext2 = *xsv_ext2_ref;
    let mut ysv_ext2 = *ysv_ext2_ref;
    let mut zsv_ext2 = *zsv_ext2_ref;
    let mut wsv_ext2 = *wsv_ext2_ref;
    let mut value = *value_ref;
    
    let mut a_score;
    let mut a_point;
    let mut a_is_bigger_side = 1;
    let mut b_score;
    let mut b_point;
    let mut b_is_bigger_side = 1;

    if (xins + yins) > (zins + wins) {
        a_score = xins + yins;
        a_point = 0x03;
    } else {
        a_score = zins + wins;
        a_point = 0x0C;
    }

    if (xins + zins) > (yins + wins) {
        b_score = xins + zins;
        b_point = 0x05;
    } else {
        b_score = yins + wins;
        b_point = 0x0A;
    }

    if (xins + wins) > (yins + zins) {
        let score = xins + wins;
        if (a_score >= b_score) && (score > b_score) {
            b_score = score;
            b_point = 0x09;
        } else if (a_score < b_score) && (score > a_score) {
            a_score = score;
            a_point = 0x09;
        }
    } else {
        let score = yins + zins;
        if (a_score >= b_score) && (score > b_score) {
            b_score = score;
            b_point = 0x06;
        } else if (a_score < b_score) && (score > a_score) {
            a_score = score;
            a_point = 0x06;
        }
    }

    let p1 = (2.0 - in_sum) + xins;
    if (a_score >= b_score) && (p1 > b_score) {
        b_score = p1;
        b_point = 0x01;
        b_is_bigger_side = 0;
    } else if (a_score < b_score) && (p1 > a_score) {
        a_score = p1;
        a_point = 0x01;
        a_is_bigger_side = 0;
    }

    let p2 = (2.0 - in_sum) + yins;
    if (a_score >= b_score) && (p2 > b_score) {
        b_score = p2;
        b_point = 0x02;
        b_is_bigger_side = 0;
    } else if (a_score < b_score) && (p2 > a_score) {
        a_score = p2;
        a_point = 0x02;
        a_is_bigger_side = 0;
    }

    let p3 = (2.0 - in_sum) + zins;
    if (a_score >= b_score) && (p3 > b_score) {
        b_score = p3;
        b_point = 0x04;
        b_is_bigger_side = 0;
    } else if (a_score < b_score) && (p3 > a_score) {
        a_score = p3;
        a_point = 0x04;
        a_is_bigger_side = 0;
    }

    let p4 = (2.0 - in_sum) + wins;
    if (a_score >= b_score) && (p4 > b_score) {
        b_score = p4;
        b_point = 0x08;
        b_is_bigger_side = 0;
    } else if (a_score < b_score) && (p4 > a_score) {
        a_score = p4;
        a_point = 0x08;
        a_is_bigger_side = 0;
    }

    if a_is_bigger_side == b_is_bigger_side {
        helper_helper_open_simplex_noise4_4_2(
            &mut dx_ext0, &mut dy_ext0, &mut dz_ext0, &mut dw_ext0,
            &mut dx_ext1, &mut dy_ext1, &mut dz_ext1, &mut dw_ext1,
            &mut dx_ext2, &mut dy_ext2, &mut dz_ext2, &mut dw_ext2,
            &mut xsv_ext0, &mut ysv_ext0, &mut zsv_ext0, &mut wsv_ext0,
            &mut xsv_ext1, &mut ysv_ext1, &mut zsv_ext1, &mut wsv_ext1,
            &mut xsv_ext2, &mut ysv_ext2, &mut zsv_ext2, &mut wsv_ext2,
            xsb, ysb, zsb, wsb, dx0, dy0, dz0, dw0, a_point, a_is_bigger_side, b_point,
        );
    } else {
        helper_helper_open_simplex_noise4_4_1(
            &mut dx_ext0, &mut dy_ext0, &mut dz_ext0, &mut dw_ext0,
            &mut dx_ext1, &mut dy_ext1, &mut dz_ext1, &mut dw_ext1,
            &mut dx_ext2, &mut dy_ext2, &mut dz_ext2, &mut dw_ext2,
            &mut xsv_ext0, &mut ysv_ext0, &mut zsv_ext0, &mut wsv_ext0,
            &mut xsv_ext1, &mut ysv_ext1, &mut zsv_ext1, &mut wsv_ext1,
            &mut xsv_ext2, &mut ysv_ext2, &mut zsv_ext2, &mut wsv_ext2,
            xsb, ysb, zsb, wsb, dx0, dy0, dz0, dw0, a_point, a_is_bigger_side, b_point,
        );
    }

    let dx1 = (dx0 - 1.0) - 0.309016994374947;
    let dy1 = (dy0 - 0.0) - 0.309016994374947;
    let dz1 = (dz0 - 0.0) - 0.309016994374947;
    let dw1 = (dw0 - 0.0) - 0.309016994374947;
    let mut attn1 = ((2.0 - (dx1 * dx1)) - (dy1 * dy1)) - (dz1 * dz1) - (dw1 * dw1);
    if attn1 > 0.0 {
        attn1 *= attn1;
        value += (attn1 * attn1) * extrapolate4(ctx, xsb + 1, ysb + 0, zsb + 0, wsb + 0, dx1, dy1, dz1, dw1);
    }

    let dx2 = (dx0 - 0.0) - 0.309016994374947;
    let dy2 = (dy0 - 1.0) - 0.309016994374947;
    let dz2 = dz1;
    let dw2 = dw1;
    let mut attn2 = ((2.0 - (dx2 * dx2)) - (dy2 * dy2)) - (dz2 * dz2) - (dw2 * dw2);
    if attn2 > 0.0 {
        attn2 *= attn2;
        value += (attn2 * attn2) * extrapolate4(ctx, xsb + 0, ysb + 1, zsb + 0, wsb + 0, dx2, dy2, dz2, dw2);
    }

    let dx3 = dx2;
    let dy3 = dy1;
    let dz3 = (dz0 - 1.0) - 0.309016994374947;
    let dw3 = dw1;
    let mut attn3 = ((2.0 - (dx3 * dx3)) - (dy3 * dy3)) - (dz3 * dz3) - (dw3 * dw3);
    if attn3 > 0.0 {
        attn3 *= attn3;
        value += (attn3 * attn3) * extrapolate4(ctx, xsb + 0, ysb + 0, zsb + 1, wsb + 0, dx3, dy3, dz3, dw3);
    }

    let dx4 = dx2;
    let dy4 = dy1;
    let dz4 = dz1;
    let dw4 = (dw0 - 1.0) - 0.309016994374947;
    let mut attn4 = ((2.0 - (dx4 * dx4)) - (dy4 * dy4)) - (dz4 * dz4) - (dw4 * dw4);
    if attn4 > 0.0 {
        attn4 *= attn4;
        value += (attn4 * attn4) * extrapolate4(ctx, xsb + 0, ysb + 0, zsb + 0, wsb + 1, dx4, dy4, dz4, dw4);
    }

    let dx5 = (dx0 - 1.0) - (2.0 * 0.309016994374947);
    let dy5 = (dy0 - 1.0) - (2.0 * 0.309016994374947);
    let dz5 = (dz0 - 0.0) - (2.0 * 0.309016994374947);
    let dw5 = (dw0 - 0.0) - (2.0 * 0.309016994374947);
    let mut attn5 = ((2.0 - (dx5 * dx5)) - (dy5 * dy5)) - (dz5 * dz5) - (dw5 * dw5);
    if attn5 > 0.0 {
        attn5 *= attn5;
        value += (attn5 * attn5) * extrapolate4(ctx, xsb + 1, ysb + 1, zsb + 0, wsb + 0, dx5, dy5, dz5, dw5);
    }

    let dx6 = (dx0 - 1.0) - (2.0 * 0.309016994374947);
    let dy6 = (dy0 - 0.0) - (2.0 * 0.309016994374947);
    let dz6 = (dz0 - 1.0) - (2.0 * 0.309016994374947);
    let dw6 = (dw0 - 0.0) - (2.0 * 0.309016994374947);
    let mut attn6 = ((2.0 - (dx6 * dx6)) - (dy6 * dy6)) - (dz6 * dz6) - (dw6 * dw6);
    if attn6 > 0.0 {
        attn6 *= attn6;
        value += (attn6 * attn6) * extrapolate4(ctx, xsb + 1, ysb + 0, zsb + 1, wsb + 0, dx6, dy6, dz6, dw6);
    }

    let dx7 = (dx0 - 1.0) - (2.0 * 0.309016994374947);
    let dy7 = (dy0 - 0.0) - (2.0 * 0.309016994374947);
    let dz7 = (dz0 - 0.0) - (2.0 * 0.309016994374947);
    let dw7 = (dw0 - 1.0) - (2.0 * 0.309016994374947);
    let mut attn7 = ((2.0 - (dx7 * dx7)) - (dy7 * dy7)) - (dz7 * dz7) - (dw7 * dw7);
    if attn7 > 0.0 {
        attn7 *= attn7;
        value += (attn7 * attn7) * extrapolate4(ctx, xsb + 1, ysb + 0, zsb + 0, wsb + 1, dx7, dy7, dz7, dw7);
    }

    let dx8 = (dx0 - 0.0) - (2.0 * 0.309016994374947);
    let dy8 = (dy0 - 1.0) - (2.0 * 0.309016994374947);
    let dz8 = (dz0 - 1.0) - (2.0 * 0.309016994374947);
    let dw8 = (dw0 - 0.0) - (2.0 * 0.309016994374947);
    let mut attn8 = ((2.0 - (dx8 * dx8)) - (dy8 * dy8)) - (dz8 * dz8) - (dw8 * dw8);
    if attn8 > 0.0 {
        attn8 *= attn8;
        value += (attn8 * attn8) * extrapolate4(ctx, xsb + 0, ysb + 1, zsb + 1, wsb + 0, dx8, dy8, dz8, dw8);
    }

    let dx9 = (dx0 - 0.0) - (2.0 * 0.309016994374947);
    let dy9 = (dy0 - 1.0) - (2.0 * 0.309016994374947);
    let dz9 = (dz0 - 0.0) - (2.0 * 0.309016994374947);
    let dw9 = (dw0 - 1.0) - (2.0 * 0.309016994374947);
    let mut attn9 = ((2.0 - (dx9 * dx9)) - (dy9 * dy9)) - (dz9 * dz9) - (dw9 * dw9);
    if attn9 > 0.0 {
        attn9 *= attn9;
        value += (attn9 * attn9) * extrapolate4(ctx, xsb + 0, ysb + 1, zsb + 0, wsb + 1, dx9, dy9, dz9, dw9);
    }

    let dx10 = (dx0 - 0.0) - (2.0 * 0.309016994374947);
    let dy10 = (dy0 - 0.0) - (2.0 * 0.309016994374947);
    let dz10 = (dz0 - 1.0) - (2.0 * 0.309016994374947);
    let dw10 = (dw0 - 1.0) - (2.0 * 0.309016994374947);
    let mut attn10 = ((2.0 - (dx10 * dx10)) - (dy10 * dy10)) - (dz10 * dz10) - (dw10 * dw10);
    if attn10 > 0.0 {
        attn10 *= attn10;
        value += (attn10 * attn10) * extrapolate4(ctx, xsb + 0, ysb + 0, zsb + 1, wsb + 1, dx10, dy10, dz10, dw10);
    }

    *dx_ext0_ref = dx_ext0;
    *dy_ext0_ref = dy_ext0;
    *dz_ext0_ref = dz_ext0;
    *dw_ext0_ref = dw_ext0;
    *dx_ext1_ref = dx_ext1;
    *dy_ext1_ref = dy_ext1;
    *dz_ext1_ref = dz_ext1;
    *dw_ext1_ref = dw_ext1;
    *dx_ext2_ref = dx_ext2;
    *dy_ext2_ref = dy_ext2;
    *dz_ext2_ref = dz_ext2;
    *dw_ext2_ref = dw_ext2;
    *xsv_ext0_ref = xsv_ext0;
    *ysv_ext0_ref = ysv_ext0;
    *zsv_ext0_ref = zsv_ext0;
    *wsv_ext0_ref = wsv_ext0;
    *xsv_ext1_ref = xsv_ext1;
    *ysv_ext1_ref = ysv_ext1;
    *zsv_ext1_ref = zsv_ext1;
    *wsv_ext1_ref = wsv_ext1;
    *xsv_ext2_ref = xsv_ext2;
    *ysv_ext2_ref = ysv_ext2;
    *zsv_ext2_ref = zsv_ext2;
    *wsv_ext2_ref = wsv_ext2;
    *value_ref = value;
}
pub fn open_simplex_noise3(ctx: &OsnContext, x: f64, y: f64, z: f64) -> f64 {
    let stretch_offset = ((x + y) + z) * ((-1.0) / 6.0);
    let xs = x + stretch_offset;
    let ys = y + stretch_offset;
    let zs = z + stretch_offset;
    let xsb = fastFloor(xs);
    let ysb = fastFloor(ys);
    let zsb = fastFloor(zs);
    let squish_offset = ((xsb as f64 + ysb as f64) + zsb as f64) * (1.0 / 3.0);
    let xb = xsb as f64 + squish_offset;
    let yb = ysb as f64 + squish_offset;
    let zb = zsb as f64 + squish_offset;
    let xins = xs - xsb as f64;
    let yins = ys - ysb as f64;
    let zins = zs - zsb as f64;
    let in_sum = (xins + yins) + zins;
    let mut dx0 = x - xb;
    let mut dy0 = y - yb;
    let mut dz0 = z - zb;

    let mut dx_ext0 = 0.0;
    let mut dy_ext0 = 0.0;
    let mut dz_ext0 = 0.0;
    let mut dx_ext1 = 0.0;
    let mut dy_ext1 = 0.0;
    let mut dz_ext1 = 0.0;
    let mut xsv_ext0 = 0;
    let mut ysv_ext0 = 0;
    let mut zsv_ext0 = 0;
    let mut xsv_ext1 = 0;
    let mut ysv_ext1 = 0;
    let mut zsv_ext1 = 0;
    let mut value = 0.0;

    if in_sum <= 1.0 {
        helper_open_simplex_noise3_1(
            &mut dx_ext0,
            &mut dy_ext0,
            &mut dz_ext0,
            &mut dx_ext1,
            &mut dy_ext1,
            &mut dz_ext1,
            &mut xsv_ext0,
            &mut ysv_ext0,
            &mut zsv_ext0,
            &mut xsv_ext1,
            &mut ysv_ext1,
            &mut zsv_ext1,
            &mut value,
            ctx,
            xsb,
            ysb,
            zsb,
            xins,
            yins,
            zins,
            in_sum,
            dx0,
            dy0,
            dz0,
        );
    } else if in_sum >= 2.0 {
        helper_open_simplex_noise3_2(
            &mut dx0,
            &mut dy0,
            &mut dz0,
            &mut dx_ext0,
            &mut dy_ext0,
            &mut dz_ext0,
            &mut dx_ext1,
            &mut dy_ext1,
            &mut dz_ext1,
            &mut xsv_ext0,
            &mut ysv_ext0,
            &mut zsv_ext0,
            &mut xsv_ext1,
            &mut ysv_ext1,
            &mut zsv_ext1,
            &mut value,
            ctx,
            xsb,
            ysb,
            zsb,
            xins,
            yins,
            zins,
            in_sum,
        );
    } else {
        helper_open_simplex_noise3_3(
            &mut dx_ext0,
            &mut dy_ext0,
            &mut dz_ext0,
            &mut dx_ext1,
            &mut dy_ext1,
            &mut dz_ext1,
            &mut xsv_ext0,
            &mut ysv_ext0,
            &mut zsv_ext0,
            &mut xsv_ext1,
            &mut ysv_ext1,
            &mut zsv_ext1,
            &mut value,
            ctx,
            xsb,
            ysb,
            zsb,
            xins,
            yins,
            zins,
            dx0,
            dy0,
            dz0,
        );
    }

    let attn_ext0 = ((2.0 - (dx_ext0 * dx_ext0)) - (dy_ext0 * dy_ext0)) - (dz_ext0 * dz_ext0);
    if attn_ext0 > 0.0 {
        let attn_ext0 = attn_ext0 * attn_ext0;
        value += (attn_ext0 * attn_ext0) * extrapolate3(ctx, xsv_ext0, ysv_ext0, zsv_ext0, dx_ext0, dy_ext0, dz_ext0);
    }

    let attn_ext1 = ((2.0 - (dx_ext1 * dx_ext1)) - (dy_ext1 * dy_ext1)) - (dz_ext1 * dz_ext1);
    if attn_ext1 > 0.0 {
        let attn_ext1 = attn_ext1 * attn_ext1;
        value += (attn_ext1 * attn_ext1) * extrapolate3(ctx, xsv_ext1, ysv_ext1, zsv_ext1, dx_ext1, dy_ext1, dz_ext1);
    }

    value / 103.0
}
pub fn open_simplex_noise4(ctx: &OsnContext, x: f64, y: f64, z: f64, w: f64) -> f64 {
    let stretch_offset = (((x + y) + z) + w) * (-0.138196601125011);
    let xs = x + stretch_offset;
    let ys = y + stretch_offset;
    let zs = z + stretch_offset;
    let ws = w + stretch_offset;
    let xsb = fastFloor(xs);
    let ysb = fastFloor(ys);
    let zsb = fastFloor(zs);
    let wsb = fastFloor(ws);
    let squish_offset = (((xsb as f64 + ysb as f64) + zsb as f64) + wsb as f64) * 0.309016994374947;
    let xb = xsb as f64 + squish_offset;
    let yb = ysb as f64 + squish_offset;
    let zb = zsb as f64 + squish_offset;
    let wb = wsb as f64 + squish_offset;
    let xins = xs - xsb as f64;
    let yins = ys - ysb as f64;
    let zins = zs - zsb as f64;
    let wins = ws - wsb as f64;
    let in_sum = ((xins + yins) + zins) + wins;
    let mut dx0 = x - xb;
    let mut dy0 = y - yb;
    let mut dz0 = z - zb;
    let mut dw0 = w - wb;

    let mut dx_ext0 = 0.0;
    let mut dy_ext0 = 0.0;
    let mut dz_ext0 = 0.0;
    let mut dw_ext0 = 0.0;
    let mut dx_ext1 = 0.0;
    let mut dy_ext1 = 0.0;
    let mut dz_ext1 = 0.0;
    let mut dw_ext1 = 0.0;
    let mut dx_ext2 = 0.0;
    let mut dy_ext2 = 0.0;
    let mut dz_ext2 = 0.0;
    let mut dw_ext2 = 0.0;
    let mut xsv_ext0 = 0;
    let mut ysv_ext0 = 0;
    let mut zsv_ext0 = 0;
    let mut wsv_ext0 = 0;
    let mut xsv_ext1 = 0;
    let mut ysv_ext1 = 0;
    let mut zsv_ext1 = 0;
    let mut wsv_ext1 = 0;
    let mut xsv_ext2 = 0;
    let mut ysv_ext2 = 0;
    let mut zsv_ext2 = 0;
    let mut wsv_ext2 = 0;
    let mut value = 0.0;

    if in_sum <= 1.0 {
        helper_open_simplex_noise4_1(
            &mut dx_ext0,
            &mut dy_ext0,
            &mut dz_ext0,
            &mut dw_ext0,
            &mut dx_ext1,
            &mut dy_ext1,
            &mut dz_ext1,
            &mut dw_ext1,
            &mut dx_ext2,
            &mut dy_ext2,
            &mut dz_ext2,
            &mut dw_ext2,
            &mut xsv_ext0,
            &mut ysv_ext0,
            &mut zsv_ext0,
            &mut wsv_ext0,
            &mut xsv_ext1,
            &mut ysv_ext1,
            &mut zsv_ext1,
            &mut ysv_ext2,
            &mut zsv_ext2,
            &mut wsv_ext2,
            &mut value,
            ctx,
            xsb,
            ysb,
            zsb,
            wsb,
            xins,
            yins,
            zins,
            wins,
            in_sum,
            dx0,
            dy0,
            dz0,
            dw0,
            wsv_ext1,
            xsv_ext2,
        );
    } else if in_sum >= 3.0 {
        helper_open_simplex_noise4_2(
            &mut dx0,
            &mut dy0,
            &mut dz0,
            &mut dw0,
            &mut dx_ext0,
            &mut dy_ext0,
            &mut dz_ext0,
            &mut dw_ext0,
            &mut dx_ext1,
            &mut dy_ext1,
            &mut dz_ext1,
            &mut dw_ext1,
            &mut dx_ext2,
            &mut dy_ext2,
            &mut dz_ext2,
            &mut dw_ext2,
            &mut xsv_ext0,
            &mut ysv_ext0,
            &mut zsv_ext0,
            &mut wsv_ext0,
            &mut xsv_ext1,
            &mut ysv_ext1,
            &mut zsv_ext1,
            &mut ysv_ext2,
            &mut zsv_ext2,
            &mut wsv_ext2,
            &mut value,
            ctx,
            xsb,
            ysb,
            zsb,
            wsb,
            xins,
            yins,
            zins,
            wins,
            in_sum,
            wsv_ext1,
            xsv_ext2,
        );
    } else if in_sum <= 2.0 {
        helper_open_simplex_noise4_4(
            &mut dx_ext0,
            &mut dy_ext0,
            &mut dz_ext0,
            &mut dw_ext0,
            &mut dx_ext1,
            &mut dy_ext1,
            &mut dz_ext1,
            &mut dw_ext1,
            &mut dx_ext2,
            &mut dy_ext2,
            &mut dz_ext2,
            &mut dw_ext2,
            &mut xsv_ext0,
            &mut ysv_ext0,
            &mut zsv_ext0,
            &mut wsv_ext0,
            &mut xsv_ext1,
            &mut ysv_ext1,
            &mut zsv_ext1,
            &mut wsv_ext1,
            &mut xsv_ext2,
            &mut ysv_ext2,
            &mut zsv_ext2,
            &mut wsv_ext2,
            &mut value,
            ctx,
            xsb,
            ysb,
            zsb,
            wsb,
            xins,
            yins,
            zins,
            wins,
            in_sum,
            dx0,
            dy0,
            dz0,
            dw0,
        );
    } else {
        helper_open_simplex_noise4_3(
            &mut dx_ext0,
            &mut dy_ext0,
            &mut dz_ext0,
            &mut dw_ext0,
            &mut dx_ext1,
            &mut dy_ext1,
            &mut dz_ext1,
            &mut dw_ext1,
            &mut dx_ext2,
            &mut dy_ext2,
            &mut dz_ext2,
            &mut dw_ext2,
            &mut xsv_ext0,
            &mut ysv_ext0,
            &mut zsv_ext0,
            &mut wsv_ext0,
            &mut xsv_ext1,
            &mut ysv_ext1,
            &mut zsv_ext1,
            &mut wsv_ext1,
            &mut xsv_ext2,
            &mut ysv_ext2,
            &mut zsv_ext2,
            &mut wsv_ext2,
            &mut value,
            ctx,
            xsb,
            ysb,
            zsb,
            wsb,
            xins,
            yins,
            zins,
            wins,
            in_sum,
            dx0,
            dy0,
            dz0,
            dw0,
        );
    }

    let attn_ext0 = (((2.0 - (dx_ext0 * dx_ext0)) - (dy_ext0 * dy_ext0)) - (dz_ext0 * dz_ext0)) - (dw_ext0 * dw_ext0);
    if attn_ext0 > 0.0 {
        let attn_ext0 = attn_ext0 * attn_ext0;
        value += (attn_ext0 * attn_ext0) * extrapolate4(ctx, xsv_ext0, ysv_ext0, zsv_ext0, wsv_ext0, dx_ext0, dy_ext0, dz_ext0, dw_ext0);
    }

    let attn_ext1 = (((2.0 - (dx_ext1 * dx_ext1)) - (dy_ext1 * dy_ext1)) - (dz_ext1 * dz_ext1)) - (dw_ext1 * dw_ext1);
    if attn_ext1 > 0.0 {
        let attn_ext1 = attn_ext1 * attn_ext1;
        value += (attn_ext1 * attn_ext1) * extrapolate4(ctx, xsv_ext1, ysv_ext1, zsv_ext1, wsv_ext1, dx_ext1, dy_ext1, dz_ext1, dw_ext1);
    }

    let attn_ext2 = (((2.0 - (dx_ext2 * dx_ext2)) - (dy_ext2 * dy_ext2)) - (dz_ext2 * dz_ext2)) - (dw_ext2 * dw_ext2);
    if attn_ext2 > 0.0 {
        let attn_ext2 = attn_ext2 * attn_ext2;
        value += (attn_ext2 * attn_ext2) * extrapolate4(ctx, xsv_ext2, ysv_ext2, zsv_ext2, wsv_ext2, dx_ext2, dy_ext2, dz_ext2, dw_ext2);
    }

    value / 30.0
}
