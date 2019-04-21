use std::f64;
use libc::{c_int, c_double};

extern crate libc;

#[repr(C)]
pub struct c_foo_struct {
    pub a:c_double,
    pub b:c_double,
    pub i:c_int,
}

#[no_mangle]
pub fn cosine(x: f64) -> f64 {
    x.cos()
}

#[no_mangle]
pub fn change_struct(mut stuff: *mut c_foo_struct) {
    assert!(!stuff.is_null());

    unsafe {
        (*stuff).a = 1.0;
        (*stuff).b = 2.0;
        (*stuff).i = 3;
    }
}

#[cfg(test)]
mod tests {
    use assert_approx_eq::assert_approx_eq;
    use super::*;

    #[test]
    fn cos_of_0() {
        assert_approx_eq!(cosine(0.0), 1.0, 1e-8);
    }

    #[test]
    fn cos_of_pi() {
        assert_approx_eq!(cosine(f64::consts::PI), -1.0, 1e-8);
    }


    #[test]
    fn cos_of_pi_over_2() {
        assert_approx_eq!(cosine(f64::consts::PI / 2.0), 0.0, 1e-8);
    }
}

