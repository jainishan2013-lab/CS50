text = str(input("Text: "))

letters = 0
words = len(text.split())
sentences = 0

for char in text:
    if char.isalpha():
        letters += 1
    elif char in ['.', '!', '?']:
        sentences += 1


S = (sentences / words) * 100
L = (letters / words) * 100

######################################

age = 0.0588 * L - 0.296 * S - 15.8

######################################
grade = round(age)

if grade < 1:
    print("Before Grade 1")

elif grade >= 16:
    print("Grade 16+")


else:
    print("Grade ", grade)
