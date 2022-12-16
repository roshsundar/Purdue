import scipy.stats as stats
import numpy as np


def get_data(filename):
    return np.loadtxt(filename)


def get_coordinates(data, each_dist):
    # Part B
    """
    :param: np.ndarray, str
    :return: np.ndarray, np.ndarray
    """
    # Your code starts here...
    p = stats.probplot(data, dist=each_dist)
    return p[0]


def calculate_distance(x, y):
    # Part B

    """
    :param: float, float
    :return: float
    """
    d = ((x - 0.5*(x+y))**2 + (y - 0.5*(x+y))**2) ** 0.5
    return d


def find_dist(sum_err, dists):
    # Part B
    """
    :param: list[float], list[str]
    :return: str, float
    """
    # Your code starts here...
    m = min(sum_err)
    d = dists[sum_err.index(m)]
    return (d, m)


def main(data_file):
    """
        Input a csv file and return distribution type, the error corresponding to the distribution type (e.g. return 'norm',0.32)
    :param: *.csv file name (str)
    :return: str, float
    """
    # Part B
    data = get_data(data_file)
    dists = ("norm", "expon", "uniform", "wald")
    sum_err = [0] * 4
    for ind, each_dist in enumerate(dists):
        X, Y = get_coordinates(data, each_dist)
        for x, y in zip(X, Y):
            sum_err[ind] += calculate_distance(x, y)
    return find_dist(sum_err, dists)


if __name__ == "__main__":
    for each_dataset in [
        "sample_norm.csv",
        "sample_expon.csv",
        "sample_uniform.csv",
        "sample_wald.csv",
        "distA.csv",
        "distB.csv",
        "distC.csv",
    ]:
        print(main(each_dataset))
