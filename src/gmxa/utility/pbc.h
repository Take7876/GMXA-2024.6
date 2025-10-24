#ifndef PBC_GMXA_H
#define PBC_GMXA_H


#ifdef __cplusplus
extern "C" {
#endif
    int applyPeriodicBoundary_int(int, int);
    double applyPeriodicBoundary_double(double, double);
#ifdef __cplusplus
}
#endif


#define STATIC_ASSERT(COND, MSG) typedef char static_assertion_##MSG[(COND) ? 1 : -1]
#define ARGUMENT_TYPES_ARE_INCORRECT 1
#define UNSUPPORTED_TYPE_FOR_PREV 1
#define applyPeriodicBoundary(prev, max) \
    _Generic((prev), \
        int: _Generic((max), \
            int: applyPeriodicBoundary_int, \
            default: STATIC_ASSERT(0, Argument_types_are_incorrect), \
        ), \
        double: _Generic((max), \
            double: applyPeriodicBoundary_double, \
            default: STATIC_ASSERT(0, Argument_types_are_incorrect), \
        ), \
        default: STATIC_ASSERT(0, Unsupported_type_for_prev), \
    )(prev, max)


#endif