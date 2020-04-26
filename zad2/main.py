import pymoo
from matplotlib import pyplot
from platypus import ZDT1, ZDT2, ZDT3, ZDT4, ZDT5, ZDT6
from platypus.algorithms import NSGAII, IBEA, EpsMOEA, SPEA2, GDE3, EpsNSGAII
from pymoo.factory import get_problem
from pymoo.visualization.scatter import Scatter

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


argument_parser = ArgumentParser()

# result = minimize(
#     problem,
#     algorithm,
#     ('n_gen', argument_parser.get_n_generations()),
#     seed=1,
#     verbose=argument_parser.get_quiet(),
#     save_history=True
# )
#
pic = plot_setup(
    get_problem('zdt1').pareto_front(),
).save('pic')

problem = {
    'zdt1': ZDT1(),
    'zdt2': ZDT2(),
    'zdt3': ZDT3(),
    'zdt4': ZDT4(),
    'zdt5': ZDT5(),
    'zdt6': ZDT6()
}['zdt1']

population_size = 50

algorithm = {
    'nsga2': NSGAII(problem, population_size),
    'ibea': IBEA(problem, population_size),
    # 'epsilon-moea': EpsMOEA(problem),
    'spea2': SPEA2(problem, population_size),
    'gde3': GDE3(problem, population_size),
    # 'epsilon-nsga2': EpsNSGAII(problem)
}['nsga2']

algorithm.run(5000)

figure = pyplot.figure()
ax = figure.add_subplot()
ax.scatter(
    [s.objectives[0] for s in algorithm.result],
    [s.objectives[1] for s in algorithm.result]
)

pyplot.savefig(
    'pic',
    dpi=200,
    bbox_inches='tight'
)
