import pandas
from sys import argv
from matplotlib import pyplot

data = []
#names = ["OnePoint", "ThreeParent", "Uniform"]
names = ["0.0", "0.2", "0.4", "0.6", "0.8", "1.0"]

for i, filepath in zip(range(len(argv[1:])), argv[1:]):
    data.append(pandas.read_csv(filepath, names=[names[i]]))

fig, ax = pyplot.subplots()  # (figsize=(10, 5))

for d in data:
    d.astype(float).plot(ax=ax)

pyplot.xlabel("generacja")
pyplot.ylabel("przystosowanie")
pyplot.legend()
pyplot.savefig("sga_uniformcrossover")
pyplot.show()
