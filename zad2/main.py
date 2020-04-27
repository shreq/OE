import numpy
from matplotlib import pyplot
from platypus import ZDT1, ZDT2, ZDT3, ZDT4, ZDT5, ZDT6
from platypus.algorithms import NSGAII, IBEA, SPEA2, GDE3
from platypus.operators import UniformMutation
from platypus.core import nondominated
from pymoo.factory import get_problem, get_performance_indicator
from scipy.interpolate import interp1d
from sklearn.metrics import mean_squared_error

from utils import clear
from argument_parser import ArgumentParser

args = ArgumentParser()

algorithm_name = args.get_algorithm()
population_size = args.get_population()
problem_name = args.get_problem()

clear()

# variator = UniformMutation(
#     probability=args.get_probability(),
#     perturbation=0.5
# )

variator=None

problem = {
    'zdt1': ZDT1(),
    'zdt2': ZDT2(),
    'zdt3': ZDT3(),
    'zdt4': ZDT4(),
}[problem_name]
for generation in [1000, 10000, 30000, 60000, 100000]:
    algorithm = {
        'nsga2': NSGAII(problem, population_size, variator=variator),
        'ibea': IBEA(problem, population_size, variator=variator),
        'spea2': SPEA2(problem, population_size, variator=variator),
    }[algorithm_name]

    algorithm.run(generation)

    pareto = get_problem(problem_name).pareto_front()
    pareto_x = pareto[:, 0]
    pareto_y = pareto[:, 1]
    pareto_function = interp1d(pareto_x, pareto_y, kind='cubic')

    result_nondominated = nondominated(algorithm.result)
    result_x = [s.objectives[0] for s in result_nondominated]
    result_y = [s.objectives[1] for s in result_nondominated]

    result_y_true = [pareto_function(x) for x in result_x]
    igd = get_performance_indicator('igd', pareto)

    mse = mean_squared_error(result_y_true, result_y)
    igd_val = igd.calc(numpy.array(list(zip(result_x, result_y))))
    print(mse, ",", igd_val)

    # region plot
    ax = pyplot.figure().add_subplot()
    ax.scatter(
        result_x,
        result_y,
        alpha=0.6,
        marker='x',
        label='results',
        color='red'
    )
    ax.plot(
        pareto_x,
        pareto_y,
        alpha=0.7,
        label='pareto front'
    )
    ax.legend()
    pyplot.grid(alpha=0.3)

    title = problem_name + \
            '_' + algorithm_name + \
            '_g' + str(generation) + \
            '_o' + str(args.get_population()) + \
            '_r' + str(args.get_probability())
    pyplot.savefig(
        title + '.png',
        dpi=200,
        bbox_inches='tight'
    )
    # endregion plot
