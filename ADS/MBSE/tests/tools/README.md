# ADS MBSE test tools

## `parse_ads_serial0.py`

Standard-library Python 3 parser/validator for the local `ads.serial0.v1` JSON Lines baseline:

```sh
python3 ADS/MBSE/tests/tools/parse_ads_serial0.py --help
python3 ADS/MBSE/tests/tools/parse_ads_serial0.py path/to/serial0.jsonl
python3 ADS/MBSE/tests/tools/parse_ads_serial0.py path/to/serial0.jsonl --duration-s 600 --nominal-rate-hz 5 --require-expected-count
```

The parser exits `0` only when the log structurally conforms. It exits nonzero on unparseable JSON, missing required fields, unsupported schema/version values, duplicate or non-monotonic `sample_id`, timestamp reversal, and stale/error/unavailable fields that are not flagged by the record envelope.
