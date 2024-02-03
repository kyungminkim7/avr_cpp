namespace avr_cpp {
namespace Chrono {

template<typename ToDuration, typename PeriodConversion, typename CommonRep,
         bool NumIsOne = false, bool DenIsOne = false>
struct DurationCastImpl {
    template<typename Rep, typename Period>
    static constexpr ToDuration cast(const Duration<Rep, Period> &d) {
        using ToRep = typename ToDuration::rep;
        return ToDuration(static_cast<ToRep>(
            static_cast<CommonRep>(d.count()) * 
            static_cast<CommonRep>(PeriodConversion::num) / 
            static_cast<CommonRep>(PeriodConversion::den)));
    }
};

template<typename ToDuration, typename PeriodConversion, typename CommonRep>
struct DurationCastImpl<ToDuration, PeriodConversion, CommonRep, true, true> {
    template<typename Rep, typename Period>
    static constexpr ToDuration cast(const Duration<Rep, Period> &d) {
        using ToRep = typename ToDuration::rep;
        return ToDuration(static_cast<ToRep>(d.count()));
    }
};

template<typename ToDuration, typename PeriodConversion, typename CommonRep>
struct DurationCastImpl<ToDuration, PeriodConversion, CommonRep, true, false> {
    template<typename Rep, typename Period>
    static constexpr ToDuration cast(const Duration<Rep, Period> &d) {
        using ToRep = typename ToDuration::rep;
        return ToDuration(static_cast<ToRep>(
            static_cast<CommonRep>(d.count()) / 
            static_cast<CommonRep>(PeriodConversion::den)));
    }
};

template<typename ToDuration, typename PeriodConversion, typename CommonRep>
struct DurationCastImpl<ToDuration, PeriodConversion, CommonRep, false, true> {
    template<typename Rep, typename Period>
    static constexpr ToDuration cast(const Duration<Rep, Period> &d) {
        using ToRep = typename ToDuration::rep;
        return ToDuration(static_cast<ToRep>(
            static_cast<CommonRep>(d.count()) *
            static_cast<CommonRep>(PeriodConversion::num)));
    }
};

template<typename ToDuration, typename FromRep, typename FromPeriod, typename>
constexpr ToDuration durationCast(const Duration<FromRep, FromPeriod> &d) {
    using ToRep = typename ToDuration::rep;
    using ToPeriod = typename ToDuration::period;
    using PeriodConversion = Divide<FromPeriod, ToPeriod>;
    using CommonRep = etl::common_type_t<FromRep, ToRep, intmax_t>;

    return DurationCastImpl<ToDuration, PeriodConversion, CommonRep, 
                            PeriodConversion::num == 1,
                            PeriodConversion::den == 1>::cast(d);
}

template<typename Rep, typename Period>
template<typename Rep2, typename>
constexpr Duration<Rep, Period>::Duration(const Rep2& ticks) : 
    ticks(static_cast<Rep>(ticks)) { }

template<typename Rep, typename Period>
template<typename Rep2, typename Period2>
constexpr Duration<Rep, Period>::Duration(const Duration<Rep2, Period2> &d)
    : ticks(durationCast<Duration>(d).count()) {}

template<typename Rep, typename Period>
constexpr Rep Duration<Rep, Period>::count() const { 
    return ticks;
}

template<typename Rep1, typename Period1,
         typename Rep2, typename Period2>
constexpr etl::common_type_t<Duration<Rep1, Period1>,
                             Duration<Rep2, Period2>>
operator+(const Duration<Rep1, Period1> &lhs,
          const Duration<Rep2, Period2> &rhs) {
    using Dur1 = Duration<Rep1, Period1>;
    using Dur2 = Duration<Rep2, Period2>;
    using CommonDuration = etl::common_type_t<Dur1, Dur2>;
    return CommonDuration(CommonDuration(lhs).count() + 
                          CommonDuration(rhs).count());
}

template<typename Rep1, typename Period1,
         typename Rep2, typename Period2>
constexpr etl::common_type_t<Duration<Rep1, Period1>,
                             Duration<Rep2, Period2>>
operator-(const Duration<Rep1, Period1> &lhs,
          const Duration<Rep2, Period2> &rhs) {
    using Dur1 = Duration<Rep1, Period1>;
    using Dur2 = Duration<Rep2, Period2>;
    using CommonDuration = etl::common_type_t<Dur1, Dur2>;
    return CommonDuration(CommonDuration(lhs).count() - 
                          CommonDuration(rhs).count());
}

template<typename Rep1, typename Period, typename Rep2,
         typename, typename CommonDuration, typename>
constexpr CommonDuration operator*(const Duration<Rep1, Period> &lhs, 
                                   const Rep2 &rhs) {
    return CommonDuration(CommonDuration(lhs).count() * rhs);
}

template<typename Rep1, typename Rep2, typename Period,
         typename, typename CommonDuration>
constexpr CommonDuration operator*(const Rep1 &lhs,
                                   const Duration<Rep2, Period> &rhs) {
    return rhs * lhs;
}

template<typename Rep1, typename Period, typename Rep2,
         typename, typename CommonDuration, typename>
constexpr CommonDuration operator/(const Duration<Rep1, Period> &lhs, 
                                   const Rep2 &rhs) {
    return CommonDuration(CommonDuration(lhs).count() / rhs);
}

template<typename Rep1, typename Period1,
         typename Rep2, typename Period2>
etl::common_type_t<Rep1, Rep2> operator/(const Duration<Rep1, Period1> &lhs,
                                         const Duration<Rep2, Period2> &rhs) {
    using Dur1 = Duration<Rep1, Period1>;
    using Dur2 = Duration<Rep2, Period2>;
    using CommonDuration = etl::common_type_t<Dur1, Dur2>;
    return CommonDuration(lhs).count() / CommonDuration(rhs).count();
}

template<typename Rep1, typename Period, typename Rep2,
         typename, typename CommonDuration, typename>
constexpr CommonDuration operator%(const Duration<Rep1, Period> &lhs, 
                                   const Rep2 &rhs) {
    return CommonDuration(CommonDuration(lhs).count() % rhs);
}

template<typename Rep1, typename Period1,
         typename Rep2, typename Period2>
etl::common_type_t<Duration<Rep1, Period1>,
                   Duration<Rep2, Period2>> 
operator%(const Duration<Rep1, Period1> &lhs,
          const Duration<Rep2, Period2> &rhs) {
    using Dur1 = Duration<Rep1, Period1>;
    using Dur2 = Duration<Rep2, Period2>;
    using CommonDuration = etl::common_type_t<Dur1, Dur2>;
    return CommonDuration(CommonDuration(lhs).count() %
                          CommonDuration(rhs).count());
}

template<typename Rep1, typename Period1,
         typename Rep2, typename Period2>
constexpr bool operator==(const Duration<Rep1, Period1> &lhs, 
                          const Duration<Rep2, Period2> &rhs) {
    using Dur1 = Duration<Rep1, Period1>;
    using Dur2 = Duration<Rep2, Period2>;
    using CommonDuration = etl::common_type_t<Dur1, Dur2>;
    return CommonDuration(lhs).count() == CommonDuration(rhs).count();
}

template<typename Rep1, typename Period1,
         typename Rep2, typename Period2>
constexpr bool operator!=(const Duration<Rep1, Period1> &lhs, 
                          const Duration<Rep2, Period2> &rhs) {
    return !(lhs == rhs);
}

template<typename Rep1, typename Period1,
         typename Rep2, typename Period2>
constexpr bool operator<(const Duration<Rep1, Period1> &lhs, 
                         const Duration<Rep2, Period2> &rhs) {
    using Dur1 = Duration<Rep1, Period1>;
    using Dur2 = Duration<Rep2, Period2>;
    using CommonDuration = etl::common_type_t<Dur1, Dur2>;
    return CommonDuration(lhs).count() < CommonDuration(rhs).count();
}

template<typename Rep1, typename Period1,
         typename Rep2, typename Period2>
constexpr bool operator<=(const Duration<Rep1, Period1> &lhs, 
                          const Duration<Rep2, Period2> &rhs) {
    return !(rhs < lhs);
}

template<typename Rep1, typename Period1,
         typename Rep2, typename Period2>
constexpr bool operator>(const Duration<Rep1, Period1> &lhs, 
                         const Duration<Rep2, Period2> &rhs) {
    return rhs < lhs;
}

template<typename Rep1, typename Period1,
         typename Rep2, typename Period2>
constexpr bool operator>=(const Duration<Rep1, Period1> &lhs, 
                          const Duration<Rep2, Period2> &rhs) {
    return !(lhs < rhs);
}

} // namespace Chrono
} // namespace avr_cpp