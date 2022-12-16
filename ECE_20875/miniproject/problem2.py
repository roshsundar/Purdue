from MiniProjectPath1 import dataset_1
import numpy as np
from sklearn.linear_model import LinearRegression
from sklearn.model_selection import train_test_split

def input_X_matrix():
    """output a 3 column matrix containing high temp, low temp, and precipitation as colnmn vectors"""
    return np.array(
            [
             list(dataset_1['High Temp']),
             list(dataset_1['Low Temp']),
             list(dataset_1['Precipitation'])
             ]
                    ).transpose()

def output_y_matrix():
    """output the total number of bikers in NYC in a single column vector"""
    return np.array(list(dataset_1['Total'])).transpose()

def split_data(X, y):
    """split dataset into train-test subsets with a 80-20 split"""
    """use None for random_state"""
    """return 4 lists of data: x_train, x_test; y_train, y_test"""
    x_train, x_test, y_train, y_test = train_test_split(X, y, test_size=0.2, random_state= None)
    return x_train, x_test, y_train, y_test


def regression(X, y):
    """fit a least square linear regression to input X matrix and y column vector"""
    norm_X, norm_y = normalize(X), normalize(y)
    return LinearRegression().fit(X,y)

def normalize(vector):
    """normalizing a vector such that mean is 0 and standard deviation is 1"""
    # vector is a list, shall return normalized vector
    return (vector - np.mean(vector, axis = 0)) / np.std(vector, axis = 0)

def main():
    X = input_X_matrix()
    y = output_y_matrix()

    """5 fold (80-20) cv"""
    models_and_scores = []

    for k in range(5):
        x_train, x_test, y_train, y_test = split_data(X,y)
        model = regression(normalize(x_train), normalize(y_train))
        r_square = model.score(normalize(x_test),normalize(y_test))
        models_and_scores.append((model, r_square))

    """selecting model with greatest r^2 value"""
    best_model = None
    best_score = 0

    for model, score in models_and_scores:
        if score > best_score:
            best_score = score
            best_model = model

    """printing out resulting equation"""
    print('equation:')
    for num, x in zip(best_model.coef_, ['High Temp', 'Low Temp', 'Precipitation']):
        print(str(num) + x, end = '')
        if x != 'Precipitation':
            print(' + ', end = '')
    print(' + ' + str(best_model.intercept_))

    print(f"\nintercept of the model is {best_model.intercept_}")
    print(f"r^2 value = {best_score}")

if __name__ == '__main__':
    main()
