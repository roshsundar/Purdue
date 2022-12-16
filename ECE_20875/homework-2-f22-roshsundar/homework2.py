def histogram(data, n, b, h):
    # data is a list
    # n is an integer
    # b and h are floats
    
    # Write your code here
    if b == h:
        print("b and h are the same value")
        return []
    if b > h:
        temp = b
        b = h
        h = temp
    if n == 0:
        return []
    
    hist = [0] * n

    unique_data = list(set(data)) # remove duplicate values

    for i in range(0,n):
        lb = b + i*((h-b)/n)
        ub = b + (i+1)*((h-b)/n)

        for val in unique_data:
            if (val >= lb and val < ub) and (val > b and val < h):
                hist[i] += 1

    # return the variable storing the histogram
    # Output should be a list

    return hist
    pass


def happybirthday(name_to_day, name_to_month, name_to_year):
    #name_to_day, name_to_month and name_to_year are dictionaries
    
    # Write your code here
    date_to_all = {}
    keys  = list(name_to_day.keys())

    for key in keys:
        if (name_to_day.get(key) not in list(date_to_all.keys())):
            date_to_all[name_to_day.get(key)] = (key, (name_to_month.get(key), name_to_year.get(key), 2022 - name_to_year.get(key)))
        elif (2022 - name_to_year.get(key) > date_to_all.get(name_to_day.get(key))[1][2]):
            date_to_all[name_to_day.get(key)] = (key, (name_to_month.get(key), name_to_year.get(key), 2022 - name_to_year.get(key)))


    # return the variable storing date_to_all
    # Output should be a dictionary
    return date_to_all
    pass

