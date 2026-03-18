use crate::*;
use rand::Rng;

pub fn ti_obv_start(options: Option<&f64>) -> i32 {
    let _ = options; // Explicitly ignore the parameter to avoid unused variable warning
    0
}

pub struct Person {
    name: String,
    age: u32,
}

pub fn process_person(name: Option<&str>) -> Option<String> {
    if name.is_none() {
        return None;
    }

    let name = name.unwrap();
    let mut rng = rand::thread_rng();
    let age = rng.gen_range(20..=60);

    let p = Person {
        name: name.to_string(),
        age,
    };

    Some(format!("Person: {}, Age: {}", p.name, p.age))
}
