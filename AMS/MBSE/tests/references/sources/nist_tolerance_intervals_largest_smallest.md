---
url: "https://www.itl.nist.gov/div898/handbook/prc/section2/prc264.htm"
final_url: "https://www.itl.nist.gov/div898/handbook/prc/section2/prc264.htm"
title: "7.2.6.4."
extracted_at: "2026-06-11T22:22:33.084893+00:00"
parser: "trafilatura-markdown"
confidence: 0.657
content_type: "text/html; charset=utf-8"
http_status: 200
word_count: 655
---

# 7.2.6.4.

7.
[Product and Process Comparisons](../prc.htm)
7.2.
[Comparisons based on data from one process](prc2.htm)
7.2.6.
[What intervals contain a fixed percentage of the population values?](prc26.htm)
## 7.2.6.4.
|
## Tolerance intervals based on the largest and smallest observations
|
|
*Tolerance intervals can be constructed for a distribution of any form*
|
The methods on the previous pages for computing tolerance limits are based
on the assumption that the measurements come from a normal distribution.
If the distribution is not normal, tolerance intervals based on this
assumption will not provide coverage for the intended proportion \(p\)
of the population. However, there are methods for achieving the
intended coverage if the form of the distribution is not known, but these
methods may produce substantially wider tolerance intervals.
|
*Risks associated with making assumptions about the distribution*
|
There are situations where it would be particularly dangerous to make
unwarranted assumptions about the exact shape of the distribution, for
example, when testing the strength of glass for airplane windshields where
it is imperative that a very large proportion of the population fall within
acceptable limits.
|
*Tolerance intervals based on largest and smallest observations*
|
One obvious choice for a two-sided tolerance interval for an unknown
distribution is the interval between the smallest and largest observations
from a sample of \(Y_1, \, \ldots, \, Y_N\)
measurements. Given the sample size \(N\)
and coverage \(p\),
an equation from
[Hahn and Meeker (p. 91)](../section5/prc5.htm#Hahn),
$$ \alpha = 1 - Np^{N-1} + (N-1)p^{N} \, , $$
allows us to calculate the confidence \(\alpha\)
of the tolerance interval. For example, the confidence levels for selected
coverages between 0.5 and 0.9999 are shown below for \(N\)
= 25.
Confidence Coverage
1.000 0.5000
0.993 0.7500
0.729 0.9000
0.358 0.9500
0.129 0.9750
0.026 0.9900
0.007 0.9950
0.0 0.9990
0.0 0.9995
0.0 0.9999
Note that if 99 % confidence is required, the interval that covers the
entire sample data set is guaranteed to achieve a coverage of only 75 %
of the population values.
|
*What is the optimal sample size?*
|
Another question of interest is, "How large should a sample be so that
one can be assured with probability \(\alpha\)
that the tolerance interval will contain at least a proportion \(p\)
of the population?"
|
*Approximation for \(N\)*
|
A rather good approximation for the required sample size is given by
$$ N \cong \frac{1}{4}
\frac{(1+p)}{(1-p)} \, \chi^2_{\alpha, \, 4} +\frac{1}{2} \, , $$
where \(\chi_{\alpha, \, 4}^2\)
is the critical value of the chi-square distribution with 4 degrees of
freedom that is exceeded with probability \(\alpha\).
|
*Example of the effect of \(p\) on the sample size*
|
Suppose we want to know how many measurements to make in order to guarantee
that the interval between the smallest and largest observations covers a
proportion \(p\)
of the population with probability \(\alpha\)
= 0.95. From the
table for the [upper critical value
of the chi-square distribution](../../eda/section3/eda3674.htm), look under the column labeled 0.95 in
the row for 4 degrees of freedom. The value is found to be
\(\chi_{0.95, \, 4}^2\)
= 9.488 and calculations are shown below for \(p\)
equal to 0.90 and 0.99.
For \(p\) = 0.90, \(\alpha\) = 0.95;
$$ N \cong \frac{1}{4} \frac{(1+0.90)}{(1-0.90)} \, \chi^2_{0.95, 4}
+ \frac{1}{2} = 0.25(19)(9.488)+0.5 = 45.57 = 46 \, . $$
For \(p\) = 0.99, \(\alpha\) = 0.95;
$$ N \cong \frac{1}{4} \frac{(1+0.99)}{(1-0.99)} \, \chi^2_{0.95, 4}
+\frac{1}{2} = 0.25(199)(9.488)+0.5 = 472.5 = 473 \, . $$
These calculations demonstrate that requiring the tolerance interval to
cover a very large proportion of the population may lead to an unacceptably
large sample size.
|
