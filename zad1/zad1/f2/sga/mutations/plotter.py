import pandas
from sys import argv
from matplotlib import pyplot

data = []
#names = ["OnePoint", "ThreeParent", "Uniform"]
names = ["CustomUniform", "FlipBit", "ReverseSequence", "Twors"]

for i, filepath in zip(range(len(argv[1:])), argv[1:]):
    data.append(pandas.read_csv(filepath, names=[names[i]]))

fig, ax = pyplot.subplots()  # (figsize=(10, 5))

for d in data:
    d.astype(float).plot(ax=ax)

pyplot.xlabel("generacja")
pyplot.ylabel("przystosowanie")
pyplot.legend()
pyplot.savefig("aga_crossover")
pyplot.show()
