import csv
import sys


def main():

    # 1. Check for command-line arguments
    if len(sys.argv) != 3:
        print("Usage: python dna.py data.csv sequence.txt")
        sys.exit(1)

    # 2. Read CSV database into memory
    database = []
    strs = []

    with open(sys.argv[1], "r") as csv_file:
        reader = csv.DictReader(csv_file)
        # Extract the STR list (everything after the 'name' column)
        strs = reader.fieldnames[1:]
        # Save all rows (people) into a list of dictionaries
        database = list(reader)

    # 3. Read DNA sequence text file into memory
    with open(sys.argv[2], "r") as txt_file:
        dna_sequence = txt_file.read()

    # 4. Find longest match of each STR in the DNA sequence
    # This dictionary will store the counts we calculate (e.g., {'AGATC': 4, 'AATG': 1})
    dna_counts = {}
    for str_name in strs:
        dna_counts[str_name] = longest_match(dna_sequence, str_name)

    # 5. Check database for matching profiles
    for person in database:
        match_count = 0

        # Check every STR for this specific person
        for str_name in strs:
            # Crucial: Cast the database string value to an integer before comparing
            if int(person[str_name]) == dna_counts[str_name]:
                match_count += 1

        # If all STR counts match perfectly, we found our person
        if match_count == len(strs):
            print(person["name"])
            return

    # If the loop finishes without returning, no match was found
    print("No match")


def longest_match(sequence, subsequence):
    """Returns the length of the longest run of subsequence in sequence."""

    # Initialize variables
    longest_run = 0
    subsequence_length = len(subsequence)
    sequence_length = len(sequence)

    # Check each character in sequence for most consecutive runs of subsequence
    for i in range(sequence_length):

        # Initialize count of consecutive runs
        count = 0

        # If a match is found, check for consecutive matches
        while True:

            # Adjust substring start and end
            start = i + count * subsequence_length
            end = start + subsequence_length

            # If there is a match in the substring
            if sequence[start:end] == subsequence:
                count += 1

            # If there is no match in the substring
            else:
                break

        # Update most consecutive matches found
        longest_run = max(longest_run, count)

    return longest_run


if __name__ == "__main__":
    main()
