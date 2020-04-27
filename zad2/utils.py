from os import system, name


def clear():
    if name == 'nt':
        _ = system('cls')
    else:
        _ = system('clear')


def stringify(dict_):
    return ''.join(['[%s] %s\n' % (key, value.upper()) for (key, value) in dict_.items()])


def stringify1line(iterable):
    return '[ %s ]' % ' | '.join(iterable)
