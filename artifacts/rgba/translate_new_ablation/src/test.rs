use crate::*;

pub fn test_named() {
    let mut ok: i16 = 0;
    let val = rgba_from_string(Some("olive"), &mut ok);
    assert!(ok != 0);
    assert_eq!(0x808000FF, val.unwrap());
}
pub fn test_rgb() {
    let mut ok: i16 = 0;
    let mut val = rgba_from_string(Some("rgb(255, 30   , 0)"), &mut ok);
    assert!(ok != 0);
    assert!(Some(0xff1e00ff) == val);
    val = rgba_from_string(Some("rgb(0,0,0)"), &mut ok);
    assert!(ok != 0);
    assert!(Some(0x000000ff) == val);
}
pub fn test_rgba() {
    let mut ok: i16 = 0;
    let val = rgba_from_string(Some("rgba(255, 30   , 0, .5)"), &mut ok);
    assert!(ok != 0);
    assert_eq!(Some(0xff1e007f), val);
    
    let val = rgba_from_string(Some("rgba(0,0,0, 1)"), &mut ok);
    assert!(ok != 0);
    assert_eq!(Some(0x000000ff), val);
}
pub fn test_hex() {
    let mut ok: i16 = 0;
    let mut val = rgba_from_string(Some("#ff1e00"), &mut ok);
    assert!(ok != 0);
    assert_eq!(Some(0xff1e00ff), val);
    
    val = rgba_from_string(Some("#ffffff"), &mut ok);
    assert!(ok != 0);
    assert_eq!(Some(0xffffffff), val);
    
    val = rgba_from_string(Some("#ffcc00"), &mut ok);
    assert!(ok != 0);
    assert_eq!(Some(0xffcc00ff), val);
    
    val = rgba_from_string(Some("#fco"), &mut ok);
    assert!(ok != 0);
    assert_eq!(Some(0xffcc00ff), val);
}
pub fn test_to_string() {
    let mut buf = [0u8; 256];
    let mut color = rgba_new(0xffcc00ff);
    rgba_to_string(color, &mut buf).unwrap();
    assert_eq!("#ffcc00", std::str::from_utf8(&buf).unwrap().trim_end_matches('\0'));
    
    color = rgba_new(0xffcc0050);
    rgba_to_string(color, &mut buf).unwrap();
    assert_eq!("rgba(255, 204, 0, 0.31)", std::str::from_utf8(&buf).unwrap().trim_end_matches('\0'));
}
