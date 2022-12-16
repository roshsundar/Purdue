from MiniProjectPath1 import dataset_1
import datetime
import matplotlib.pyplot as plt

def parse_bridge_data(dataset = dataset_1):
    return [
            list(dataset_1['Brooklyn Bridge']),
            list(dataset_1['Manhattan Bridge']),
            list(dataset_1['Queensboro Bridge']),
            list(dataset_1['Williamsburg Bridge'])
            ], list(dataset_1['Date'])

def graphing_bridge_distribution(bridges):
    """bridges is a list of lists of bridge data"""
    list_of_bridges, dates = bridges
    Brooklyn, Manhattan, Queensboro, Williamsburg = list_of_bridges
    processed_dates = []
    date_to_num = {
                    'Apr': 4,
                    'May': 5,
                    'Jun': 6,
                    'Jul': 7,
                    'Aug': 8,
                    'Sep': 9,
                    'Oct': 10
                  }
    """processing dates"""
    for date in dates:
         d, m = date.split('-')
         dt = datetime.date(2016, date_to_num[m], int(d))
         processed_dates.append(dt)

    """plotting 4 subplots in a same image"""
    fig, ax = plt.subplots(2,2)

    """plot traffic vs time plot for each bridge"""
    fig.suptitle("Number of bikes on each bridge per day")
    ax[0,0].plot(processed_dates, Brooklyn)
    ax[0,0].set_title('Brooklyn_Bridge')

    ax[0,1].plot(processed_dates, Manhattan)
    ax[0,1].set_title('Manhattan Bridge')

    ax[1,0].plot(processed_dates, Queensboro)
    ax[1,0].set_title('Queensboro Bridge')

    ax[1,1].plot(processed_dates, Williamsburg)
    ax[1,1].set_title('Williamsburg Bridge')

    fig.autofmt_xdate()

    plt.show()



def main():
    graphing_bridge_distribution(parse_bridge_data())


if __name__ == '__main__':
    main()
