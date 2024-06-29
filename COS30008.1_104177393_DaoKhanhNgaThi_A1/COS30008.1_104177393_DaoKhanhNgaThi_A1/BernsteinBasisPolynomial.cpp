#include "BernsteinBasisPolynomial.h"
#include <cmath>

BernsteinBasisPolynomial::BernsteinBasisPolynomial(unsigned int aV, unsigned int aN) :
    fFactor(Combination(aN, aV))
{}

double BernsteinBasisPolynomial::operator()(double x) const {
    double result = fFactor() * pow(x, fFactor.getK()) * pow((1 - x), (fFactor.getN() - fFactor.getK()));
    return result;
}
