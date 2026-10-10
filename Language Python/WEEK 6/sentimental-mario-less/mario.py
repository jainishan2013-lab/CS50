# Loop until user inputs a valid height between 1 and 8
while True:
    try:
        height = int(input("Height: "))
        if 1 <= height <= 8:
            break
    except ValueError:
        # Handles cases where the user inputs text instead of a number
        pass

# Generate the pyramid
for i in range(1, height + 1):
    spaces = " " * (height - i)
    hashes = "#" * i
    print(spaces + hashes)
