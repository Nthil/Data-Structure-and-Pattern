#include "Polynomial.h"
#include <cmath>
 
//Last 4 methods
double Polynomial::operator()(double x) const {
    if (fDegree == 0) {
        return fCoeffs[0];
    }

    double result = fCoeffs[0];
    double power = 1.0;

    for (int i = 1; i <= fDegree; i++) {
        power *= x;
        result += fCoeffs[i] * power;
    }

    return result;
}

Polynomial Polynomial::getDerivative() const {
    Polynomial result;

    if (fDegree == 0) {
        return result;
    }

    result.fDegree = fDegree - 1;

    for (int i = 1; i <= fDegree; i++) {
        result.fCoeffs[i - 1] = fCoeffs[i] * i;
    }

    return result;
}

Polynomial Polynomial::getIndefiniteIntegral() const {
    Polynomial result;
    result.fDegree = fDegree + 1;

    for (int i = fDegree + 1; i > 0; i--) {
        result.fCoeffs[i] = fCoeffs[i - 1] / i;
    }

    return result;
}

double Polynomial::getDefiniteIntegral(double xLow, double xHigh) const {
    Polynomial indefiniteIntegral = getIndefiniteIntegral();
    return indefiniteIntegral(xHigh) - indefiniteIntegral(xLow);
}
