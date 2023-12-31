from __future__ import annotations

import unicodedata

from esphome.const import ALLOWED_NAME_CHARS


def strip_accents(value):
    return "".join(
        c
        for c in unicodedata.normalize("NFD", str(value))
        if unicodedata.category(c) != "Mn"
    )


def friendly_name_slugify(value):
    value = (
        strip_accents(value)
        .lower()
        .replace(" ", "-")
        .replace("_", "-")
        .replace("--", "-")
        .strip("-")
    )
    return "".join(c for c in value if c in ALLOWED_NAME_CHARS)
