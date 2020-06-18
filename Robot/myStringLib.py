class myStringLib:
    ROBOT_LIBRARY_SCOPE = 'SUITE'

    def __init__(self):
        self._counter = 0

    def count(self):
        self._counter += 1
        print(self._counter)

    def clear_counter(self):
        self._counter = 0


    def sum_char_value(self, arg):
        sum = 0
        for char in arg:
            sum += ord(char)
        return sum


    def find_max_char(self, arg):
        z = chr(0)
        for char in arg:
            if char > z:
                z = char
        return z