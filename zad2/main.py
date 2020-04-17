from pymoo.algorithms.nsga2 import NSGA2
from pymoo.algorithms.so_brkga import BRKGA
from pymoo.algorithms.so_cmaes import CMAES
from pymoo.factory import get_problem
from pymoo.optimize import minimize
from pymoo.visualization.scatter import Scatter
from pyrecorder.recorders.file import File
from pyrecorder.recorders.gif import GIF
from pyrecorder.video import Video

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


def generate_video(history):
    video = Video(GIF('animation.gif', duration=250))
    for entry in history:
        plot = Scatter(
            title='Gen %s' % entry.n_gen
        )
        plot.add(
            entry.pop.get('F')
        )
        plot.add(
            entry.problem.pareto_front(),
            plot_type='line',
            color='black',
            alpha=0.6
        )
        plot.do()

        video.record()
    video.close()


argument_parser = ArgumentParser()

algorithm = {
    'brkga': BRKGA(),
    'cmaes': CMAES(),
    'nsga2': NSGA2()
}[argument_parser.get_algorithm()]

problem = get_problem(argument_parser.get_problem())

result = minimize(
    problem,
    algorithm,
    ('n_gen', argument_parser.get_n_generations()),
    seed=1,
    verbose=argument_parser.get_quiet(),
    save_history=True
)

pic = plot_setup(
    problem.pareto_front(),
    result.F
).save('pic')

if argument_parser.get_animation():
    generate_video(result.history)

if argument_parser.get_plot():
    pic.show()
