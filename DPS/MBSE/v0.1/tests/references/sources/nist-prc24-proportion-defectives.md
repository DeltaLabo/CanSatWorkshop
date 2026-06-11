---
url: "https://www.itl.nist.gov/div898/handbook/prc/section2/prc24.htm"
final_url: "https://www.itl.nist.gov/div898/handbook/prc/section2/prc24.htm"
title: "7.2.4."
extracted_at: "2026-06-11T20:34:49.514203+00:00"
parser: "trafilatura-markdown"
confidence: 0.659
content_type: "text/html; charset=utf-8"
http_status: 200
word_count: 664
---

# 7.2.4.

7.
[Product and Process Comparisons](../prc.htm)
7.2.
[Comparisons based on data from one process](prc2.htm)
## 7.2.4.
|
## Does the proportion of defectives meet requirements?
|
|
*Testing proportion defective is based on the binomial
distribution*
|
The proportion of defective items in a manufacturing process
can be monitored using statistics based on the observed number of
defectives in a random sample of size \(N\)
from a continuous
manufacturing process, or from a large population or lot. The
proportion defective in a sample follows the
[binomial distribution](../../eda/section3/eda366i.htm)
where \(p\)
is the probability of an individual item being found defective.
Questions of interest for quality control are:
- Is the proportion of defective items within prescribed
limits?
- Is the proportion of defective items less than a prescribed
limit?
- Is the proportion of defective items greater than a
prescribed limit?
|
*Hypotheses regarding proportion defective*
|
The corresponding hypotheses that can be tested are:
- \(p \ne p_0\)
- \(p \le p_0\)
- \(p \ge p_0\)
where \(p_0\)
is the prescribed proportion defective.
|
*Test statistic based on a normal approximation*
|
Given a random sample of measurements \(Y_1, \, \ldots, \, Y_N\)
from a population, the proportion of items that are judged
defective from these \(N\)
measurements is denoted \(\hat{p}\).
The test statistic,
$$ \large
z = \frac{\hat{p} - p_0}{\sqrt{\frac{p_0(1-p_0)}{N}}} \, , $$
depends on a normal approximation to the binomial distribution that
is valid for large \(N\), (\(N > 30\)).
This approximation
simplifies the calculations using critical values from the table
of the normal distribution as shown below.
|
[Restriction on sample size
]
|
Because the test is approximate, \(N\)
needs to be large for the test to be valid. One criterion is that \(N\)
should be chosen so that
$$ \mbox{min }\{ N_{p_0}, \, N(1-p_0)\} \ge 5 \, . $$
For example, if \(p_0\)
= 0.1, then \(N\)
should be at least 50 and if \(p_0\)
= 0.01, then \(N\)
should be at least 500.
[Criteria for choosing a sample size](prc242.htm) in
order to guarantee detecting a change of size \(\delta\)
are discussed on another page.
|
*One and two-sided tests for proportion defective*
|
Tests at the \(1-\alpha\)
confidence level corresponding to hypotheses (1), (2), and (3) are
shown below. For hypothesis (1), the test statistic, \(z\),
is compared with \(z_{1-\alpha/2}\),
the
[critical value from
the normal distribution](../../eda/section3/eda3671.htm) that is exceeded with probability \(\alpha/2\)
and similarly for (2) and (3). If
- \(|z| \ge z_{1-\alpha/2}\)
- \(z \le z_\alpha\)
- \(z \ge z_{1-\alpha}\)
the null hypothesis is rejected.
|
*Example of a one-sided test for proportion defective*
|
After a new method of processing wafers was introduced into a
fabrication process, two hundred wafers were tested, and
twenty-six showed some type of defect. Thus, for \(N\)
= 200,
the proportion defective is estimated to be \(\hat{p}\)
= 26/200 = 0.13.
In the past, the fabrication process was capable of producing
wafers with a proportion defective of at most 0.10. The issue is
whether the new process has degraded the quality of the wafers.
The relevant test is the one-sided test (3) which guards against an
increase in proportion defective from its historical level.
|
*Calculations for a one-sided test of proportion defective*
|
For a test at significance level \(\alpha\)
= 0.05,
the hypothesis of no degradation is validated if the test statistic \(z\)
is less than the critical value, \(z_{0.95}\)
= 1.645. The test statistic
is computed to be
$$ \large
z = \frac{\hat{p} - p_0}{\sqrt{\frac{p_0(1-p_0)}{N}}}
= \frac{\hat{0.13} - 0.10}{\sqrt{\frac{0.10(0.90)}{200}}}
= 1.414 \, . $$
|
*Interpretation*
|
Because the test statistic is less than the critical value (1.645),
we cannot reject hypothesis (3) and, therefore, we cannot conclude that the
new fabrication method is degrading the quality of the wafers.
The new process may, indeed, be worse, but more evidence would
be needed to reach that conclusion at the 95 % confidence level.
|
