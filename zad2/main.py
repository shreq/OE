from matplotlib import pyplot
from platypus import ZDT1, ZDT2, ZDT3, ZDT4, ZDT5, ZDT6
from platypus.algorithms import NSGAII, IBEA, SPEA2, GDE3
from platypus.operators import UniformMutation
from pymoo.factory import get_problem

from argument_parser import ArgumentParser

args = ArgumentParser()

algorithm = args.get_algorithm()

population_size = args.get_population()

variator = UniformMutation(
    probability=args.get_probability(),
    perturbation=0.5
)

problem = {
    'zdt1': ZDT1(),
    'zdt2': ZDT2(),
    'zdt3': ZDT3(),
    'zdt4': ZDT4(),
    'zdt6': ZDT6()
}[args.get_problem()]

algorithm = {
    'nsga2': NSGAII(problem, population_size, variator=variator),
    'ibea': IBEA(problem, population_size, variator=variator),
    'spea2': SPEA2(problem, population_size, variator=variator),
}[algorithm]

algorithm.run(args.get_n_generations())

pareto = get_problem(args.get_problem()).pareto_front()

ax = pyplot.figure().add_subplot()
ax.scatter(
    [s.objectives[0] for s in algorithm.result],
    [s.objectives[1] for s in algorithm.result],
    alpha=0.6,
    marker='x',
    label='results'
)
ax.plot(
    pareto[:, 0],
    pareto[:, 1],
    alpha=0.7,
    label='pareto front'
)
ax.legend()
pyplot.grid(alpha=0.3)

title = args.get_problem() + \
        '_' + args.get_algorithm() + \
        '_g' + str(args.get_n_generations()) + \
        '_o' + str(args.get_population()) + \
        '_r' + str(args.get_probability())
pyplot.savefig(
    title + '.png',
    dpi=200,
    bbox_inches='tight'
)
