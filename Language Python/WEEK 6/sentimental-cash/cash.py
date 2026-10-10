while True:
    try:
        owed = float(input("Owed - "))
        if owed > 0:
            break
    except ValueError:

        pass

######################################
owed = owed * 100
######################################

quarters = owed // 25
owed %= 25

dimes = owed // 10
owed %= 10

nickels = owed // 5
owed %= 5

penny = owed // 1
coins = int(quarters + dimes + nickels + penny)
print("Coin - ", coins)
