#!/usr/bin/env python3
#!/usr/bin/env python3

import argparse
import os
import random
import sys

ANIME_DIR = os.path.expanduser("~/anime")  # Set ~/anime as the default directory


def pick_random_file(folder_path: str) -> str:
    """Pick a random file from a given folder."""
    if not os.path.isdir(folder_path):
        print(f"Error: '{folder_path}' is not a valid directory.")
        sys.exit(1)

    files = [f for f in os.listdir(folder_path) if os.path.isfile(os.path.join(folder_path, f))]

    if not files:
        print(f"No files found in {folder_path}")
        sys.exit(1)

    return os.path.join(folder_path, random.choice(files))

def show_random_file(folder: str) -> None:
    """Pick and display a random file from the specified folder."""
    random_file = pick_random_file(folder)

def main() -> None:
    parser = argparse.ArgumentParser(
        description="CLI utility to print a random file from a specified folder",
        usage="random-file-picker [OPTION]",
    )

    parser.add_argument(
        "-d",
        "--directory",
        type=str,
        default=ANIME_DIR,  # Default is now ~/anime
        help="Specify the directory to pick a random file from (default: ~/anime)",
    )

    args = parser.parse_args()

    show_random_file(args.directory)

if __name__ == "__main__":
    main()
