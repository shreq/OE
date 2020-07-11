import pandas
import numpy
from matplotlib import pyplot
from sklearn.decomposition import PCA, FastICA
from sklearn.preprocessing import StandardScaler

LABEL_UNIQUES = {}


# region methods
def factorize(column):
    if column.dtype in [numpy.float64, numpy.float32, numpy.int32, numpy.int64]:
        return column
    else:
        codes, uniques = pandas.factorize(column)
        LABEL_UNIQUES[column.name] = uniques
        return codes


def normalize(df):
    return pandas.DataFrame(
        StandardScaler().fit_transform(df.values),
        columns=df.columns
    )


def pca(df):
    data = PCA(n_components=2).fit_transform(df)
    return pandas.DataFrame(data)


def ica(df):
    data = FastICA(n_components=2).fit_transform(df)
    return pandas.DataFrame(data)


def correlate_sort(df, limit: float = None):
    df = df.corr()
    df = df.mask(numpy.tril(numpy.ones(df.shape)).astype(numpy.bool))
    df = df.stack().reset_index()
    df = df.rename(columns={0: 'corr'})
    df = df.sort_values('corr', ascending=False)
    if limit is not None:
        df = df[df['corr'] >= limit]
    return df.reset_index(drop=True)


# endregion methods

dataset = pandas.read_csv("resources/credit_card.csv").dropna().apply(factorize)
dataset_pca = pca(normalize(dataset))
print(dataset_pca)

dataset_pca.to_csv("resources/credit_card_pca.csv", index=False)

# pyplot.scatter(
#     x=dataset_pca.iloc[:, 0],
#     y=dataset_pca.iloc[:, 1],
# )
# pyplot.show()
