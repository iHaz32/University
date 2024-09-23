import random

from package import Package

def randomPackages():
    packagesAmount = 1000
    bitSize = 20
    P = "110101"
    failedPackagesReal = 0
    failedPackagesCRC = 0

    for i in range(packagesAmount):
        data = ""
        for j in range(bitSize):
            data += str(random.randint(0, 1))
        p = Package(data, P)
        p.send()
        res = p.res
        if (not all(char == '0' for char in res)):
            failedPackagesCRC += 1
        if (p.isDiff):
            failedPackagesReal += 1

    missed = failedPackagesReal - failedPackagesCRC

    percentage_failedPackagesReal = failedPackagesReal / packagesAmount * 100
    percentage_failedPackagesCRC = failedPackagesCRC / packagesAmount * 100
    percentage_missed = missed / packagesAmount * 100

    print("Arithmos paketon: ", packagesAmount)
    print("Pososto minimaton pou ftanoun ontos me sfalma: ", str(round(percentage_failedPackagesReal, 2)) + "%")
    print("Pososto minimaton pou anixneuontai me sfalma apo ton algorithmo CRC: ", str(round(percentage_failedPackagesCRC, 2)) + "%")
    print("Pososto esfalmenon minimaton pou den anixneuontai apo ton CRC: ", str(round(percentage_missed, 2)) + "%")


#randomPackages();

randomK = random.randint(10, 30) # Random k data bits -  between 10 and 30
print("Length of data messages is: ", randomK, " bits per message.")
P = input("Give P: ")

# Generate 10 random messages of k bits per message
for i in range(10):
    randomMessage = "";
    for j in range(randomK):
        rand = random.randint(0, 1) # 0.5 chance for each bit - 0 or 1
        if (rand == 0):
            randomMessage += "0" # Add 0 to message
        else:
            randomMessage += "1" # Add 1 to message
    p = Package(randomMessage, P)
    p.send()
    res = p.res
    if (not all(char == '0' for char in res)): # If res is not zero
        print("Message ", randomMessage, " got sent incorrectly (!) with FCS: ", p.F, " and result: ", res);
    else:
        print("Message ", randomMessage, " got sent correctly with FCS: ", p.F, " and result: ", res);