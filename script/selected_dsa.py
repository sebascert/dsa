"""
get the selected dsa's to include in the library, by either parsing dsa_list
and evaluating dependencies, or selecting all
"""

import os
import sys
from enum import Enum


class dsa(Enum):
    ds_array = "ds/array"
    ds_vector = "ds/vector"


def dsa_from_str(s: str) -> dsa | None:
    return next((memb for memb in dsa if memb.value == s), None)


dependencies: dict[dsa, list[dsa]] = {
    dsa.ds_vector: [dsa.ds_array],
}


def parse_dsa_list(dsa_list_path: str) -> list[dsa]:
    selected: set[dsa] = set()
    with open(dsa_list_path, "r") as list_file:
        for line in list_file:
            listed_str = line.strip()
            listed = dsa_from_str(listed_str)
            if not listed:
                print(f"dsa not found:\n{listed_str}", file=sys.stderr)
                sys.exit(1)

            selected.update(dependencies[listed] + [listed])

    return list(selected)


def select_all_dsa() -> list[dsa]:
    return list(dsa)


def main() -> None:
    selected: list[dsa]

    if len(sys.argv) < 2:
        print("missing dsa_list file", file=sys.stderr)
        sys.exit(1)

    dsa_list_path = sys.argv[1]

    if os.path.exists(dsa_list_path):
        selected = parse_dsa_list(dsa_list_path)
    else:
        selected = select_all_dsa()

    for x in selected:
        print(x.value, file=sys.stdout)

    sys.exit(0)


if __name__ == "__main__":
    main()
