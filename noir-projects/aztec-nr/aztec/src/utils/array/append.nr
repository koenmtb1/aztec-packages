/// Appends two `BoundedVec`s together, returning one that contains all of the elements of the first one followed by all
/// of the elements of the second one. The resulting `BoundedVec` can have any arbitrary maximum length, but it must be
/// large enough to fit all of the elements of both the first and second vectors.
pub fn append<T, let A_LEN: u32, let B_LEN: u32, let DST_LEN: u32>(
    a: BoundedVec<T, A_LEN>,
    b: BoundedVec<T, B_LEN>,
) -> BoundedVec<T, DST_LEN> {
    let mut dst = BoundedVec::new();

    dst.extend_from_bounded_vec(a);
    dst.extend_from_bounded_vec(b);

    dst
}

mod test {
    use super::append;

    #[test]
    unconstrained fn append_empty_vecs() {
        let a: BoundedVec<_, 3> = BoundedVec::new();
        let b: BoundedVec<_, 14> = BoundedVec::new();

        let result: BoundedVec<Field, 5> = append(a, b);

        assert_eq(result.len(), 0);
        assert_eq(result.storage(), std::mem::zeroed());
    }

    #[test]
    unconstrained fn append_non_empty_vecs() {
        let a: BoundedVec<_, 3> = BoundedVec::from_array([1, 2, 3]);
        let b: BoundedVec<_, 14> = BoundedVec::from_array([4, 5, 6]);

        let result: BoundedVec<Field, 8> = append(a, b);

        assert_eq(result.len(), 6);
        assert_eq(result.storage(), [1, 2, 3, 4, 5, 6, std::mem::zeroed(), std::mem::zeroed()]);
    }

    #[test(should_fail_with = "out of bounds")]
    unconstrained fn append_non_empty_vecs_insufficient_max_len() {
        let a: BoundedVec<_, 3> = BoundedVec::from_array([1, 2, 3]);
        let b: BoundedVec<_, 14> = BoundedVec::from_array([4, 5, 6]);

        let _: BoundedVec<Field, 5> = append(a, b);
    }
}
