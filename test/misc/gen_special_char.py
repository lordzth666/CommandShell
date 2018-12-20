
fp = open("test.txt", "w")

for i in range(255):
    fp.write(chr(i))
fp.write("\n")

fp.close()
