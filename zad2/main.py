from matplotlib import pyplot
from platypus import ZDT1, ZDT2, ZDT3, ZDT4, ZDT5, ZDT6
from platypus.operators import UniformMutation
from platypus.algorithms import NSGAII, IBEA, EpsMOEA, SPEA2, GDE3, EpsNSGAII

from pymoo.factory import get_problem

from argument_parser import ArgumentParser


def plot_setup(problem_function, result_function):
    plot = Scatter()
    plot.add(
        problem_function,
        plot_type='line',
        color='black',
        alpha=0.6
    )
    plot.add(
        result_function,
        color='red'
    )
    return plot


args = ArgumentParser()

problem = {
    'zdt1': ZDT1(),
    'zdt2': ZDT2(),
    'zdt3': ZDT3(),
    'zdt4': ZDT4(),
    'zdt5': ZDT5(),
    'zdt6': ZDT6()
}[args.get_problem()]

population_size = args.get_population()
variator = UniformMutation(probability=args.get_probability(),
                           perturbation=0.5)
algorithm = {
    'nsga2': NSGAII(problem, population_size, variator=variator),
    'ibea': IBEA(problem, population_size, variator=variator),
    'spea2': SPEA2(problem, population_size, variator=variator),
    'gde3': GDE3(problem, population_size, variator=variator),
}[args.get_algorithm()]

algorithm.run(args.get_n_generations())

pareto = get_problem(args.get_problem()).pareto_front()

figure = pyplot.figure()
ax = figure.add_subplot()
ax.scatter(
    [s.objectives[0] for s in algorithm.result],
    [s.objectives[1] for s in algorithm.result]
)
ax.scatter(pareto[:, 0], pareto[:, 1])

pyplot.savefig(
    'pic',
    dpi=200,
    bbox_inches='tight'
)
