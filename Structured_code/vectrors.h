#ifndef STRUCTURED_CODE_VECTRORS_H
#define STRUCTURED_CODE_VECTRORS_H

/*
 * Returns value_t that is result of scalar producing of vectors
 */
template<typename value_t>
value_t operator*(const std::vector<value_t>& first, const std::vector<value_t>& second) {
    return std::inner_product(first.begin(), first.end(), second.begin(), 0,
                              std::plus<value_t>(), std::multiplies<value_t>());
}
/*
 * Returns sequence of instance between start ans stop with step between each neighboring elements
 */
template<typename value_type>
std::vector<value_type> sequence(value_type start, value_type stop, value_type step)
{
    std::vector<value_type> result;
    result.reserve(static_cast<int>((stop - start)/step));
    for (int i = 0, stop_int = static_cast<int>((stop - start)/step); i < stop_int; ++i) {
        result.emplace_back(static_cast<value_type>(start + i * step));
    }
    return std::move(result);
}
/*
 * Output operator
 * value_t is required to have the similar output operator
 */
template<typename value_t>
std::ostream &operator << (std::ostream &os, const std::vector<value_t>& v)
{
    std::cout << "[";
    for(auto i: v) {os << i <<", ";};
    std::cout << "]";
    return os;
}

#endif //STRUCTURED_CODE_VECTRORS_H
