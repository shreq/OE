import argparse
import sys

from utils import clear

algorithms = {
    1: 'nsga2',
    2: 'brkga',
    3: 'cmaes'
}
problems = {
    1: 'zdt1',
    2: 'zdt2',
    3: 'zdt3',
    4: 'zdt4',
    5: 'zdt5',
    6: 'zdt6'
}


def stringify(dict_):
    return ''.join(['[%s] %s\n' % (key, value.upper()) for (key, value) in dict_.items()])


class ArgumentParser:
    parser = argparse.ArgumentParser()
    args = None

    def __init__(self):
        self.parser.add_argument(
            '-a',
            dest='algorithm',
            type=int,
            help='[ %s ]' % ' | '.join(algorithms.values())
        )
        self.parser.add_argument(
            '-p',
            dest='problem',
            type=int,
            help='[ %s ]' % ' | '.join(problems.values())
        )
        self.parser.add_argument(
            '-g',
            default=50,
            dest='n_generations',
            type=int,
            help='number of generations, default 50'
        )
        self.parser.add_argument(
            '-q', '--quiet',
            action='store_false',
            dest='quiet',
            help='no output'
        )
        self.parser.add_argument(
            '--plot',
            action='store_true',
            dest='plot',
            help='show graph'
        )
        self.parser.add_argument(
            '--animation',
            action='store_true',
            dest='animation',
            help='save animation'
        )
        self.args = self.parser.parse_args().__dict__

    def get_algorithm(self):
        while self.args['algorithm'] is None or \
                self.args['algorithm'] < 1 or 3 < self.args['algorithm']:
            clear()
            try:
                self.args['algorithm'] = int(input(
                    'Select algorithm:\n' +
                    stringify(algorithms) +
                    'Choice:\t'
                ))
            except KeyboardInterrupt:
                print('^C')
                sys.exit(0)
            except ValueError:
                continue
        clear()
        return algorithms[self.args['algorithm']]

    def get_problem(self):
        while self.args['problem'] is None or \
                self.args['problem'] < 1 or 6 < self.args['problem']:
            clear()
            try:
                self.args['problem'] = int(input(
                    'Select problem:\n' +
                    stringify(problems) +
                    'Choice:\t'
                ))
            except KeyboardInterrupt:
                print('^C')
                sys.exit(0)
            except ValueError:
                continue
        clear()
        return problems[self.args['problem']]

    def get_n_generations(self):
        return self.args['n_generations']

    def get_quiet(self):
        return self.args['quiet']

    def get_plot(self):
        return self.args['plot']

    def get_animation(self):
        return self.args['animation']
