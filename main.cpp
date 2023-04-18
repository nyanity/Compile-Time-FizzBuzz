#include<iostream>
#include<array>

namespace detail
{
    template<std::size_t N>
    constexpr char get_char() { return '0' + N; }

    template<std::size_t... Ns>
    struct to_chars { static constexpr std::array<char, sizeof...(Ns) + 1> value{ get_char<Ns>()..., 0 }; };

    template<std::size_t N, std::size_t... Ns>
    struct explode : explode<N / 10, N % 10, Ns...> {};

    template<std::size_t... digits>
    struct explode<0, digits...> : to_chars<digits...> {};

    template<std::size_t N>
    constexpr auto num_to_string{ explode<N>::value };
    
    constexpr std::array<char, 9> fizzbuzz_array{ "fizzbuzz" };
    constexpr std::array<char, 5> fizz_array{ "fizz" };
    constexpr std::array<char, 5> buzz_array{ "buzz" };

    template<std::size_t N>
    constexpr auto fizzbuzz_impl_switcher()
    {
        if constexpr (N % 5 == 0 and N % 3 == 0)
            return fizzbuzz_array;
        else if constexpr (N % 3 == 0)
            return fizz_array;
        else if constexpr (N % 5 == 0)
            return buzz_array;
        else
            return num_to_string<N>;

    }

    template<std::size_t N1, std::size_t N2, std::size_t... Ns1, std::size_t... Ns2>
    constexpr std::array<char, N1 + N2> array_concat_impl(std::array<char, N1> const& lhs, std::array<char, N2> const& rhs,
        std::index_sequence<Ns1...>, std::index_sequence<Ns2...>)
    {
        return { std::get<Ns1>(lhs)..., std::get<Ns2>(rhs)... };
    }

    template<std::size_t N1, std::size_t N2>
    constexpr std::array<char, N1 + N2> array_concat(std::array<char, N1> const& lhs, std::array<char, N2> const& rhs)
    {
        return array_concat_impl(lhs, rhs, std::make_index_sequence<N1>{}, std::make_index_sequence<N2>{});
    }

    template <std::size_t... sizes>
    constexpr auto array_concat_few(std::array<char, sizes>&&... arrays)
    {
        std::array<char, (sizes + ...)> result;
        std::size_t index{};

        ((std::copy_n(arrays.begin(), sizes, result.begin() + index), index += sizes), ...);

        return result;
    }

    template<std::size_t... Ns>
    constexpr auto fizzbuzz_impl_make(std::index_sequence<Ns...>)
    {
        return array_concat_few(fizzbuzz_impl_switcher<Ns + 1>()...);
    }

    template<std::size_t N>
    struct fizzbuzz_impl
    {
        constexpr static auto value = fizzbuzz_impl_make(std::make_index_sequence<N>{});
        friend std::ostream& operator<<(std::ostream& out, fizzbuzz_impl<N> const& self)
        {
            for (auto& ch : self.value)
                ch == '\0' ? out << '\n' : out << ch;
            return out;
        }
    };

    template<std::size_t Offset, std::size_t... Ns>
    constexpr auto fizzbuzz_interval_impl_make(std::index_sequence<Ns...>)
    {
        return array_concat_few(fizzbuzz_impl_switcher<Offset + Ns>()...);
    }

    template<std::size_t Start, std::size_t End>
    struct fizzbuzz_interval_impl
    {
        constexpr static auto value = fizzbuzz_interval_impl_make<Start>(std::make_index_sequence<End - Start + 1>{});
        friend std::ostream& operator<<(std::ostream& out, fizzbuzz_interval_impl<Start, End> const& self)
        {
            for (auto& ch : self.value)
                ch == '\0' ? out << '\n' : out << ch;
            return out;
        }
    };

    template<std::size_t Index>
    struct fizzbuzz_at_impl
    {
        constexpr static auto value = fizzbuzz_impl_switcher<Index>();
        friend std::ostream& operator<<(std::ostream& out, fizzbuzz_at_impl<Index> const& self)
        {
            for (auto& ch : self.value)
                out << ch;
            return out;
        }
    };
}

template<std::size_t N,
    typename = std::enable_if_t <(N > 0)>>
constexpr auto fizzbuzz{ detail::fizzbuzz_impl<N>{} };

template<std::size_t Start, std::size_t End,
    typename = std::enable_if_t<(((End - Start) > 0) and (Start > 0) and (End > 0))>>
constexpr auto fizzbuzz_interval{ detail::fizzbuzz_interval_impl<Start, End>{} };

template<std::size_t Index,
    typename = std::enable_if_t <(Index > 0)>>
constexpr auto fizzbuzz_at{ detail::fizzbuzz_at_impl<Index>{} };

int main()
{
    constexpr auto v = fizzbuzz<50>;
    constexpr auto _v = fizzbuzz_interval<51, 99>;
    constexpr auto __v = fizzbuzz_at<100>;
    std::cout << v << _v << __v;
    return 0;
}
