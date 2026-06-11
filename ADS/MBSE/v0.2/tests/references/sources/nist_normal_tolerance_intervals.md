---
url: "https://www.itl.nist.gov/div898/handbook/prc/section2/prc263.htm"
final_url: "https://www.itl.nist.gov/div898/handbook/prc/section2/prc263.htm"
title: "7.2.6.3."
extracted_at: "2026-06-11T20:32:55.181179+00:00"
parser: "trafilatura-markdown"
confidence: 0.644
content_type: "text/html; charset=utf-8"
http_status: 200
word_count: 598
---

# 7.2.6.3.

|
7.
7.2.
7.2.6.
|

- What interval will contain \(p\) percent of the population measurements?
- What interval guarantees that \(p\) percent of population measurements will not fall below a lower limit?
- What interval guarantees that \(p\) percent of population measurements will not exceed an upper limit?

- \(Y_L = \bar{Y} - k_2 s; \,\,\, Y_U = \bar{Y} + k_2 s\)
- \(Y_L = \bar{Y} - k_1 s\)
- \(Y_U = \bar{Y} + k_1 s\)

The quantity \(\nu\) represents the degrees of freedom used to estimate the standard deviation. Most of the time the same sample will be used to estimate both the mean and standard deviation so that \(\nu = N-1\), but the formula allows for other possible values of \(\nu\).

The reader can download the data as a
[text file](https://www.itl.nist.gov/datasets/MPC62.DAT).

- Calculate: \((1+p)/2 = (1+0.9)/2 = 0.95 \)
and \(\nu = N-1 = 43 - 1 = 42\).
- Go to the page describing
[critical values of the normal distribution](https://www.itl.nist.gov/eda/section3/eda3671.htm). In the summary table under the column labeled 0.95, find\(z_{(1+p)/2} = z_{0.95} = 1.645\).

- Go to the table of
[lower critical values of the chi-square distribution](https://www.itl.nist.gov/eda/section3/eda3674.htm). Under the column labeled 0.01 in the row labeled degrees of freedom = 42, find\(\chi_{1-\alpha, \, \nu}^2 = \chi_{0.01, \, 42}^2 = 23.650\).

- Calculate $$ k_2 = z_{(1+p)/2} \sqrt{\frac{\nu \left(1 + \frac{1}{N}\right) \, }{\chi^2_{1-\alpha, \, \nu}}} = 1.645 \sqrt{\frac{42\left(\frac{44}{43}\right)}{23.650}} = 2.217 \, . $$

The tolerance limits are then computed from the sample mean, \(\bar{Y}\),
and standard deviation, \(s\),
according to [case(1)](https://www.itl.nist.gov/prc263.htm#cases).

Some software is capable of computing a tolerance intervals for a given
set of data so that the user does not need to perform all the calculations.
All the tolerance intervals shown in this section can be computed using
both [Dataplot code](https://www.itl.nist.gov/prc263.dp) and [R code](https://www.itl.nist.gov/prc263.r).
In addition, R software is capable of computing an exact value of the
\(k_2\)
factor thus replacing the approximation given above.
R and Dataplot examples include the case where a tolerance interval is computed
automatically from a data set.

In this case, the difference between the two computations is negligible (1.8752 versus 1.8740). However, the difference becomes more pronounced as the value of \(N\) gets smaller (in particular, for \(N \le\) 10). For example, if \(N\) = 43 is replaced with \(N\) = 6, the non-central \(t\) method returns a value of 4.4111 for \(k_1\) while the method based on the Natrella formulas returns a value of 5.2808.

The disadvantage of the non-central \(t\)
method is that it depends on the inverse cumulative distribution
function for the non-central \(t\)
distribution. This function is not available in many statistical
and spreadsheet software programs, but it is available in Dataplot and R (see
[Dataplot code](https://www.itl.nist.gov/prc263.dp) and [R code](https://www.itl.nist.gov/prc263.r)).
In addition, the inverse of the non-central t function may lose
accuracy for large sample sizes. The Natrella formulas only depend on
the inverse cumulative distribution function for the normal distribution
(which is available in just about all statistical and spreadsheet
software programs). Unless you have small samples
(say \(N \le\)
10), the difference in the methods should not have much practical effect.
