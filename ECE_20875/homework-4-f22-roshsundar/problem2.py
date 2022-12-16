def stencil(data, f, w):
    """
    1) perform a stencil using the filter function f with width, w, on list, data.
    2) return the resulting list output.
    3) note that if len(data) = k, len(output) = k - width + 1.
    4) f will accept as input a list of size w and return a single number.

    :param data: list
    :param f: function
    :param w: int
    :return output: list
    """
    # Fill in
    output = []
    starti = 0
    stopi = w
    for i in range(0, len(data)- w + 1):
        output.append(f(data[starti:stopi]))
        starti += 1
        stopi += 1
    return output


def create_box(box):
    """
    1) This function takes in a list, box.
    The box_filter function defined below accepts a list L of length len(box) and returns a simple
    convolution of it with the list, box.

    2) The meaning of this box filter is as follows:
    for each element of input list L, multiply L[i] by box[len(box) - 1  - i],
    sum the results of all of these multiplications and return the sum.

    3) For a box of length 3, box_filter(L) should return:
      (box[2] * L[0] + box[1] * L[1] + box[0] * L[2]),
      similarly, for a box of length 4, box_filter should return:
      (box[3] * L[0] + box[2] * L[1] + box[1] * L[2] + box[0] * L[3])

    The function create_box returns the box_filter function, as well as the length
    of the input list box

    :param box: list
    :return box_filter, len(box): function, int
    """

    # Fill in

    def box_filter(L):
        # Fill in
        if len(box) != len(L):
            print("Calling box filter with the wrong length list. Expected length of list should be " + str(len(box)) + '.')
            return 0
        
        convo = 0
        for i in range(0, len(box)):
            convo += L[i] * box[len(box) - 1  - i]
        return convo

    return box_filter, len(box)


if __name__ == '__main__':

    def mov_avg(L):
        return float(sum(L)) / 3

    def sum_sq(L):
        return sum([i**2 for i in L])

    data = [2, 5, -10, -7, -7, -3, -1, 9, 8, -6]

    print(stencil(data, mov_avg, 3))
    print(stencil(data, sum_sq, 5))

    # note that this creates a moving average!
    box_f1, width1 = create_box([1.0 / 3, 1.0 / 3, 1.0 / 3])
    print(stencil(data, box_f1, width1))

    box_f2, width2 = create_box([-0.5, 0, 0, 0.5])
    print(stencil(data, box_f2, width2))