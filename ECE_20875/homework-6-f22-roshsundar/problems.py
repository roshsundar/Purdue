import re

#### USEFUL TOOL FOR REGEX: https://regex101.com/
def problem1(searchstring):
    """
    Match emails.

    :param searchstring: string
    :return: True or False
    """
    s = searchstring.split('@')

    if s[0][0] == ' ':
        # Fail: No lead whitespace
        return False

    r = re.findall(r"[a-zA-Z]+", s[0])
    if len(r) != 1 or len(r[0]) > 7:
        # Fail: Rule 1
        return False
    
    m = re.compile('[0-9]+').search(s[0])
    if m:
        if len(m.group()) > 4:
            # Fail: Rule 2
            return False

    if (len(s) != 2):
        # Fail: should only be one @
        return False

    if (s[1] != 'jediacademy.edu'):
        # Fail: Rule 3, 4
        return False
    
    return True


def problem2(searchstring):
    """
    Extract student and ship.

    :param searchstring: string
    :return: tuple
    """
    p = re.compile('([A-Z][a-z]+)? ([A-Z][a-z]+) flies the ([A-Z]+[-][a-zA-z0-9]+)')
    m = p.search(searchstring)

    if m:
        g = m.groups()

        student = ''
        if g[0] == None:
            student = g[1]
        else:
            student = g[0] + ' ' + g[1]
        
        ship = g[2]

        return (student, ship)
    else:
        return ("noname", "noship")

def problem3(searchstring):
    """
    Replace apprentice with title.

    :param searchstring: string
    :return: string
    """
    s = searchstring
    p = re.compile('(?i)(jedi) apprentice')
    s = p.sub(r'\1 Master', s)
    p = re.compile('(?i)(sith) apprentice')
    s = p.sub(r'\1 Darth', s)

    if s == searchstring:
        return "nomatch"
    else:
        return s

if __name__ == "__main__":
    print("To test your code, run the `test_problems.py` file provided.")
