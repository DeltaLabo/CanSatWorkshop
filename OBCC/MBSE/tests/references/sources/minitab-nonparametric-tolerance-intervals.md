---
url: "https://support.minitab.com/en-us/minitab/help-and-how-to/quality-and-process-improvement/quality-tools/how-to/tolerance-intervals-nonnormal-distribution/methods-and-formulas/tolerance-intervals/"
final_url: "https://support.minitab.com/en-us/minitab/help-and-how-to/quality-and-process-improvement/quality-tools/how-to/tolerance-intervals-nonnormal-distribution/methods-and-formulas/tolerance-intervals/"
title: "Methods and formulas for the tolerance intervals in Tolerance Intervals (Nonnormal Distribution)"
extracted_at: "2026-06-12T06:30:08.905745+00:00"
parser: "trafilatura-markdown"
confidence: 0.860
content_type: "text/html"
http_status: 200
word_count: 2148
---

# Methods and formulas for the tolerance intervals in Tolerance Intervals (Nonnormal Distribution)

Select the method or formula of your choice.

[Tolerance interval methods](https://support.minitab.com#methods)[Exact nonparametric tolerance intervals for continuous distributions](https://support.minitab.com#exact-nonparametric-tolerance-intervals-for-continuous-distributions)[Lognormal distribution](https://support.minitab.com#lognormal)[Approximate tolerance intervals for gamma distributions](https://support.minitab.com#gamma)[Exponential distribution](https://support.minitab.com#exponential)[Smallest extreme value distribution](https://support.minitab.com#smallest-extreme-value)[Weibull distribution](https://support.minitab.com#weibull)[Largest extreme value distribution](https://support.minitab.com#largest-extreme-value)[Logistic distribution](https://support.minitab.com#logistic)[Loglogistic distribution](https://support.minitab.com#loglogistic)[Anderson-Darling test](https://support.minitab.com#anderson-darling-test)

Minitab calculates both parametric and nonparametric tolerance intervals. The calculations for the nonparametric tolerance intervals assume only that the parent distribution is continuous. The calculations for the parametric tolerance intervals assume that the parent distribution of the sample is one of these distributions:

- Lognormal
- Gamma
- Exponential
- Smallest extreme value
- Weibull
- Largest extreme value
- Logistic
- Loglogistic

Let *X* 1, *X* 2, ..., *X* n be the ordered statistics based on random sample of size

Let the distribution function be F(*x*;*Î¸*) for Î© in some parameter space with dimension greater than or equal to 1.

Let *L* < *U* be two statistics based on the sample such that for any given values *Î±* and *P*, with 0 < *Î±* < 1 and 0 < *P* < 1, the following holds for every *Î¸* in Î©:

Then, the interval [*L*, *U*] is a two-sided tolerance interval with content = *P* x 100% and confidence level = 100(1 â *Î±*)%. Such an interval can be called a two-sided (1 â *Î±*, *P*) tolerance interval. For example, if *Î±* = 0.10 and *P* = 0.85, then the resulting interval is called a two-sided (90% , 0.85) tolerance interval.

If *L* = ââ and *U* < +â, then the interval (-â, *U*] is called a one-sided (1 â *Î±*, *P*) upper tolerance bound. If *L* > -â and *U* = +â, then the interval [L, +â) is called a one-sided (1 â *Î±*, *P*) lower tolerance bound.

Tolerance intervals possess the following interesting and useful properties:

- A one-sided (1 â
*Î±*,*P*) lower tolerance bound is also a one-sided (*P*, 1 â*Î±*) upper tolerance bound. - A one-sided (1 â
*Î±*)100% lower confidence bound of the (1 â*P*)thpercentile of the distribution of the data is also a one-sided (1 â Î±,*P*) lower tolerance bound. Similarly, a one-sided (1 â*Î±*)100% upper confidence bound of the*P*thpercentile of the distribution of the data is also a one-sided (1 â*Î±*,*P*) upper tolerance bound. - If
*L*and*U*are one-sided (1 â*Î±*/2 , (1 +*P*)/2) lower and upper tolerance bounds, then [*L*,*U*] is an approximate two-sided (1 â*Î±*,*P*) tolerance interval. This method may be used in cases where two-sided tolerance intervals cannot be directly obtained. The resulting two-sided tolerance intervals are generally conservative. See Guenther1and Hahn and Meeker2.

- Guenther, W. C. (1972). Tolerance intervals for univariate distributions. Naval Research Logistics, 19: 309â333.
- Hahn G. J. and Meeker W. Q. (1991). Statistical Intervals: A Guide for Practitioners John Wiley & Sons, New York.

Minitab calculates exact (1 â *Î±*, *P*) nonparametric tolerance intervals, where 1 â *Î±* is the confidence level and *P* is the coverage (the target minimum percentage of population in the interval). The nonparametric method for tolerance intervals is a distribution free method. That is, the nonparametric tolerance interval does not depend on the parent population of your sample. Minitab uses an exact method for both one-sided and two-sided intervals.

Let *X* 1, *X* 2 , ... , *X* n be the ordered statistics based on a random sample from some continuously distributed population F(

where *B* denotes the cumulative distribution function of the beta distribution with parameters *a* = *r* and *b* = *n* â *s* + 1. Thus ( *X r * ,

Let *k* be the largest integer that satisfies the following:

where *Y* is a binomial random variable with parameters *n* and 1 â *P*. It can be shown (see Krishnamoorthy and Mathew4) that a one-sided (1 â *Î±*, *P*) lower tolerance bound is given by *X k *. Similarly, a one-sided (1 â

Let *k* be the smallest integer that satisfies the following:

where *V* is a binomial random variable with parameters *n* and *P*. Thus,

where F V

| Term | Description |
|---|---|
| 1 â Î± | the confidence level of the tolerance interval |
P | the coverage of the tolerance interval (the target minimum percentage of population in the interval) |
n | the number of observations in the sample |

- Wilks, S. S. (1941). Sample size for tolerance limits on a normal distribution. The Annals of Mathematical Statistics, 12, 91â96.
- Wilks, S. S. (1941). Statistical prediction with special reference to the problem of tolerance limits. The Annals of Mathematical Statistics, 13, 400â409.
- Robbins, H. (1944). On distribution-free tolerance limits in random sampling. The Annals of Mathematical Statistics, 15, 214â216.
- Krishnamoorthy, K. and Mathew, T. (2009). Statistical Tolerance Regions: Theory, Applications, and Computation. Wiley, Hoboken, NJ.

The tolerance interval for the lognormal distribution uses the same equations as tolerance intervals for the normal distribution. The calculations follow this process:
[Methods and formulas for Tolerance Intervals (Normal Distribution)](https://support.minitab.com/en-us/minitab/help-and-how-to/quality-and-process-improvement/quality-tools/how-to/tolerance-intervals-normal-distribution/methods-and-formulas/methods-and-formulas/) and click "Exact tolerance intervals for normal distributions.".

- Minitab takes the natural logarithm of the data.
- Minitab calculates a tolerance interval for the transformed data using the tolerance interval procedure for the normal distribution.
- Minitab exponentiates the limits of the tolerance interval obtained in the previous step to transform the interval to the scale of the original data.

The tolerance interval for the gamma distribution uses an approximation to the normal distribution. Krishnamoorthy, et al. conduct simulation studies that show that the approximation provides accurate results. The calculations follow this process:

- Minitab takes the cubic root of the data.
- Minitab calculates a tolerance interval for the transformed data using the tolerance interval procedure for the normal distribution.
- Minitab exponentiates the limits of the tolerance interval obtained in the previous step to transform the interval to the scale of the original data.

- Krishnamoorthy K., Mathew T and Mukherjee S (2008). Normal based methods for a Gamma distribution: prediction and tolerance intervals and stress-strength reliability. Technometrics, 50, 69â78.

Minitab calculates exact (1 â *Î±*, *P*) tolerance intervals, where 1 â *Î±* is the
confidence level and *P* is the coverage (the target minimum proportion of the
population in the interval). The formulas differ between the calculation of
one-sided tolerance limits and two-sided tolerance intervals.

This formula gives the lower limit:

This formula gives the upper limit:

Minitab uses Newton's method to solve the following system of equations. For more detail, see Fernandez1.

This formula gives the two-sided interval:

Where,

and the value of *k* 1 depends on the solution to this system of equations:

where,

| Term | Description |
|---|---|
n | the sample size |
| the sample mean | |
P | the target minimum proportion of the population in the interval |
the Î± th percentile of the chi-square distribution with 2n degrees of freedom | |
Î± | 1 â confidence level |
the cumulative distribution function of the chi-square distribution with 2n degrees of freedom |

- Fernandez, Arturo J. (2010). Two-sided tolerance intervals in the exponential case: Corrigenda and generalizations. Computational Statistics and Data Analysis, 54, 151â162.

Minitab calculates exact (1 â *Î±*, *P*) tolerance intervals based on Lawless1, where 1 â *Î±* is the confidence level and *P* is the coverage (the target minimum percentage of population in the interval).

This formula gives the lower limit:

where

and *x* is the unique root of this function:

with

where

and *C*z is a normalizing constant:

Also, the function *IG*n [*x*] is the incomplete gamma function:

This formula gives the upper limit:

The value of *k* 2 comes from replacing *Î±* with 1 â *Î±* and *P* with 1 â *P* in the formulas for computing *k* 1.

To calculate the approximate two-sided interval, replace *Î±* by *Î±*/2 and *P* by (*P* + 1)/2 in the formulas for computing the one-sided tolerance limits.

| Term | Description |
|---|---|
| the maximum likelihood estimate of the location parameter of the extreme value distribution | |
| the maximum likelihood estimate of the scale parameter of the extreme value distribution | |
| , the centered observations based on the MLE estimates of the location and scale parameters of the smallest extreme value distribution | |
t | the Î± th percentile of the non-central t-distribution with n â 1 degrees of freedom and noncentrality parameter Î´ P |
1 - Î± | the confidence level of the tolerance interval |
P | the coverage of the tolerance interval (the target minimum percentage of population in the interval) |
n | the number of observations in the sample |

- Lawless, J. F. (1975). Construction of tolerance bounds for the extreme-value and the Weibull distribution. Technometrics, 17, 255â261.

The tolerance interval for the Weibull distribution uses the same equations as tolerance intervals for the smallest extreme value distribution. The calculations follow this process:

- Minitab takes the natural logarithm of the data.
- Minitab calculates a tolerance interval for the transformed data using the tolerance interval procedure for the smallest extreme value distribution.
- Minitab exponentiates the limits of the tolerance interval obtained in the previous step to transform the interval to the scale of the original data.

The tolerance interval for the largest extreme value distribution uses the same equations as tolerance intervals for the smallest extreme value distribution. The calculations follow this process:

- Minitab multiplies the data by â1.
- Minitab calculates a tolerance for the transformed data using the tolerance interval procedure for the smallest extreme value distribution.
- Minitab exponentiates the limits of the tolerance interval obtained in the previous step to transform the interval to the scale of the original data.

For formulas that apply to the smallest extreme value distribution, go to the section on the smallest extreme value distribution.

Minitab calculates approximate (1 â *Î±*, *P*) tolerance intervals based on Bain and
Engelhardt1, where 1 â *Î±* is the confidence level and *P*
is the coverage (the target minimum percentage of population in the interval). The
formula for the lower tolerance factor differs from the formula for the upper
tolerance factor.

This formula gives the lower limit:

where the lower tolerance factor has the following form:

This formula gives the upper limit:

where the upper tolerance factor has the following form:

The analysis produces an approximate two-sided tolerance interval for the logistic
distribution with Bonferroni's inequality2. This approximation method
replaces *Î±* by *Î±*/2 and *P* by (*P* + 1)/2 in the formulas for
computing the one-sided tolerance limits.

| Term | Description |
|---|---|
| the lower tolerance factor | |
| the upper tolerance factor | |
zÎ± | the upper Î± percentile of the standard normal distribution, which is equivalent to the
lower 1 âÎ± percentile point |
log(p) â log(1 â p), the p Ã 100 lower percentile of the standard logistic
distribution | |
C11 | |
C22 | |
C12 | |
| the maximum likelihood estimate of the logistic location parameter | |
| the maximum likelihood estimate of the logistic scale parameter |

- Bain, L. and Englehardt, M. (1991). Statistical analysis of reliability and life testing models: Theory and methods. Second edition, Marcel Dekker, Inc.
- Hahn, G. J. and Meeker, W. Q. (2017). Statistical intervals: A guide for practitioners. Second edition, John Wiley and Sons, Inc.

The tolerance interval for the loglogistic distirbution uses the same equations as tolerance intervals for the logistic distribution. The calculations follow this process:

- Minitab takes the natural logarithm of the data.
- Minitab calculates a tolerance interval for the transformed data using the tolerance interval procedure for the logistic distribution.
- Minitab exponentiates the limits of the tolerance interval obtained in the previous step to transform the interval to the scale of the original data.

For formulas that apply to the logistic distribution, go to the section on the logistic distribution.

Minitab uses Anderson-Darling statistics to perform the goodness-of-fit test.

Let Z = F(X), where F(X) is the cumulative distribution function. Suppose that a sample X1, .., Xn gives values Z(i) = F(Xi), i=1,.., n. Rearrange Z(i) in ascending order, Z(1) < Z(2) <...<Z(n). Then the Anderson-Darling statistic (A2) is calculated as follows:

- A
2= ân - (1/n) Î£i[(2i â 1) log Z(i)+ (2n + 1 â 2i) log (1 â Z(i))]

The modified Anderson-Darling goodness-of-fit test statistic is calculated for each distribution. The p-values are based on the table given by D'Agostino and Stephens.[ 1](https://support.minitab.com#fntarg_1) If no exact p-value is found in the table, Minitab calculates the p-value based on interpolation using the range of the p-value.
