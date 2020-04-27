import argparse
import sys

from utils import clear, stringify

algorithms = {
    1: 'nsga2',
    2: 'ibea',
    3: 'spea2',
    4: 'gde3'
}
problems = {
    1: 'zdt1',
    2: 'zdt2',
    3: 'zdt3',
    4: 'zdt4',
    5: 'zdt5',
    6: 'zdt6'
}


class ArgumentParser:
    parser = argparse.ArgumentParser(formatter_class=argparse.RawTextHelpFormatter)
    args = None

    def __init__(self):
        self.parser.add_argument(
            '-a',
            dest='algorithm',
            type=int,
            help=stringify(algorithms)
        )
        self.parser.add_argument(
            '-p',
            dest='problem',
            type=int,
            help=stringify(problems)
        )
        self.parser.add_argument(
            '-g',
            default=10000,
            dest='n_generations',
            type=int,
            help='number of generations, default 10000'
        )
        self.parser.add_argument(
            '-o',
            default=50,
            dest='population',
            type=int,
            help='population size, default 50'
        )
        self.parser.add_argument(
            '-r',
            default=0.5,
            dest='probability',
            type=float,
            help='operation probability, default 0.5'
        )
        self.args = self.parser.parse_args().__dict__

    def get_algorithm(self):
        while self.args['algorithm'] is None or \
                self.args['algorithm'] < 1 or 4 < self.args['algorithm']:
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

    def get_probability(self):
        return self.args['probability']

    def get_population(self):
        return self.args['population']
