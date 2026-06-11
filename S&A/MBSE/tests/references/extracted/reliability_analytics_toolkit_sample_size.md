---
url: "https://reliabilityanalyticstoolkit.appspot.com/sample_size"
final_url: "https://reliabilityanalyticstoolkit.appspot.com/sample_size"
title: "Sample Size Calculator - Binomial Reliability Demonstration Test"
extracted_at: "2026-06-11T22:04:19.806136+00:00"
parser: "trafilatura-markdown"
confidence: 0.635
content_type: "text/html; charset=utf-8"
http_status: 200
word_count: 564
---

# Sample Size Calculator - Binomial Reliability Demonstration Test

This calculator is used to calculate the number of test samples required to demonstrate a required level of reliability at a given confidence level.
It can be used to answer questions such as:

1. How many test samples are required to demonstrate 95% reliability at a 95% confidence level?

2. How much test time is needed to demonstrate 90% reliability at a 90% confidence level?

3. Given some amount of available test time, how many test samples are needed to demonstrate 80% reliability at an 80% confidence level?

Option 1 above uses a non-parametric test approach, while options 2 and 3 assume a Weibull distribution to relate reliability to test time, which is termed a parametric binomial reliability demonstration test.

**Method 1 (non-parametric test).** This tool calculates test sample size required to demonstrate a reliability value at a given confidence level. The calculation is based on the following binomial equation:

where:

C is the test confidence level

R is the reliability to be demonstrated

f is the number of allowable test failures

n is the test sample size

Given inputs of C, R and f, this tool solves the above equation for sample size, n.

**Method 2 (parametric test).** Method 2 makes use of the Weibull distribution to define the reliability (R) in the the above binomial equation. Given a reliability requirement Rrqmt for a mission time Tmission
and a value for the Weibull shape parameter β, the Weibull reliability function
is solved for characteristic life (η). This fully defines the Weibull reliability function and
allows for the calculation of reliability at any other point on the curve below. Rtest associated with some available test time Ttest is then calculated and used in the above
binomial equation to calculate the number of test samples needed. Threfore, demonstrating Rtest at time Ttest is equivalent to demonstrating Rrqmt, provided that
the estimate of β is accurate. Method 2A solves for required sample size. Conversely, given a fixed number of samples, Method 2B solves for test time required.

.

[Toolkit Home](http://reliabilityanalyticstoolkit.appspot.com/)

**Comments/Questions:**

[reliabilityanalytics.com](http://reliabilityanalytics.com/)

[http://www.itl.nist.gov/div898/handbook/prc/section2/prc241.htm](http://www.itl.nist.gov/div898/handbook/prc/section2/prc241.htm).- MIL-HDBK-338,
[Electronic Reliability Design Handbook](http://reliabilityanalytics.com/reliability_engineering_library/MIL-HDBK-338-V1_Electronic_Reliability_Design_Handbook_15_Oct_1984/MIL-HDBK-338-V1_Electronic_Reliability_Design_Handbook_15_Oct_1984_pp_538.htm). [http://en.wikipedia.org/wiki/Binomial_proportion_confidence_interval](http://en.wikipedia.org/wiki/Binomial_proportion_confidence_interval)[http://en.wikipedia.org/wiki/Binomial_distribution](http://en.wikipedia.org/wiki/Binomial_distribution)[http://reliabilityanalyticstoolkit.appspot.com/binomial_confidence](http://reliabilityanalyticstoolkit.appspot.com/binomial_confidence)- Mathews, Paul
[Sample Size Calculations: Practical Methods for Engineers and Scientists.](https://reliabilityanalyticstoolkit.appspot.com/static/books.htm#0615324614) - Ryan, Thomas P.
[Sample Size Determination and Power.](https://reliabilityanalyticstoolkit.appspot.com/static/books.htm#1118437608) - Collani, E. von; Drager, Klaus
[Binomial Distribution Handbook for Scientists and Engineers.](https://reliabilityanalyticstoolkit.appspot.com/static/books.htm#0817641297) [Calculating Test Sample Sizes with Microsoft Excel.xlsx](http://reliabilityanalyticstoolkit.appspot.com/static/Calculating Test Sample Sizes with Microsoft Excel.xlsx)

All content and materials on this site are provided "as is" Reliability Analytics makes no warranty, express or implied, including the warranties of merchantability and fitness for a particular purpose; nor assumes any legal liability or responsibility for the accuracy, completeness, or usefulness of any information, apparatus, product, or process disclosed; nor represents that its use would not infringe privately owned rights.
