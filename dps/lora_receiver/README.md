This subsystem requires a patch to the raspi_lora library to use
Orange Pi GPIO instead of Raspberry Pi peripherals.

To install the patch:
1. `pip install -r requirements.txt`
2. Copy `lora.py` to the `site-packages/raspi_lora` directory.