import time

recurse = 20000000
start = time.time()
for i in range(recurse):
    pass
end = time.time()
print('Oh I can do %d computations per second!' %(int(recurse/(end-start))))
