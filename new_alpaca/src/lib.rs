use std::f64;
use libc::{c_int, c_float, c_double};
use std::mem;
use std::slice;

extern crate libc;

#[repr(C)]
pub struct c_foo_struct {
    pub a: c_double,
    pub b: c_double,
    pub i: c_int,
    pub array: [c_float; 2],
    pub ptr: *mut c_float,
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
        (*stuff).array[0] = 4.0;
        (*stuff).array[1] = 5.0;
    }
}

#[no_mangle]
pub fn use_malloc(mut stuff: *mut c_foo_struct) {
    assert!(!stuff.is_null());

    unsafe {
        let new_array: *mut c_float = libc::malloc(mem::size_of::<c_float>() as libc::size_t * 2) as *mut c_float;
        (*stuff).ptr = new_array;

        if new_array.is_null() {
            panic!("failed to allocate memory");
        }

        let c_array = slice::from_raw_parts_mut(new_array, 2);

        c_array[0] = 7.0;
        c_array[1] = 8.0;
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

