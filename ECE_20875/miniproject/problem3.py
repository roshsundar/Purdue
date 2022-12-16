import numpy as np

from MiniProjectPath1 import dataset_1

from sklearn.neighbors import KNeighborsClassifier
from sklearn.model_selection import train_test_split
from sklearn import metrics


def input_X_matrix():
    """returns a 5 column matrix such that data for each bridge is recorded in a single colmn vector"""
    Brooklyn, Manhattan = list(dataset_1['Brooklyn Bridge']), list(dataset_1['Manhattan Bridge'])
    Williamsburg, Queensboro = list(dataset_1['Williamsburg Bridge']), list(dataset_1['Queensboro Bridge'])
    return np.array([Brooklyn, Manhattan, Williamsburg, Queensboro]).transpose()

def output_y_matrix():
    """return matrix of days from the dataset, dims are 214 rows, 1 col"""
    daydict = {'Monday': 0, 'Tuesday': 1, 'Wednesday': 2, 'Thursday': 3, 'Friday': 4, 'Saturday': 5, 'Sunday': 6}
    days = list(dataset_1['Day'])
    days = [daydict[day] for day in days]
    return np.array(days).transpose()

def split_data(X, y):
    """shall return 4 lists of data: x_train, x_test; y_train, y_test"""
    # using a 80-20 split: temporarily use None for random_state
    x_train, x_test, y_train, y_test = train_test_split(X, y, test_size=0.2, random_state= None)
    return x_train, x_test, y_train, y_test

def knn(X, y, k):
    """return a kNN classifier trained on input dataset X, output dataset y, with k neighbors"""
    return KNeighborsClassifier(n_neighbors=k).fit(X,y)

if __name__ == '__main__':
    """fetch the data into 4 matrices for input(x) training/testing and output(y) training/testing"""
    X = input_X_matrix()
    y = output_y_matrix()
    x_train, x_test, y_train, y_test = split_data(X,y)

    """train knn model, predict, and output preformance stats"""
    for k in range(1, 7):
        knn_model = knn(x_train, y_train, k)
        response = knn_model.predict(x_test)
        acc = metrics.accuracy_score(y_test, response)
        auc_score = metrics.roc_auc_score(y_test, knn_model.predict_proba(x_test), multi_class='ovr')
        
        print("k=%d acc=%f auroc=%f" %(k, acc, auc_score))