use std::f64;

#[no_mangle]
pub fn cosine(x: f64) -> f64 {
    x.cos()
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
